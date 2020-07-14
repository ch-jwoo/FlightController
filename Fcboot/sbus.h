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
#include "algorithmCollection.h"

#define SBUS_BUF_SIZE 25		//rcv buffer
#define SBUS_DMA_BUF_SIZE 25 	// DMA buffer
#define SBUS_CHANNEL_NUMBER 18 	// digtal signal unimplementation
#define SBUS_FAILSAFE 900		// RC failsafe

#define SBUS_LOST_FRAME 0x04
#define SBUS_FAIL_SAFE 0x08
#define SBUS_HEADER 0x0F
#define SBUS_FOOTER 0x00
#define SBUS2MASK 0x0F

static uint8_t sbus_rxBuf[SBUS_BUF_SIZE];				//temp buffer
static uint8_t sbus_dmaBuf[SBUS_DMA_BUF_SIZE];			//dma buffer


static uint16_t sbus_rcValue[SBUS_CHANNEL_NUMBER];
static uint16_t sbus_comp_rcValue[SBUS_CHANNEL_NUMBER];	//pwm decode

static UART_HandleTypeDef *sbus_phuart;					//uart pointer

uint16_t sbus_hzcnt = 0;
uint16_t sbus_errcnt = 0;

static uint8_t _parserState = 0;		//for parsing
static uint8_t _curByte, _prevByte;

void sbus_start(UART_HandleTypeDef *huart) {
	sbus_phuart = huart;
//	HAL_UART_Receive_DMA(huart, sbus_rxBuf, SBUS_BUF_SIZE);
	HAL_UART_Receive_DMA(huart, sbus_dmaBuf, SBUS_DMA_BUF_SIZE);
}

void sbus_reset(UART_HandleTypeDef *huart){
	HAL_UART_Receive_DMA(huart, sbus_dmaBuf, SBUS_DMA_BUF_SIZE);
}

