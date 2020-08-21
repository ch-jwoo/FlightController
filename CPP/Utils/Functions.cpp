/*
 * Functions.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#include "Functions.h"

#include <Utils/Constants.h>
#include <cmath>
#define _USE_MATH_DEFINES



float FC::map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max){
	return (float)(value - in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}


float FC::radianThreshold(float radian){
	while(radian >= FC_PI){
		radian -= FC_2PI;
	}
	while(radian <= -FC_PI){
		radian += FC_2PI;
	}
	return radian;
}

float FC::deg2rad(float num){
	return num * (float)M_PI / 180.0;
}

float FC::rad2deg(float num){
	return num * 180.0 / (float)M_PI;
}
