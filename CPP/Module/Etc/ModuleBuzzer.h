/*
 * Buzzer.h
 *
 *  Created on: Aug 8, 2020
 *      Author: cjb88
 */

#ifndef DRIVER_BUZZER_H_
#define DRIVER_BUZZER_H_

#include <MsgBus/MsgType.h>
#include "cmsis_os.h"
#include "Peripherals/Etc/Buzzer.h"

namespace FC {

enum class BuzzerCommand{
	Armed,
	DisArmed,
	Success,
	Denied
};

/*
 *	Command queue.
 *	this module will work on the queue
 */
extern osMessageQueueId_t Buzzer_QueueHandle;

class ModuleBuzzer {
public:

	/*
	 *  ModuleBuzzer main function
	 *  this function is called by CMSIS task function
	 */
	static void main();

	/*
	 *  ModuleBuzzer initializer
	 *  Buzzer_Queue is created
	 *
	 *  \Setting		Prescaler : 0
	 *  				AutoReload Register : 10-1
	 *  				Pulse : 5
	 *
	 *  \param[in]		htim		HAL driver timer handler	ex) &htim5
	 *  \param[in]		Channel		timer channel				ex) TIM_CHANNEL_2
	 *  \param[in]		PCLK		peripheral clock
	 */
	ModuleBuzzer(Buzzer *buzzer);

	/*
	 *  Give a order to buzzer
	 *  this function is called by the other Module		ex)ModuleCommander
	 *  this function will fail if the command queue is full
	 *  \param[in]		cmd		command to buzzer
	 *  \return	success(1), fail(0)
	 */
	static bool sendCommand(BuzzerCommand cmd);
	
	~ModuleBuzzer() = default;
	ModuleBuzzer() = delete;
	ModuleBuzzer& operator=(ModuleBuzzer &&other) = delete;
	ModuleBuzzer& operator=(const ModuleBuzzer &other) = delete;
	ModuleBuzzer(ModuleBuzzer &&other) = delete;
	ModuleBuzzer(const ModuleBuzzer &other) = delete;

private:
	Buzzer *pbuzzer;

	const Note_t armedNotes[3];
	const Note_t disarmedNotes[3];
	const Note_t successedNotes[2];
	const Note_t deniedNotes[1];

	/*
	 *  handle command using switch
	 *  \param[in]		command for handling
	 */
	void commandHandler(BuzzerCommand result);

	/*
	 *  function of dealing the command
	 */
	void armed();
	void disarmed();
	void denied();
	void success();
};

} /* namespace FC */

#endif /* DRIVER_BUZZER_H_ */
