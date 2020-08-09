/*
 * ModuleAttitudeController.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Module/ModuleAttitudeController.h>
#include "Usec.h"

namespace FC {


void ModuleAttitudeController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
	if(modeFlagSub.armMode != Command::Arm) return;

	if(modeFlagSub.flightMode == Command::ControlAttitude){
		setFromRC();
	}
	else{
		setFromPositionController();
	}

	Second_att_control_codeblock__U.set_pitch = targetPitch;
	Second_att_control_codeblock__U.set_roll = targetRoll;
	Second_att_control_codeblock__U.set_yaw = targetYawRate;
	Second_att_control_codeblock__U.set_thrust = throttle;

	msgBus.getAttitude(&attitudeSub);
	msgBus.getBodyAngularVelocity(&bodyAngularVelocitySub);

	Second_att_control_codeblock__U.Roll = attitudeSub.roll;
	Second_att_control_codeblock__U.Pitch = attitudeSub.pitch;
	Second_att_control_codeblock__U.p = bodyAngularVelocitySub.xyz[0];
	Second_att_control_codeblock__U.q = bodyAngularVelocitySub.xyz[1];
	Second_att_control_codeblock__U.r = bodyAngularVelocitySub.xyz[2];

	Second_att_control_codeblock_fly_step();

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
