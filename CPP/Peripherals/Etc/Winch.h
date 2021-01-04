/*
 * Winch.h
 *
 *  Created on: Nov 10, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERALS_ETC_WINCH_H_
#define PERIPHERALS_ETC_WINCH_H_

#include "gpio.h"

namespace FC{

class Winch {
public:
	Winch(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

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
	Winch() = delete;
	~Winch() = default;
	Winch(const Winch &other) = delete;
	Winch(Winch &&other) = delete;
	Winch& operator=(const Winch &other) = delete;
	Winch& operator=(Winch &&other) = delete;
};

extern Winch winch;

}
#endif /* PERIPHERALS_ETC_WINCH_H_ */
