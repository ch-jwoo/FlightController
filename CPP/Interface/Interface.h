/*
 * Interface.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef INTERFACE_INTERFACE_H_
#define INTERFACE_INTERFACE_H_

#include <Interface/InterfaceAccel.h>
#include <Interface/InterfaceBaro.h>
#include <Interface/InterfaceGPS.h>
#include <Interface/InterfaceGyro.h>
#include <Interface/InterfaceLidar.h>
#include <Interface/InterfaceMag.h>
#include <Interface/InterfaceRC.h>

namespace FC{

extern InterfaceRC interfaceRC;
extern InterfaceAccel interfaceAccel;
extern InterfaceGyro interfaceGyro;
extern InterfaceMag interfaceMag;
extern InterfaceBaro sensorBaro;
extern InterfaceGPS interfaceGPS;
extern InterfaceLidar interfaceLidar;

}


#endif /* INTERFACE_INTERFACE_H_ */