void sbus_decoding() { // input to HAL_UART_RxCpltCallback
	if(sbus_rxBuf[23] & SBUS_LOST_FRAME || sbus_rxBuf[23] & SBUS_FAIL_SAFE){//failsafe frame
//		printf("fail safe\r\n");
		sbus_errcnt++;
		return;
	}

	sbus_rcValue[0] = ((uint16_t)sbus_rxBuf[1] >> 0 | ((uint16_t)sbus_rxBuf[2] << 8)) & 0x07FF;
	sbus_rcValue[1] = ((uint16_t)sbus_rxBuf[2] >> 3 | ((uint16_t)sbus_rxBuf[3] << 5)) & 0x07FF;
	sbus_rcValue[2] = ((uint16_t)sbus_rxBuf[3] >> 6 | ((uint16_t)sbus_rxBuf[4] << 2) | (uint16_t)sbus_rxBuf[5] << 10) & 0x07FF;
	sbus_rcValue[3] = ((uint16_t)sbus_rxBuf[5] >> 1 | ((uint16_t)sbus_rxBuf[6] << 7)) & 0x07FF;
	sbus_rcValue[4] = ((uint16_t)sbus_rxBuf[6] >> 4 | ((uint16_t)sbus_rxBuf[7] << 4)) & 0x07FF;
	sbus_rcValue[5] = ((uint16_t)sbus_rxBuf[7] >> 7 | ((uint16_t)sbus_rxBuf[8] << 1) | (uint16_t)sbus_rxBuf[9] << 9) & 0x07FF;
	sbus_rcValue[6] = ((uint16_t)sbus_rxBuf[9] >> 2 | ((uint16_t)sbus_rxBuf[10] << 6)) & 0x07FF;
	sbus_rcValue[7] = ((uint16_t)sbus_rxBuf[10] >> 5 | ((uint16_t)sbus_rxBuf[11] << 3)) & 0x07FF;

	sbus_rcValue[8] = ((uint16_t)sbus_rxBuf[12] << 0 | ((uint16_t)sbus_rxBuf[13] << 8)) & 0x07FF;
	sbus_rcValue[9] = ((uint16_t)sbus_rxBuf[13] >> 3 | ((uint16_t)sbus_rxBuf[14] << 5)) & 0x07FF;
	sbus_rcValue[10] = ((uint16_t)sbus_rxBuf[14] >> 6 | ((uint16_t)sbus_rxBuf[15] << 2) | (uint16_t)sbus_rxBuf[16] << 10) & 0x07FF;
	sbus_rcValue[11] = ((uint16_t)sbus_rxBuf[16] >> 1 | ((uint16_t)sbus_rxBuf[17] << 7)) & 0x07FF;
	sbus_rcValue[12] = ((uint16_t)sbus_rxBuf[17] >> 4 | ((uint16_t)sbus_rxBuf[18] << 4)) & 0x07FF;
	sbus_rcValue[13] = ((uint16_t)sbus_rxBuf[18] >> 7 | ((uint16_t)sbus_rxBuf[19] << 1) | (uint16_t)sbus_rxBuf[21] << 9) & 0x07FF;
	sbus_rcValue[14] = ((uint16_t)sbus_rxBuf[20] >> 2 | ((uint16_t)sbus_rxBuf[21] << 6)) & 0x07FF;
	sbus_rcValue[15] = ((uint16_t)sbus_rxBuf[21] >> 5 | ((uint16_t)sbus_rxBuf[22] << 3)) & 0x07FF;


	if (((uint16_t)sbus_rxBuf[23]) & 0x0001)       sbus_rcValue[16] = 2000; else sbus_rcValue[16] = 1000;
	if (((uint16_t)sbus_rxBuf[23] >> 1) & 0x0001)  sbus_rcValue[17] = 2000; else sbus_rcValue[17] = 1000;

	for (int i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		sbus_comp_rcValue[i] = (sbus_rcValue[i]) * 5 / 8 + 880;
	}

//	if(sbus_comp_rcValue[0]<SBUS_FAILSAFE && sbus_comp_rcValue[1]<SBUS_FAILSAFE
//	&& sbus_comp_rcValue[2]<SBUS_FAILSAFE && sbus_comp_rcValue[3]<SBUS_FAILSAFE) return; // failsafe

	sbus_hzcnt++;
}


void sbus_callback(){
	static uint8_t i=0;
	for(i=0; i<SBUS_DMA_BUF_SIZE;i++){
		_curByte = sbus_dmaBuf[i];
		if (_parserState == 0) {
				if ((_curByte == SBUS_HEADER) && ((_prevByte == SBUS_FOOTER) || ((_prevByte & SBUS2MASK) == SBUS_FOOTER))) {
					sbus_rxBuf[_parserState] = _curByte;
					_parserState++;
				} else {
					_parserState = 0;
				}
		}
		else {
			// strip off the data
			if ((_parserState) < SBUS_BUF_SIZE) {
				sbus_rxBuf[_parserState] = _curByte;
				_parserState++;
			}
			// check the end byte
			if ((_parserState) == SBUS_BUF_SIZE) {
				if ((_curByte == SBUS_FOOTER) || ((_curByte & SBUS2MASK) == SBUS_FOOTER)) {
					_parserState = 0;
//					return true;
					sbus_decoding();
				}
				else {
					_parserState = 0;
//					return false;
				}
			}
		}
		_prevByte = _curByte;
	}
}
uint16_t sbus_getHz(){ // call this func 1hz
	uint16_t temp = sbus_hzcnt;
	sbus_hzcnt = 0;
	return temp;
}

void sbus_print() {
	for (int i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
		printf("%d \t", sbus_comp_rcValue[i]);
	}
	printf("\r\n");
}

uint16_t sbus_getChannel(uint8_t chan) { // start from 1
	return sbus_comp_rcValue[chan - 1];
}


#ifdef __cplusplus
}
#endif

#endif /* INC_SBUS_H_ */
