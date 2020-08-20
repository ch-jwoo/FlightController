/*
 * ModuleAttitudeController.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Module/ModuleAttitudeController.h>
#include "Usec.h"
#include "Utils/function.h"
#include "printf.h"

namespace FC {

ModuleAttitudeController::ModuleAttitudeController(){}

void ModuleAttitudeController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);

	/* not armed */
	if(modeFlagSub.armMode != Command::Arm){
		setMotor(1000, 1000, 1000, 1000, 1000, 1000);
//		armFlag = false;
		return;
	}

	/* change disarm to arm -> initialize */
//	if(armFlag == false){
//		armFlag = true;
//		initialize();
//	}

	/* manual control */
	if(modeFlagSub.flightMode == Command::ControlAttitude){
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
	targetPitch = map(controllerSub.pitch, 1000, 2000, -1.0, 1.0);
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


//	m7.setPWM(pwm6);
//	m8.setPWM(pwm6);
//	m9.setPWM(pwm6);
//	m10.setPWM(pwm6);
//	m11.setPWM(pwm6);
//	m12.setPWM(pwm6);
//	m13.setPWM(pwm6);
//	m14.setPWM(pwm6);
//	m15.setPWM(pwm6);
//	m16.setPWM(pwm6);
//	m17.setPWM(pwm6);
//	m18.setPWM(pwm6);
//	m19.setPWM(pwm6);
//	m20.setPWM(pwm6);
//	m21.setPWM(pwm6);
//	m22.setPWM(pwm6);
//	m23.setPWM(pwm6);
//	m24.setPWM(pwm6);
//	m25.setPWM(pwm6);


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
