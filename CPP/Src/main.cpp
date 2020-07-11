
#include "main.h"
#include "i2c.h"
#include "tim.h"

#include "stdio.h"
#include "mpu6050.h"
#include "Estimator.h"

#include "utils.h"
#include "MPU9250.h"

extern "C"{
#include "px4demo_attitude_control.h"
#include "rtwtypes.h"
}

#define DEG2RAD 0.0174532f

MPU6050 mpu(&hi2c1);
Estimator esti;

__IO ITStatus flagMpu = RESET;
__IO ITStatus flagControl = RESET;

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
  px4demo_attitude_control_step();

  /* Get model outputs here */
//  __disable_irq();
  OverrunFlag--;
}
volatile boolean_T stopRequested;
volatile boolean_T runModel;

/* External inputs (root inport signals with default storage) */
extern ExtU_px4demo_attitude_control_T px4demo_attitude_control_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_px4demo_attitude_control_T px4demo_attitude_control_Y;

void printOut(ExtY_px4demo_attitude_control_T* obj){
	printf("%u, %u, %u, %u, %u, %u \r\n"
			, obj->PWM[0], obj->PWM[1], obj->PWM[2], obj->PWM[3], obj->PWM[4], obj->PWM[5]);
}

void printIn(ExtU_px4demo_attitude_control_T* obj){
	printf("%f, %f, %f, %f, %f, %u, %u, %u, %u, %u\r\n"
			, obj->phi, obj->theta, obj->p, obj->q, obj->r
			, obj->target_thrust, obj->target_roll, obj->target_pitch, obj->target_yaw, obj->armingControl);
}
void CppMain()
{

	//cpp main

	printf("asdf\r\n");

    /* mpu it start*/
	HAL_TIM_Base_Start_IT(&htim11);

	mpu.initialize();

	/* Initialize variables */
	  stopRequested = false;
	  runModel = false;
//	  SystemCoreClockUpdate();
	  rtmSetErrorStatus(px4demo_attitude_control_M, 0);
	  px4demo_attitude_control_initialize();
//	  ARMCM_SysTick_Config(modelBaseRate);
	  runModel =
	    rtmGetErrorStatus(px4demo_attitude_control_M) == (NULL);

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

//			mpu.printRawData();
			static uint8_t cnt = 0;
//			cnt++;
			if(cnt > 99){
//				printf("%f, %f, %f, %f, %f, %f\r\n", mpu.roll, mpu.pitch, mpu.yaw, mpu.p, mpu.q, mpu.r);
				cnt = 0;
			}

			if(runModel && cnt==1){
		    	px4demo_attitude_control_U = {mpu.roll*DEG2RAD, -mpu.pitch*DEG2RAD
		    			 	 	 	 	 	 , 1500, 1500, 1500, 1500, 2000
											 , mpu.p*DEG2RAD, -mpu.q*DEG2RAD, -mpu.r*DEG2RAD};

//		    		    	printIn(&px4demo_attitude_control_U);
		        __disable_irq();
		        rt_OneStep();

		  	    __enable_irq();
		  	    printOut(&px4demo_attitude_control_Y);
		  	    stopRequested = !(
		  	                      rtmGetErrorStatus(px4demo_attitude_control_M) == (NULL));
		  	    runModel = !(stopRequested);
//		  	    flagControl = RESET;
			}
			cnt=1;
		}

//	    if ( flagControl == SET && runModel) {
//
//	    	px4demo_attitude_control_U = {mpu.roll*DEG2RAD, -mpu.pitch*DEG2RAD
//	    			 	 	 	 	 	 , 1500, 1500, 1500, 1500, 2000
//										 , mpu.p*DEG2RAD, -mpu.q*DEG2RAD, -mpu.r*DEG2RAD};
//
//	    		    	printIn(&px4demo_attitude_control_U);
//	        __disable_irq();
//	        rt_OneStep();
//
//	  	    __enable_irq();
////	  	    printOut(&px4demo_attitude_control_Y);
//	  	    stopRequested = !(
//	  	                      rtmGetErrorStatus(px4demo_attitude_control_M) == (NULL));
//	  	    runModel = !(stopRequested);
//	  	    flagControl = RESET;
//	    }
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
		if(imuTime>16 && flagMpu == RESET){// 58.8hz
			mpu.getMotionIT();
			imuTime = 0;
			flagControl = SET;
		}
	}
}
