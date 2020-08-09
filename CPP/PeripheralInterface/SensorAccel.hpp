#ifndef __SENSORACCEL__H
#define __SENSORACCEL__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "main.h"
#include "Usec.h"
#include "Module/ModuleAHRS.h"
#include "Utils/Freq.h"

namespace FC{

class SensorAccel : public Freq<SensorAccel>{
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
	ModuleAHRS::setSignal(AhrsAccel);

	/* Freq class variable */
	freqCnt++;
}

}



#endif
