/*
 * ModuleINS.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#include "ModuleINS.h"
#include <Utils/Constants.h>
#include "Usec.h"
#include "printf.h"

namespace FC {


ModuleINS::ModuleINS()
	: refLat(0)
	, refLon(0)
	, refAlt(0)
{}

void ModuleINS::onestep(){
	ExtU input;
	if(msgBus.getNedAccel(&nedAccelSub)){
		input.AhrsFlag = true;
		input.ax = nedAccelSub.xyz[0];
		input.ay = nedAccelSub.xyz[1];
		input.az = nedAccelSub.xyz[2] + FC_GRAVITY_ACCEERATION;		/* subtract gravity */
	}
	else input.AhrsFlag = false;

	if(msgBus.getGPS(&gpsSub)){
		input.GpsFlag = false;
	}
	else input.GpsFlag = false;

	if(msgBus.getBarometer(&baroSub)){
		input.BaroFlag = true;
		input.baroZ = baroSub.altitude;
	}
	else input.BaroFlag = false;

	if(msgBus.getLidar(&lidar) && lidar.valid){
		input.LidarFlag = true;
		input.Lidar_height = lidar.altitude;
	}
	else input.LidarFlag = false;

	setExternalInputs(&input);
	step();
	ExtY output = getExternalOutputs();


	localPositionPub.timestamp = microsecond();
	localPositionPub.ax = (float)output.estiAX;
	localPositionPub.ay = (float)output.estiAY;
	localPositionPub.az = (float)output.estiAZ;

	localPositionPub.vx = (float)output.estiVX;
	localPositionPub.vy = (float)output.estiVY;
	localPositionPub.vz = (float)output.estiVZ;

	localPositionPub.x = (float)output.estiX;
	localPositionPub.y = (float)output.estiY;
	localPositionPub.z = (float)output.estiZ;

	msgBus.getAttitude(&attitudeSub);
	localPositionPub.yaw = attitudeSub.yaw;

	msgBus.setLocalPosition(localPositionPub);
}


} /* namespace FC */
