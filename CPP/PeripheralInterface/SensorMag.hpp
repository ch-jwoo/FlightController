#ifndef __SENSORMAG__H
#define __SENSORMAG__H

#include "Usec.h"
#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"

namespace FC{

class SensorMag{
public:
    void setMag(float x, float y, float z);
    void calibration();
private:
    struct BodyMag bodyMag;
    float bias[3];
    float scale[3];
};


void SensorMag::setMag(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */
	this->bodyMag.timestamp = microsecond();
	this->bodyMag.xyz[0] = x;
	this->bodyMag.xyz[1] = y;
	this->bodyMag.xyz[2] = z;
	msgBus.setBodyMag(this->bodyMag);
}

}


#endif
