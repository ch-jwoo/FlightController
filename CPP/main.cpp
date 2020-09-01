/*
 * cppmain.h
 *
 *  Created on: 2020. 8. 2.
 *      Author: junwoo
 */

//essential
#include <Interface/Interface.h>
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "timers.h"

//additional
//#include "cstdio"
//#include "cstdlib"

//selfmade
#include <Module/Manager/ModuleCommander.h>
#include <Module/Estimator/ModuleAHRS.h>
#include <Module/Etc/ModuleBuzzer.h>
#include <Peripherals/Sensors/bme280.h>
#include <Peripherals/Sensors/IST8310.h>
#include <Peripherals/Sensors/Lidar1D.h>
#include <Peripherals/Sensors/MPU9250.h>
#include <Peripherals/Coms/sbus.h>
#include <Peripherals/Sensors/tm_stm32_gps.h>
#include <Utils/Constants.h>
#include "Module/Manager/ModuleHealth.h"
#include "Module/Storage/ModuleSD.h"
#include "Module/Controller/ModuleAttitudeController.h"
#include "Module/Estimator/ModuleINS.h"
#include "Module/Controller/ModulePositionController.h"
#include "Module/Manager/ModuleGCS.h"

#include "Peripherals/Actuator/Motor.h"
#include "Peripherals/Etc/LED.h"
#include "Peripherals/Etc/Buzzer.h"
#include "Peripherals/Coms/Telemetry.h"
#include "Peripherals/Sensors/MS4525DO.h"
#include "Peripherals/Sensors/VoltageChecker.h"


#include "printf.h"

using namespace FC;

//#define USE_MPU9250
//#define USE_IST8310
#define USE_GPS
//#define USE_BME280
#define USE_SBUS
//#define USE_AHRS

float attitude;
uint16_t hzAccel, hzBaro, hzGyro, hzGPS, hzMag, hzAHRS, hzRC, hzAtti, hzPos, hzINS, hzLidar;
uint16_t pwm1, pwm2, pwm3, pwm4, pwm5, pwm6;
float att_roll, att_pitch, att_yaw;
uint16_t ctl_roll, ctl_pitch, ctl_yaw, ctl_throtle;
float att_p, att_q, att_r;
float baro_alt;
float ned_ax, ned_ay, ned_az;

float local_x, local_y, local_z;
float local_vx, local_vy, local_vz;

float gps_lat, gps_lon, gps_alt;
float body_ax, body_ay, body_az;
float body_gx, body_gy, body_gz;

float mag_maxX, mag_maxY, mag_maxZ;
float mag_minX, mag_minY, mag_minZ;
float mag_x, mag_y, mag_z;
float mag_biasX, mag_biasY, mag_biasZ;
float mag_scaleX, mag_scaleY, mag_scaleZ;

float sp_roll, sp_pitch, sp_throtle, sp_yaw;

float lidar_alt;
uint8_t lidar_valid;

float airspeed_p;
uint8_t debug_loop;

float voltage;

uint8_t mode_arm, mode_flight;

uint32_t channel;

uint16_t timeCheck;
int test = 0;

float raw_magX, raw_magY, raw_magZ;

void _putchar(char character){
	HAL_UART_Transmit(&huart3, (uint8_t*)&character, 1, 10);
}

void Health_StartTask(void *argument){
	ModuleHealth::main();
}

