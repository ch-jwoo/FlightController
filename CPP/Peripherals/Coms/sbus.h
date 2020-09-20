/*
 * Sbus.h
 *
 *  Created on: Sep 11, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERALS_COMS_SBUS_H_
#define PERIPHERALS_COMS_SBUS_H_

#include "usart.h"
#include "cmsis_os.h"

#define SBUS_BUF_SIZE 25		//rcv buffer
#define SBUS_DMA_BUF_SIZE 25 	// DMA buffer
#define SBUS_CHANNEL_NUMBER 18 	// digtal signal unimplementation

#define SBUS_LOST_FRAME 0x04
#define SBUS_FAIL_SAFE 0x08
#define SBUS_HEADER 0x0F
#define SBUS_FOOTER 0x00
#define SBUS2MASK 0x0F

namespace FC {

class Sbus {
public:

    /*
     *  \setting		baudrate			100000
     *  				word length			9bits
     *  				parity				even
     *  				stop_bits			2
     *  				rx_dma(circular)
     */
	Sbus(UART_HandleTypeDef *huart);

	void init();

	bool update();

	void rcvCompleteCallback(UART_HandleTypeDef *huart);

	inline uint16_t getChannelVal(uint8_t chan){
		return compRcValue[chan - 1];
	}

private:
	/* uart pointer */
	UART_HandleTypeDef *huart;
	uint8_t dmaBuf[SBUS_DMA_BUF_SIZE];
	uint8_t tmpBuf[SBUS_DMA_BUF_SIZE];
	uint8_t parseBuf[SBUS_BUF_SIZE];

	uint16_t rcValue[SBUS_CHANNEL_NUMBER];
	uint16_t compRcValue[SBUS_CHANNEL_NUMBER];	//pwm decode

	uint8_t _parserState;		//for parsing
	uint8_t _curByte, _prevByte;

	osMessageQueueId_t queueId;

	bool decoding();

	bool parse();
public:
	Sbus() = delete;
	~Sbus() = default;
	Sbus(const Sbus &other) = delete;
	Sbus(Sbus &&other) = delete;
	Sbus& operator=(const Sbus &other) = delete;
	Sbus& operator=(Sbus &&other) = delete;
};

extern Sbus sbus;

} /* namespace FC */

#endif /* PERIPHERALS_COMS_SBUS_H_ */
