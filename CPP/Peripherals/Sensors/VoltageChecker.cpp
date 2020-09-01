/*
 * VoltageChecker.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: cjb88
 */

#include <Peripherals/Sensors/VoltageChecker.h>
#include "printf.h"

namespace FC {

VoltageChecker voltageChecker(&hadc3, 3.3f, 330.0f, 47.0f, 0.004051f, -0.006481f);

VoltageChecker::VoltageChecker(ADC_HandleTypeDef *hadc, float refVolt, float resistanceR1, float resistanceR2, float constantA, float constantB)
:hadc(hadc)
,constantA(constantA)
,constantB(constantB)
{
	resistanceConstant = (resistanceR1+resistanceR2)/resistanceR2;
	refVoltageConstant = refVolt / 4096.0f;		/* 12bit */
	adcMultiply = resistanceConstant * refVoltageConstant;
}

void VoltageChecker::start(){
//	HAL_ADC_Start_IT(hadc);  // start using ADC
	HAL_ADC_Start_DMA(hadc, (uint32_t*)adcVal, AVG_SIZE);
}

void VoltageChecker::callback(ADC_HandleTypeDef* hadc){
	if(this->hadc->Instance != hadc->Instance) return;
	//		adcVal = HAL_ADC_GetValue(hadc);				/* if interrupt */
	uint32_t sum = 0;
	for(int i=0; i<AVG_SIZE; i++){
		sum += adcVal[i];
	}
	float avgAdcVal = (float)sum/AVG_SIZE;
	voltage = avgAdcVal * adcMultiply;
	compVoltage = voltage + compensateVoltage(voltage);
	printf_("%f\r\n", voltageChecker.compVoltage);
}


} /* namespace FC */
