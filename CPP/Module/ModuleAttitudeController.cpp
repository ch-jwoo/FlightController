/*
 * ModuleAttitudeController.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Module/ModuleAttitudeController.h>
#include "Usec.h"

namespace FC {

ModuleAttitudeController::ModuleAttitudeController(){
	/* matlab codegen function */
	initialize();
}

void ModuleAttitudeController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
	if(modeFlagSub.armMode != Command::Arm) return;

	if(modeFlagSub.flightMode == Command::ControlAttitude){
		setFromRC();
	}
	else{
		setFromPositionController();
	}

	ExtU_Second_att_control_codeb_T input;
	input.set_pitch = targetPitch;
	input.set_roll = targetRoll;
	input.set_yaw = targetYawRate;
	input.set_thrust = throttle;

	msgBus.getAttitude(&attitudeSub);
	msgBus.getBodyAngularVelocity(&bodyAngularVelocitySub);

	input.Roll = attitudeSub.roll;
	input.Pitch = attitudeSub.pitch;
	input.p = bodyAngularVelocitySub.xyz[0];
	input.q = bodyAngularVelocitySub.xyz[1];
	input.r = bodyAngularVelocitySub.xyz[2];
	input.Arm_cmd = 2000;

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
}

void ModuleAttitudeController::setFromPositionController(){
	//TODO make position control struct, and this function
}

void ModuleAttitudeController::setFromRC(){
	msgBus.getController(&controllerSub);
	targetRoll = (controllerSub.roll - 1500)/500;
	targetPitch = -(controllerSub.pitch - 1500)/500;
	targetYawRate = (controllerSub.yaw - 1500)/500;
	throttle = controllerSub.throttle;
}

void ModuleAttitudeController::setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6){
	m1.setPWM(pwm1);
	m2.setPWM(pwm2);
	m3.setPWM(pwm3);
	m4.setPWM(pwm4);
	m5.setPWM(pwm5);
	m6.setPWM(pwm6);

	motorPwmSub.timestamp = microsecond();
	motorPwmSub.m1 = pwm1;
	motorPwmSub.m2 = pwm2;
	motorPwmSub.m3 = pwm3;
	motorPwmSub.m4 = pwm4;
	motorPwmSub.m5 = pwm5;
	motorPwmSub.m6 = pwm6;

	msgBus.setMotorPWM(motorPwmSub);
}

} /* namespace FC */
