/*
 * Motor.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Peripherals/Actuator/Motor.h>
#include "printf.h"

namespace FC {


/*
 *  M1 	PD15 	TIM4 	CHANNEL4
 *  M2 	PD14 	TIM4 	CHANNEL3
 *  M3 	PD12 	TIM4 	CHANNEL1
 *  M4 	PD13 	TIM4 	CHANNEL2
 *  M5 	PB1 	TIM3 	CHANNEL4
 *  M6 	PC7 	TIM3 	CHANNEL2
 */

Motor m1(&htim4, TIM_CHANNEL_4);
Motor m2(&htim4, TIM_CHANNEL_3);
Motor m3(&htim4, TIM_CHANNEL_1);
Motor m4(&htim4, TIM_CHANNEL_2);
Motor m5(&htim3, TIM_CHANNEL_4);
Motor m6(&htim3, TIM_CHANNEL_2);

Motor::Motor(TIM_HandleTypeDef *htim, uint32_t Channel)
	: htim(htim)
	, Channel(Channel)
	, pwm(1000)
{ }

void Motor::start(){
	HAL_TIM_PWM_Start(htim, Channel);
	setPWM(1000);
}

void Motor::stop(){
	HAL_TIMEx_PWMN_Stop(htim, Channel);
}

void Motor::setPWM(uint16_t pwm){
	if(pwm < MIN_PWM) 			pwm = MIN_PWM;
	else if(pwm > MAX_PWM)		pwm = MAX_PWM;

	this->pwm = pwm;

	/*
	 *  pwm(1000 ~ 2000) scale to CCR register value(10500 ~ 21000);
	 */
	uint16_t output = (pwm - MIN_PWM) * ((MAX_CCR - MIN_CCR) / (MAX_PWM - MIN_PWM)) + MIN_CCR;
	__HAL_TIM_SET_COMPARE(htim, Channel, output);
}

} /* namespace FC */
