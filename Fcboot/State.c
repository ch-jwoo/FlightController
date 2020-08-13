/*
 * State.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */


#include "State.h"
#include "estimate.h"
#include "MPU9250.h"

struct bootState iBootState;


// hz check
uint16_t imu_hz, mag_hz, sbus_hz, gps_hz, estimator_hz;
void sensorHz_update(){
	imu_hz = MPU9250_getHz();
	estimator_hz = estimate_getHz(&iEstimate);
	sbus_hz = sbus_getHz();
}

void sensorHz_print(){
	printf("imu: %uhz, estimator: %uhz, sbus_hz: %uhz\r\n", imu_hz, estimator_hz, sbus_hz);
}
