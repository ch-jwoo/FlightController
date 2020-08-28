/*
 * Telemetry.h
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERAL_COMS_TELEMETRY_H_
#define PERIPHERAL_COMS_TELEMETRY_H_

#include "usart.h"
#include <cstdint>
#include "cmsis_os.h"

namespace FC {

class Telemetry {
public:

	/*
	 *  telemetry setting
	 *  \setting		baud rate		57600
	 *  				global interrupt enable
	 *  				rx, tx dma enable
	 */
	Telemetry(UART_HandleTypeDef *huart);

	void init();

	/*
	 *  send msg using dma
	 *  using mutex in this function
	 */
	void send(uint8_t *pData, uint16_t Size);

	/*
	 *  receive msg using dma, mutex
	 *  \pram[in]		*pData		receive data address
	 *  \pram[in]		Size		receive data size
	 *  \return						received data size
	 */
	uint16_t receive(uint8_t *pData, uint16_t Size);

	void rcvCompleteCallback(UART_HandleTypeDef *huart);

	void rcvIdleCallback();

	void sendCompleteCallback(UART_HandleTypeDef *huart);
private:
	UART_HandleTypeDef *huart;

	osMutexId_t sendMutexHandle;
	osMessageQueueId_t sendQueueId;

	osMutexId_t rcvMutexHandle;
	osMessageQueueId_t rcvQueueId;

	uint8_t *rxData;
	uint16_t rxSize;


public:
	Telemetry() = default;
	~Telemetry() = default;
	Telemetry(const Telemetry &other) = delete;
	Telemetry(Telemetry &&other) = delete;
	Telemetry& operator=(const Telemetry &other) = delete;
	Telemetry& operator=(Telemetry &&other) = delete;
};

extern Telemetry telem;
extern uint8_t telemBuffer[];

} /* namespace FC */

#endif /* PERIPHERAL_COMS_TELEMETRY_H_ */
