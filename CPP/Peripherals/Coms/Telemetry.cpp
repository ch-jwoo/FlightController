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

//	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
}

void Telemetry::send(uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(sendMutexHandle, osWaitForever);
	HAL_UART_Transmit_DMA(huart, pData, Size);
	osMessageQueueGet(sendQueueId, (void*)&ret, NULL, osWaitForever);
	osMutexRelease(sendMutexHandle);
}

uint16_t Telemetry::receive(uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(rcvMutexHandle, osWaitForever);
	rxData = pData;
	rxSize = Size;
	HAL_UART_Receive_DMA(huart, pData, Size);
	osMessageQueueGet(rcvQueueId, (void*)&ret, NULL, osWaitForever);
	osMutexRelease(rcvMutexHandle);
	return rxSize;
}

void Telemetry::rcvCompleteCallback(UART_HandleTypeDef *huart){
	if(huart->Instance != this->huart->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(rcvQueueId, (void*)&ret, 0, 0);
}

void Telemetry::rcvIdleCallback(){
	uint32_t temp;
	uint32_t idleFlag = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
	if(idleFlag == RESET) return;

	__HAL_UART_CLEAR_IDLEFLAG(huart);

	temp = huart->Instance->ISR;
	temp = huart->Instance->RDR;
	HAL_UART_DMAStop(huart);
	temp = ((DMA_Stream_TypeDef*)(huart->hdmarx->Instance))->NDTR;
	rxSize = rxSize - temp;

	uint8_t ret = 0;
	osMessageQueuePut(rcvQueueId, (void*)&ret, 0, 0);
}

void Telemetry::sendCompleteCallback(UART_HandleTypeDef *huart){
	if(huart->Instance != this->huart->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(sendQueueId, (void*)&ret, 0, 0);
}

} /* namespace FC */
