/*
 * ModuleCommander.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Interface/Interface.h>
#include <Module/Manager/ModuleCommander.h>
#include <Module/Controller/ModulePositionController.h>
#include "Module/Controller/ModuleAutoController.h"
#include <MsgBus/MsgType.h>
#include <Peripherals/Actuator/Motor.h>
#include "printf.h"

namespace FC{

typedef StaticQueue_t osStaticMessageQDef_t;

/* Definitions for Command_Queue */
osMessageQueueId_t Commander_QueueHandle;
uint8_t Commander_QueueBuffer[ 3 * sizeof( Command ) ];
osStaticMessageQDef_t Commander_QueueControlBlock;
const osMessageQueueAttr_t Commander_Queue_attributes = {
  .name = "Commander_Queue",
  .attr_bits = 0,
  .cb_mem = &Commander_QueueControlBlock,
  .cb_size = sizeof(Commander_QueueControlBlock),
  .mq_mem = &Commander_QueueBuffer,
  .mq_size = sizeof(Commander_QueueBuffer)
};

ModuleCommander::ModuleCommander(){
	  /* creation of Command_Queue */
	  Commander_QueueHandle = osMessageQueueNew (3, sizeof(Command), &Commander_Queue_attributes);
}

void ModuleCommander::main(){
	ModuleCommander moduleCommander;

	osDelay(1500);
	interfaceAccel.setBias();
	interfaceGyro.setBias();
	interfaceBaro.setSeaLevelPressure(26.0); /* inha univ. altitude */
	interfaceBaro.setRefAltitude();
	osDelay(500);

	while(1){
		Command rcvCommand;
		if(osMessageQueueGet(Commander_QueueHandle, (void*)&rcvCommand, NULL, osWaitForever) == osOK){
			moduleCommander.commandHandler(rcvCommand);
		}
	}
}

bool ModuleCommander::sendCommand(Command cmd){
	if(osMessageQueueGetSpace(Commander_QueueHandle) != 0){
		osMessageQueuePut(Commander_QueueHandle, (void*)&cmd, 0, 0);
		return true;
	}
	return false;
}

void ModuleCommander::sendSignal(enum CmdSignal signal){
	osThreadFlagsSet(Commander_TaskHandle, signal);
}

bool ModuleCommander::commandHandler(Command cmd){
	switch(cmd){
	case Command::ControlAttitude:
		return toAttitude();
		break;
	case Command::ControlALT:
		return toAltitude();
		break;
	case Command::ControlPosition:
		return toPosition();
		break;
	case Command::AutoWaypoint:
		return toWaypoint();
		break;
	case Command::AutoRTL:
		return toRTL();
		break;
	case Command::AutoTakeoff:
		return toTakeoff();
		break;
	case Command::AutoLand:
		return toLand();
		break;

	case Command::AutoTransitionMC:
		return toMulticopter();
		break;
	case Command::AutoTransitionFW:
		return toFixedWing();
		break;

	case Command::Arm:
		return toArm();
		break;
	case Command::DisArm:
		return toDisArm();
		break;

	case Command::MotorCalibration:
		return toMotorCalibration();
		break;

	default:
		return false;
	}
}

