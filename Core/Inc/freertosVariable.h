/*
 * freertos.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef INC_FREERTOSVARIABLE_H_
#define INC_FREERTOSVARIABLE_H_

#include "main.h"
#include "cmsis_os.h"

extern osThreadId_t defaultTaskHandle;
extern osThreadId_t MPU9250_TaskHandle;
extern osThreadId_t BME280_TaskHandle;
extern osThreadId_t IST8310_TaskHandle;
extern osThreadId_t SD_TaskHandle;
extern osThreadId_t AHRS_TaskHandle;
extern osThreadId_t Commander_TaskHandle;
extern osThreadId_t Debug_myTaskHandle;
extern osThreadId_t Buzzer_TaskHandle;
extern osThreadId_t Health_TaskHandle;
extern osThreadId_t AC_TaskHandle;
extern osThreadId_t INS_TaskHandle;
extern osThreadId_t PC_TaskHandle;

#endif /* INC_FREERTOSVARIABLE_H_ */
