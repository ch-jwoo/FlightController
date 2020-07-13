/*
 * userMain.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */

#define YJD_DEBUG

//essential
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "tim.h"

//additional
#include "stdio.h"

//selfmade
#include "MPU9250.h"
#include "sbus.h"
#include "estimate.h"
#include "algorithmCollection.h"

//global variable
__IO ITStatus flagMpu = RESET;
__IO ITStatus flagControl = RESET;

//we can use printf
int _write(int file, unsigned char* p, int len) // for debug through uart3
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}

void userMain(){
    setvbuf(stdout, NULL, _IONBF, 0);

    MPU9250_init(&iMPU9250, &hi2c1);

    sbus_start(&huart7);

    HAL_TIM_Base_Start_IT(&htim11); // start mpu9250 it

	while(1){
		if(iMPU9250.itSet == SET){
			static struct junTimer timer = {0,};
			if(timer.start){
				MadgwickAHRSupdateIMU(&iEstimate, iMPU9250.gx*DEG2PI, iMPU9250.gy*DEG2PI, iMPU9250.gz*DEG2PI
									, iMPU9250.ax, iMPU9250.ay, iMPU9250.az, junTimer_toc(&timer)/1000.0);
			}

			junTimer_tic(&timer);
			iMPU9250.itSet = RESET;

//			printf("%f %f %f %f\r\n", iEstimate.bodyQ[0], iEstimate.bodyQ[1], iEstimate.bodyQ[2], iEstimate.bodyQ[3]);
			sbus_print();
		}
	}
}



//callback
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	//mpu9250
	if(hi2c->Instance == I2C1){
		uint8_t result = MPU9250_callbackMPU9250IT(&iMPU9250);
		if(result){
			iMPU9250.hzCnt++;
			iMPU9250.itSet = SET;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(iMPU9250.itSet == RESET){// imu hz timer
		MPU9250_readMPU9250IT(&iMPU9250);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART7){
		sbus_callback();
	}
	if(huart->Instance == USART2){
		// telemetry
	}
}