void Debug_StartTask(void *argument){
	uint32_t tick;
	tick = osKernelGetTickCount();
	struct Health health;
	struct MotorPWM pwm;
	struct Attitude att;
	struct Controller ctl;
	struct Barometer baro;
	struct NedAccel nedAccel;
	struct LocalPosition localPosition;
	struct GPS gps;
	struct BodyAccel bodyAccel;
	struct BodyAngularVelocity bodyAnglularVel;
	struct BodyMag bodyMag;

	struct ModeFlag modeFlag;

	struct VehicleAttitueSP attitudeSP;

	struct Lidar lidar;

//	MS4525DO ms4525DO(&rtosI2C2);

	while(1){
		tick += 1000;
		osDelayUntil(tick);

		debug_loop++;

//		ms4525DO.update();
//		airspeed_p = ms4525DO.difPressure;

		if(msgBus.getHealth(&health)){
			hzAccel = health.accel;
			hzBaro = health.baro;
			hzGyro = health.gyro;
			hzGPS = health.gps;
			hzMag = health.mag;
			hzAHRS = health.ahrs;
			hzRC = health.rc;
			hzAtti = health.attitudeController;
			hzPos = health.positionController;
			hzINS = health.ins;
			hzLidar = health.lidar;
		}

		if(msgBus.getMotorPWM(&pwm)){
			pwm1 = pwm.m1;
			pwm2 = pwm.m2;
			pwm3 = pwm.m3;
			pwm4 = pwm.m4;
			pwm5 = pwm.m5;
			pwm6 = pwm.m6;
		}

		if(msgBus.getLidar(&lidar)){
			lidar_alt = lidar.altitude;
			lidar_valid = lidar.valid;
		}

		if(msgBus.getAttitude(&att)){
			att_roll = att.roll;
			att_pitch = att.pitch;
			att_yaw = att.yaw;
		}

		if(msgBus.getController(&ctl)){
			ctl_roll = ctl.roll;
			ctl_pitch = ctl.pitch;
			ctl_yaw = ctl.yaw;
			ctl_throtle = ctl.throttle;
		}
		if(msgBus.getBodyAccel(&bodyAccel)){
			body_ax = bodyAccel.xyz[0];
			body_ay = bodyAccel.xyz[1];
			body_az = bodyAccel.xyz[2];
		}
		if(msgBus.getBodyAngularVelocity(&bodyAnglularVel)){
			body_gx = bodyAnglularVel.xyz[0];
			body_gy = bodyAnglularVel.xyz[1];
			body_gz = bodyAnglularVel.xyz[2];
		}
		if(msgBus.getBarometer(&baro)){
			baro_alt = baro.altitude;
		}

		if(msgBus.getNedAccel(&nedAccel)){
			ned_ax = nedAccel.xyz[0];
			ned_ay = nedAccel.xyz[1];
			ned_az = nedAccel.xyz[2];
		}

		if(msgBus.getGPS(&gps)){
			gps_lat = gps.lat;
			gps_lon = gps.lon;
			gps_alt = gps.alt;
		}

		if(msgBus.getLocalPosition(&localPosition)){
			local_x = localPosition.x;
			local_y = localPosition.y;
			local_z = localPosition.z;
			local_vx = localPosition.vx;
			local_vy = localPosition.vy;
			local_vz = localPosition.vz;
		}

		if(msgBus.getBodyMag(&bodyMag)){
			mag_x = bodyMag.xyz[0];
			mag_y = bodyMag.xyz[1];
			mag_z = bodyMag.xyz[2];
		}

		if(msgBus.getModeFlag(&modeFlag)){
			mode_flight = (uint8_t)modeFlag.flightMode;
		}

		if(msgBus.getVehicleAttitueSP(&attitudeSP)){
			sp_roll = attitudeSP.roll;
			sp_pitch = attitudeSP.pitch;
			sp_throtle = attitudeSP.throttle;
			sp_yaw = attitudeSP.yawRate;
		}

		/* mag calibration */
		mag_minX = interfaceMag.min[0];
		mag_minY = interfaceMag.min[1];
		mag_minZ = interfaceMag.min[2];

		mag_maxX = interfaceMag.max[0];
		mag_maxY = interfaceMag.max[1];
		mag_maxZ = interfaceMag.max[2];

		mag_scaleX = interfaceMag.scale[0];
		mag_scaleY = interfaceMag.scale[1];
		mag_scaleZ = interfaceMag.scale[2];

		mag_biasX = interfaceMag.bias[0];
		mag_biasY = interfaceMag.bias[1];
		mag_biasZ = interfaceMag.bias[2];
		/* mag calibration end */

		voltageChecker.start();
		voltage = voltageChecker.voltage;

//		printf_("%d\t%d\t%f\t%f\t%f\r\n", ModuleINS::calGpsHomeFlag, ModuleINS::avgIndexGPS, ModuleINS::avgLat, ModuleINS::avgLon, ModuleINS::avgAlt);

//		int len = sprintf((char*)telemBuffer, "ready\r\n");
//		telem.send(telemBuffer, len);
//		len = telem.receive(telemBuffer, 100);
//		telem.send(telemBuffer, len);
//
//		int len = telem.receive(telemBuffer, 100);
//		if(len != 0)
//			printf_("%s\r\n", (char*)telemBuffer);
//		osDelay(5);
	}
}

