///*
// * VoltageChecker.h
// *
// *  Created on: Aug 28, 2020
// *      Author: cjb88
// */
//
//#ifndef PERIPHERALS_SENSORS_VOLTAGECHECKER_H_
//#define PERIPHERALS_SENSORS_VOLTAGECHECKER_H_
//
//#include "adc.h"
//
//namespace FC {
//
//class VoltageChecker {
//public:
//
//	/*
//	 * 	targetVoltage -> (R1) ------> (R2) -> GND
//	 * 							||
//	 * 						    \/
//	 * 						  (ADC)
//	 *
//	 *  \param[in]		*hadc					adc handler
//	 *  \param[in]		refVolt					real reference voltage
//	 *  \param[in]		resistanceR1			resistance R1 in kOhm
//	 *  \param[in]		resistanceR2			resistance R2 in kOhm
//	 *  \param[in]		constantA				compensate function(ax + b) constant a
//	 *  \param[in]		constantB				compensate function(ax + b) constant b
//	 */
//	VoltageChecker(ADC_HandleTypeDef *hadc, float refVolt, float resistanceR1, float resistanceR2, float constantA, float constantB)
//	:hadc(hadc)
//	,constantA(constantA)
//	,constantB(constantB)
//	{
//		resistanceConstant = (R1+R2)/R2;
//		refVoltageConstant = refVoltage / 4096.0f;		/* 12bit */
//		adcMultiply = resistanceConstant * refVoltageConstant;
//	}
//
//	void start(){
////		HAL_ADC_Start_IT(hadc);  // start using ADC
//		HAL_ADC_Start_DMA(hadc, &adcVal, AVG_SIZE);
//	}
//
//	void callback(ADC_HandleTypeDef* hadc){
//		if(this->hadc->Instance != hadc->Instance) return;
//		//		adcVal = HAL_ADC_GetValue(hadc);				/* if interrupt */
//		uint32_t sum = 0;
//		for(int i=0; i<AVG_SIZE; i++){
//			sum += adcVal[i];
//		}
//		float avgAdcVal = (float)sum/AVG_SIZE;
//		voltage = avgAdcVal * adcMultiply;
//		compVoltage = voltage + compensateVoltage(voltage);
//	}
//
//	inline float compensateVoltage(float voltage){
//		return (voltage * constantA) + constantB;
//	}
//
//	float voltage;
//	float compVoltage;
//
//private:
//	ADC_HandleTypeDef *hadc;
//	float refVoltageConstant;
//	float resistanceConstant;
//	float constantA;
//	float constantB;
//
//	uint16_t adcVal[AVG_SIZE];
//	float adcMultiply;
//
//	static const uint8_t AVG_SIZE = 20;
//
//public:
//	VoltageChecker() = delete;
//	~VoltageChecker() = default;
//	VoltageChecker(const VoltageChecker &other) = delete;
//	VoltageChecker(VoltageChecker &&other) = delete;
//	VoltageChecker& operator=(const VoltageChecker &other) = delete;
//	VoltageChecker& operator=(VoltageChecker &&other) = delete;
//};
//
//VoltageChecker voltageChecker(&hadc3, 3.3f, 330.0f, 47.0f, 0.004051f, -0.006481f);
//
//} /* namespace FC */
//
//#endif /* PERIPHERALS_SENSORS_VOLTAGECHECKER_H_ */
