#ifndef __SENSORGYRO__H
#define __SENSORGYRO__H

#include "Usec.h"
#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"

namespace FC{

class SensorGyro{
public:
    void setGyro(float x, float y, float z);
private:
    struct BodyAngularVelocity bodyAngularVelocity;
};

void SensorGyro::setGyro(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */
	this->bodyAngularVelocity.timestamp = microsecond();
	this->bodyAngularVelocity.xyz[0] = x;
	this->bodyAngularVelocity.xyz[1] = y;
	this->bodyAngularVelocity.xyz[2] = z;
	msgBus.setBodyAngularVelocity(this->bodyAngularVelocity);
}

}


#endif
