/*
 * State.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */


#include "State.h"
#include "estimate.h"
#include "MPU9250.h"

uint8_t vehicleState = VEHICLE_INIT;
uint8_t flightMode;

// hz check

uint16_t imu_state, mag_state, sbus_state, gps_state, estimator_state;
uint16_t imu_hz, mag_hz, sbus_hz, gps_hz, estimator_hz;
void sensorHz_update(){
	imu_hz = MPU9250_getHz();
	estimator_hz = estimate_getHz(&iEstimate);
	sbus_hz = sbus_getHz();

	//state update
	imu_state = imu_hz > 60 ? STATE_STABLE : STATE_DISABLE;
	estimator_state = estimator_hz > 60 ? STATE_STABLE : STATE_DISABLE;
	sbus_state = sbus_hz > 60 ? STATE_STABLE : STATE_DISABLE;
}

void sensorHz_print(){
	printf("imu: %uhz, estimator: %uhz, sbus_hz: %uhz\r\n", imu_hz, estimator_hz, sbus_hz);
}
