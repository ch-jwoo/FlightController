/*
 * Buzzer.h
 *
 *  Created on: 2020. 8. 23.
 *      Author: cjb88
 */

#ifndef PERIPHERALS_ETC_BUZZER_H_
#define PERIPHERALS_ETC_BUZZER_H_

#include "tim.h"

namespace FC {

typedef enum {
	C3 = 13100, // do
	D3 = 14700, // re
	E3 = 16500, // mi
	F3 = 17500, // pa
	G3 = 19600, // sol
	A3 = 22000, // ra
	B3 = 24700, // si
	C4 = 26163, // do (261.63Hz)
	D4 = 29366, // re (293.66Hz)
	E4 = 32963, // mi (329.63Hz)
	F4 = 34923, // pa (349.23Hz)
	G4 = 39200, // soi (392.00Hz)
	A4 = 44000, // ra (440.00Hz)
	B4 = 49388, // si (493.88Hz)
	C5 = 52325, // do (523.25Hz)
	D5 = 58700, // re
	E5 = 65900, // mi
	F5 = 69800,  // pa
	A1 = 200000, //Low Battery
	Z1 = 260000,
	Z2 = 274000,
	Z3 = 280000,
	Z4 = 100000,
	Z5 = 285000,
	Z6 = 380000		/* 3800hz */
} Note_t;

class Buzzer {
public:
	Buzzer(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t APBNum);

	void setNote(Note_t note);

	inline void start(){
		HAL_TIM_PWM_Start(htim, Channel);
	}
	inline void stop(){
		HAL_TIM_PWM_Stop(htim, Channel);
	}

private:
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint32_t PCLK;

public:
	Buzzer() = delete;
	~Buzzer() = default;
	Buzzer(const Buzzer &other) = delete;
	Buzzer(Buzzer &&other) = delete;
	Buzzer& operator=(const Buzzer &other) = delete;
	Buzzer& operator=(Buzzer &&other) = delete;
};

extern Buzzer buzzer;

} /* namespace FC */

#endif /* PERIPHERALS_ETC_BUZZER_H_ */
