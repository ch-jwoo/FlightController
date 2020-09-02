/*
 * ModuleAttitudeController.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include "ModuleAttitudeController.h"
#include <Utils/Functions.h>
#include "Usec.h"
#include "printf.h"

namespace FC {

ModuleAttitudeController::ModuleAttitudeController(){}

void ModuleAttitudeController::main(){
	ModuleAttitudeController attitudeController;
	while(1){
		/* check reset command */
		if(osThreadFlagsGet() & AC_reset){
			osThreadFlagsClear(AC_reset);
			attitudeController.initialize();
		}

		/* wait AHRS set */
		osThreadFlagsWait(AC_fromAHRS, osFlagsWaitAny, osWaitForever);
		attitudeController.oneStep();
	}
}

void ModuleAttitudeController::oneStep(){
	msgBus.getArmFlag(&armFlagSub);
	msgBus.getModeFlag(&modeFlagSub);

	/* not armed */
	if(armFlagSub.armMode != ArmMode::Arm){
		setMotor(1000, 1000, 1000, 1000, 1000, 1000);
		return;
	}

	/* manual control */
	if(modeFlagSub.flightMode == FlightMode::AttitudeControl){
		setFromRC();
	}
	/* position control */
	else{
		setFromPositionController();
	}

	ExtU_Second_att_control_codeb_T input;
	input.set_pitch = targetPitch;
	input.set_roll = targetRoll;
	input.set_yaw = targetYawRate;
	input.set_thrust = targetThrottle;

	msgBus.getAttitude(&attitudeSub);
	msgBus.getBodyAngularVelocity(&bodyAngularVelocitySub);

	input.Roll = attitudeSub.roll;
	input.Pitch = attitudeSub.pitch;
	input.p = bodyAngularVelocitySub.xyz[0];
	input.q = bodyAngularVelocitySub.xyz[1];
	input.r = bodyAngularVelocitySub.xyz[2];

	/* matlab codegen function */
	setExternalInputs(&input);
	step();
	ExtY_Second_att_control_codeb_T output = getExternalOutputs();

	/* set motor pwm */
	setMotor((uint16_t)output.PWM_OUT[0],
			 (uint16_t)output.PWM_OUT[1],
			 (uint16_t)output.PWM_OUT[2],
			 (uint16_t)output.PWM_OUT[3],
			 (uint16_t)output.PWM_OUT[4],
			 (uint16_t)output.PWM_OUT[5]);


	freqCount();
}

void ModuleAttitudeController::setFromPositionController(){
	msgBus.getVehicleAttitueSP(&vehicleAttitudeSpSub);
	targetRoll = vehicleAttitudeSpSub.roll;
	targetPitch = vehicleAttitudeSpSub.pitch;
	targetYawRate = vehicleAttitudeSpSub.yawRate;
	targetThrottle = vehicleAttitudeSpSub.throttle;
}

void ModuleAttitudeController::setFromRC(){
	msgBus.getController(&controllerSub);
//	targetRoll = (float)(controllerSub.roll - 1500)/500.0;				/* map 1000~2000 to -1 ~ 1 */
//	targetPitch = -(float)(controllerSub.pitch - 1500)/500.0;			/* map 1000~2000 to -1 ~ 1 */
//	targetYawRate = (float)(controllerSub.yaw - 1500)/500.0;			/* map 1000~2000 to -1 ~ 1 */
//	targetThrottle = (float)(controllerSub.throttle - 1000)/1000.0;		/* map 1000~2000 to 0 ~ 1 */
	targetRoll = map(controllerSub.roll, 1000, 2000, -1.0, 1.0);
	targetPitch = -map(controllerSub.pitch, 1000, 2000, -1.0, 1.0);
	targetYawRate = map(controllerSub.yaw, 1000, 2000, -1.0, 1.0);
	targetThrottle = map(controllerSub.throttle, 1000, 2000, 0.0, 1.0);
}

void ModuleAttitudeController::setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6){
	m1.setPWM(pwm1);
	m2.setPWM(pwm2);
	m3.setPWM(pwm3);
	m4.setPWM(pwm4);
	m5.setPWM(pwm5);
	m6.setPWM(pwm6);

	motorPwmPub.timestamp = microsecond();
	motorPwmPub.m1 = pwm1;
	motorPwmPub.m2 = pwm2;
	motorPwmPub.m3 = pwm3;
	motorPwmPub.m4 = pwm4;
	motorPwmPub.m5 = pwm5;
	motorPwmPub.m6 = pwm6;

	msgBus.setMotorPWM(motorPwmPub);
}

} /* namespace FC */
