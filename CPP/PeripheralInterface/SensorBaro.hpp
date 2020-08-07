#ifndef __SENSORBARO__H
#define __SENSORBARO__H

#include "MsgBus/MsgType.hpp"
#include "MsgBus/MsgBus.hpp"
#include "Usec.h"

namespace FC{

class SensorBaro{
public:
    void setBaro(float pressure/*[hPa]*/, float temperature/*[degC]*/);
private:
    struct Barometer barometer;
};


void SensorBaro::setBaro(float pressure, float temperature){
	this->barometer.timestamp = microsecond();
	this->barometer.pressure = pressure;
	this->barometer.temperature = temperature;

	msgBus.setBarometer(this->barometer);
}

}


#endif
