/*
 * SensorAccel.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Interface/InterfaceAccel.h>
#include "Module/Estimator/ModuleAHRS.h"
#include <Utils/Constants.h>
#include "Usec.h"
#include "printf.h"
#include <cmath>
namespace FC{

InterfaceAccel interfaceAccel;

InterfaceAccel::InterfaceAccel()
: bodyAccel{0,}, biasX(0), biasY(0), biasZ(0)
, averX(0), averY(0), averZ(0)
//, scale(1.0), scaleFactor(1.005)
, calBiasFlag(false), averageIndex(0)
{}

void InterfaceAccel::setBias(){
	calBiasFlag = true;
	averageIndex = 0;
	averX = 0;
	averY = 0;
	averZ = 0;
}

void InterfaceAccel::setAccel(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */

	if(calBiasFlag) calAverage(x, y, z);

	this->bodyAccel.timestamp = microsecond();
	this->bodyAccel.xyz[0] = x - biasX;
	this->bodyAccel.xyz[1] = y - biasY;
	this->bodyAccel.xyz[2] = z - biasZ;

//	float rawScale = std::sqrt(bodyAccel.xyz[0]*bodyAccel.xyz[0] + bodyAccel.xyz[1]*bodyAccel.xyz[1] + bodyAccel.xyz[2]*bodyAccel.xyz[2]);
//	float filterScale = scale*rawScale;
//
//	if(FC_GRAVITY_ACCEERATION < filterScale){
//		scale /= scaleFactor;
//	}
//	else if(FC_GRAVITY_ACCEERATION > filterScale){
//		scale *= scaleFactor;
//	}


//	printf_("%f\t%f\t%f\r\n", scale, rawScale, filterScale);


//	this->bodyAccel.xyz[0] *= scale;
//	this->bodyAccel.xyz[1] *= scale;
//	this->bodyAccel.xyz[2] *= scale;

	msgBus.setBodyAccel(this->bodyAccel);
	ModuleAHRS::setSignal(AHRS_fromAccel);
	/* Freq class variable */
	freqCount();
}

void InterfaceAccel::calAverage(float x, float y, float z){
	float alpha = (averageIndex-1)/averageIndex;
	averX = alpha*averX + (1-alpha)*x;
	averY = alpha*averY + (1-alpha)*y;
	averZ = alpha*averZ + (1-alpha)*z;

	averageIndex++;
	if(averageIndex > AVERAGE_SIZE) {
		calBiasFlag = false;
		biasX = averX;
		biasY = averY;
		biasZ = averZ + FC_GRAVITY_ACCEERATION;		/* gravity is not bias */
	}
}

}
