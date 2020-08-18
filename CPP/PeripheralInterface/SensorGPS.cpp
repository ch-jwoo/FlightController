/*
 * SensorGPS.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */
#include "SensorGPS.h"

namespace FC{

SensorGPS sensorGPS;

void SensorGPS::setGPS(double lat, double lon, float alt,
        			   float vel, float direction, float hdop, float vdop,
					   uint8_t numSat, uint8_t fixType, uint64_t UtcUsec)
{

	/* calculate velocity NED  */
	float radDirection = direction*M_PI/180.0;
	float velN = std::cos(radDirection)*vel;
	float velE = std::sin(radDirection)*vel;

	this->gps.timestamp = microsecond();
	this->gps.timestampUTC = UtcUsec;
	this->gps.lat = lat;
	this->gps.lon = lon;
	this->gps.alt = alt;

	this->gps.vel = vel;
	this->gps.velN = velN;
	this->gps.velE = velE;
	this->gps.velD = 0; /* ??? */
	this->gps.direction = radDirection;
	this->gps.hdop = hdop;
	this->gps.vdop = vdop;

	this->gps.numSatellites = numSat;
	this->gps.fixType = fixType;

	msgBus.setGPS(this->gps);

	/* Freq class variable */
	freqCnt++;

}

}
