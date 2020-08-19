/*
 * function.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef UTILS_FUNCTION_H_
#define UTILS_FUNCTION_H_

#include "Constant.h"

namespace FC{

static float map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max){
	return (float)(value - in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}

static float radianThreshold(float radian){
	while(radian >= FC_PI){
		radian -= FC_2PI;
	}
	while(radian <= -FC_PI){
		radian += FC_2PI;
	}
	return radian;
}

}

#endif /* UTILS_FUNCTION_H_ */
