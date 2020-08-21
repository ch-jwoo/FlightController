/*
 * ModulePositionController.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Module/ModulePositionController.h>
#include <Utils/Constants.h>
#include <Utils/Functions.h>
#include "Module/ModuleCommander.h"
#include "Usec.h"
#include "cmath"
#include "printf.h"
namespace FC {

ModulePositionController::ModulePositionController() {
	// TODO Auto-generated constructor stub
}

void ModulePositionController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
	msgBus.getLocalPosition(&localPositionSub);

	if(modeFlagSub.flightMode == Command::ControlPosition || modeFlagSub.flightMode == Command::ControlALT){
		setFromRC();
	}
	else{
		setFromAutoController();
	}

	ExtU_positionControl_T input;

	input.set_x = targetX;
	input.set_y = targetY;
	input.set_z = targetZ;
	input.set_yaw = targetYaw;;

	input.estim_dx = localPositionSub.vx;
	input.estim_dy = localPositionSub.vy;
	input.estim_dz = localPositionSub.vz;
	input.estim_x = localPositionSub.x;
	input.estim_y = localPositionSub.y;
	input.estim_z = localPositionSub.z;
	input.estim_yaw = localPositionSub.yaw;

	setExternalInputs(&input);
	step();
	ExtY_positionControl_T output = getExternalOutputs();

	vehicleAttitudeSpPub.timestamp = microsecond();
	vehicleAttitudeSpPub.throttle = output.des_Thrust;


	/* position control mode */
	if(modeFlagSub.flightMode == Command::ControlPosition){
		vehicleAttitudeSpPub.pitch = output.des_pitch;
		vehicleAttitudeSpPub.roll = output.des_roll;
		vehicleAttitudeSpPub.yawRate = output.des_yaw_rate;
	}
	/* alt hold mode */
	else {
		vehicleAttitudeSpPub.pitch = map(controllerSub.pitch, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.roll = map(controllerSub.roll, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.yawRate = map(controllerSub.yaw, 1000, 2000, -1.0, 1.0);
	}
	msgBus.setVehicleAttitueSP(vehicleAttitudeSpPub);
}

void ModulePositionController::setFromRC(){
	static bool throtleStickSet = false;
	static bool yawStickSet = false;
	static bool rollStickSet = false;
	static bool pitchStickSet = false;
	float roll;
	float pitch;

	msgBus.getController(&controllerSub);

	if( 1500 - STICK_THRESHOLD < controllerSub.throttle && controllerSub.throttle < 1500 + STICK_THRESHOLD){
		// set altitude
		if(!throtleStickSet){
			targetZ = localPositionSub.z;
			throtleStickSet = true;
		}
	}
	else{
		targetZ = localPositionSub.z - map(controllerSub.throttle, 1000, 2000, -MAX_VELTICAL, MAX_VELTICAL);
		throtleStickSet = false;
	}

	if( 1500 - STICK_THRESHOLD < controllerSub.yaw && controllerSub.yaw < 1500 + STICK_THRESHOLD){
		// set altitude
		if(!yawStickSet){
			targetYaw = localPositionSub.yaw;
			yawStickSet = true;
		}
	}
	else{
		targetYaw = localPositionSub.yaw + map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);
		targetYaw = radianThreshold(targetYaw);
		yawStickSet = false;
	}

	if(1500 - STICK_THRESHOLD < controllerSub.roll && controllerSub.roll < 1500 + STICK_THRESHOLD){
		if(!rollStickSet){
			roll = 0;
			rollStickSet = true;
		}
	}
	else{
		roll = map(controllerSub.roll, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* roll */
		rollStickSet = false;
	}
	if(1500 - STICK_THRESHOLD < controllerSub.pitch && controllerSub.pitch < 1500 + STICK_THRESHOLD){
		if(!pitchStickSet){
			pitch = 0;
			pitchStickSet = true;
		}
	}
	else{
		pitch = map(controllerSub.pitch, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* pitch */
		pitchStickSet = false;
	}
//	float roll = map(controllerSub.roll, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* roll */
//	float pitch = map(controllerSub.pitch, 1000, 2000, -MAX_HORISION, MAX_HORISION);	/* pitch */
//	targetYaw = map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);

	if( !rollStickSet || !pitchStickSet){
		float cosYaw = cos(localPositionSub.yaw);
		float sinYaw = sin(localPositionSub.yaw);
		targetX = localPositionSub.x + pitch*cosYaw + -roll*sinYaw;
		targetY = localPositionSub.y + pitch*sinYaw + roll*cosYaw;
	}
//	targetZ += localPositionSub.z;
//	targetYaw += localPositionSub.yaw;
}

void ModulePositionController::setFromAutoController(){
	//TODO add struct VehiclePositionSP, convert to target
}

} /* namespace FC */
