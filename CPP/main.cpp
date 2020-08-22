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

#include "Peripherals/Actuator/Motor.h"

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

uint8_t mode_arm, mode_flight;

uint32_t channel;

uint16_t timeCheck;
int test = 0;

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
//	osDelay(2000);
//	sensorBaro.setSeaLevelPressure(gps.alt);
	while(1){
		tick += 5;
		osDelayUntil(tick);
		msgBus.getHealth(&health);
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
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		msgBus.getMotorPWM(&pwm);
		pwm1 = pwm.m1;
		pwm2 = pwm.m2;
		pwm3 = pwm.m3;
		pwm4 = pwm.m4;
		pwm5 = pwm.m5;
		pwm6 = pwm.m6;

		if(msgBus.getLidar(&lidar)){
			lidar_alt = lidar.altitude;
			lidar_valid = lidar.valid;
		}

		msgBus.getAttitude(&att);
		att_roll = att.roll;
		att_pitch = att.pitch;
		att_yaw = att.yaw;

		msgBus.getController(&ctl);
		ctl_roll = ctl.roll;
		ctl_pitch = ctl.pitch;
		ctl_yaw = ctl.yaw;
		ctl_throtle = ctl.throttle;

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
//		osKernelLock();
		if(msgBus.getBarometer(&baro)){
			baro_alt = baro.altitude;
//			printf_("baro : %u %f\r\n", (unsigned int)baro.timestamp, baro_alt);
		}

		if(msgBus.getNedAccel(&nedAccel)){
			ned_ax = nedAccel.xyz[0];
			ned_ay = nedAccel.xyz[1];
			ned_az = nedAccel.xyz[2];
//			printf_("ned accel : %u %f %f %f\r\n", (unsigned int)nedAccel.timestamp, nedAccel.xyz[0], nedAccel.xyz[1], nedAccel.xyz[2]);
		}

		if(msgBus.getGPS(&gps)){
			gps_lat = gps.lat;
			gps_lon = gps.lon;
			gps_alt = gps.alt;
//			printf_("GPS : %u %f %f %f %f %f %f %f %u %f %f\r\n", (unsigned int)gps.timestamp, gps.lat, gps.lon, gps.alt, gps.velN, gps.velE
//						   , gps.direction, gps.vel
//						   , gps.fixType, gps.hdop, gps.vdop);
		}

		if(msgBus.getLocalPosition(&localPosition)){
			local_x = localPosition.x;
			local_y = localPosition.y;
			local_z = localPosition.z;
			local_vx = localPosition.vx;
			local_vy = localPosition.vy;
			local_vz = localPosition.vz;
//			printf_("ned position : %u %f %f %f\r\n", (unsigned int)localPosition.timestamp, local_x, local_y, local_z);
		}

		if(msgBus.getBodyMag(&bodyMag)){
			mag_x = bodyMag.xyz[0];
			mag_y = bodyMag.xyz[1];
			mag_z = bodyMag.xyz[2];
		}

		if(msgBus.getModeFlag(&modeFlag)){
			mode_arm = (uint8_t)modeFlag.armMode;
			mode_flight = (uint8_t)modeFlag.flightMode;
		}

		if(msgBus.getVehicleAttitueSP(&attitudeSP)){
			sp_roll = attitudeSP.roll;
			sp_pitch = attitudeSP.pitch;
			sp_throtle = attitudeSP.throttle;
			sp_yaw = attitudeSP.yawRate;
		}
//		osKernelUnlock();

		/* mag calibration */
//		mag_minX = sensorMag.min[0];
//		mag_minY = sensorMag.min[1];
//		mag_minZ = sensorMag.min[2];
//
//		mag_maxX = sensorMag.max[0];
//		mag_maxY = sensorMag.max[1];
//		mag_maxZ = sensorMag.max[2];
//
//		mag_scaleX = sensorMag.scale[0];
//		mag_scaleY = sensorMag.scale[1];
//		mag_scaleZ = sensorMag.scale[2];
//
//		mag_biasX = sensorMag.bias[0];
//		mag_biasY = sensorMag.bias[1];
//		mag_biasZ = sensorMag.bias[2];
		/* mag calibration end */

//		osDelay(5);
	}
}

