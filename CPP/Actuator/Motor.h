/*
 * Motor.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef ACTUATOR_MOTOR_H_
#define ACTUATOR_MOTOR_H_

#include "main.h"
#include "tim.h"

namespace FC {

class Motor {
public:

	/*
	 *  This class use standard pwm protocol ~ 500hz
	 *  And, we are adopted 500hz
	 *  minimum pwm at 1ms,
	 *  maximum duty cycle is 2ms
	 *  \setting		PCLK : 168Mhz
	 *  				Prescaler : 4-1
	 *  				Counter Period : 42000-1
	 *  				-> 500hz
	 *
	 *  				PCLK : 100Mhz
	 *  				Prescaler : 5-1
	 *  				Counter Period : 40000-1
	 *  				-> 500hz
	 */
	Motor(TIM_HandleTypeDef *htim, uint32_t Channel);

	/*
	 *  set pwm to 1000(duty cycle is 25%), and start timer
	 */
	void start();

	/*
	 *  stop the pwm timer, set pwm to 0
	 */
	void stop();

	/*
	 *  set motor pwm (1000 ~ 2000)
	 *  \param[in]		pwm		integer value(1000 ~ 2000)
	 */
	void setPWM(uint16_t pwm);

	~Motor() = default;
	Motor(const Motor &other) = delete;
	Motor(Motor &&other) = delete;
	Motor& operator=(const Motor &other) = delete;
	Motor& operator=(Motor &&other) = delete;

	uint32_t Channel;
private:
	TIM_HandleTypeDef* htim;
	uint16_t pwm;

	static const uint16_t MIN_PWM = 1000;
	static const uint16_t MAX_PWM = 2000;

	static const uint16_t MIN_CCR = 20000;		/* duty cycle 1ms */
	static const uint16_t MAX_CCR = 40000;		/* duty cycle 2ms */
};

extern Motor m1;
extern Motor m2;
extern Motor m3;
extern Motor m4;
extern Motor m5;
extern Motor m6;

} /* namespace FC */

#endif /* ACTUATOR_MOTOR_H_ */
