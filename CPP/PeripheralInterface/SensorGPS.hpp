#ifndef __SENSORGPS__H
#define __SENSORGPS__H

#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"
#include "Usec.h"
#include "cmath"

namespace FC{

class SensorGPS{
public:
    void setGPS(double lat, double lon, float alt/*sea level altitude [m]*/,
                float vel/*[m/s]*/, float direction/*[deg]*/, float hdop, float vdop,
                uint8_t numSat, uint8_t fixType, uint64_t UtcUsec);
private:
    struct GPS gps;
};


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
}


}


#endif
