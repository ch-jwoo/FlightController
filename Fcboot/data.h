/*
 * data.h
 *
 *  Created on: Jul 30, 2020
 *      Author: cjb88
 */

#ifndef DATA_H_
#define DATA_H_

#include "main.h"

typedef struct {
	uint64_t timestamp;

	float xyz[3];
} sensor_accel;

typedef struct{
	uint64_t timestamp;

	float xyz[3];
} sensor_gyro;

#endif /* DATA_H_ */
