/*
 * VoltageChecker.h
 *
 *  Created on: Aug 28, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERALS_SENSORS_VOLTAGECHECKER_H_
#define PERIPHERALS_SENSORS_VOLTAGECHECKER_H_

#include "adc.h"

namespace FC {

class VoltageChecker {
public:

	/*
	 * 	targetVoltage -> (R1) ------> (R2) -> GND
	 * 							||
	 * 						    \/
	 * 						  (ADC)
	 *
	 *  \param[in]		*hadc					adc handler
	 *  \param[in]		refVolt					real reference voltage
	 *  \param[in]		resistanceR1			resistance R1 in kOhm
	 *  \param[in]		resistanceR2			resistance R2 in kOhm
	 *  \param[in]		constantA				compensate function(ax + b) constant a
	 *  \param[in]		constantB				compensate function(ax + b) constant b
	 */
	VoltageChecker(ADC_HandleTypeDef *hadc, float refVolt, float resistanceR1, float resistanceR2, float constantA, float constantB);

	void start();

	void callback(ADC_HandleTypeDef* hadc);

	inline float compensateVoltage(float voltage){
		return (voltage * constantA) + constantB;
	}

	float voltage;
	float compVoltage;

private:
	static const uint8_t AVG_SIZE = 1;

	ADC_HandleTypeDef *hadc;
	float refVoltageConstant;
	float resistanceConstant;
	float constantA;
	float constantB;

	uint16_t adcVal[AVG_SIZE];
	float adcMultiply;


public:
	VoltageChecker() = delete;
	~VoltageChecker() = default;
	VoltageChecker(const VoltageChecker &other) = delete;
	VoltageChecker(VoltageChecker &&other) = delete;
	VoltageChecker& operator=(const VoltageChecker &other) = delete;
	VoltageChecker& operator=(VoltageChecker &&other) = delete;
};

extern VoltageChecker voltageChecker;

} /* namespace FC */

#endif /* PERIPHERALS_SENSORS_VOLTAGECHECKER_H_ */
