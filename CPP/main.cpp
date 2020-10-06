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

//selfmade
#include <Module/Manager/ModuleCommander.h>
#include <Module/Estimator/ModuleAHRS.h>
#include <Module/Etc/ModuleBuzzer.h>
#include <Peripherals/Coms/Sbus.h>
#include <Peripherals/Sensors/bme280.h>
#include <Peripherals/Sensors/IST8310.h>
#include <Peripherals/Sensors/Lidar1D.h>
#include <Peripherals/Sensors/MPU9250.h>
#include <Peripherals/Sensors/tm_stm32_gps.h>
#include <Utils/Constants.h>
#include "Module/Manager/ModuleHealth.h"
#include "Module/Storage/ModuleSD.h"
#include "Module/Controller/ModuleAttitudeController.h"
#include "Module/Estimator/ModuleINS.h"
#include "Module/Controller/ModulePositionController.h"
#include "Module/Manager/ModuleGCS.h"
#include "Module/Controller/ModuleAutoController.h"

#include "Peripherals/Actuator/Motor.h"
#include "Peripherals/Actuator/Servo.h"
#include "Peripherals/Etc/LED.h"
#include "Peripherals/Etc/Buzzer.h"
#include "Peripherals/Coms/Telemetry.h"
#include "Peripherals/Sensors/MS4525DO.h"
#include "Peripherals/Sensors/VoltageChecker.h"

#include "MsgBus/Params.h"

#include "printf.h"

using namespace FC;

//#define USE_MPU9250
//#define USE_IST8310
#define USE_GPS
//#define USE_BME280
#define USE_SBUS
//#define USE_AHRS

uint8_t accelIntCnt=0;

float attitude;
uint16_t hzAccel, hzBaro, hzGyro, hzGPS, hzMag;
uint16_t hzAHRS, hzRC, hzAtti, hzPos, hzINS, hzLidar, hzAuto;
uint16_t pwm1, pwm2, pwm3, pwm4, pwm5, pwm6;
float att_roll, att_pitch, att_yaw;
uint16_t ctl_roll, ctl_pitch, ctl_yaw, ctl_throtle;
float att_p, att_q, att_r;
float baro_alt;
float ned_ax, ned_ay, ned_az;

float local_x, local_y, local_z;
float local_vx, local_vy, local_vz;

float gps_lat, gps_lon, gps_alt, local_gps_x, local_gps_y;
float gps_velN,gps_velE;
float body_ax, body_ay, body_az;
float body_gx, body_gy, body_gz;

float mag_maxX, mag_maxY, mag_maxZ;
float mag_minX, mag_minY, mag_minZ;
float mag_x, mag_y, mag_z;
float mag_biasX, mag_biasY, mag_biasZ;
float mag_scaleX, mag_scaleY, mag_scaleZ;
float targetyaw,targetroll,targetx,targety,targetz,dist;

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

bool accelCalibration = false;
float airspeed = 0;

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
	struct AirSpeed airSpeed;

	while(1){
		tick += 100;
		osDelayUntil(tick);
		debug_loop++;

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
			hzAuto = health.autoController;
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
			gps_velN=gps.velN;
			gps_velE=gps.velE;

		}

		if(msgBus.getLocalPosition(&localPosition)){
			local_x = localPosition.x;
			local_y = localPosition.y;
			local_z = localPosition.z;
			local_vx = localPosition.vx;
			local_vy = localPosition.vy;
			local_vz = localPosition.vz;
			local_gps_x=localPosition.gpsrawx;
			local_gps_y=localPosition.gpsrawy;
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

		int len= sprintf_((char*)telemBuffer,"%f %f %f %f %f %f %f \n\r",local_x,local_y,sp_roll,sp_pitch,att_yaw,sp_throtle,gps.hdop);
//		int len= sprintf_((char*)telemBuffer,"%f %f %f %d %d \n\r",gps.lat,gps.lon,gps.hdop,gps.usedSatellites,gps.visibleSatellites);

//		int len= sprintf_((char*)telemBuffer,"%f %f %f %f %f %f  \n\r",local_x,local_y,local_vx,local_vy, gps_velN, gps_velE);
//		telem.send(telemBuffer,len);
////
//		int len= sprintf_((char*)telemBuffer,"%f %f %f %f %f %f  \n\r",mag_scaleX,mag_scaleY,mag_scaleZ,mag_biasX,mag_biasY,mag_biasZ);
//		telem.send(telemBuffer,len);

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
									mpu9250.accel[2]*FC_GRAVITY_ACCEERATION,
									accelCalibration);
			interfaceGyro.setGyro(mpu9250.gyro[0]*FC_DEG2RAD,
								  mpu9250.gyro[1]*FC_DEG2RAD,
								  mpu9250.gyro[2]*FC_DEG2RAD);
		}
		if(osKernelGetTickCount() - magTick > 15){		/* 66hz */
			if(mpu9250.updateAK8963()){
				raw_magX = mpu9250.mag[0];
				raw_magY = mpu9250.mag[1];
				raw_magZ = mpu9250.mag[2];
//				interfaceMag.setMag(mpu9250.mag[0], mpu9250.mag[1], mpu9250.mag[2]);
				magTick = osKernelGetTickCount();
			}
		}

		if(accelCalibration) accelCalibration = false;
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
	BME280 bme280(&rtosI2C2, P_OSR_04, H_OSR_00, T_OSR_01, normal, full,t_00_5ms);
	bme280.init();

	bme280.update();
	bme280.update();
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
		tick += 10;
		osDelayUntil(tick);		/* 100hz */
		ist8310.update();
		interfaceMag.setMag(ist8310.raw[0],ist8310.raw[1],ist8310.raw[2]);
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

