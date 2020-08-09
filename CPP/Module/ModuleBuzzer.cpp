/*
 * Buzzer.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: cjb88
 */

#include <Module/ModuleBuzzer.h>
#include "tim.h"


namespace FC {

typedef StaticQueue_t osStaticMessageQDef_t;

/* Definitions for Buzzer_Queue */
osMessageQueueId_t Buzzer_QueueHandle;
uint8_t Buzzer_QueueBuffer[ 3 * sizeof( BuzzerCommand ) ];
osStaticMessageQDef_t Buzzer_QueueControlBlock;
static const osMessageQueueAttr_t Buzzer_Queue_attributes = {
	.name = "Buzzer_Queue",
	.attr_bits = 0,
	.cb_mem = &Buzzer_QueueControlBlock,
	.cb_size = sizeof(Buzzer_QueueControlBlock),
	.mq_mem = &Buzzer_QueueBuffer,
	.mq_size = sizeof(Buzzer_QueueBuffer)
};


void ModuleBuzzer::main() {
	ModuleBuzzer buzzer(&htim5, TIM_CHANNEL_2, 84000000);

	BuzzerCommand rcvResult;
	while(1){
		if(osMessageQueueGet(Buzzer_QueueHandle, (void*)&rcvResult, NULL, osWaitForever) == osOK){
			buzzer.commandHandler(rcvResult);
		}
		else{
			osMessageQueueReset(Buzzer_QueueHandle);
		}
		osDelay(10);
	}
}

ModuleBuzzer::ModuleBuzzer(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t CLK)
	: A{Z1, Z2, Z5, Z6}
{
	  /* creation of Buzzer_Queue */
	  Buzzer_QueueHandle = osMessageQueueNew (3, sizeof(BuzzerCommand), &Buzzer_Queue_attributes);

	  this->htim = htim;
	  this->Channel = Channel;
	  this->CLK = CLK/10;		/* 10 : AutoReload Register+1 */
}


bool ModuleBuzzer::sendCommand(BuzzerCommand cmd){
	if(osMessageQueueGetSpace(Buzzer_QueueHandle) != 0){
		osMessageQueuePut(Buzzer_QueueHandle, (void*)&cmd, 0, 0);
		return true;
	}
	return false;
}

void ModuleBuzzer::commandHandler(BuzzerCommand result){
	switch(result){
	case BuzzerCommand::Armed:
		armed();
		break;
	case BuzzerCommand::DisArmed:
		disarmed();
		break;
	case BuzzerCommand::Success:
		success();
		break;
	case BuzzerCommand::Denied:
		denied();
		break;
	}
}

void ModuleBuzzer::armed(){
	//TODO armed sound
}

void ModuleBuzzer::disarmed(){
	//TODO disarmed sound
}

void ModuleBuzzer::denied(){
	//TODO denied sound
}

void ModuleBuzzer::success(){
	for (uint8_t i = 0 ; i < sizeof(A)/sizeof(enum notes) ; i++) {
		__HAL_TIM_SET_PRESCALER(htim, CLK / A[i] * 100);
		HAL_TIM_PWM_Start(htim, Channel);
		osDelay(500);

		/* Make each note sound and cut 1 mileecond */
		HAL_TIM_PWM_Stop(htim, Channel);
//		__HAL_TIM_SET_COMPARE(htim, Channel, 0);
		osDelay(10);
	}
//	__HAL_TIM_SET_COMPARE(htim, Channel, 0);
}

} /* namespace FC */
