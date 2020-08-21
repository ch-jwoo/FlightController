/*
 * function.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef UTILS_FUNCTIONS_H_
#define UTILS_FUNCTIONS_H_

#include <cstdint>

namespace FC{

float map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max);

float radianThreshold(float radian);

float deg2rad(float);

float rad2deg(float);


}

#endif /* UTILS_FUNCTIONS_H_ */
