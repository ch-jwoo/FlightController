
#include "main.h"
#include "i2c.h"
#include "tim.h"

#include "stdio.h"
#include "mpu6050.h"
#include "Estimator.h"

float ax, ay, az, gx, gy, gz;

MPU6050 mpu(&hi2c1);
Estimator esti;

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

	mpu.initialize();
//    mpu.getMotionIT();

    /* mpu it start*/
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim11);

//	HAL_Delay(100);
	while(1)
	{
//		esti.calGyroAngle();
//		printf("%f, %f\r\n", esti.roll, esti.pitch)
		printf("%u\r\n", TIM11->CNT);
//		printf("hello\r\n");
		HAL_Delay(1000);
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
	static uint8_t cnt = 0;
	if(hi2c->Instance == I2C1){
		cnt++;
		mpu.updateMotionIT();
		if(cnt>10){
//			printf("%f, %f, %f, %f, %f, %f\r\n", mpu.Ax, mpu.Ay, mpu.Az, mpu.Gx, mpu.Gy, mpu.Gz);
//			printf("%d, %d, %d, %d, %d, %d\r\n", mpu.rawAx, mpu.rawAy, mpu.rawAz, mpu.rawGx, mpu.rawGy, mpu.rawGz);
			cnt = 0;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	static uint8_t a = 0;
	if(htim->Instance == TIM10){ // 60hz test
		a++;
		mpu.getMotionIT();
		if(a >2){
//			printf("%d\r\n", a);
//			mpu.getMotionIT();
			a = 0;
		}
	}
}
