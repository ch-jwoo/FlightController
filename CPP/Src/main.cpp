
#include "main.h"
#include "i2c.h"
#include "tim.h"

#include "stdio.h"
#include "mpu6050.h"
#include "Estimator.h"

#include "utils.h"
#include "MPU9250.h"

MPU6050 mpu(&hi2c1);
Estimator esti;

__IO ITStatus flagMpu = RESET;

void CppMain()
{

	//cpp main

	printf("asdf\r\n");

    /* mpu it start*/
	HAL_TIM_Base_Start_IT(&htim11);

	mpu.initialize();
	while(1)
	{
		if(flagMpu == SET){ // mpu check
			mpu.updateMotionIT();
//			mpu.printFilteredData();
//			mpu.getData(&ax, &ay, &az, &gx, &gy, &gz);
//			calAccelAngle();
//			calGyroAngle();
//			calFilteredAngle();
//			printf("%f, %f, %f, %f, %f, %f\r\n", mpu.roll, mpu.pitch, mpu.yaw, mpu.p, mpu.q, mpu.r);
			flagMpu = RESET;

			static uint8_t cnt = 0;
			cnt++;
			if(cnt > 99){
				printf("%f, %f, %f, %f, %f, %f\r\n", mpu.roll, mpu.pitch, mpu.yaw, mpu.p, mpu.q, mpu.r);
				cnt = 0;
			}
		}

	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == I2C1){
		flagMpu = SET;
		HAL_DMA_Abort_IT(hi2c->hdmatx);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM11){ // 1000hz
		static uint8_t imuTime = 0;
		imuTime++;
		if(imuTime>1 && flagMpu == RESET){// 58.8hz
			mpu.getMotionIT();
			imuTime = 0;
//			flagMpu = SET;
		}
	}
}
