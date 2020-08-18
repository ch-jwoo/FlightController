/*
 * ModulePositionController.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Module/ModulePositionController.h>
#include "Module/ModuleCommander.h"
#include "Usec.h"
#include "cmath"
#include "Utils/function.h"
#include "printf.h"
namespace FC {

ModulePositionController::ModulePositionController() {
	// TODO Auto-generated constructor stub

}

void ModulePositionController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
//	if((modeFlagSub.armMode != Command::Arm)
//	 || modeFlagSub.flightMode == Command::ControlAttitude){
//		startFlag = false;
//		return;
//	}

	msgBus.getLocalPosition(&localPositionSub);

	if(modeFlagSub.flightMode == Command::ControlPosition){
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
	vehicleAttitudeSpPub.pitch = output.des_pitch;
	vehicleAttitudeSpPub.roll = output.des_roll;
	vehicleAttitudeSpPub.throttle = output.des_Thrust;
	vehicleAttitudeSpPub.yawRate = output.des_yaw_rate;

	msgBus.setVehicleAttitueSP(vehicleAttitudeSpPub);
}

void ModulePositionController::setFromRC(){
	msgBus.getController(&controllerSub);

	float roll = map(controllerSub.roll, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* roll */
	float pitch = map(controllerSub.pitch, 1000, 2000, -MAX_HORISION, MAX_HORISION);	/* pitch */
	targetYaw = map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);
	targetZ = map(controllerSub.throttle, 1000, 2000, -MAX_VELTICAL, MAX_VELTICAL);

	float cosYaw = cos(localPositionSub.yaw);
	float sinYaw = sin(localPositionSub.yaw);
	targetX = localPositionSub.x + pitch*cosYaw + -roll*sinYaw;
	targetY = localPositionSub.x + pitch*sinYaw + roll*cosYaw;
	targetZ += localPositionSub.z;
	targetYaw += localPositionSub.yaw;

//	printf("%f %f %f %f\r\n", targetX, targetY, targetZ, targetYaw);
}

void ModulePositionController::setFromAutoController(){
	//TODO add struct VehiclePositionSP, convert to target
}



} /* namespace FC */
