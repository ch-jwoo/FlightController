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


#define SBUS_BUF_SIZE 25 // require research
#define SBUS_CHANNEL_NUMBER 18 // digtal signal unimplementation

static uint8_t sbus_rxBuf[SBUS_BUF_SIZE];
static uint16_t sbus_rcValue[SBUS_CHANNEL_NUMBER];
static uint16_t sbus_comp_rcValue[SBUS_CHANNEL_NUMBER];

uint16_t sbus_hzcnt = 0;

void sbus_start(UART_HandleTypeDef *huart) {
	HAL_UART_Receive_DMA(huart, sbus_rxBuf, SBUS_BUF_SIZE);
}

void sbus_callback() { // input to HAL_UART_RxCpltCallback
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
	sbus_hzcnt++;
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
