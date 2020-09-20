/*
 * Sbus.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: cjb88
 */

#include <Peripherals/Coms/Sbus.h>
#include "usart.h"
#include <cstring>
#include "printf.h"

namespace FC {

Sbus sbus(&huart7);

/*
 *  1. dma buffer update
 *  2. parsing
 *  		OK -> decoding
 *  		NO -> not decode
 *  3. if parsing ok -> update
 */

Sbus::Sbus(UART_HandleTypeDef *huart)
: huart(huart)
, _parserState(0)
, _curByte(0)
, _prevByte(0)
{
	queueId = osMessageQueueNew(1, sizeof(uint8_t), NULL);
}

void Sbus::init(){
	HAL_UART_Receive_DMA(huart, dmaBuf, SBUS_DMA_BUF_SIZE);
//	__HAL_UART_DISABLE_IT(huart, UART_IT_RTO);
//	__HAL_UART_DISABLE_IT(huart, UART_IT_ERR);
}

bool Sbus::update(){
	bool result = false;
	uint8_t ret;
	HAL_StatusTypeDef stat;

	osMessageQueueReset(queueId);
	while(osMessageQueueGet(queueId, (void*)&ret, NULL, 100) != osOK){
//		while(HAL_UART_Abort(huart) != HAL_OK) osDelay(1);
//		while(HAL_UART_Receive_DMA(huart, dmaBuf, SBUS_DMA_BUF_SIZE) != HAL_OK) osDelay(1);

		printf_("sbus abort\r\n");
		while(1){
			osKernelLock();
			stat = HAL_UART_Abort(huart);
			osKernelUnlock();
			if(stat == HAL_OK) break;
			osDelay(20);
		}

		while(1){
			osKernelLock();
			HAL_UART_Receive_DMA(huart, dmaBuf, SBUS_DMA_BUF_SIZE);
			osKernelUnlock();
			if(stat == HAL_OK) break;
			osDelay(20);
		}
	}
//	while(ret != 0){
//		/* uart error */
//		while(HAL_UART_Abort(huart) != HAL_OK) osDelay(1);
//		printf_("sbus abort\r\n");
//
//		while(HAL_UART_Receive_DMA(huart, dmaBuf, SBUS_DMA_BUF_SIZE) != HAL_OK) osDelay(1);
//		osMessageQueueGet(queueId, (void*)&ret, NULL, osWaitForever);
//	}

	return parse();
}

void Sbus::rcvCompleteCallback(UART_HandleTypeDef *huart){
	if(huart->Instance != this->huart->Instance) return;
	uint8_t ret = 0;

	std::memcpy((void*)tmpBuf, (const void*)dmaBuf, SBUS_DMA_BUF_SIZE);
	osMessageQueuePut(queueId, (void*)&ret, 0, 0);
}

bool Sbus::decoding(){
	if(parseBuf[23] & SBUS_FAIL_SAFE){	/* failsafe frame */
		return false;
	}

	/* handle bit flag  */
//	if(++(sbus._bitPos) == SBUS_ERROR_FLAG_BIT_SIZE) sbus._bitPos = 0; /* bitPos over 64 */

//	if(parseBuf[23] & SBUS_LOST_FRAME) sbus._errBit |= 1<<sbus._bitPos;	/* lost frame */
//	else sbus._errBit &= ~(1<<sbus._bitPos);	/* normal frame */

//	sbus._errCnt = _bitCount64(sbus._errBit);	/* count error bit */

	/* handle sbus state */
//	if(sbus._errCnt > SBUS_ERROR_THRESHHOLD) sbus.state = SBUS_STATE_LOSS; /* if error rate over the threshold */
//	else sbus.state = SBUS_STATE_STEADY;	/* sbus signal stable */

//	if(parseBuf[23] & SBUS_LOST_FRAME) return SBUS_Result_OldData; /* if this frame is lost frame, not decode packet */

	/* decode packet */
	rcValue[0] = ((uint16_t)parseBuf[1] >> 0 | ((uint16_t)parseBuf[2] << 8)) & 0x07FF;
	rcValue[1] = ((uint16_t)parseBuf[2] >> 3 | ((uint16_t)parseBuf[3] << 5)) & 0x07FF;
	rcValue[2] = ((uint16_t)parseBuf[3] >> 6 | ((uint16_t)parseBuf[4] << 2) | (uint16_t)parseBuf[5] << 10) & 0x07FF;
	rcValue[3] = ((uint16_t)parseBuf[5] >> 1 | ((uint16_t)parseBuf[6] << 7)) & 0x07FF;
	rcValue[4] = ((uint16_t)parseBuf[6] >> 4 | ((uint16_t)parseBuf[7] << 4)) & 0x07FF;
	rcValue[5] = ((uint16_t)parseBuf[7] >> 7 | ((uint16_t)parseBuf[8] << 1) | (uint16_t)parseBuf[9] << 9) & 0x07FF;
	rcValue[6] = ((uint16_t)parseBuf[9] >> 2 | ((uint16_t)parseBuf[10] << 6)) & 0x07FF;
	rcValue[7] = ((uint16_t)parseBuf[10] >> 5 | ((uint16_t)parseBuf[11] << 3)) & 0x07FF;

	rcValue[8] = ((uint16_t)parseBuf[12] << 0 | ((uint16_t)parseBuf[13] << 8)) & 0x07FF;
	rcValue[9] = ((uint16_t)parseBuf[13] >> 3 | ((uint16_t)parseBuf[14] << 5)) & 0x07FF;
	rcValue[10] = ((uint16_t)parseBuf[14] >> 6 | ((uint16_t)parseBuf[15] << 2) | (uint16_t)parseBuf[16] << 10) & 0x07FF;
	rcValue[11] = ((uint16_t)parseBuf[16] >> 1 | ((uint16_t)parseBuf[17] << 7)) & 0x07FF;
	rcValue[12] = ((uint16_t)parseBuf[17] >> 4 | ((uint16_t)parseBuf[18] << 4)) & 0x07FF;
	rcValue[13] = ((uint16_t)parseBuf[18] >> 7 | ((uint16_t)parseBuf[19] << 1) | (uint16_t)parseBuf[21] << 9) & 0x07FF;
	rcValue[14] = ((uint16_t)parseBuf[20] >> 2 | ((uint16_t)parseBuf[21] << 6)) & 0x07FF;
	rcValue[15] = ((uint16_t)parseBuf[21] >> 5 | ((uint16_t)parseBuf[22] << 3)) & 0x07FF;

	if (((uint16_t)parseBuf[23]) & 0x0001)       rcValue[16] = 2000; else rcValue[16] = 1000;
	if (((uint16_t)parseBuf[23] >> 1) & 0x0001)  rcValue[17] = 2000; else rcValue[17] = 1000;

	for (int i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		compRcValue[i] = (rcValue[i]) * 5 / 8 + 880;
	}

//	if(sbus_comp_rcValue[0]<SBUS_FAILSAFE && sbus_comp_rcValue[1]<SBUS_FAILSAFE
//	&& sbus_comp_rcValue[2]<SBUS_FAILSAFE && sbus_comp_rcValue[3]<SBUS_FAILSAFE) return; // failsafe
//	return SBUS_Result_NewData;
}

bool Sbus::parse(){
	for(uint8_t i=0; i<SBUS_DMA_BUF_SIZE;i++){
		_curByte = tmpBuf[i];
		if (_parserState == 0) {
			if ((_curByte == SBUS_HEADER) && ((_prevByte == SBUS_FOOTER) || ((_prevByte & SBUS2MASK) == SBUS_FOOTER))) {
				parseBuf[_parserState] = _curByte;
				_parserState++;
			} else {
				_parserState = 0;
			}
		}
		else {
			// strip off the data
			if ((_parserState) < SBUS_BUF_SIZE) {
				parseBuf[_parserState] = _curByte;
				_parserState++;
			}
			// check the end byte
			if ((_parserState) == SBUS_BUF_SIZE) {
				if ((_curByte == SBUS_FOOTER) || ((_curByte & SBUS2MASK) == SBUS_FOOTER)) {
					_parserState = 0;
					return decoding();
				}
				else {
					_parserState = 0;
				}
			}
		}
		_prevByte = _curByte;
	}
	return false;
}

} /* namespace FC */
