/*
 * SensorAccel.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Interface/InterfaceAccel.h>
#include "Module/Estimator/ModuleAHRS.h"
#include "Module/Etc/ModuleBuzzer.h"
#include <Utils/Constants.h>
#include "Usec.h"
#include "printf.h"
#include <cmath>
namespace FC{

InterfaceAccel interfaceAccel;

float InterfaceAccel::transform[3][3] = {1.0,	0.0,	0.0,
										 0.0,	1.0,	0.0,
										 0.0,	0.0,	1.0};

float InterfaceAccel::offset[3] = {0.0,	0.0,	0.0};

InterfaceAccel::InterfaceAccel()
: bodyAccel{0,}, biasX(0), biasY(0), biasZ(0)
, averX(0), averY(0), averZ(0)
, calBiasFlag(false), averageIndex(0)
, accelCalibration()
, calibStart(false), calibStep(1), calibCnt(0)
{}

void InterfaceAccel::setBias(){
	calBiasFlag = true;
	averageIndex = 0;
	averX = 0;
	averY = 0;
	averZ = 0;
}

void InterfaceAccel::setAccel(float x, float y, float z, bool calibFlag){
	if((x == 0.0f) && (y == 0.0f) && (z == 0.0f)) return;	/* invalid value */

	if(calBiasFlag) calAverage(x, y, z);
	if(!calibStart && calibFlag)  calibStart = true;

	if(calibStart){
		switch(calibStep){
		case 1:
			accelCalibration.setNoseUpAccel(x, y, z);
			break;
		case 2:
			accelCalibration.setNoseDownAccel(x, y, z);
			break;
		case 3:
			accelCalibration.setLeftSideAccel(x, y, z);
			break;
		case 4:
			accelCalibration.setRightSideAccel(x, y, z);
			break;
		case 5:
			accelCalibration.setOnBackAccel(x, y, z);
			break;
		case 6:
			accelCalibration.setLevelAccel(x, y, z);
			break;
		default:
			break;
		}

		if(++calibCnt == AVERAGE_SIZE){
			calibStart = false;
			calibCnt = 0;
			calibStep++;
			ModuleBuzzer::sendCommand(BuzzerCommand::Success);
		}
		if(calibStep > 6){
			calibStep = 1;

			accelCalibration.calculate();
			matrix::Matrix<float, 3, 3> transformMatrix = accelCalibration.getTransformMatrix();
			matrix::Matrix<float, 3, 1> offsetMatrix = accelCalibration.getOffsetMatrix();
			for(int i=0; i<3; i++){
				offset[i] = offsetMatrix(i, 0);
				for(int j=0; j<3; j++){
					transform[i][j] = transformMatrix(i, j);
				}
			}

			accelCalibration.reset();
			ModuleBuzzer::sendCommand(BuzzerCommand::Success);
		}
	}
//
//	x -= offset[0];
//	y -= offset[1];
//	z -= offset[2];

//	this->bodyAccel.timestamp = microsecond();
//	this->bodyAccel.xyz[0] = transform[0][0]*x + transform[0][1]*y + transform[0][2]*z;
//	this->bodyAccel.xyz[1] = transform[1][0]*x + transform[1][1]*y + transform[1][2]*z;
//	this->bodyAccel.xyz[2] = transform[2][0]*x + transform[2][1]*y + transform[2][2]*z;

	this->bodyAccel.timestamp = microsecond();
	this->bodyAccel.xyz[0] = x-biasX;
	this->bodyAccel.xyz[1] = y-biasY;
	this->bodyAccel.xyz[2] = z-biasZ;

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
