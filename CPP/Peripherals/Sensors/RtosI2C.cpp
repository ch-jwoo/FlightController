/*
 * RtosI2C.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#include "RtosI2C.h"

namespace FC {

RtosI2C rtosI2C1(&hi2c1, I2C_DMA);
RtosI2C rtosI2C2(&hi2c2, I2C_Interrupt);

RtosI2C::RtosI2C(I2C_HandleTypeDef *hi2c, RtosI2Ctype type)
: hi2c(hi2c)
, type(type)
{
	readMutexHandle = osMutexNew(NULL);
	readQueueId = osMessageQueueNew(1, sizeof(uint8_t), NULL);

	writeMutexHandle = osMutexNew(NULL);
	writeQueueId = osMessageQueueNew(1, sizeof(uint8_t), NULL);
}

void RtosI2C::read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(readMutexHandle, osWaitForever);

//	switch(type){
//	case I2C_Interrupt:
//		HAL_I2C_Mem_Read_IT(hi2c, DevAddress, MemAddress, 1, pData, Size);
//		break;
//	case I2C_DMA:
//		HAL_I2C_Mem_Read_DMA(hi2c, DevAddress, MemAddress, 1, pData, Size);
//		break;
//	}
	_read(DevAddress, MemAddress, pData, Size);
	while(osMessageQueueGet(readQueueId, (void*)&ret, NULL, 1000) != osOK){
		_read(DevAddress, MemAddress, pData, Size);
	}

	osMutexRelease(readMutexHandle);
}

void RtosI2C::write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size){
	uint8_t ret = 0;
	osMutexAcquire(writeMutexHandle, osWaitForever);

	_write(DevAddress, MemAddress, pData, Size);
	while(osMessageQueueGet(writeQueueId, (void*)&ret, NULL, 1000) != osOK){
		_write(DevAddress, MemAddress, pData, Size);
	}
//	switch(type){
//	case I2C_Interrupt:
//		HAL_I2C_Mem_Write_IT(hi2c, DevAddress, MemAddress, 1, pData, Size);
//		break;
//	case I2C_DMA:
//		HAL_I2C_Mem_Write_DMA(hi2c, DevAddress, MemAddress, 1, pData, Size);
//		break;
//	}

	osMutexRelease(writeMutexHandle);
}

void RtosI2C::readCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance != this->hi2c->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(readQueueId, (void*)&ret, 0, 0);
}

void RtosI2C::writeCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance != this->hi2c->Instance) return;
	uint8_t ret = 0;
	osMessageQueuePut(writeQueueId, (void*)&ret, 0, 0);
}

} /* namespace FC */
