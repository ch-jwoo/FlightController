///*
// * UartControl.h
// *
// *  Created on: Oct 5, 2020
// *      Author: cjb88
// */
//
//#ifndef PERIPHERALS_COMS_UARTCONTROL_H_
//#define PERIPHERALS_COMS_UARTCONTROL_H_
//
//#include "usart.h"
//
//class UartControl {
//public:
//	UartControl(UART_HandleTypeDef *huart);
//	void setThrotle(uint16_t value);
//	void setRoll(uint16_t value);
//	void setPitch(uint16_t value);
//	void setYaw(uint16_t value);
//	void setArm(uint16_t value);
//	void setTilt(uint16_t value);
//	void setMode(uint16_t value);
//
//	void init();
//	void rcvCompleteCallback(UART_HandleTypeDef *huart);
//
//private:
//	UART_HandleTypeDef *huart;
//	uint8_t buf;
//	uint8_t len;
//
//public:
//	virtual ~UartControl();
//	UartControl(const UartControl &other);
//	UartControl(UartControl &&other);
//	UartControl& operator=(const UartControl &other);
//	UartControl& operator=(UartControl &&other);
//};
//
//#endif /* PERIPHERALS_COMS_UARTCONTROL_H_ */
