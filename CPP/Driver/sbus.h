/*
 * sbus.h
 *
 *  Created on: Jul 12, 2020
 *      Author: junim
 */

#ifndef INC_SBUS_H_
#define INC_SBUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"

#define SBUS_BUF_SIZE 25		//rcv buffer
#define SBUS_DMA_BUF_SIZE 25 	// DMA buffer
#define SBUS_CHANNEL_NUMBER 18 	// digtal signal unimplementation
//#define SBUS_FAILSAFE 900		// RC failsafe

#define SBUS_LOST_FRAME 0x04
#define SBUS_FAIL_SAFE 0x08
#define SBUS_HEADER 0x0F
#define SBUS_FOOTER 0x00
#define SBUS2MASK 0x0F

#define SBUS_ERROR_THRESHHOLD 20
#define SBUS_ERROR_FLAG_BIT_SIZE 64

/*
 *  count '1' from 64bit varible
 */
uint8_t _bitCount64(uint64_t flagBit){
	uint8_t cnt = 0;
	for(int i=0; i < 64; i++){
		if((flagBit & (1<<i))!=0) cnt++;
	}
	return cnt;
}

typedef enum{
	SBUS_STATE_FAILSAFE = 0,
	SBUS_STATE_LOSS = 1,
	SBUS_STATE_STEADY = 2,
} SBUS_State_t;

typedef enum{
	SBUS_Result_OldData,
	SBUS_Result_NewData
}SBUS_Result_t;

typedef struct{
	UART_HandleTypeDef *huart;			//uart pointer
	uint8_t dmaBuf[SBUS_DMA_BUF_SIZE];	// dma buffer
	uint8_t rxBuf[SBUS_BUF_SIZE];		// temperary buffer of sbus

	uint16_t rcValue[SBUS_CHANNEL_NUMBER];
	uint16_t compRcValue[SBUS_CHANNEL_NUMBER];	//pwm decode

	SBUS_State_t state;		/* sbus state */

	uint64_t _errBit;		/* 64bit flag variable */
	uint8_t _bitPos;		/* current flag bit postion */
	uint8_t _errCnt;		/* number of '1' of _errBit */
} SBUS_t;

SBUS_t sbus;

static uint8_t _parserState = 0;		//for parsing
static uint8_t _curByte, _prevByte;

void SBUS_init(UART_HandleTypeDef *huart) {
	sbus.huart = huart;

	memset(sbus.dmaBuf, 0, sizeof(sbus.dmaBuf));
	memset(sbus.rxBuf, 0, sizeof(sbus.rxBuf));
	memset(sbus.rcValue, 0, sizeof(sbus.rcValue));
	memset(sbus.compRcValue, 0, sizeof(sbus.compRcValue));
	sbus.state = SBUS_STATE_FAILSAFE;

	HAL_UART_Receive_DMA(sbus.huart, sbus.dmaBuf, SBUS_DMA_BUF_SIZE);
}

