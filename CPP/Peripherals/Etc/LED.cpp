/*
 * LED.cpp
 *
 *  Created on: Aug 23, 2020
 *      Author: cjb88
 */

#include <Peripherals/Etc/LED.h>

namespace FC {

LED led1(GPIOF, GPIO_PIN_2);
LED led2(GPIOF, GPIO_PIN_3);
LED led3(GPIOF, GPIO_PIN_4);

LED::LED(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
: GPIOx(GPIOx)
, GPIO_Pin(GPIO_Pin)
{}

} /* namespace FC */
