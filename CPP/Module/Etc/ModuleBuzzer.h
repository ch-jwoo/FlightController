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
#include "tim.h"

namespace FC {

enum notes {
	C3 = 13100, // do
	D3 = 14700, // re
	E3 = 16500, // mi
	F3 = 17500, // pa
	G3 = 19600, // sol
	A3 = 22000, // ra
	B3 = 24700, // si
	C4 = 26163, // do (261.63Hz)
	D4 = 29366, // re (293.66Hz)
	E4 = 32963, // mi (329.63Hz)
	F4 = 34923, // pa (349.23Hz)
	G4 = 39200, // soi (392.00Hz)
	A4 = 44000, // ra (440.00Hz)
	B4 = 49388, // si (493.88Hz)
	C5 = 52325, // do (523.25Hz)
	D5 = 58700, // re
	E5 = 65900, // mi
	F5 = 69800,  // pa
	A1 = 200000, //Low Battery
	Z1 = 260000,
	Z2 = 274000,
	Z3 = 280000,
	Z4 = 100000,
	Z5 = 285000,
	Z6 = 380000		/* 3800hz */
};



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
	ModuleBuzzer(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t PCLK);

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
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint32_t CLK;

	enum notes A[10];// = {Z1, Z2, Z5, Z1, Z2, Z5, Z1, Z2, Z5, Z6};

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
