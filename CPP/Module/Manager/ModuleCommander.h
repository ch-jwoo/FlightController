/*
 * ModuleCommander.h
 *
 *  Created on: Aug 4, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULECOMMANDER_H_
#define MODULE_MODULECOMMANDER_H_

#include <Module/Etc/ModuleBuzzer.h>
#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "main.h"
#include "Usec.h"
#include "cmsis_os.h"


namespace FC{

extern osMessageQueueId_t Commander_QueueHandle;

/* command for commander */
enum class Command{
	ControlAttitude,
	ControlALT,
	ControlPosition,

	AutoWaypoint,
	AutoRTL,
	AutoTakeoff,
	AutoLand,
	AutoTransitionMC,
	AutoTransitionFW,

	Arm,
	DisArm,

	MotorCalibration
};

enum CmdSignal {
	CMD_ACK = 0x01,
	CMD_NACK = 0x02
};

class ModuleCommander{
public:

	/*
	 *  ModuleCommander initializer
	 *  Commander_Queue is created
	 */
	ModuleCommander();

	/*
	 *  ModuleCommander main function
	 *  this function is called by CMSIS task function
	 */
	static void main();

	/*
	 *  Give a order to commander
	 *  this function is called by the RemoteController			ex)RC
	 *  this function will fail if the command queue is full
	 *  \param[in]		cmd		command to buzzer
	 *  \return	success(1), fail(0)
	 */
	static bool sendCommand(Command cmd);

	static void sendSignal(enum CmdSignal signal);

private:
	struct Controller controllerSub{};
	struct ModeFlag modeFlagSub{};
	struct StatusFlag statusFlagSub{};
	struct AirframeStatus airframeStatusSub{};

	struct ArmFlag armFlagPub{};
	struct ModeFlag modeFlagPub{};

	/*
	 *  handle command
	 *  this function call toAttitude(), toPosition() etc...
	 *  \param[in]		command for handling
	 */
	bool commandHandler(Command cmd);

	/*
	 *  function of dealing the command
	 *  \return Success(1), Denied(0)
	 */
	bool toAttitude();
	bool toAltitude();
	bool toPosition();		/* cmd = controlAttitude or controlALT */
	bool toWaypoint();
	bool toRTL();
	bool toTakeoff();
	bool toLand();

	bool toMulticopter();
	bool toFixedWing();

	bool toArm();
	bool toDisArm();

	bool toMotorCalibration();

	/*
	 *  When change mode, stop not using task
	 */
	bool stopTheOtherTask(FlightMode flightMode);

	/*
	 *  reset controller
	 */
	void resetController(FlightMode flightMode);

//	static const uint16_t DISARM_PWM = 1100;
public:
	~ModuleCommander() = default;
	ModuleCommander& operator=(ModuleCommander &&other) = delete;
	ModuleCommander& operator=(const ModuleCommander &other) = delete;
	ModuleCommander(ModuleCommander &&other) = delete;
	ModuleCommander(const ModuleCommander &other) = delete;
};


}


#endif /* MODULE_MODULECOMMANDER_H_ */
