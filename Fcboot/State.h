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



#ifdef __cplusplus
}
#endif

#endif /* INC_STATE_H_ */
