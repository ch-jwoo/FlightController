/*
 * Telemetry.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#include "Telemetry.h"

namespace FC {

Telemetry telem(&huart2);

Telemetry::Telemetry(UART_HandleTypeDef *huart)
: huart(huart)
{
	sendMutexHandle = osMutexNew(NULL);
	sendQueueId = osMessageQueueNew(1, sizeof(uint8_t), NULL);

	rcvMutexHandle = osMutexNew(NULL);
	rcvQueueId = osMessageQueueNew(1, sizeof(uint8_t), NULL);
}

void Telemetry::send(uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(sendMutexHandle, osWaitForever);
	HAL_UART_Transmit_DMA(huart, pData, Size);
	osMessageQueueGet(sendQueueId, (void*)&ret, NULL, osWaitForever);
	osMutexRelease(sendMutexHandle);
}

void Telemetry::receive(uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(rcvMutexHandle, osWaitForever);
	HAL_UART_Receive_DMA(huart, pData, Size);
	osMessageQueueGet(rcvQueueId, (void*)&ret, NULL, osWaitForever);
	osMutexRelease(rcvMutexHandle);
}

void Telemetry::rcvCompleteCallback(UART_HandleTypeDef *huart){
	if(huart->Instance != this->huart->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(rcvQueueId, (void*)&ret, 0, 0);
}

void Telemetry::sendCompleteCallback(UART_HandleTypeDef *huart){
	if(huart->Instance != this->huart->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(sendQueueId, (void*)&ret, 0, 0);
}

} /* namespace FC */
