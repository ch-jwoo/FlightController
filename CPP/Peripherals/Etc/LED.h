/*
 * LED.h
 *
 *  Created on: Aug 23, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERALS_ETC_LED_H_
#define PERIPHERALS_ETC_LED_H_

#include "gpio.h"

namespace FC {

class LED {
public:
	LED(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

	inline void toggle(){
		HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
	}
	inline void set(){
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
	inline void reset(){
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}
private:
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
public:
	LED() = delete;
	~LED() = default;
	LED(const LED &other) = delete;
	LED(LED &&other) = delete;
	LED& operator=(const LED &other) = delete;
	LED& operator=(LED &&other) = delete;
};

extern LED led1;
extern LED led2;
extern LED led3;

} /* namespace FC */

#endif /* PERIPHERALS_ETC_LED_H_ */
