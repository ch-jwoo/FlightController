/*
 * usec.h
 *
 *  Created on: Jul 30, 2020
 *      Author: cjb88
 */

#ifndef FC_USEC_H_
#define FC_USEC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "tim.h"

#define FC_USEC_TIMER &htim2

uint32_t _fcOverflowCnt;
static __inline uint32_t fcMicroSecond(){
	return ((uint64_t)_fcOverflowCnt<<32) | (__HAL_TIM_GetCounter(FC_USEC_TIMER));
}

static __inline void fcMsOverFlow(){
	_fcOverflowCnt++;
}

#ifdef __cplusplus
}
#endif

#endif /* FC_USEC_H_ */
