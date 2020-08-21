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
	if(millisecond() - lastUpdatedMillisec < MINIMUM_TIME_INTERVAL_MILLISEC) return;
	if(distance == 0.0f) return;

	msgBus.getAttitude(&attitudeSub);
	if(attitudeSub.roll > MAX_RADIAN || attitudeSub.roll < -MAX_RADIAN ||
	   attitudeSub.pitch > MAX_RADIAN || attitudeSub.pitch < -MAX_RADIAN){

		lidarPub.timestamp = microsecond();
		lidarPub.valid = false;
		msgBus.setLidar(lidarPub);
		return;
	}
	float altitude = distance * abs((double)cos(attitudeSub.roll) * cos(attitudeSub.pitch));

	if(calRefFlag) calAverage(altitude);

	lidarPub.timestamp = microsecond();
	lidarPub.altitude = altitude;
	lidarPub.valid = true;
	msgBus.setLidar(lidarPub);

	lastUpdatedMillisec = millisecond();
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
