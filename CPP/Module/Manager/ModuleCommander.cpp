/*
 * ModuleCommander.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Interface/Interface.h>
#include <Module/Manager/ModuleCommander.h>
#include <Module/Controller/ModulePositionController.h>
#include <MsgBus/MsgType.h>
#include <Peripherals/Actuator/Motor.h>

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
	sensorBaro.setSeaLevelPressure(26.0); /* inha univ. altitude */
	sensorBaro.setRefAltitude();
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
	case Command::ControlPosition:
		return toPosition(cmd);
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

	case Command::Arm:
		return toArm();
		break;
	case Command::DisArm:
		return toDisArm();
		break;

	case Command::MotorCalibration:
		return toMotorCalibration();
		break;
	}
	return false;
}

bool ModuleCommander::toAttitude(){
	//TODO change to attitude control
	/*
	 * check condition of attitude control
	 */


	resetController();
	/* change to attitude */
	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = Command::ControlAttitude;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask();

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toPosition(Command cmd){
	//TODO check condition of position controller

	/* set position controller */
	ModulePositionController::setSignal(PC_start);
	if(!(osThreadFlagsWait(CMD_ACK, osFlagsWaitAny, 500) & CMD_ACK)){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false;
	}

	/* reset */
	resetController();

	/* mode set */
	modeFlagPub.timestamp = microsecond();
	modeFlagPub.flightMode = cmd;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask();

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
}

bool ModuleCommander::toWaypoint(){
	//TODO change to waypoint autopilot
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

bool ModuleCommander::toArm(){
	//TODO check arm condition

	/* toArm condition */
	msgBus.getController(&controllerSub);
	if(controllerSub.throttle > 1050){
		ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
		return false; /* can't arm */
	}

	/* arm initialize */
	interfaceAccel.setBias();
	interfaceGyro.setBias();
	sensorBaro.setRefAltitude();
	resetController();
	osDelay(150);					/* wait sensor calibration */

	modeFlagPub.timestamp = microsecond();
	modeFlagPub.armMode = Command::Arm;
	msgBus.setModeFlag(modeFlagPub);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
	return true;
}

bool ModuleCommander::toDisArm(){
	//TODO check DisArm condition
//	struct MotorPWM pwm;
	/* disarm condition check */
//	msgBus.getMotorPWM(&pwm);
//	if(pwm.m1 > DISARM_PWM && pwm.m2 > DISARM_PWM && pwm.m3 > DISARM_PWM &&
//	   pwm.m4 > DISARM_PWM && pwm.m5 > DISARM_PWM && pwm.m6 > DISARM_PWM){
//		/* can't disarm */
//
//	}

	modeFlagPub.timestamp = microsecond();
	modeFlagPub.armMode = Command::DisArm;
	msgBus.setModeFlag(modeFlagPub);

	stopTheOtherTask();

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
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

bool ModuleCommander::stopTheOtherTask(){
	switch(modeFlagPub.flightMode){
	case Command::ControlAttitude:
		ModulePositionController::setSignal(PC_stop);
	case Command::ControlPosition:
	case Command::ControlALT:
		//TODO stop auto controller
	case Command::AutoWaypoint:
		//??
		break;
	}
}

void ModuleCommander::resetController(){
	switch(modeFlagPub.flightMode){
	case Command::AutoWaypoint:
		//TODO initialize auto controller
		/* not break */
	case Command::ControlPosition:
	case Command::ControlALT:
		ModulePositionController::setSignal(PC_reset);
		/* not break */
	case Command::ControlAttitude:
		ModuleAttitudeController::setSignal(AC_reset);
		break;
	}
}

} /* namespace FC */

