/*
 * ModuleCommander.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Module/ModuleCommander.h>
#include <MsgBus/MsgType.h>
#include "Actuator/Motor.h"

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

bool ModuleCommander::commandHandler(Command cmd){
	switch(cmd){
	case Command::ControlAttitude:
		return toAttitude();
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
	//TODO change to attitude controll
	/*
	 * check condition of attitude control
	 */
}

bool ModuleCommander::toPosition(){
	//TODO change to position controll
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
	struct Controller ctl;

	/* toArm condition */
	//TODO denied buzz
	msgBus.getController(&ctl);
	if(ctl.throttle > 1050) return false; /* can't arm */


	struct ModeFlag modeFlag;
	msgBus.getModeFlag(&modeFlag);
	modeFlag.timestamp = microsecond();
	modeFlag.armMode = Command::Arm;
	msgBus.setModeFlag(modeFlag);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
}

bool ModuleCommander::toDisArm(){
	//TODO check DisArm condition
	struct ModeFlag modeFlag;
	struct MotorPWM pwm;

	/* disarm condition check */
	//TODO disarm condition
//	msgBus.getMotorPWM(&pwm);
//	if(pwm.m1 > DISARM_PWM && pwm.m2 > DISARM_PWM && pwm.m3 > DISARM_PWM &&
//	   pwm.m4 > DISARM_PWM && pwm.m5 > DISARM_PWM && pwm.m6 > DISARM_PWM){
//		/* can't disarm */
//
//	}

	msgBus.getModeFlag(&modeFlag);
	modeFlag.timestamp = microsecond();
	modeFlag.armMode = Command::DisArm;
	msgBus.setModeFlag(modeFlag);

	ModuleBuzzer::sendCommand(BuzzerCommand::Success);
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

} /* namespace FC */

