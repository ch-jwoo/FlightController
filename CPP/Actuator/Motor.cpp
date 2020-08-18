/*
 * Motor.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include <Actuator/Motor.h>

namespace FC {


/*
 *  M1 PB1 TIM3 CHANNEL4
 *  M2 PB4 TIM3 CHANNEL1
 *  M3 PA7 TIM3 CHANNEL2
 *  M4 PA0 TIM5 CHANNEL1
 *  M5 PA1 TIM5 CHANNEL2
 *  M6 PB0 TIM3 CHANNEL3
 */

Motor m1(&htim3, TIM_CHANNEL_4);
Motor m2(&htim3, TIM_CHANNEL_1);
Motor m3(&htim3, TIM_CHANNEL_2);
Motor m4(&htim5, TIM_CHANNEL_1);
Motor m5(&htim5, TIM_CHANNEL_2);
Motor m6(&htim3, TIM_CHANNEL_3);

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
