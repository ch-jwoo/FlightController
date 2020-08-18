/*
 * RC.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */


#include "RC.h"

namespace FC{

RC rc;

void RC::setRC(uint16_t roll, uint16_t pitch, uint16_t yaw, uint16_t throttle,
    		   uint16_t armming,
			   uint16_t mode)
{
	if(start == false && throttle > MOTOR_CALIBRATION_THROTLE){
		ModuleCommander::sendCommand(Command::MotorCalibration);
	}
	start = true;

	/* cotnroller publish */
	this->controllerPub.timestamp = microsecond();
	this->controllerPub.roll = roll;
	this->controllerPub.pitch = pitch;
	this->controllerPub.yaw = yaw;
	this->controllerPub.throttle = throttle;
	msgBus.setController(this->controllerPub);

	/* arming */
	struct ModeFlag modeFlag;
	msgBus.getModeFlag(&modeFlag);							/* current arm mode */
	Command rcvArmFlag = Command::DisArm;						/* request arm mode */
	if( armming > ARMING_THRESHOLD ) rcvArmFlag = Command::Arm;
	if(modeFlag.armMode != rcvArmFlag && millisecond()-lastArmReq > 500){
		ModuleCommander::sendCommand(rcvArmFlag); /* send command */
		lastArmReq = millisecond();
	}

	if(millisecond() - lastModeReq > 500){
		if(mode > FLIGHT_ATTITUDE_MODE_THRSHOLD){
			if(modeFlag.flightMode != Command::ControlAttitude){
				ModuleCommander::sendCommand(Command::ControlAttitude); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_POSITION_MODE_THRSHOLD){
			if(modeFlag.flightMode != Command::ControlPosition){
				ModuleCommander::sendCommand(Command::ControlPosition); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_AUTO_MODE_THRSHOLD){ /* FLIGHT_AUTO_MODE_THRSHOLD */
			if(modeFlag.flightMode != Command::AutoWaypoint){
				ModuleCommander::sendCommand(Command::ControlPosition); /* send command */
				lastModeReq = millisecond();
			}
		}
	}

	/* Freq class variable */
	freqCnt++;
}
}
