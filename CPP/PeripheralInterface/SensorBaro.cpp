/*
 * SensorBaro.cpp
 *
 *  Created on: 2020. 8. 16.
 *      Author: cjb88
 */

#include "SensorBaro.h"
#include "cmath"

namespace FC{

SensorBaro sensorBaro;

void SensorBaro::setBaro(float pressure, float temperature){
	/* invalid pressure */
	if(pressure > 1200.0 || pressure < 900.0) return;

	this->pressure = pressure;
	this->temperature = temperature;
	this->altitude = calAltitude(seaLevelPressure, pressure);

	this->barometerPub.timestamp = microsecond();
	this->barometerPub.pressure = this->pressure;
	this->barometerPub.temperature = this->temperature;
	this->barometerPub.altitude = this->altitude - refAltitude;

	msgBus.setBarometer(this->barometerPub);

	/* Freq class variable */
	freqCnt++;
}

void SensorBaro::setSeaLevelPressure(float altitude){
	seaLevelPressure = calSeaLevelPressure(altitude, pressure);
}

void SensorBaro::setRefAltitude(){
	refAltitude = calAltitude(seaLevelPressure, pressure);
}

float SensorBaro::calAltitude(float seaLevel, float pressure){
	return 44330.0 * (1.0 - pow(pressure / seaLevel, 0.1903));
}

float SensorBaro::calSeaLevelPressure(float altitude, float pressure){
	return pressure / pow(1.0 - (altitude / 44330.0), 5.255);
}


}
