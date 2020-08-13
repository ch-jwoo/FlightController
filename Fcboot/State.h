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
	Disable,
	Able
};

struct bootState{
	enum state imu;
	enum state mag;
	enum state sbus;
	enum state gps;
	enum state telemetry;
	enum state estimator;
};

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

uint8_t vehicleState;
uint8_t flightMode;

#ifdef __cplusplus
}
#endif

#endif /* INC_STATE_H_ */
