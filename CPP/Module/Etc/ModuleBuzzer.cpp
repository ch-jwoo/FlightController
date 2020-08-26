/*
 * Buzzer.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: cjb88
 */

#include "ModuleBuzzer.h"

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

	/*
	 *  using peripherals/Etc/Buzzer.h
	 */
	ModuleBuzzer moduleBuzzer(&buzzer);
	BuzzerCommand rcvResult;
	while(1){
		if(osMessageQueueGet(Buzzer_QueueHandle, (void*)&rcvResult, NULL, osWaitForever) == osOK){
			moduleBuzzer.commandHandler(rcvResult);
		}
		else{
			osMessageQueueReset(Buzzer_QueueHandle);
		}
		osDelay(10);
	}
}

ModuleBuzzer::ModuleBuzzer(Buzzer *buzzer)
: pbuzzer(buzzer)
, armedNotes{C4, G4, C5}
, disarmedNotes{C5, G4, C4}
, successedNotes{D5, D5}
, deniedNotes{D5}
{
	  /* creation of Buzzer_Queue */
	  Buzzer_QueueHandle = osMessageQueueNew(3, sizeof(BuzzerCommand), &Buzzer_Queue_attributes);
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
    for (uint8_t i = 0 ; i < sizeof(armedNotes)/sizeof(Note_t) ; i++) {
	  pbuzzer->start();
      pbuzzer->setNote(armedNotes[i]);
      osDelay(500);

      /* Make each note sound and cut 1 mileecond */
      pbuzzer->stop();
      osDelay(10);
    }
}

void ModuleBuzzer::disarmed(){
	//TODO disarmed sound
	for (uint8_t i = 0 ; i < sizeof(disarmedNotes)/sizeof(Note_t) ; i++) {
	    pbuzzer->start();
		pbuzzer->setNote(disarmedNotes[i]);
		osDelay(500);

		/* Make each note sound and cut 1 mileecond */
	    pbuzzer->stop();
		osDelay(10);
	}
}

void ModuleBuzzer::denied(){
	//TODO denied sound
	for (uint8_t i = 0 ; i < sizeof(deniedNotes)/sizeof(Note_t) ; i++) {
	    pbuzzer->start();
		pbuzzer->setNote(deniedNotes[i]);
		osDelay(2000);

		/* Make each note sound and cut n mileecond */
	    pbuzzer->stop();
		osDelay(5);
	}
}

void ModuleBuzzer::success(){
	 for (uint8_t i = 0 ; i < sizeof(successedNotes)/sizeof(Note_t) ; i++) {
	   pbuzzer->start();
	   pbuzzer->setNote(disarmedNotes[i]);
	   osDelay(100);

	   /* Make each note sound and cut 1 mileecond */
	   pbuzzer->stop();
	   osDelay(10);
	 }
}

} /* namespace FC */
