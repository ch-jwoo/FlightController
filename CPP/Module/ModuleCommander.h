/*
 * ModuleCommander.h
 *
 *  Created on: Aug 4, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULECOMMANDER_H_
#define MODULE_MODULECOMMANDER_H_

#include "main.h"
#include "Usec.h"
#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"
#include "queue.h"

namespace FC{

#define CMD_QUEUE_LENGTH 3
#define CMD_QUEUE_ITEM_SIZE sizeof(Command)

enum class CmdResult{
	Denied,
	Changed
};

class ModuleCommander{
public:
	void init();
	void main();

	static bool sendCommand(Command cmd);
private:
//	static StaticQueue_t xQueueBuffer;
//	static uint8_t ucQueueStorage[CMD_QUEUE_LENGTH*CMD_QUEUE_ITEM_SIZE];
//	static QueueHandle_t commandQueue;

	struct ModeFlag modeFlagPub{};

	CmdResult commandHandler(Command cmd);
	CmdResult toAttitude();
	CmdResult toPosition();
	CmdResult toArm();
	CmdResult toDisArm();
};

//uint8_t ModuleCommander::ucQueueStorage[CMD_QUEUE_LENGTH*CMD_QUEUE_ITEM_SIZE];
//QueueHandle_t ModuleCommander::commandQueue = xQueueCreateStatic(CMD_QUEUE_LENGTH,
//																   sizeof(Command),
//																   ucQueueStorage,
//																   &xQueueBuffer);


StaticQueue_t xQueueBuffer;
uint8_t ucQueueStorage[CMD_QUEUE_LENGTH*CMD_QUEUE_ITEM_SIZE];
QueueHandle_t commandQueue = xQueueCreateStatic(CMD_QUEUE_LENGTH,
							   sizeof(Command),
							   ucQueueStorage,
							   &xQueueBuffer);

ModuleCommander moduleCommander;

void ModuleCommander::main(){
	Command rcvCommand;
	if(xQueueReceive(commandQueue, &rcvCommand, portMAX_DELAY)){
		commandHandler(rcvCommand);
	}
}

bool ModuleCommander::sendCommand(Command cmd){
//	if(xQueueSendToBack(commandQueue, &cmd, 0) != pdPASS) return false;
	xQueueSendToBackFromISR( commandQueue, &cmd, NULL );

	return true;
}

CmdResult ModuleCommander::commandHandler(Command cmd){
	switch(cmd){
	case Command::ControlAttitude:
		return toAttitude();
		break;
	case Command::ControlPosition:
//		return toPosition();
		break;
	case Command::AutoWaypoint:
		break;
	case Command::AutoRTL:
		break;
	case Command::AutoTakeoff:
		break;
	case Command::AutoLand:
		break;

	case Command::Arm:
		return toArm();
		break;
	case Command::DisArm:
		return toDisArm();
		break;
	}
	return CmdResult::Denied;
}

CmdResult ModuleCommander::toAttitude(){
//	msgBus.setFlightMode(FlightMode::ControlAttitude);
}

CmdResult ModuleCommander::toArm(){
	struct ModeFlag modeFlag;
	msgBus.getModeFlag(&modeFlag);
	modeFlag.timestamp = microsecond();
	modeFlag.armMode = Command::Arm;
	msgBus.setModeFlag(modeFlag);
}

CmdResult ModuleCommander::toDisArm(){
	struct ModeFlag modeFlag;
	msgBus.getModeFlag(&modeFlag);
	modeFlag.timestamp = microsecond();
	modeFlag.armMode = Command::DisArm;
	msgBus.setModeFlag(modeFlag);
}

}


#endif /* MODULE_MODULECOMMANDER_H_ */
