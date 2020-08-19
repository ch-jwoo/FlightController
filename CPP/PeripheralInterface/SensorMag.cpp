/*
 * SensorMag.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */
#include "SensorMag.h"
#include "cstring"

namespace FC{

SensorMag sensorMag;

SensorMag::SensorMag()
: bodyMag{0, }
, startCalibrationFlag(false)
, endCalibrationFlag(false)
, bias{-216.450f,-276.416f, -170.502f}
, scale{0.95011f, 1.04095f, 1.01334f}
, min{0, }, max{0, }
{
	/*
	 * mpu9250 cali :
	 * 		biasX = -216.450f
	 * 		biasY = -276.416f
	 * 		biasZ = -170.502f
	 * 		scaleX = 0.95011f
	 * 		scaleY = 1.04095f
	 * 		scaleZ = 1.01334f
	 */
}

void SensorMag::setMag(float x, float y, float z){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */

	if(startCalibrationFlag) calCalibration(x, y, z);

	this->bodyMag.timestamp = microsecond();
	this->bodyMag.xyz[0] = (x - bias[0])*scale[0];
	this->bodyMag.xyz[1] = (y - bias[1])*scale[1];
	this->bodyMag.xyz[2] = (z - bias[2])*scale[2];
	msgBus.setBodyMag(this->bodyMag);

	/* Freq class variable */
	freqCnt++;
}

void SensorMag::startCalibration(){
	startCalibrationFlag = true;
	for(int i=0; i<3; i++) min[i] = 30000.0;
	for(int i=0; i<3; i++) max[i] = -30000.0;
}

void SensorMag::endCalibration(){
	endCalibrationFlag = true;
}

void SensorMag::calCalibration(float x, float y, float z){
	if(x > max[0]) max[0] = x;
	if(y > max[1]) max[1] = y;
	if(z > max[2]) max[2] = z;

	if(x < min[0]) min[0] = x;
	if(y < min[1]) min[1] = y;
	if(z < min[2]) min[2] = z;

	if(endCalibrationFlag/* end */){
		/* get hard iron correction */
		bias[0] = (max[0] + min[0])/2;
		bias[1] = (max[1] + min[1])/2;
		bias[2] = (max[2] + min[2])/2;

		/* get soft iron correction estimate */
		scale[0] = (max[0] - min[0])/2;
		scale[1] = (max[1] - min[1])/2;
		scale[2] = (max[2] - min[2])/2;
		float avgRad = (scale[0] + scale[1] + scale[2])/3.0f;

		scale[0] = avgRad/scale[0];
		scale[1] = avgRad/scale[1];
		scale[2] = avgRad/scale[2];

		startCalibrationFlag = false;
		endCalibrationFlag = false;
	}
}

}
