
//=====================================================================================================
// MadgwickAHRS.c
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
//
//=====================================================================================================

//---------------------------------------------------------------------------------------------------
// Header files

#include "algorithmCollection.h"
#include <math.h>

#define DEG2PI 0.01745329251F

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void junTimer_tic(struct junTimer* t){
   t->last_time = HAL_GetTick();
   t->start = 1;
}

uint32_t junTimer_toc(struct junTimer* t){
   return HAL_GetTick() - t->last_time;
}

//====================================================================================================
// END OF CODE
//====================================================================================================

