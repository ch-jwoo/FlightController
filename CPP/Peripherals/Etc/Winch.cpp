/*
 * Winch.cpp
 *
 *  Created on: Nov 10, 2020
 *      Author: cjb88
 */

#include <Peripherals/Etc/Winch.h>

namespace FC{

Winch winch(GPIOE, GPIO_PIN_2);

Winch::Winch(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
: GPIOx(GPIOx)
, GPIO_Pin(GPIO_Pin)
{}


}