void MPU9250_StartTask(void *argument){
	uint32_t tick;
	tick = osKernelGetTickCount();

	uint32_t magTick = osKernelGetTickCount();

	/*
	 * \setting		i2c1
	 * 				fastmode
	 * 				using global interrupt
	 * 				using dma_rx
	 */
	MPU9250 mpu9250(&rtosI2C1, MPU9250_AFS_16G, MPU9250_GFS_2000DPS, MPU9250_MFS_16BITS, MPU9250_M_100HZ);
	mpu9250.init();
	while(1){
		tick += 5;
		osDelayUntil(tick);/* 200hz */
		if(mpu9250.updateMPU9250())	{
			interfaceAccel.setAccel(mpu9250.accel[0]*FC_GRAVITY_ACCEERATION,
									mpu9250.accel[1]*FC_GRAVITY_ACCEERATION,
									mpu9250.accel[2]*FC_GRAVITY_ACCEERATION);
			interfaceGyro.setGyro(mpu9250.gyro[0]*FC_DEG2RAD,
								  mpu9250.gyro[1]*FC_DEG2RAD,
								  mpu9250.gyro[2]*FC_DEG2RAD);
		}
		if(osKernelGetTickCount() - magTick > 15){		/* 66hz */
			if(mpu9250.updateAK8963()){
				raw_magX = mpu9250.mag[0];
				raw_magY = mpu9250.mag[1];
				raw_magZ = mpu9250.mag[2];
				interfaceMag.setMag(mpu9250.mag[0], mpu9250.mag[1], mpu9250.mag[2]);
				magTick = osKernelGetTickCount();
			}
		}
	}
}

void BME280_StartTask(void *argument){
	uint32_t tick;
	tick = osKernelGetTickCount();

	/*
	 * \setting		i2c2
	 * 				fastmode
	 * 				using global interrupt
	 *
	 * recommended mode : gaming
	 * Sensor mode : normal mode, standby = 0.5ms
	 * oversampling : pressureX4, temperatureX1, humidityX0
	 * IIR filter coefficient : 16
	 * RMS Noise : 0.3Pa/2.5cm
	 * Data output rate : 83hz
	 * Filter bandwidth : 1.75 Hz
	 * response time : 0.3s
	 */
	BME280 bme280(&rtosI2C2, P_OSR_04, H_OSR_00, T_OSR_01, normal, BW0_021ODR,t_00_5ms);
	bme280.init();
	while(1){
		tick += 15;
		osDelayUntil(tick);		/* 66.6hz */

		if(bme280.update()){
			interfaceBaro.setBaro(bme280.P, bme280.T);
		}
	}
}

void IST8310_StartTask(void *argument){
	uint32_t tick;
	tick = osKernelGetTickCount();

	IST8310 ist8310(&rtosI2C2);
	ist8310.init();
	while(1){
		tick += 7;
		osDelayUntil(tick);		/* 142hz */
		ist8310.update();
	}
}