bool ModuleCommander::toAttitude(){
	msgBus.getStatusFlag(&statusFlagSub);
	if(!statusFlagSub.attitudeCTL){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false;
	}

	resetController(FlightMode::AttitudeControl);
	/* change to attitude */
	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = FlightMode::AttitudeControl;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask(FlightMode::AttitudeControl);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toAltitude(){
	msgBus.getStatusFlag(&statusFlagSub);
	if(!statusFlagSub.altitudeCTL){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false;
	}

	msgBus.getModeFlag(&modeFlagSub);

	/* if not altitude and position control, task start */
	if(modeFlagSub.flightMode != FlightMode::AltitudeControl
	&& modeFlagSub.flightMode != FlightMode::PositionControl){
		ModulePositionController::setSignal(PC_start);
		if(!(osThreadFlagsWait(CMD_ACK, osFlagsWaitAny, 500) & CMD_ACK)){
			ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
			return false;
		}
	}

	resetController(FlightMode::AltitudeControl);

	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = FlightMode::AltitudeControl;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask(FlightMode::AltitudeControl);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toPosition(){
	msgBus.getStatusFlag(&statusFlagSub);
	if(!statusFlagSub.positionCTL){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false;
	}

	msgBus.getModeFlag(&modeFlagSub);
	//TODO check condition of position controller

	/* if not altitude and position control, task start */
	if(modeFlagSub.flightMode == FlightMode::AttitudeControl){
		ModulePositionController::setSignal(PC_start);
		if(!(osThreadFlagsWait(CMD_ACK, osFlagsWaitAny, 500) & CMD_ACK)){
			ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
			return false;
		}
	}

	/* reset */
	resetController(FlightMode::PositionControl);

	/* mode set */
	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = FlightMode::PositionControl;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask(FlightMode::PositionControl);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toWaypoint(){
	//TODO check condition of autoWaypoint

	ModuleAutoController::start(FlightMode::AutoWaypoint);
	if(!(osThreadFlagsWait(CMD_ACK, osFlagsWaitAny, 1000) & CMD_ACK)){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false;
	}

	/* reset */
	resetController(FlightMode::AutoWaypoint);

	/* mode set */
	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = FlightMode::AutoWaypoint;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask(FlightMode::AutoWaypoint);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toRTL(){
	//TODO change to auto RTL
}

bool ModuleCommander::toTakeoff(){
	//TODO change to auto takeoff
}

bool ModuleCommander::toLand(){
	//TODO change to auto land
}


bool ModuleCommander::toMulticopter(){
	ModuleAttitudeController::setSignal(AC_transitionMC);
	return true;
}

bool ModuleCommander::toFixedWing(){
	ModuleAttitudeController::setSignal(AC_transitionFW);
	return true;
}

bool ModuleCommander::toArm(){
	msgBus.getController(&controllerSub);
	msgBus.getModeFlag(&modeFlagSub);
	//TODO check arm condition
	/* toArm condition */
	if(controllerSub.throttle > 1050){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false; /* can't arm */
	}

	/* arm initialize */
	resetController(modeFlagSub.flightMode);
	osDelay(150);					/* wait sensor calibration */

	armFlagPub.timestamp = microsecond();
	armFlagPub.armMode = ArmMode::Arm;
	msgBus.setArmFlag(armFlagPub);

	ModuleBuzzer::sendCommand(BuzzerCommand::Armed);
	return true;
}

bool ModuleCommander::toDisArm(){
	msgBus.getModeFlag(&modeFlagPub);
	//TODO check DisArm condition
//	struct MotorPWM pwm;
	/* disarm condition check */
//	msgBus.getMotorPWM(&pwm);
//	if(pwm.m1 > DISARM_PWM && pwm.m2 > DISARM_PWM && pwm.m3 > DISARM_PWM &&
//	   pwm.m4 > DISARM_PWM && pwm.m5 > DISARM_PWM && pwm.m6 > DISARM_PWM){
//		/* can't disarm */
//
//	}

	armFlagPub.timestamp = microsecond();
	armFlagPub.armMode = ArmMode::DisArm;
	msgBus.setArmFlag(armFlagPub);

	stopTheOtherTask(modeFlagPub.flightMode);

	ModuleBuzzer::sendCommand(BuzzerCommand::DisArmed);
	return true;
}

bool ModuleCommander::toMotorCalibration(){
	osKernelLock();

	struct Controller ctl;

	while(1){
		msgBus.getController(&ctl);

		m1.setPWM(ctl.throttle);
		m2.setPWM(ctl.throttle);
		m3.setPWM(ctl.throttle);
		m4.setPWM(ctl.throttle);
		m5.setPWM(ctl.throttle);
		m6.setPWM(ctl.throttle);
	}
	osKernelUnlock();
}

bool ModuleCommander::stopTheOtherTask(FlightMode flightMode){
	switch(flightMode){
	case FlightMode::AttitudeControl:
		ModulePositionController::setSignal(PC_stop);
	case FlightMode::AltitudeControl:
	case FlightMode::PositionControl:
		ModuleAutoController::setSignal(AUTO_stop);
	case FlightMode::AutoWaypoint:
		//??
	default:
		break;
	}
}

void ModuleCommander::resetController(FlightMode flightMode){
	switch(flightMode){
	case FlightMode::AutoWaypoint:
		ModuleAutoController::setSignal(AUTO_reset);
		/* not break */
	case FlightMode::PositionControl:
	case FlightMode::AltitudeControl:
		ModulePositionController::setSignal(PC_reset);
		/* not break */
	case FlightMode::AttitudeControl:
		ModuleAttitudeController::setSignal(AC_reset);
	default:
		break;
	}
}

} /* namespace FC */

