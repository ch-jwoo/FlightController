/*
 * RC.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */


#include <Interface/InterfaceRC.h>

namespace FC{

InterfaceRC interfaceRC;

void InterfaceRC::setRC(uint16_t roll, uint16_t pitch, uint16_t yaw, uint16_t throttle,
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

	msgBus.getArmFlag(&armFlagSub);							/* current arm mode */
	msgBus.getModeFlag(&modeFlagSub);							/* current arm mode */

	/* current arming */
	if(armFlagSub.armMode == ArmMode::Arm){
		/* disarm command */
		if(armming < ARMING_THRESHOLD && millisecond()-lastArmReq > 500){
			ModuleCommander::sendCommand(Command::DisArm);
			lastArmReq = millisecond();
		}
	}
	/* current disArm */
	else{
		/* arm command */
		if(armming > ARMING_THRESHOLD && millisecond()-lastArmReq > 500){
			ModuleCommander::sendCommand(Command::Arm);
			lastArmReq = millisecond();
		}
	}

	if(millisecond() - lastModeReq > 500){
		if(mode > FLIGHT_ATTITUDE_MODE_THRSHOLD){
			if(modeFlagSub.flightMode != FlightMode::AttitudeControl){
				ModuleCommander::sendCommand(Command::ControlAttitude); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_POSITION_MODE_THRSHOLD){
			if(modeFlagSub.flightMode != FlightMode::PositionControl){
				ModuleCommander::sendCommand(Command::ControlPosition); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_AUTO_MODE_THRSHOLD){ /* FLIGHT_AUTO_MODE_THRSHOLD */
			if(modeFlagSub.flightMode != FlightMode::AutoWaypoint){
				ModuleCommander::sendCommand(Command::ControlPosition); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_RTL_MODE_THRSHOLD){
			if(modeFlagSub.flightMode != FlightMode::AutoRTL){
				ModuleCommander::sendCommand(Command::AutoRTL); /* send command */
				lastModeReq = millisecond();
			}
		}
		else if(mode > FLIGHT_ALT_MODE_THRSHOLD){
			if(modeFlagSub.flightMode != FlightMode::AltitudeControl){
				ModuleCommander::sendCommand(Command::ControlALT); /* send command */
				lastModeReq = millisecond();
			}
		}
	}

	/* Freq class variable */
	freqCnt++;
}
}
