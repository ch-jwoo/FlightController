/*
 * cppmain.h
 *
 *  Created on: 2020. 8. 2.
 *      Author: junwoo
 */

//essential
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "fatfs.h"
#include "timers.h"

//additional
#include "cstdio"
#include "cstdlib"

//selfmade
#include "Driver/MPU9250.h"
#include "Driver/sbus.h"
#include "Driver/tm_stm32_gps.h"
#include "Driver/IST8310.h"
#include "Driver/bme280.h"
#include "Driver/Lidar1D.h"
//
#include "PeripheralInterface/SensorAccel.hpp"
#include "PeripheralInterface/SensorGyro.hpp"
#include "PeripheralInterface/SensorMag.hpp"
#include "PeripheralInterface/SensorGPS.hpp"
#include "PeripheralInterface/SensorBaro.hpp"
#include "PeripheralInterface/RC.hpp"

#include "Module/ModuleAHRS.hpp"
#include "Module/ModuleCommander.h"


using namespace FC;

//#define USE_MPU9250
//#define USE_IST8310
#define USE_GPS
//#define USE_BME280
#define USE_SBUS
//#define USE_AHRS


SensorMag sensorMag;
SensorAccel sensorAccel;
SensorGyro sensorGyro;
SensorBaro sensorBaro;
SensorGPS sensorGPS;
RC rc;

//we can use printf
int _write(int file, unsigned char* p, int len) // for debug through uart3
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}

