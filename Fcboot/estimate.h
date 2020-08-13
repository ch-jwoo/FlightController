/*
 * estimator.h
 *
 *  Created on: Jul 13, 2020
 *      Author: cjb88
 */

#ifndef INC_ESTIMATOR_H_
#define INC_ESTIMATOR_H_

#include "algorithmCollection.h"
#include "MPU9250.h"

#ifdef __cplusplus
extern "C" {
#endif

struct estimate{
	float bodyQ[4]; // quaternion from NED
	float roll, pitch, yaw;
	float p, q, r;
	float ax,ay,az;
	uint16_t estimate_hzcnt;
};

void MadgwickAHRSupdate(struct estimate* e, float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MadgwickAHRSupdateIMU(struct estimate* e, float gx, float gy, float gz, float ax, float ay, float az, float dt);

void estimate_update(struct estimate* e, struct MPU9250* mpu9250);

void estimate_print(struct estimate* e);

extern struct estimate iEstimate;
uint16_t estimate_getHz();


#ifdef __cplusplus
}
#endif
#endif /* INC_ESTIMATOR_H_ */
