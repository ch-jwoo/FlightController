/*
 * ModuleAttitudeController.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include "ModuleAttitudeController.h"
#include <Peripherals/Actuator/Motor.h>
#include <Peripherals/Actuator/Servo.h>
#include <Utils/Functions.h>
#include <Utils/Constants.h>
#include "Usec.h"
#include "printf.h"

namespace FC {

float ModuleAttitudeController::vtolTransitionTHR = 1750.0;
float ModuleAttitudeController::vtolTransitionPhase1Time = 3.0;
//float ModuleAttitudeController::vtolTransitionCpltAirSpeed = 10.0;
float ModuleAttitudeController::vtolTransitionPhase2Time = 2.0;

float ModuleAttitudeController::FW_SERVO_1 = 1000.0;
float ModuleAttitudeController::FW_SERVO_2 = 2000.0;

float ModuleAttitudeController::MC_SERVO_1 = 2000.0;
float ModuleAttitudeController::MC_SERVO_2 = 1000.0;

float ModuleAttitudeController::TRANSITION_SERVO_1 = 1500.0;
float ModuleAttitudeController::TRANSITION_SERVO_2 = 1500.0;

TiltingPhase ModuleAttitudeController::phase = TiltingPhase::MultiCopter;

ModuleAttitudeController::ModuleAttitudeController()
: airframeStatusPub{0, AirframeMode::Multicopter}
, targetRoll(0.0f)
, targetPitch(0.0f)
, targetYawRate(0.0f)
, targetThrottle(0.0f)
, phase1TotalStep(0)
, phase2TotalStep(0)
, phase1Step(0)
, phase2Step(0)
, phase1Ratio(0.0f)
, phase2Ratio(0.0f)
, tiltingRisingThrottle(0)
, tiltingRisingTime(0)
{
}

void ModuleAttitudeController::main(){
	ModuleAttitudeController attitudeController;

	/* 200hz */
	while(1){
		/* check reset command */
		if(osThreadFlagsGet() & AC_reset){
			osThreadFlagsClear(AC_reset);
			attitudeController.MC_px4_AlgorithmModelClass::initialize();
			attitudeController.FW_px4_AlgorithmModelClass::initialize();
		}

		/* transition to multicopter */
		if(osThreadFlagsGet() & AC_transitionMC){
			osThreadFlagsClear(AC_transitionMC);
			phase = TiltingPhase::MultiCopter;
		}

		/* transition to fixed wing */
		if(osThreadFlagsGet() & AC_transitionFW){
			osThreadFlagsClear(AC_transitionFW);
			phase = TiltingPhase::MC2FW_Phase1;
		}

		/* wait AHRS set */
		osThreadFlagsWait(AC_fromAHRS, osFlagsWaitAny, osWaitForever);
		attitudeController.oneStep();
	}
}

