#ifndef __SENSORGYRO__H
#define __SENSORGYRO__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "Module/ModuleAHRS.h"
#include "Utils/Freq.h"


namespace FC{

class SensorGyro : public Freq<SensorGyro>{
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
	ModuleAHRS::setSignal(AHRS_fromGyro);

	freqCnt++;
}

}


#endif