void AUTO_StartTask(void *argument){
	ModuleAutoController::main();       //NEVER EVER OPEN
//	while(1) osDelay(1000);
}


void GPS_StartTask(void *argument){
	uint32_t tick;

	/*
	 *  \setting		uart8
	 *  				baudrate		115200
	 *  				rx_dma(circular)
	 */
	TM_GPS_Init(&huart8);

	tick = osKernelGetTickCount();
	while(1){
//		tick += 200;
//		osDelayUntil(tick);		/* 5hz */

		/*
		 *  dma gps update
		 *  parse data (static time, 10 hz?)
		 */
		if(TM_GPS_Update() == TM_GPS_Result_NewData){
			interfaceGPS.setGPS(tmGps.Latitude, tmGps.Longitude, tmGps.Altitude,
								TM_GPS_ConvertSpeed(tmGps.Speed, TM_GPS_Speed_MeterPerSecond), tmGps.Direction, tmGps.HDOP, tmGps.VDOP,
								tmGps.Satellites, tmGps.SatellitesInView, tmGps.FixMode, 0/* UTC in microsecond */);
//			printf_("%f %f %f %d\r\n", tmGps.Latitude, tmGps.Longitude, tmGps.Altitude, tmGps.Satellites);
		}
	}
}

void SBUS_StartTask(void *argument){

	while(1){
		/*
		 *  dma sbus update
		 */
		if(sbus.update()){
			interfaceRC.setRC(sbus.getChannelVal(2),	/* roll */
						 	  sbus.getChannelVal(3),	/* pitch */
							  sbus.getChannelVal(4), 	/* yaw */
							  sbus.getChannelVal(1),	/* throttle */
							  sbus.getChannelVal(11),	/* arming */
							  sbus.getChannelVal(5),	/* mode change */
							  sbus.getChannelVal(9));	/* tilting */
		}
	}
}


void MS4525D_StartTask(void *argument){
	uint32_t tick;
	MS4525DO ms4525(&rtosI2C2);

	tick = osKernelGetTickCount();
	while(1){
		tick += 10;
		osDelayUntil(tick);		/* 100hz */

		if(ms4525.update()){
			interfaceAirSpeed.setAirSpeed(ms4525.diffPressure);
		}
	}
}

void cppMain(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf_("test\r\n");

    paramInit();

    /* micro second timer start */
	HAL_TIM_Base_Start_IT(&htim2);

	HAL_Delay(1000);

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

	s1.start();
	s2.start();
	s3.start();
	s4.start();
	s5.start();
	s6.start();

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
	TM_GPS_CpltCallback(huart);
	sbus.rcvCompleteCallback(huart);
	telem.rcvCompleteCallback(huart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == UART7){
		printf_("sbus error : %x\r\n", huart->ErrorCode);
	}
	if(huart->Instance == UART8){
		printf_("gps error : %x\r\n", huart->ErrorCode);
	}
	if(huart->Instance == USART2){
		printf_("telem error : %x\r\n", huart->ErrorCode);
	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == I2C1){
		printf_("i2c1 error\r\n");
	}
	if(hi2c->Instance == I2C2){
		printf_("i2c2 error\r\n");
	}
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
		accelCalibration = true;
		if(ModuleINS::calGpsHomeFlag == false){
			ModuleINS::setAvgLLA();
		}
	}

	if(GPIO_Pin == GPIO_PIN_5){
		accelIntCnt++;
	}
}


void Telem_IdleHandler(void){
	telem.rcvIdleCallback();
}