void MPU9250_StartTask(void *argument){
	uint32_t tick;
	tick = osKernelGetTickCount();
	while(1){
		tick += 5;
		osDelayUntil(tick);/* 200hz */
		MPU9250_updateDMA();
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
//		IST8310_updataIT();
		osDelay(10); 			/* 100hz */
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
//	ModuleBuzzer::main();
	while(1){
		osDelay(100);
	}
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
	 * \setting		i2c1
	 * 				fastmode
	 * 				using global interrupt
	 * 				using dma_rx
	 */
	MPU9250(&hi2c1);

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
	BME280_init(&hi2c2, P_OSR_04, H_OSR_00, T_OSR_01, normal, BW0_021ODR,t_00_5ms);

	/*
	 * \setting		i2c2
	 * 				fastmode
	 * 				using global interrupt
	 * 	magnetometer in gps module
	 */
//	IST8310(&hi2c2);

	/*
	 *  \setting		uart8
	 *  				baudrate		38400
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

	Lidar1D_init(&htim15, TIM_CHANNEL_1, TIM_CHANNEL_2);
	Lidar1D_run();

	m1.start();
	m2.start();
	m3.start();
	m4.start();
	m5.start();
	m6.start();

    printf_("boot complete\r\n");
}

//callback
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == mpu9250.hi2c->Instance){
		switch(MPU9250_i2cRxCpltCallback()){
		case 1:
			interfaceAccel.setAccel(mpu9250.accel[0]*FC_GRAVITY_ACCEERATION
							   , mpu9250.accel[1]*FC_GRAVITY_ACCEERATION
							   , mpu9250.accel[2]*FC_GRAVITY_ACCEERATION);
			interfaceGyro.setGyro(mpu9250.gyro[0], mpu9250.gyro[1], mpu9250.gyro[2]);
			break;
		case 2:
			interfaceMag.setMag(mpu9250.mag[0], mpu9250.mag[1], mpu9250.mag[2]);
			break;
		}
	}

	if(hi2c->Instance == ist8310.hi2c->Instance){
		if(IST8310_i2cRxCpltCallback()){
//			sensorMag.setMag(ist8310.raw[0], ist8310.raw[1], ist8310.raw[2]);
		}
	}

	if(hi2c->Instance == bme280.hi2c->Instance){
		if(BME280_i2cRxCpltCallback()){
			sensorBaro.setBaro(bme280.P, bme280.T);
		}
	}
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

//	if(huart->Instance == USART6){
//		if(TM_GPS_Update() == TM_GPS_Result_NewData && gpsUart.gpsData.Fix != 0 /* gps must fixed */){
//			sensorGPS.setGPS(gpsUart.gpsData.Latitude, gpsUart.gpsData.Longitude, gpsUart.gpsData.Altitude,
//							 TM_GPS_ConvertSpeed(gpsUart.gpsData.Speed, TM_GPS_Speed_MeterPerSecond), gpsUart.gpsData.Direction, gpsUart.gpsData.HDOP, gpsUart.gpsData.VDOP,
//							 gpsUart.gpsData.Satellites, gpsUart.gpsData.FixMode, 0/* UTC in microsecond */);
//		}
//	}

//	if(TM_GPS_Update(huart) == TM_GPS_Result_NewData){
//		sensorGPS.setGPS(gpsUart.gpsData.Latitude, gpsUart.gpsData.Longitude, gpsUart.gpsData.Altitude,
//						 TM_GPS_ConvertSpeed(gpsUart.gpsData.Speed, TM_GPS_Speed_MeterPerSecond), gpsUart.gpsData.Direction, gpsUart.gpsData.HDOP, gpsUart.gpsData.VDOP,
//						 gpsUart.gpsData.Satellites, gpsUart.gpsData.FixMode, 0/* UTC in microsecond */);
//	}
	if(huart->Instance == UART8){
		if(TM_GPS_Update() == TM_GPS_Result_NewData && gpsUart.gpsData.Fix != 0 /* gps must fixed */){
			interfaceGPS.setGPS(gpsUart.gpsData.Latitude, gpsUart.gpsData.Longitude, gpsUart.gpsData.Altitude,
							 TM_GPS_ConvertSpeed(gpsUart.gpsData.Speed, TM_GPS_Speed_MeterPerSecond), gpsUart.gpsData.Direction, gpsUart.gpsData.HDOP, gpsUart.gpsData.VDOP,
							 gpsUart.gpsData.Satellites, gpsUart.gpsData.FixMode, 0/* UTC in microsecond */);
		}
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(Lidar1D_CaptureCallback(htim)){
		interfaceLidar.setDistance(lidar1D.distance_mm/1000.0f);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_13){
		sensorBaro.setSeaLevelPressure(gps_alt);
//		if(sensorMag.startCalibrationFlag == false)
//			sensorMag.startCalibration();
//		else sensorMag.endCalibration();
		interfaceAccel.setBias();
		interfaceGyro.setBias();
	}
}
