/*
 * SensorGyro.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Interface/InterfaceGyro.h>

namespace FC{

InterfaceGyro interfaceGyro;

InterfaceGyro::InterfaceGyro()
: bodyAngularVelocity{0, }
, biasX(0), biasY(0), biasZ(0)
, averX(0), averY(0), averZ(0)
, calBiasFlag(false), averageIndex(0)
{}

void InterfaceGyro::setBias(){
	calBiasFlag = true;
	averageIndex = 0;
	averX = 0;
	averY = 0;
	averZ = 0;
}

void InterfaceGyro::setGyro(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */

	if(calBiasFlag) calAverage(x, y, z);

	this->bodyAngularVelocity.timestamp = microsecond();
	this->bodyAngularVelocity.xyz[0] = x - biasX;
	this->bodyAngularVelocity.xyz[1] = y - biasY;
	this->bodyAngularVelocity.xyz[2] = z - biasZ;
	msgBus.setBodyAngularVelocity(this->bodyAngularVelocity);
	ModuleAHRS::setSignal(AHRS_fromGyro);

	freqCount();
}

void InterfaceGyro::calAverage(float x, float y, float z){
	float alpha = (averageIndex-1)/averageIndex;
	averX = alpha*averX + (1-alpha)*x;
	averY = alpha*averY + (1-alpha)*y;
	averZ = alpha*averZ + (1-alpha)*z;

	averageIndex++;
	if(averageIndex > AVERAGE_SIZE) {
		calBiasFlag = false;
		biasX = averX;
		biasY = averY;
		biasZ = averZ;
	}
}

}
