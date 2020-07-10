
#include "main.h"
#include "i2c.h"
#include "tim.h"

#include "stdio.h"
#include "mpu6050.h"
#include "Estimator.h"

#include "utils.h"

float ax, ay, az, gx, gy, gz;

MPU6050 mpu(&hi2c1);
Estimator esti;

extern uint32_t stm_millis; // boot time ?

bool mpu_set = false;
uint8_t mpu_hz = 0;
uint32_t mpu_hz_time = 0;
uint16_t mpu_hz_cnt = 0;
uint8_t mpu_start = RESET;
uint8_t mpu_error = 0;

void CppMain()
{
//	bool devStatus = false;
	/*
	while(!devStatus){
		mpu.initialize();
		devStatus = mpu.testConnection();
		if(devStatus){
			printf("MPU6050 connection successful");
		}
		else{
			printf("MPU6050 connection failed");

		}
		HAL_Delay(2000);
	}
	*/
//	devStatus = true;
//	while(devStatus){
//		printf("wait...");
//		devStatus = mpu.testConnection();
//		HAL_Delay(1000);
//	}
//	if(devStatus == 0){
//	    mpu.CalibrateAccel(6);
//	    mpu.CalibrateGyro(6);
//        mpu.PrintActiveOffsets();
//	}
	//cpp main

	printf("asdf\r\n");

//    mpu.getMotionIT();

    /* mpu it start*/
//	HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim11);

	mpu.initialize();
	mpu_start = SET;

//	HAL_Delay(100);
	while(1)
	{
		if(mpu_set == SET){ // mpu check
			uint8_t result = mpu.updateMotionIT();
			printf("%d\r\n", result);
			if( !result ){//update
				mpu_error++;
			}
			mpu_error = 0;
			mpu_hz_cnt++;
			if(stm_millis - mpu_hz_time > 1000){ // calc mpu hz
				mpu_hz = mpu_hz_cnt;
				mpu_hz_cnt = 0;
				mpu_hz_time = stm_millis;
			}
			mpu_set = RESET;
		}
		else if(mpu_error > 30){ //error check,,
			mpu_set = RESET;
			mpu_start = RESET; // mpu disconnect
			mpu_hz = 0;
			mpu.initialize();
			mpu_start = SET; // mpu connect
		}
//		printf("%d\r\n", mpu_hz);
//		esti.calGyroAngle();
//		printf("%f, %f\r\n", esti.roll, esti.pitch)
//		printf("%u\r\n", mpu.hz);
//		HAL_Delay(1000);
		//main while
//		ax=0; ay=0; az=0; gx=0; gy=0, gz=0;
//		mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
//		printf("%d, %d, %d, %d, %d, %d\r\n", ax, ay, az, gx, gy, gz);
//		printf("%f, %f, %f, %f, %f, %f\r\n", mpu.Ax, mpu.Ay, mpu.Az, mpu.Gx, mpu.Gy, mpu.Gz);
//		uint16_t id = mpu.getDeviceID();
//		HAL_Delay(100);
//		std::printf("test %d\r\n", mpu.getDeviceID());
//		HAL_Delay(100);
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == I2C1){
		mpu_set = SET;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	static uint8_t a = 0;
//	if(htim->Instance == TIM10){ // 60hz
//		a++;
//		mpu.getMotionIT();
//		if(a >2){
////			printf("%d\r\n", a);
////			mpu.getMotionIT();
//			a = 0;
//		}
//	}

	if(htim->Instance == TIM11){ // 1000hz
		static uint8_t imuTime = 0;
		stm_millis++;
		imuTime++;
		if(imuTime>16 && mpu_start == SET){// 58.8hz
			mpu.getMotionIT();
			imuTime = 0;
		}

		//sec test
//		static uint16_t sec = 0;
//		sec++;
//		if(sec>999){
//			printf("%u\r\n", stm_millis);
//			sec = 0;
//		}
	}
}
