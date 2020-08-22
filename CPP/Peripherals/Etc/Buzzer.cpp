/*
 * Buzzer.cpp
 *
 *  Created on: 2020. 8. 23.
 *      Author: cjb88
 */

#include <Peripherals/Etc/Buzzer.h>

namespace FC {

Buzzer buzzer(&htim5, TIM_CHANNEL_2, 1);

Buzzer::Buzzer(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t APBNum)
: htim(htim)
, Channel(Channel)
{
	if(APBNum == 1) PCLK = HAL_RCC_GetPCLK1Freq();
	else			PCLK = HAL_RCC_GetPCLK2Freq();
}

void Buzzer::setNote(Note_t note){
	__HAL_TIM_SET_PRESCALER(htim, PCLK / note * 1000);
}

} /* namespace FC */
