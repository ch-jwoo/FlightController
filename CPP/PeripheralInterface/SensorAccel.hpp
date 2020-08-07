#ifndef __SENSORACCEL__H
#define __SENSORACCEL__H

#include "main.h"
#include "Usec.h"
#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"

namespace FC{

class SensorAccel{
public:
	SensorAccel() = default;
    void setAccel(float x, float y, float z);
private:
    struct BodyAccel bodyAccel{};
};


void SensorAccel::setAccel(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */
	this->bodyAccel.timestamp = microsecond();
	this->bodyAccel.xyz[0] = x;
	this->bodyAccel.xyz[1] = y;
	this->bodyAccel.xyz[2] = z;
	msgBus.setBodyAccel(this->bodyAccel);
}

}



#endif
