/*
 * SensorGPS.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */
#include <Interface/InterfaceGPS.h>

namespace FC{

InterfaceGPS interfaceGPS;

void InterfaceGPS::setGPS(double lat, double lon, float alt,
        			   float vel, float direction, float hdop, float vdop,
					   uint8_t usedSat, uint8_t visibleSat, uint8_t fixType, uint64_t UtcUsec)
{
//	if(fixType == 0 || usedSat < 4) return;			/* not fixed */

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

	this->gps.usedSatellites = usedSat;
	this->gps.visibleSatellites = visibleSat;
	this->gps.fixType = fixType;

	msgBus.setGPS(this->gps);

//	int len= sprintf_((char*)telemBuffer,"%f %f %f %f %f\n\r",lat,lon,alt,velN,velE);
//	telem.send(telemBuffer,len);

	/* Freq class variable */
	freqCount();
}

}
