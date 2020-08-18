///*
// * FCI2C.h
// *
// *  Created on: Aug 5, 2020
// *      Author: cjb88
// */
//
//#ifndef DRIVER_FCI2C_H_
//#define DRIVER_FCI2C_H_
//
//#include "i2c.h"
//
//namespace FC{
//
//enum class i2cTaskType{
//	ReadIT,
//	WriteIT,
//	ReadDMA,
//	WriteDMA
//};
//
//typedef struct{
//	i2cTaskType type,
//	uint16_t DevAddress,
//	uint16_t MemAddress,
//	uint16_t MemAddSize,
//	uint8_t *pData,
//	uint16_t Size
//}i2cItem_t;
//
//class I2C{
//public:
//	I2C(I2C_HandleTypeDef *hi2c);
//	HAL_StatusTypeDef memReadIT(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
//	HAL_StatusTypeDef memWriteIT(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
//	void rxCpltCallback(UART_HandleTypeDef *huart);
//	void main();
//private:
//	I2C_HandleTypeDef *hi2c;
//
//	const uint8_t qLength;
//	StaticQueue_t xQueueBuffer;
//	uint8_t ucQueueStorage[sizeof(i2cItem_t)*qLength];
//	QueueHandle_t xQueue;
//};
//
//I2C i2c2(&hi2c);
//
//I2C::I2C(I2C_HandleTypeDef *hi2c, uint8_t qLength)
//	: qLength(qLength)
//{
//	xQueueCreateStatic(qLength,
//					   sizeof(i2cItem_t),
//					   ucQueueStorage,
//					   &xQueueBuffer);
//}
//
//void I2C::main(){
//	i2cItem_t item;
//	if(xQueueReceive(xQueue, &item, portMAX_DELAY)){
//		switch(item.type){
//		case i2cTaskType::ReadIT:
//			HAL_I2C_Mem_Read_IT(hi2c, item.DevAddress, item.MemAddress, item.MemAddSize, item.pData, item.Size);
//			break;
//		case i2cTaskType::WriteIT:
//			HAL_I2C_Mem_Write_IT(hi2c, item.DevAddress, item.MemAddress, item.MemAddSize, item.pData, item.Size);
//			break;
//		}
//	}
//}
//
//HAL_StatusTypeDef I2C::memReadIT(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size){
//	i2cItem_t item = {i2cTaskType::Read, DevAddress, MemAddress, MemAddSize, pData, Size};
//	xQueueSendToBack( xQueueBuffer, &item, NULL );
//}
//
//void I2C::rxCpltCallback(UART_HandleTypeDef *huart){
//
//}
//
//}
//
//extern "C"{
//void i2cMain(void* param){
//	while(1){
//		if(xQueueReceive(commandQueue))
//	}
//}
//}
//
//#endif /* DRIVER_FCI2C_H_ */