void SD_StartTask(void *argument){
	ModuleSD::main();
}

void AHRS_StartTask(void *argument){
	ModuleAHRS::main();
}

void Commander_StartTask(void *argument){
	ModuleCommander::main();
}

void Buzzer_StartTask(void *argument){
	ModuleBuzzer::main();
}

void AC_StartTask(void *argument){
	ModuleAttitudeController::main();
}

void INS_StartTask(void *argument){
	ModuleINS::main();
}

void PC_StartTask(void *argument){
	ModulePositionController::main();
}


void GCS_StartTask(void *argument){
	ModuleGCS::main();
//	while(1) osDelay(1000);
}

/*
 *  Switch
 *  Click : High
 *  GPIO_PinState result = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);
 */
/*
 *  LED signal
 *  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET);
 */

void cppMain(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf_("test\r\n");

    /* micro second timer start */
	HAL_TIM_Base_Start_IT(&htim2);

	/*
	 *  \setting		uart8
	 *  				baudrate		115200
	 *  				rx_dma(circular)
	 */
    TM_GPS_Init(&huart8);

    /*
     *  \setting		uart7
     *  				baudrate			100000
     *  				word length			9bits
     *  				parity				even
     *  				stop_bits			2
     *  				rx_dma(circular)
     */
	SBUS_init(&huart7);

	/*
	 *  TODO if lidar not connected, the lidar altitude is 6
	 *  so if you don't use lidar, this code must uncommente
	 */
//	Lidar1D_init(&htim15, TIM_CHANNEL_1, TIM_CHANNEL_2);
//	Lidar1D_run();

	telem.init();

	m1.start();
	m2.start();
	m3.start();
	m4.start();
	m5.start();
	m6.start();

    printf_("boot complete\r\n");
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
	rtosI2C1.writeCpltCallback(hi2c);
	rtosI2C2.writeCpltCallback(hi2c);
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	rtosI2C1.readCpltCallback(hi2c);
	rtosI2C2.readCpltCallback(hi2c);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	voltageChecker.callback(hadc);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	telem.sendCompleteCallback(huart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == sbus.huart->Instance){
		if(SBUS_uartRxCpltCallback() == SBUS_Result_NewData){
			interfaceRC.setRC(SBUS_getChannel(2),	/* roll */
					 SBUS_getChannel(3),	/* pitch */
					 SBUS_getChannel(4), 	/* yaw */
					 SBUS_getChannel(1),	/* throttle */
					 SBUS_getChannel(11),	/* arming */
					 SBUS_getChannel(5)		/* mode change */);
		}
	}

	if(huart->Instance == UART8){
		if(TM_GPS_Update() == TM_GPS_Result_NewData && gpsUart.gpsData.Fix != 0 /* gps must fixed */){
			interfaceGPS.setGPS(gpsUart.gpsData.Latitude, gpsUart.gpsData.Longitude, gpsUart.gpsData.Altitude,
							 TM_GPS_ConvertSpeed(gpsUart.gpsData.Speed, TM_GPS_Speed_MeterPerSecond), gpsUart.gpsData.Direction, gpsUart.gpsData.HDOP, gpsUart.gpsData.VDOP,
							 gpsUart.gpsData.Satellites, gpsUart.gpsData.FixMode, 0/* UTC in microsecond */);
		}
	}

	telem.rcvCompleteCallback(huart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	printf_("uart error\r\n");
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(Lidar1D_CaptureCallback(htim)){
		interfaceLidar.setDistance(lidar1D.distance_mm/1000.0f);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_13){
//		if(interfaceMag.startCalibrationFlag == false)
//			interfaceMag.startCalibration();
//		else interfaceMag.endCalibration();

		if(ModuleINS::calGpsHomeFlag == false){
			ModuleINS::setAvgLLA();
		}
	}
}


void Telem_IdleHandler(void){
	telem.rcvIdleCallback();
}