void ModuleAttitudeController::oneStep(){
	msgBus.getArmFlag(&armFlagSub);
	msgBus.getModeFlag(&modeFlagSub);

	/* manual control */
	if(modeFlagSub.flightMode == FlightMode::AttitudeControl){
		setFromRC();
	}
	/* position control */
	else{
		setFromPositionController();
	}

	/* tilting logic */
	switch(phase){
	case TiltingPhase::FW2MC_Phase1:
		break;
	case TiltingPhase::FW2MC_Phase2:
		break;
	case TiltingPhase::MC2FW_Phase1:
		if(phase1Step > phase1TotalStep){
			phase = TiltingPhase::MC2FW_Phase2;
		}
		else{
			phase1TotalStep = (uint16_t)(vtolTransitionPhase1Time*AC_TASK_FREQUENCY);
			phase1Step++;
			phase1Ratio = phase1Step/(float)phase1TotalStep;
			s3.setPWM(MC_SERVO_1 + ((TRANSITION_SERVO_1 - MC_SERVO_1)*phase1Ratio));
			s4.setPWM(MC_SERVO_2 + ((TRANSITION_SERVO_2 - MC_SERVO_2)*phase1Ratio));
		}
		break;
	case TiltingPhase::MC2FW_Phase2:
		if(phase2Step > phase2TotalStep){
			phase = TiltingPhase::FixedWing;
			phase1Step = 0;
			phase1Ratio = 0.0f;
			phase2Step = 0;
			phase2Ratio = 0.0f;
		}
		else{
			phase2TotalStep = (uint16_t)(vtolTransitionPhase2Time*AC_TASK_FREQUENCY);
			phase2Step++;
			phase2Ratio = phase2Step/(float)phase2TotalStep;

			s3.setPWM(TRANSITION_SERVO_1 + ((FW_SERVO_1 - TRANSITION_SERVO_1)*phase2Ratio));
			s4.setPWM(TRANSITION_SERVO_2 + ((FW_SERVO_2 - TRANSITION_SERVO_2)*phase2Ratio));
		}
		break;
	case TiltingPhase::FixedWing:
		s3.setPWM((uint16_t)FW_SERVO_1);
		s4.setPWM((uint16_t)FW_SERVO_2);
		airframeStatusPub.airframeMode = AirframeMode::FixedWing;
		break;
	case TiltingPhase::MultiCopter:
		s3.setPWM((uint16_t)MC_SERVO_1);
		s4.setPWM((uint16_t)MC_SERVO_2);
		airframeStatusPub.airframeMode = AirframeMode::Multicopter;
		break;
	default:
		break;
	}
	airframeStatusPub.timestamp = microsecond();
	msgBus.setAirframeStatus(airframeStatusPub);

	/* not armed */
	if(armFlagSub.armMode != ArmMode::Arm){
		m1.setPWM(1000);
		m2.setPWM(1000);
		m3.setPWM(1000);
		m4.setPWM(1000);
		m5.setPWM(1000);
		m6.setPWM(1000);
		return;
	}

	/* attitude controller */
	switch(airframeStatusPub.airframeMode){
	case AirframeMode::Multicopter:
		mcOneStep();
		break;
	case AirframeMode::FixedWing:
		fwOneStep();
		break;
	}

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

//void ModuleAttitudeController::setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6){
//
//}

void ModuleAttitudeController::mcOneStep(){
	MC_px4_AlgorithmModelClass::ExtU_Second_att_control_codeb_T input;
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
	MC_px4_AlgorithmModelClass::setExternalInputs(&input);
	MC_px4_AlgorithmModelClass::step();
	MC_px4_AlgorithmModelClass::ExtY_Second_att_control_codeb_T output = MC_px4_AlgorithmModelClass::getExternalOutputs();


	/* motor pwm */
	m1.setPWM(output.PWM_OUT[0] + (uint16_t)(vtolTransitionTHR - 1500)*phase1Ratio);
	m2.setPWM(output.PWM_OUT[1] );
	m3.setPWM(output.PWM_OUT[2] + (uint16_t)((vtolTransitionTHR - 1500)*phase1Ratio));
	m4.setPWM(output.PWM_OUT[3]);
	m5.setPWM(output.PWM_OUT[4]);
	m6.setPWM(output.PWM_OUT[5]);


	motorPwmPub.timestamp = microsecond();
	motorPwmPub.m1 = output.PWM_OUT[0];
	motorPwmPub.m2 = output.PWM_OUT[1];
	motorPwmPub.m3 = output.PWM_OUT[2];
	motorPwmPub.m4 = output.PWM_OUT[3];
	motorPwmPub.m5 = output.PWM_OUT[4];
	motorPwmPub.m6 = output.PWM_OUT[5];

	s1.setPWM(1500);
	s2.setPWM(1500);

	msgBus.setMotorPWM(motorPwmPub);
}

void ModuleAttitudeController::fwOneStep(){
	msgBus.getAttitude(&attitudeSub);
	msgBus.getBodyAngularVelocity(&bodyAngularVelocitySub);
	msgBus.getStatusFlag(&statusFlagSub);

	FW_px4_AlgorithmModelClass::ExtU_FW_att_control_codeblock_T input;
	/* vehicle state */
	input.Roll = attitudeSub.roll;
	input.Pitch = attitudeSub.pitch;
	input.p = bodyAngularVelocitySub.xyz[0];
	input.q = bodyAngularVelocitySub.xyz[1];
	input.r = bodyAngularVelocitySub.xyz[2];

	/* control */
	input.set_pitch = targetPitch;
	input.set_roll = targetRoll;
	input.set_yaw = targetYawRate;
//	if(statusFlagSub.airspeed){
//		msgBus.getAirSpeed(&airspeedSub);
//		if(airspeedSub.TAS != 0.0f){
//			input.set_yaw = tanf(targetRoll) * cosf(targetPitch) * FC_GRAVITY_ACCEERATION / airspeedSub.TAS;
//		}
//	}
	input.set_thrust = targetThrottle;
//	_rate_setpoint = tanf(constrained_roll) * cosf(ctl_data.pitch) * CONSTANTS_ONE_G / (ctl_data.airspeed


	/* matlab codegen function */
	FW_px4_AlgorithmModelClass::setExternalInputs(&input);
	FW_px4_AlgorithmModelClass::step();
	FW_px4_AlgorithmModelClass::ExtY_FW_att_control_codeblock_T output = FW_px4_AlgorithmModelClass::getExternalOutputs();

	/* set motor pwm */
	m1.setPWM(output.PWM_OUT[0]);
	m2.setPWM(output.PWM_OUT[1]);
	m3.setPWM(output.PWM_OUT[2]);
	m4.setPWM(output.PWM_OUT[3]);

	motorPwmPub.timestamp = microsecond();
	motorPwmPub.m1 = output.PWM_OUT[0];
	motorPwmPub.m2 = output.PWM_OUT[1];
	motorPwmPub.m3 = output.PWM_OUT[2];
	motorPwmPub.m4 = output.PWM_OUT[3]	;
	msgBus.setMotorPWM(motorPwmPub);

	/* set servo pwm */
	s1.setPWM(output.PWM_OUT[4]);
	s2.setPWM(output.PWM_OUT[5]);
//	s3.setPWM(output.PWM_OUT[6]);
//	s3.setPWM(output.PWM_OUT[7]);


	servoPwmPub.timestamp = microsecond();
	servoPwmPub.s1 = output.PWM_OUT[0];
	servoPwmPub.s2 = output.PWM_OUT[1];
	servoPwmPub.s3 = output.PWM_OUT[2];
	servoPwmPub.s3 = output.PWM_OUT[3];
	msgBus.setServoPWM(servoPwmPub);

}

} /* namespace FC */
