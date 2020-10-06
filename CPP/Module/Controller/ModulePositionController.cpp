/*
 * ModulePositionController.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Module/Controller/ModulePositionController.h>
#include <Utils/Constants.h>
#include <Utils/Functions.h>
#include <Module/Manager/ModuleCommander.h>
#include "Usec.h"
#include "cmath"

namespace FC {

ModulePositionController::ModulePositionController() {
	// TODO Auto-generated constructor stub
}

void ModulePositionController::main(){
	uint8_t firstLoop;
	ModulePositionController positionController;
	while(1){
		firstLoop = 0;
		/* wait position controller start */
		osThreadFlagsWait(PC_start, osFlagsWaitAny, osWaitForever);
		osThreadFlagsClear(PC_reset | PC_stop | PC_start);
		while(1){
			/* if first loop or reset command, initialize */
			if(osThreadFlagsGet() & PC_reset){
				osThreadFlagsClear(PC_reset);
				positionController.initialize();
			}

			/* wait EKF data */
			osThreadFlagsWait(PC_fromEKF, osFlagsWaitAny, osWaitForever);
			positionController.oneStep();

			/* check position controller stop */
			if(osThreadFlagsGet() & PC_stop){
				osThreadFlagsClear(PC_stop);
				break;
			}

			/* if first loop, send ACK */
			if(firstLoop < 2){
				firstLoop++;
			}
			else if(firstLoop == 2){
				ModuleCommander::sendSignal(CMD_ACK);
				firstLoop++;
			}
		}
	}
}

void ModulePositionController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
	msgBus.getLocalPosition(&localPositionSub);

	if(modeFlagSub.flightMode == FlightMode::PositionControl || modeFlagSub.flightMode == FlightMode::AltitudeControl){
		setFromRC();
	}
	else{
		setFromAutoController();
	}

	positionControlModelClass::ExtU_positionControl_T input;

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

	positionControlModelClass::setExternalInputs(&input);
	positionControlModelClass::step();
	positionControlModelClass::ExtY_positionControl_T output = getExternalOutputs();

	vehicleAttitudeSpPub.timestamp = microsecond();
	vehicleAttitudeSpPub.throttle = output.des_Thrust;

	/* position control mode */
	if(modeFlagSub.flightMode == FlightMode::PositionControl){
		vehicleAttitudeSpPub.pitch = output.des_pitch;
		vehicleAttitudeSpPub.roll = output.des_roll;
		vehicleAttitudeSpPub.yawRate = output.des_yaw_rate;
	}
	/* alt hold mode */
	else {
		vehicleAttitudeSpPub.pitch = -map(controllerSub.pitch, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.roll = map(controllerSub.roll, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.yawRate = map(controllerSub.yaw, 1000, 2000, -1.0, 1.0);
	}

	msgBus.setVehicleAttitueSP(vehicleAttitudeSpPub);

	freqCount();
}

void ModulePositionController::setFromRC(){
	static bool throtleStickSet = false;
	static bool yawStickSet = false;
	static bool rollStickSet = false;
	static bool pitchStickSet = false;
	float roll;
	float pitch;

	msgBus.getController(&controllerSub);

	/* throtle stick */
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

	/* yaw stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.yaw && controllerSub.yaw < 1500 + STICK_THRESHOLD){
		// set altitude
		if(!yawStickSet){
			targetYaw = localPositionSub.yaw;
			yawStickSet = true;
		}
	}
	else{
		targetYaw = localPositionSub.yaw + map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);
		targetYaw = radianThreshold(targetYaw, -FC_PI, FC_PI);
		yawStickSet = false;
	}

	/* roll stick */
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

	/* pitch stick */
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

	if( !rollStickSet || !pitchStickSet){
		float cosYaw = cos(localPositionSub.yaw);
		float sinYaw = sin(localPositionSub.yaw);
		targetX = localPositionSub.x + pitch*cosYaw + -roll*sinYaw;
		targetY = localPositionSub.y + pitch*sinYaw + roll*cosYaw;
	}
}

void ModulePositionController::setFromAutoController(){
	//TODO add struct VehiclePositionSP, convert to target
	msgBus.getVehiclePositionSP(&vehiclePositionSpSub);
	targetX = vehiclePositionSpSub.x;
	targetY = vehiclePositionSpSub.y;
	targetYaw = vehiclePositionSpSub.yaw;
	targetZ = vehiclePositionSpSub.z;
}

} /* namespace FC */
