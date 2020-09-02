/*
 * ModuleINS.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#include "ModuleINS.h"
#include <Utils/Constants.h>
#include <Module/Controller/ModulePositionController.h>
#include "Usec.h"

namespace FC {

bool ModuleINS::calGpsHomeFlag = true;
uint8_t ModuleINS::avgIndexGPS = 0;
double ModuleINS::avgLat = 0;
double ModuleINS::avgLon = 0;
float ModuleINS::avgAlt = 0;

ModuleINS::ModuleINS()
	: refLat(0)
	, refLon(0)
	, refAlt(0)
{}

void ModuleINS::main(){
	uint32_t tick;
	tick = osKernelGetTickCount();

	ModuleINS moduleINS;
	moduleINS.initialize();
	osDelay(2000);
	while(1){
		tick += 5;
		osDelayUntil(tick);

		moduleINS.onestep();
		ModulePositionController::setSignal(PC_fromEKF);
	}
}

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
		if(calGpsHomeFlag && gpsSub.fixType != 0){
			calAvgLLA(gpsSub.lat, gpsSub.lon, gpsSub.alt);
		}
		else if(!calGpsHomeFlag){
			/* input set */
		}
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

	freqCount();
}

void ModuleINS::setAvgLLA(){
	calGpsHomeFlag = true;
	avgIndexGPS = 0;
	avgLat = 0;
	avgLon = 0;
	avgAlt = 0;
}

void ModuleINS::calAvgLLA(double lat, double lon, float alt){
	float alpha = (avgIndexGPS-1)/avgIndexGPS;
	avgLat = alpha*avgLat + (1-alpha)*lat;
	avgLon = alpha*avgLon + (1-alpha)*lon;
	avgAlt = alpha*avgAlt + (1-alpha)*alt;

	avgIndexGPS++;

	if(avgIndexGPS > AVERAGE_SIZE){
		calGpsHomeFlag = false;
		refLat = avgLat;
		refLon = avgLon;
		refAlt = avgAlt;
	}
}

} /* namespace FC */
