/*
 * RtosI2C.h
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERAL_COMS_RTOSI2C_H_
#define PERIPHERAL_COMS_RTOSI2C_H_

#include "i2c.h"
#include "cmsis_os.h"

namespace FC {

typedef enum {
	I2C_Interrupt,
	I2C_DMA
} RtosI2Ctype;

class RtosI2C {
public:

	/*
	 * 	i2c using mutex, dma, interrupt
	 *  \pram[in]		hi2c		hal hi2c handler address
	 *  \pram[in]		type		dma or interrupt
	 */
	RtosI2C(I2C_HandleTypeDef *hi2c, RtosI2Ctype type);

	/*
	 *  read memory from i2c
	 *  \pram[in]		DevAddress		device address
	 *  \pram[in]		MemAddress		memory address
	 *  \pram[out]		pData			read data
	 *  \pram[in]		Size			read data size
	 */
	void read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);

	/*
	 *  \pram[in]		DevAddress		device address
	 *  \pram[in]		MemAddress		memory address
	 *  \pram[out]		pData			write data
	 *  \pram[in]		Size			write data size
	 */
	void write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);

	/*
	 *  callback function
	 */
	void readCpltCallback(I2C_HandleTypeDef *hi2c);
	void writeCpltCallback(I2C_HandleTypeDef *hi2c);
private:
	I2C_HandleTypeDef *hi2c;
	RtosI2Ctype type;

	osMutexId_t readMutexHandle;
	osMessageQueueId_t readQueueId;

	osMutexId_t writeMutexHandle;
	osMessageQueueId_t writeQueueId;

public:
	RtosI2C() = default;
	~RtosI2C() = default;
	RtosI2C(const RtosI2C &other) = delete;
	RtosI2C(RtosI2C &&other) = delete;
	RtosI2C& operator=(const RtosI2C &other) = delete;
	RtosI2C& operator=(RtosI2C &&other) = delete;
};

extern RtosI2C rtosI2C1;
extern RtosI2C rtosI2C2;

} /* namespace FC */

#endif /* PERIPHERAL_COMS_RTOSI2C_H_ */
