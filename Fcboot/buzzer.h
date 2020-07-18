///*
// * buzzer.h
// *
// *  Created on: 2020. 7. 15.
// *      Author: cjb88
// */
//
//#ifndef BUZZER_H_
//#define BUZZER_H_
//
//// no sound.
//// special sound.
//
//HAL_TIM_Base_Start(&htim11);
//
//TIM_HandleTypeDef* buzzer_phtim;
//
//static uint8_t buzzer_delayStart = 0;
//static uint32_t buzzer_delayTime = 0;
//
//enum notes {
//  C4 = 26163, // 도(261.63Hz)
//  D4 = 29366, // 래(293.66Hz)
//  E4 = 32963, // 미(329.63Hz)
//  F4 = 34923, // 파(349.23Hz)
//  G4 = 39200, // 솔(392.00Hz)
//  A4 = 44000, // 라(440.00Hz)
//  B4 = 49388, // 시(493.88Hz)
//  C5 = 52325  // 도(523.25Hz)
//};
//
//void buzzer_start(TIM_HandleTypeDef* phtim, uint32_t Channel){
//	buzzer_phtim = phtim;
//	HAL_TIM_PWM_Start(phtim, Channel);
//}
//
//void buzzer_update(){
//
//}
//
//uint8_t buzzer_delay(uint32_t delay){ // ms
//	if(buzzer_delayStart){
//		return (HAL_GetTick() - buzzer_delayTime) > delay;
//	}
//	else{
//		buzzer_
//		buzzer_delayStart = 1;
//	}
//}
//void buzzer_delayReset(){
//	buzzer_delayStart = 0;
//}
//
//
//#endif /* BUZZER_H_ */
