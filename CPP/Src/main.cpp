
#include "main.h"
#include "i2c.h"
#include "tim.h"

#include "stdio.h"
#include "mpu6050.h"
#include "Estimator.h"

#include "utils.h"

//#define RAD_TO_DEG 57.295779513082320876798154814105

//const float RAD2DEG = 180/3.14159;
//const float alpha = 0.96;
//
//float ax, ay, az, gx, gy, gz;
//float aRoll, aPitch;
//float gRoll, gPitch, gYaw;
//float roll, pitch, yaw;


MPU6050 mpu(&hi2c1);
Estimator esti;

bool mpu_set = false;
bool mpu_start = false;

//void calAccelAngle(){
//	float accel_yz = sqrt(ay*ay + az*az);
//	float accel_xz = sqrt(ax*ax + az*az);
//
//	aPitch = atan(-ax / accel_yz)*RAD_TO_DEG;
//	aRoll = atan(ay / accel_xz)*RAD_TO_DEG;
//}
//void calGyroAngle()
//{
//	static uint32_t lastTime = HAL_GetTick();
//	float dt = (HAL_GetTick() - lastTime)/1000.0;
////	printf("%f\r\n", dt);
//	gRoll += gx*dt;
//	gPitch += gy*dt;
//	gYaw += gz*dt;
//	lastTime = HAL_GetTick();
//}
//
//void calFilteredAngle()
//{
//	static uint32_t lastTime = HAL_GetTick();
//	float dt = (HAL_GetTick() - lastTime)/1000.0;
//
////	printf("%f\r\n", dt);
//	float temp_angle_x = roll + gx*dt;
//	float temp_angle_y = pitch + gy*dt;
//	float temp_angle_z = yaw + gz*dt;
//
//	roll = alpha*temp_angle_x + (1-alpha)*aRoll;
//	pitch = alpha*temp_angle_y + (1-alpha)*aPitch;
//	yaw = temp_angle_z;
//
//	lastTime = HAL_GetTick();
//}

void CppMain()
{

	//cpp main

	printf("asdf\r\n");

    /* mpu it start*/
	HAL_TIM_Base_Start_IT(&htim11);

	mpu.initialize();
	mpu_start = true;
	while(1)
	{
//		printf("%u\r\n",mpu.getDeviceID());
//		HAL_Delay(1000);
		if(mpu_set == true){ // mpu check
			mpu.updateMotionIT();
//			mpu.printFilteredData();
//			mpu.getData(&ax, &ay, &az, &gx, &gy, &gz);
//			calAccelAngle();
			printf("%f, %f, %f, %f, %f, %f\r\n", mpu.roll, mpu.pitch, mpu.yaw, mpu.p, mpu.q, mpu.r);
//			calGyroAngle();
//			calFilteredAngle();
			mpu_set = false;
		}

	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == I2C1){
		mpu_set = true;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM11){ // 1000hz
		static uint8_t imuTime = 0;
		imuTime++;
		if(imuTime>16 && mpu_start == true){// 58.8hz
			mpu.getMotionIT();
			imuTime = 0;
		}
	}
}
