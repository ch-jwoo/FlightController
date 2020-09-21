/*
 * RC.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */


#include <Interface/InterfaceRC.h>
#include "Module/Etc/ModuleBuzzer.h"

namespace FC{

enum{
	RC_PREV_ATTITUDE,
	RC_PREV_ALTITUDE,
	RC_PREV_POSITION,
	RC_PREV_AUTOWAYPOINT,
	RC_PREV_AUTORTL,
};

InterfaceRC interfaceRC;

void InterfaceRC::setRC(uint16_t roll, uint16_t pitch, uint16_t yaw, uint16_t throttle,
    		   uint16_t armming,
			   uint16_t mode)
{
	static uint16_t prevArmming = 1000;
	static uint8_t curMode = 0;

	if(start == false){
		if(throttle > MOTOR_CALIBRATION_THROTLE)
			ModuleCommander::sendCommand(Command::MotorCalibration);

		if(armming > ARMING_THRESHOLD){
			ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
			return;
		}
	}
	start = true;

	/* cotnroller publish */
	this->controllerPub.timestamp = microsecond();
	this->controllerPub.roll = roll;
	this->controllerPub.pitch = pitch;
	this->controllerPub.yaw = yaw;
	this->controllerPub.throttle = throttle;
	msgBus.setController(this->controllerPub);

	msgBus.getArmFlag(&armFlagSub);							/* current arm mode */
	msgBus.getModeFlag(&modeFlagSub);							/* current arm mode */

	/* current arming */
	if(prevArmming > ARMING_THRESHOLD){
		/* disarm command */
		if(armming < ARMING_THRESHOLD){
			ModuleCommander::sendCommand(Command::DisArm);
		}
	}
	/* current disArm */
	else{
		/* arm command */
		if(armming > ARMING_THRESHOLD){
			ModuleCommander::sendCommand(Command::Arm);
		}
	}

	if(mode > FLIGHT_ATTITUDE_MODE_THRSHOLD){
		if(curMode != RC_PREV_ATTITUDE){
			ModuleCommander::sendCommand(Command::ControlAttitude); /* send command */
			curMode = RC_PREV_ATTITUDE;
		}
	}
	else if(mode > FLIGHT_POSITION_MODE_THRSHOLD){
		if(curMode != RC_PREV_POSITION){
			ModuleCommander::sendCommand(Command::ControlPosition); /* send command */
			curMode = RC_PREV_POSITION;
		}
	}
	else if(mode > FLIGHT_AUTO_MODE_THRSHOLD){ /* FLIGHT_AUTO_MODE_THRSHOLD */
		if(curMode != RC_PREV_AUTOWAYPOINT){
			ModuleCommander::sendCommand(Command::AutoWaypoint); /* send command */
			curMode = RC_PREV_AUTOWAYPOINT;
		}
	}
	else if(mode > FLIGHT_RTL_MODE_THRSHOLD){
		if(curMode != RC_PREV_AUTORTL){
			ModuleCommander::sendCommand(Command::AutoRTL); /* send command */
			curMode = RC_PREV_AUTORTL;
		}
	}
	else if(mode > FLIGHT_ALT_MODE_THRSHOLD){
		if(curMode != RC_PREV_ALTITUDE){
			ModuleCommander::sendCommand(Command::ControlALT); /* send command */
			curMode = RC_PREV_ALTITUDE;
		}
	}

	prevArmming = armming;

	/* Freq class variable */
	freqCount();
}
}