void MPU9250_StartTask(void *argument){
	while(1){
		MPU9250_updateDMA();
		osDelay(5);				/* 200hz */
	}
}
void BME280_StartTask(void *argument){
	while(1){
		BME280_readIT();
		osDelay(20); 			/* 50hz */
	}
}
void IST8310_StartTask(void *argument){
	while(1){
		IST8310_updataIT();
		osDelay(10); 			/* 100hz */
	}
}
void SD_StartTask(void *argument){
	char buf[256];
	uint32_t bw;
	int len = 0;
	retSD=f_mount(&SDFatFS ,&SDPath[0],1);
	if(retSD==FR_OK){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

	while(1){
		/* open */
		f_open(&SDFile,"log.txt", FA_OPEN_APPEND | FA_WRITE );
		if(retSD==FR_OK){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		}
		else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

		/* data read */
		struct Attitude attitude;
		struct NedAccel nedAccel;
		struct GPS gps;
		struct Barometer baro;
		struct BodyAngularVelocity gyro;

		if(msgBus.getAttitude(&attitude)){
		msgBus.getAttitude(&attitude);
			len = sprintf(buf, "att %u %d %d %d\n", (uint)attitude.timestamp, (int)(attitude.roll*1000000),
													(int)(attitude.pitch*1000000),
													(int)(attitude.yaw*1000000));
			f_write(&SDFile, buf, len, (UINT*)&bw);
		}
		if(msgBus.getNedAccel(&nedAccel)){
			len=sprintf(buf,"accNED %u %d %d %d\n",(uint)nedAccel.timestamp,(int)(nedAccel.xyz[0]*1000000),
																	(int)(nedAccel.xyz[1]*1000000),
																	(int)(nedAccel.xyz[2]*1000000));
			f_write(&SDFile, buf, len, (UINT*)&bw);
		}
		if(msgBus.getBodyAngularVelocity(&gyro)){
			len=sprintf(buf,"gyro %u %d\n",(uint)gyro.timestamp,(int)(gyro.xyz[2]*1000000));
			f_write(&SDFile, buf, len, (UINT*)&bw);
		}
		if(msgBus.getGPS(&gps)){
			int32_t latDecimal = (int32_t)gps.lat;
			int32_t latFraction = (int32_t)((gps.lat-latDecimal)*100000000);
			int32_t lonDecimal = (int32_t)gps.lon;
			int32_t lonFraction = (int32_t)((gps.lon-lonDecimal)*100000000);
			len=std::sprintf(buf,"GPS %u %d.%d %d.%d %d %d %d %d\n",(uint)gps.timestamp,
															  latDecimal, latFraction,
															  lonDecimal, lonFraction,
															  (int)(gps.alt*1000000),
															  (int)(gps.velN*1000000),
															  (int)(gps.velE*1000000),
															  (int)(gps.velD*1000000));
			f_write(&SDFile, buf, len, (UINT*)&bw);
		}   // Lat Lon Alt velN velE velD
		if(msgBus.getBarometer(&baro)){
			len=sprintf(buf,"Baro %u %d\n",(uint)baro.timestamp,(int)(baro.pressure*1000000));
			f_write(&SDFile, buf, len, (UINT*)&bw);
		}

		if(retSD==FR_OK){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		}
		else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

		f_close(&SDFile);
		if(retSD==FR_OK){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		}
		else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
		osDelay(100);			/* 10hz */
	}
}

void AHRS_StartTask(void *argument){
	ModuleAHRS moduleAHRS;
	while(1){
		moduleAHRS.main();
		osDelay(20);				/* 200hz */
	}
}

void moduleCommanderMain(void* param){
	while(1){
		moduleCommander.main();
	}
}

/*
 *  Switch
 *  Click : High
 *  GPIO_PinState result = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);
 */
/*
 * 	buzzer
 *  if(HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1) != HAL_OK){
 *		error
 *	}
 */
/*
 *  LED signal
 *  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET);
 */
void debug_main(void* param){
	while(1){
		osDelay(1000);
	}
}

void cppMain(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("test\r\n");

    /* micro second timer start */
	HAL_TIM_Base_Start_IT(&htim2);

	MPU9250(&hi2c1);

	/*
	 * recommended mode : gaming
	 * Sensor mode : normal mode, standby = 0.5ms
	 * oversampling : pressureX4, temperatureX1, humidityX0
	 * IIR filter coefficient : 16
	 * RMS Noise : 0.3Pa/2.5cm
	 * Data output rate : 83hz
	 * Filter bandwidth : 1.75 Hz
	 * response time : 0.3s
	 */
	BME280_init(&hi2c2, P_OSR_04, H_OSR_00, T_OSR_01, normal, BW0_021ODR,t_00_5ms);

	IST8310(&hi2c2);

#ifdef USE_GPS
	/*
	 *  GPS using DMA circular mode
	 */
    TM_GPS_Init(&huart8);
#endif

#ifdef USE_SBUS
	SBUS_init(&huart7);
#endif

	//	Lidar1D_init(&htim9, TIM_CHANNEL_1, TIM_CHANNEL_2);
	//	Lidar1D_run();

    std::printf("boot complete\r\n");

	xTaskCreate(debug_main,
				"debug_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				2,
				NULL);
}

//callback
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
//#ifdef USE_MPU9250
	if(hi2c->Instance == mpu9250.hi2c->Instance){
		MPU9250_i2cRxCpltCallback();
		sensorAccel.setAccel(mpu9250.accel[0], mpu9250.accel[1], mpu9250.accel[2]);
		sensorGyro.setGyro(mpu9250.gyro[0], mpu9250.gyro[1], mpu9250.gyro[2]);
//		sensorMag.setMag(mpu9250.mag[0], mpu9250.mag[1], mpu9250.mag[2]);
	}
//#endif

//#ifdef USE_IST8310
	if(hi2c->Instance == ist8310.hi2c->Instance){
		IST8310_i2cRxCpltCallback();
		sensorMag.setMag(ist8310.raw[0], ist8310.raw[1], ist8310.raw[2]);
	}
//#endif

//#ifdef USE_BME280
	if(hi2c->Instance == bme280.hi2c->Instance){
		BME280_i2cRxCpltCallback();
		sensorBaro.setBaro(bme280.P, bme280.T);
	}
//#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#ifdef USE_SBUS
	if(huart->Instance == sbus.huart->Instance){
		if(SBUS_uartRxCpltCallback() == SBUS_Result_NewData){
			rc.setRC(SBUS_getChannel(2),	/* roll */
					 SBUS_getChannel(3),	/* pitch */
					 SBUS_getChannel(3), 	/* yaw */
					 SBUS_getChannel(1),	/* throttle */
					 SBUS_getChannel(11));
		}
	}
#endif

#ifdef USE_GPS
	if(huart->Instance == UART8){
		if(TM_GPS_Update() == TM_GPS_Result_NewData && gpsUart.gpsData.Fix != 0 /* gps must fixed */){
			sensorGPS.setGPS(gpsUart.gpsData.Latitude, gpsUart.gpsData.Longitude, gpsUart.gpsData.Altitude,
							 TM_GPS_ConvertSpeed(gpsUart.gpsData.Speed, TM_GPS_Speed_MeterPerSecond), gpsUart.gpsData.Direction, gpsUart.gpsData.HDOP, gpsUart.gpsData.VDOP,
							 gpsUart.gpsData.Satellites, gpsUart.gpsData.FixMode, 0/* UTC in microsecond */);
		}
	}
#endif

	if(huart->Instance == USART2){
		// telemetry
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	Lidar1D_CaptureCallback(htim);
}
