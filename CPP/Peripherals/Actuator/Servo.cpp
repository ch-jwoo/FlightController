/*
 * Servo.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#include "Servo.h"

namespace FC {

/*
 *  S1 	PE11 	TIM1 	TIM_CHANNEL_2
 *  S2 	PE13 	TIM1 	TIM_CHANNEL_3
 *  S3 	PE14 	TIM1 	TIM_CHANNEL_4
 *  S4 	PE9 	TIM1 	TIM_CHANNEL_1
 *  S5 	PB14 	TIM12 	TIM_CHANNEL_1
 *  S6 	PB15 	TIM12	TIM_CHANNEL_2
 */

Servo s1(&htim1, 	TIM_CHANNEL_2);
Servo s2(&htim1, 	TIM_CHANNEL_3);
Servo s3(&htim1, 	TIM_CHANNEL_4);
Servo s4(&htim1, 	TIM_CHANNEL_1);
Servo s5(&htim12,	TIM_CHANNEL_1);
Servo s6(&htim12,	TIM_CHANNEL_2);

Servo::Servo(TIM_HandleTypeDef *htim, uint32_t Channel)
: htim(htim)
, Channel(Channel)
, us(0)
{}

void Servo::start(){
	HAL_TIM_PWM_Start(htim, Channel);
	setPWM(1000);
}

void Servo::setMicrosecond(uint16_t us){
	if(us > MAX_MICROSECOND)		us = MAX_MICROSECOND;
	else if(us < MIN_MICROSECOND)	us = MIN_MICROSECOND;
	this->us = us;
	__HAL_TIM_SET_COMPARE(htim, Channel, us);
}

} /* namespace FC */
