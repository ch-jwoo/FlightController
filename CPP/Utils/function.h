/*
 * function.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef UTILS_FUNCTION_H_
#define UTILS_FUNCTION_H_

namespace FC{

static float map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max){
	return (float)(value - in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}

}

#endif /* UTILS_FUNCTION_H_ */
