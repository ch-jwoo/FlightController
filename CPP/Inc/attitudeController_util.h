/*
 * attitudeController.h
 *
 *  Created on: Jul 12, 2020
 *      Author: cjb88
 */

#ifndef INC_ATTITUDECONTROLLER_UTIL_H_
#define INC_ATTITUDECONTROLLER_UTIL_H_

#include "px4demo_attitude_control.h"
#include "rtwtypes.h"


#define ATTITUDE_CONTROL_INPUT_TYPE ExtU_px4demo_attitude_control_T
#define ATTITUDE_CONTROL_OUTPUT_TYPE ExtY_px4demo_attitude_control_T
#define INPUT_INSTANCE px4demo_attitude_control_U
#define OUTPUT_INSTANCE px4demo_attitude_control_Y

#define AT_INIT_FUNC px4demo_attitude_control_initialize
#define AT_STEP_FUNC px4demo_attitude_control_step
#define AT_TERM_FUNC px4demo_attitude_control_terminate

#define AT_MODEL_TYPE RT_MODEL_px4demo_attitude_control_T
#define AT_MODEL_INSTANCE px4demo_attitude_control_M

extern ATTITUDE_CONTROL_INPUT_TYPE INPUT_INSTANCE;
extern ATTITUDE_CONTROL_OUTPUT_TYPE OUTPUT_INSTANCE;

volatile boolean_T stopRequested;
volatile boolean_T runModel;

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;

void AC_initAC(){
	  /* Initialize variables */
	  stopRequested = false;
	  runModel = false;
	  //SystemCoreClockUpdate();
	  rtmSetErrorStatus(AT_MODEL_INSTANCE, 0);
	  AT_INIT_FUNC();
	  //ARMCM_SysTick_Config(modelBaseRate);
	  runModel =
	    rtmGetErrorStatus(AT_MODEL_INSTANCE) == (NULL);
}

void AC_oneStep(float roll, float pitch
			  , uint16_t armingControl
			  , uint16_t target_roll, uint16_t target_pitch, uint16_t target_thrust, uint16_t target_yaw)
{
	if(runModel){
		// Input update & check

		/* Check for overrun. Protect OverrunFlag against preemption */
		if (OverrunFlag++) {
			IsrOverrun = 1;
			OverrunFlag--;
			return;
		}

		//  __enable_irq();
		AT_STEP_FUNC();

		/* Get model outputs here */
		//  __disable_irq();
		OverrunFlag--;

	  	stopRequested = !(
	  	                      rtmGetErrorStatus(px4demo_attitude_control_M) == (NULL));
		runModel = !(stopRequested);

	    // Output update
	}
}

// for debug
void AC_printIn(){
	printf("%f, %f, %f, %f, %f, %u, %u, %u, %u, %u\r\n"
			, INPUT_INSTANCE->phi, INPUT_INSTANCE->theta, INPUT_INSTANCE->p, INPUT_INSTANCE->q, INPUT_INSTANCE->r
			, INPUT_INSTANCE->target_thrust, INPUT_INSTANCE->target_roll, INPUT_INSTANCE->target_pitch, INPUT_INSTANCE->target_yaw, INPUT_INSTANCE->armingControl);
}

void AC_printOut(){
	printf("%u, %u, %u, %u, %u, %u \r\n"
			, OUTPUT_INSTANCE->PWM[0], OUTPUT_INSTANCE->PWM[1], OUTPUT_INSTANCE->PWM[2], OUTPUT_INSTANCE->PWM[3], OUTPUT_INSTANCE->PWM[4], OUTPUT_INSTANCE->PWM[5]);
}

#endif /* INC_ATTITUDECONTROLLER_UTIL_H_ */