SBUS_Result_t SBUS_decoding() {
	if(sbus.rxBuf[23] & SBUS_FAIL_SAFE){	/* failsafe frame */
		sbus.state = SBUS_STATE_FAILSAFE;
		return SBUS_Result_OldData;
	}

	/* handle bit flag  */
	if(++(sbus._bitPos) == SBUS_ERROR_FLAG_BIT_SIZE) sbus._bitPos = 0; /* bitPos over 64 */

	if(sbus.rxBuf[23] & SBUS_LOST_FRAME) sbus._errBit |= 1<<sbus._bitPos;	/* lost frame */
	else sbus._errBit &= ~(1<<sbus._bitPos);	/* normal frame */

	sbus._errCnt = _bitCount64(sbus._errBit);	/* count error bit */

	/* handle sbus state */
	if(sbus._errCnt > SBUS_ERROR_THRESHHOLD) sbus.state = SBUS_STATE_LOSS; /* if error rate over the threshold */
	else sbus.state = SBUS_STATE_STEADY;	/* sbus signal stable */

	if(sbus.rxBuf[23] & SBUS_LOST_FRAME) return SBUS_Result_OldData; /* if this frame is lost frame, not decode packet */

	/* decode packet */
	sbus.rcValue[0] = ((uint16_t)sbus.rxBuf[1] >> 0 | ((uint16_t)sbus.rxBuf[2] << 8)) & 0x07FF;
	sbus.rcValue[1] = ((uint16_t)sbus.rxBuf[2] >> 3 | ((uint16_t)sbus.rxBuf[3] << 5)) & 0x07FF;
	sbus.rcValue[2] = ((uint16_t)sbus.rxBuf[3] >> 6 | ((uint16_t)sbus.rxBuf[4] << 2) | (uint16_t)sbus.rxBuf[5] << 10) & 0x07FF;
	sbus.rcValue[3] = ((uint16_t)sbus.rxBuf[5] >> 1 | ((uint16_t)sbus.rxBuf[6] << 7)) & 0x07FF;
	sbus.rcValue[4] = ((uint16_t)sbus.rxBuf[6] >> 4 | ((uint16_t)sbus.rxBuf[7] << 4)) & 0x07FF;
	sbus.rcValue[5] = ((uint16_t)sbus.rxBuf[7] >> 7 | ((uint16_t)sbus.rxBuf[8] << 1) | (uint16_t)sbus.rxBuf[9] << 9) & 0x07FF;
	sbus.rcValue[6] = ((uint16_t)sbus.rxBuf[9] >> 2 | ((uint16_t)sbus.rxBuf[10] << 6)) & 0x07FF;
	sbus.rcValue[7] = ((uint16_t)sbus.rxBuf[10] >> 5 | ((uint16_t)sbus.rxBuf[11] << 3)) & 0x07FF;

	sbus.rcValue[8] = ((uint16_t)sbus.rxBuf[12] << 0 | ((uint16_t)sbus.rxBuf[13] << 8)) & 0x07FF;
	sbus.rcValue[9] = ((uint16_t)sbus.rxBuf[13] >> 3 | ((uint16_t)sbus.rxBuf[14] << 5)) & 0x07FF;
	sbus.rcValue[10] = ((uint16_t)sbus.rxBuf[14] >> 6 | ((uint16_t)sbus.rxBuf[15] << 2) | (uint16_t)sbus.rxBuf[16] << 10) & 0x07FF;
	sbus.rcValue[11] = ((uint16_t)sbus.rxBuf[16] >> 1 | ((uint16_t)sbus.rxBuf[17] << 7)) & 0x07FF;
	sbus.rcValue[12] = ((uint16_t)sbus.rxBuf[17] >> 4 | ((uint16_t)sbus.rxBuf[18] << 4)) & 0x07FF;
	sbus.rcValue[13] = ((uint16_t)sbus.rxBuf[18] >> 7 | ((uint16_t)sbus.rxBuf[19] << 1) | (uint16_t)sbus.rxBuf[21] << 9) & 0x07FF;
	sbus.rcValue[14] = ((uint16_t)sbus.rxBuf[20] >> 2 | ((uint16_t)sbus.rxBuf[21] << 6)) & 0x07FF;
	sbus.rcValue[15] = ((uint16_t)sbus.rxBuf[21] >> 5 | ((uint16_t)sbus.rxBuf[22] << 3)) & 0x07FF;

	if (((uint16_t)sbus.rxBuf[23]) & 0x0001)       sbus.rcValue[16] = 2000; else sbus.rcValue[16] = 1000;
	if (((uint16_t)sbus.rxBuf[23] >> 1) & 0x0001)  sbus.rcValue[17] = 2000; else sbus.rcValue[17] = 1000;

	for (int i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		sbus.compRcValue[i] = (sbus.rcValue[i]) * 5 / 8 + 880;
	}

//	if(sbus_comp_rcValue[0]<SBUS_FAILSAFE && sbus_comp_rcValue[1]<SBUS_FAILSAFE
//	&& sbus_comp_rcValue[2]<SBUS_FAILSAFE && sbus_comp_rcValue[3]<SBUS_FAILSAFE) return; // failsafe
	return SBUS_Result_NewData;
}


SBUS_Result_t SBUS_uartRxCpltCallback(){// must call this function on HAL_UART_RxCpltCallback
	static uint8_t i=0;
	SBUS_Result_t result = SBUS_Result_OldData;
	for(i=0; i<SBUS_DMA_BUF_SIZE;i++){
		_curByte = sbus.dmaBuf[i];
		if (_parserState == 0) {
			if ((_curByte == SBUS_HEADER) && ((_prevByte == SBUS_FOOTER) || ((_prevByte & SBUS2MASK) == SBUS_FOOTER))) {
				sbus.rxBuf[_parserState] = _curByte;
				_parserState++;
			} else {
				_parserState = 0;
			}
		}
		else {
			// strip off the data
			if ((_parserState) < SBUS_BUF_SIZE) {
				sbus.rxBuf[_parserState] = _curByte;
				_parserState++;
			}
			// check the end byte
			if ((_parserState) == SBUS_BUF_SIZE) {
				if ((_curByte == SBUS_FOOTER) || ((_curByte & SBUS2MASK) == SBUS_FOOTER)) {
					_parserState = 0;
					result = SBUS_decoding();
				}
				else {
					_parserState = 0;
				}
			}
		}
		_prevByte = _curByte;
	}
	return result;
}

void SBUS_print() {
	for (int i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		printf("%d \t", sbus.compRcValue[i]);
	}
	printf("\r\n");
}

uint16_t SBUS_getChannel(uint8_t chan) { // start from 1
	return sbus.compRcValue[chan - 1];
}


#ifdef __cplusplus
}
#endif

#endif /* INC_SBUS_H_ */
