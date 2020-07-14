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

#define SAFTY_SWITCH() (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)

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

void printOut(ExtY_Second_att_control_codeb_T* obj){
	printf("%u, %u, %u, %u, %u, %u \r\n"
			, obj->PWM_OUT[0], obj->PWM_OUT[1], obj->PWM_OUT[2], obj->PWM_OUT[3], obj->PWM_OUT[4], obj->PWM_OUT[5]);
}

void printIn(ExtU_Second_att_control_codeb_T* obj){
	printf("%f %f, %f %f %f, %u, %u, %u, %u, %u\r\n"
			, obj->Roll, obj->Pitch, obj->p, obj->q, obj->r
			, obj->set_thrust, obj->set_roll, obj->set_pitch, obj->set_yaw, obj->Arm_cmd);
}


//struct junTimer debugTimer = {0,};

void userMain(){
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("boot complete\r\n");
//    MPU9250_init(&iMPU9250, &hi2c1);


//    sbus_start(&huart7);
//    HAL_TIM_Base_Start_IT(&htim11); // start mpu9250 it

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



	while(1){
//		sensorHz_print();
//		MPU9250_print(&iMPU9250,1);

	    static uint8_t cnt = 0;

	    if(SAFTY_SWITCH()){
	    	printf("switch set\r\n");
	    }
//		sbus_print();
		HAL_Delay(300);
		//boot essential part
		if(iMPU9250.itSet == SET){
			estimate_update(&iEstimate, &iMPU9250);
//			estimate_print(&iEstimate);
			iMPU9250.itSet = RESET;
		}

		if(sbus_getChannel(10) > 1500){ // kill switch on
			motor_write(&iMotor1, MOTOR_PWM_MIN);
			motor_write(&iMotor2, MOTOR_PWM_MIN);
			motor_write(&iMotor3, MOTOR_PWM_MIN);
			motor_write(&iMotor4, MOTOR_PWM_MIN);
			motor_write(&iMotor5, MOTOR_PWM_MIN);
			motor_write(&iMotor6, MOTOR_PWM_MIN);
		}
		else{
			if(vehicleState == VEHICLE_INIT){ // can HAL_Delay
				static struct junTimer init_timer = {0,};

				if(imu_state && estimator_state && sbus_state){
					vehicleState = VEHICLE_PREARM;
				}
				else if(junTimer_toc(&init_timer)>3000 || !init_timer.start){
					if(!imu_state){ // imu problem
						HAL_TIM_Base_Stop_IT(&htim11);
						HAL_Delay(50);
						MPU9250_init(&iMPU9250, &hi2c1);
						HAL_TIM_Base_Start_IT(&htim11);
					}
					if(!estimator_hz){
						// this problem from mpu
					}
					if(!sbus_state){
						// must turn on RC
						HAL_UART_DMAStop(&huart7);
						HAL_Delay(50);
						sbus_start(&huart7);
					}
				}
			}
			// prearm
			else if(vehicleState == VEHICLE_PREARM){
				if(!(imu_state && estimator_state && sbus_state)){
					vehicleState = VEHICLE_INIT;
				}
				else if(SAFTY_SWITCH()){
					vehicleState = VEHICLE_DISARM;

					motor_write(&iMotor1, MOTOR_PWM_MIN);
					motor_write(&iMotor2, MOTOR_PWM_MIN);
					motor_write(&iMotor3, MOTOR_PWM_MIN);
					motor_write(&iMotor4, MOTOR_PWM_MIN);
					motor_write(&iMotor5, MOTOR_PWM_MIN);
					motor_write(&iMotor6, MOTOR_PWM_MIN);
				}
			}
			else if(vehicleState == VEHICLE_DISARM){
				if(!(imu_state && estimator_state && sbus_state)){
					vehicleState = VEHICLE_INIT;
				}
				else if(sbus_getChannel(11)>1500 && abs(iEstimate.pitch)<0.5 && abs(iEstimate.roll) < 0.5){ // roll, pitch up to 30degree
					vehicleState = VEHICLE_ARM;
				}
			}
			else if(vehicleState == VEHICLE_ARM){

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
	//			printOut(&Second_att_control_codeblock_Y);
			}
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
	static uint8_t hz_update = 0;
	if(iMPU9250.itSet == RESET){// imu hz timer 100hz
		MPU9250_readMPU9250IT(&iMPU9250);
	}
	if(++hz_update > 99){
		sensorHz_update();
		hz_update = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART7){
//		sbus_parse();
		sbus_callback();
	}
	if(huart->Instance == USART2){
		// telemetry
	}
}
