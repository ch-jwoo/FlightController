/*
 * usec.h
 *
 *  Created on: Jul 30, 2020
 *      Author: cjb88
 */
#ifndef __USEC__H
#define __USEC__H

#include "main.h"
#include "tim.h"


/* micro second counter timer */
#define USEC_TIMER &htim2

static uint32_t _timerOverflowCnt = 0;

static __inline uint64_t microsecond(){
	return ((uint64_t)_timerOverflowCnt<<32) | (__HAL_TIM_GetCounter(USEC_TIMER));
}

static __inline void msOverFlow(){
	_timerOverflowCnt++;
}

#endif
