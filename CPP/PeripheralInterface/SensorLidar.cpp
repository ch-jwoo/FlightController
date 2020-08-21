/*
 * SensorLidar.cpp
 *
 *  Created on: Aug 21, 2020
 *      Author: cjb88
 */

#include <PeripheralInterface/SensorLidar.h>
#include "Usec.h"
#include <cmath>

namespace FC {

SensorLidar sensorLidar;

SensorLidar::SensorLidar()
: lidarPub{0, }
, refDistance(0.0)
, calRefFlag(false)
, avgDistance(0.0)
, avgIndex(0)
{}

void SensorLidar::setDistance(float distance /*[m]*/){
	if(distance == 0.0f) return;
	if(!msgBus.getAttitude(&attitudeSub)) return;		/* can't acquisite attitude */

	float altitude = distance * cos(attitudeSub.roll) * sin(attitudeSub.pitch);

	if(calRefFlag) calAverage(altitude);

	lidarPub.timestamp = microsecond();
	lidarPub.altitude = altitude;
	lidarPub.valid = 0;
	msgBus.setLidar(lidarPub);

	freqCnt++;
}

void SensorLidar::setRefDistance(){
	calRefFlag = true;
	avgIndex = 0;
	refDistance = 0;
}

void SensorLidar::calAverage(float distance){
	float alpha = (avgIndex-1)/avgIndex;
	avgDistance = alpha*distance + (1-alpha)*distance;

	avgIndex++;
	if(avgIndex > AVERAGE_SIZE){
		calRefFlag = false;
		refDistance = avgDistance;
	}
}


} /* namespace FC */
