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
#include "motor.h"
#include "Second_att_control_codeblock.h"
#include "State.h"

//global variable
//__IO ITStatus flagMpu = RESET;
//__IO ITStatus flagControl = RESET;

//we can use printf
int _write(int file, unsigned char* p, int len) // for debug through uart3
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

//  __enable_irq();
  Second_att_control_codeblock_step();

  /* Get model outputs here */
//  __disable_irq();
  OverrunFlag--;
}

//volatile boolean_T stopRequested;
volatile boolean_T runModel = 1;

//void printOut(ExtU_Second_att_control_codeb_T* obj,Second_att_control_codeblock_B* setvalue){
/*	printf("%u, %u, %u, %u, %u, %u \r\n"
			, obj->PWM_OUT[0], obj->PWM_OUT[1], obj->PWM_OUT[2], obj->PWM_OUT[3], obj->PWM_OUT[4], obj->PWM_OUT[5]);
	printf("%f,  %f , %f  , %f  ,%f  \r\n",setvalue->Sum2,setvalue->.Sum1_h , obj->p, obj->q, obj->r);
}*/
void printIn(ExtU_Second_att_control_codeb_T* obj){
	printf("%f %f, %f %f %f, %u, %u, %u, %u, %u\r\n"
			, obj->Roll, obj->Pitch, obj->p, obj->q, obj->r
			, obj->set_thrust, obj->set_roll, obj->set_pitch, obj->set_yaw, obj->Arm_cmd);
}


//struct junTimer debugTimer = {0,};

void userMain(){

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("boot complete\r\n");
    MPU9250_init(&iMPU9250, &hi2c1);

    sbus_start(&huart7);
//    HAL_Delay(10);


    motor_init(&iMotor1, &htim4, TIM_CHANNEL_1);
    motor_init(&iMotor2, &htim4, TIM_CHANNEL_2);
    motor_init(&iMotor3, &htim4, TIM_CHANNEL_3);
    motor_init(&iMotor4, &htim4, TIM_CHANNEL_4);
    motor_init(&iMotor5, &htim3, TIM_CHANNEL_1);
    motor_init(&iMotor6, &htim3, TIM_CHANNEL_2);

    motor_start(&iMotor1);
    motor_start(&iMotor2);
    motor_start(&iMotor3);
    motor_start(&iMotor4);
    motor_start(&iMotor5);
    motor_start(&iMotor6);

    HAL_TIM_Base_Start_IT(&htim11); // start mpu9250 it
//    HAL_Delay(10);
    printf("mpu set\r\n");
	while(1){
//		sensorHz_print();
		//boot essential part
//		MPU9250_print(&iMPU9250,1);
		if(iMPU9250.itSet == SET){
			estimate_update(&iEstimate, &iMPU9250);
			uint32_t cur_time=HAL_GetTick();

	        estimate_print(&iEstimate);
//			printf("R:%f SR:%f P:%f SP:%f T:%lu\r\n",iEstimate.roll,Second_att_control_codeblock_B.urad_max[0], iEstimate.pitch, Second_att_control_codeblock_B.urad_max[1],cur_time);
//			printf("R:%f SR:%f T:%lu\r\n",iEstimate.roll,Second_att_control_codeblock_B.Gain[0],cur_time);

			if(runModel){
//				junTimer_tic(&debugTimer);
				Second_att_control_codeblock_U.Roll = iEstimate.roll;
				Second_att_control_codeblock_U.Pitch = iEstimate.pitch;
				Second_att_control_codeblock_U.p = iEstimate.p;
				Second_att_control_codeblock_U.q = iEstimate.q;
				Second_att_control_codeblock_U.r = iEstimate.r;
				Second_att_control_codeblock_U.set_thrust = sbus_getChannel(1);
				Second_att_control_codeblock_U.set_roll = sbus_getChannel(2);
				Second_att_control_codeblock_U.set_pitch = sbus_getChannel(3);
				Second_att_control_codeblock_U.set_yaw = sbus_getChannel(4);
				Second_att_control_codeblock_U.Arm_cmd = sbus_getChannel(11);

				__disable_irq();
				rt_OneStep();
				__enable_irq();

				motor_write(&iMotor1, Second_att_control_codeblock_Y.PWM_OUT[0]);
				motor_write(&iMotor2, Second_att_control_codeblock_Y.PWM_OUT[1]);
				motor_write(&iMotor3, Second_att_control_codeblock_Y.PWM_OUT[2]);
				motor_write(&iMotor4, Second_att_control_codeblock_Y.PWM_OUT[3]);
				motor_write(&iMotor5, Second_att_control_codeblock_Y.PWM_OUT[4]);
				motor_write(&iMotor6, Second_att_control_codeblock_Y.PWM_OUT[5]);
			}
//			printIn(&Second_att_control_codeblock_U);
			iMPU9250.itSet = RESET;
//			printOut(&Second_att_control_codeblock_Y);
		}


//		printf("%f %f %f\r\n",iEstimate.p , iEstimate.q,iEstimate.r);
//		printf("%f \r\n",Second_att_control_codeblock_DW.Integrator_DSTATE);
//		MPU9250_print(&iMPU9250,1);

		/*if(vehicleState == VEHICLE_INIT){

		}
		else if(vehicleState == VEHICLE_PREARM){

		}
		else if(vehicleState == VEHICLE_DISARM){

		}
		else if(vehicleState == VEHICLE_ARM){

		}*/
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
	if(htim->Instance == TIM11){
		static uint8_t hz_update = 0;
		if(iMPU9250.itSet == RESET){// imu hz timer 100hz
			MPU9250_readMPU9250IT(&iMPU9250);
		}
		if(++hz_update > 199){
			sensorHz_update();
			hz_update = 0;
//			sensorHz_print();
		}
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
