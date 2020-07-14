/*
 * State.h
 *
 *  Created on: Jul 13, 2020
 *      Author: cjb88
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MPU9250.h"

enum state{
	STATE_DISABLE,
	STATE_UNSTABLE,
	STATE_STABLE
};

extern uint16_t imu_state, mag_state, sbus_state, gps_state, estimator_state;
extern uint16_t imu_hz, mag_hz, sbus_hz, gps_hz, estimator_hz;
void sensorHz_update();

enum vehicleState{
	VEHICLE_INIT = 0,
	VEHICLE_PREARM,
	VEHICLE_DISARM,
	VEHICLE_ARM
};

enum flightMode{
	FLIGHT_ATTITUDE = 0,
	FLIGHT_POSITION,
	FLIGHT_MISSION
};

extern uint8_t vehicleState;
extern uint8_t flightMode;

#ifdef __cplusplus
}
#endif

#endif /* INC_STATE_H_ */
