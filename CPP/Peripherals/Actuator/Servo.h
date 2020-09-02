/*
 * Servo.h
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#ifndef ACTUATOR_SERVO_H_
#define ACTUATOR_SERVO_H_

#include "tim.h"

namespace FC {

class Servo {
public:

	/*
	 *  Servo timer frequency set to 50hz and counter 20000 (1 count = 1 microsecond).
	 *
	 *  \setting		PCLK : 240Mhz
	 *  				Prescaler : 240-1
	 *  				Counter Period : 20000-1
	 *  				-> 50hz
	 */
	Servo(TIM_HandleTypeDef *htim, uint32_t Channel);

	void start();

	void setMicrosecond(uint16_t us);

	inline void setPWM(uint16_t pwm) { setMicrosecond(pwm); }

private:
	TIM_HandleTypeDef* htim;
	uint32_t Channel;
	uint16_t us;

	static const uint16_t MIN_MICROSECOND = 1000;
	static const uint16_t MAX_MICROSECOND = 2000;

public:
	Servo() = delete;
	~Servo() = default;
	Servo(const Servo &other) = delete;
	Servo(Servo &&other) = delete;
	Servo& operator=(const Servo &other) = delete;
	Servo& operator=(Servo &&other) = delete;
};

extern Servo s1;
extern Servo s2;
extern Servo s3;
extern Servo s4;
extern Servo s5;
extern Servo s6;

} /* namespace FC */

#endif /* ACTUATOR_SERVO_H_ */
