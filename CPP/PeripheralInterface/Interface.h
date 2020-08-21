/*
 * Interface.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef PERIPHERALINTERFACE_INTERFACE_H_
#define PERIPHERALINTERFACE_INTERFACE_H_

#include <PeripheralInterface/RC.h>
#include <PeripheralInterface/SensorAccel.h>
#include <PeripheralInterface/SensorGPS.h>
#include <PeripheralInterface/SensorGyro.h>
#include <PeripheralInterface/SensorMag.h>
#include "SensorBaro.h"
#include "SensorLidar.h"

namespace FC{

extern RC rc;
extern SensorAccel sensorAccel;
extern SensorGyro sensorGyro;
extern SensorMag sensorMag;
extern SensorBaro sensorBaro;
extern SensorGPS sensorGPS;
extern SensorLidar sensorLidar;

}


#endif /* PERIPHERALINTERFACE_INTERFACE_H_ */
