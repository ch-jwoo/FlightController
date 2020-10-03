/*
 * AccelCalibration.cpp
 *
 *  Created on: 2020. 9. 24.
 *      Author: cjb88
 */



#include "AccelCalibration.h"
#include <Utils/Constants.h>
#include "Lib/Matrix/matrix/Matrix.hpp"
#include "printf.h"

namespace FC{

AccelCalibration::AccelCalibration()
: _noseUpIndex(0)
, _noseDownIndex(0)
, _leftSideIndex(0)
, _rightSideIndex(0)
, _onBackIndex(0)
, _levelIndex(0)
{
	_transform.setZero();
	_offset.setZero();
}

void AccelCalibration::setNoseUpAccel(float x, float y, float z){
	float alpha;
	_noseUpIndex++;
	alpha = (float)(_noseUpIndex-1)/_noseUpIndex;

	_avgNoseUpAccel(0,0) = alpha*_avgNoseUpAccel(0,0) + (1-alpha)*x;
	_avgNoseUpAccel(1,0) = alpha*_avgNoseUpAccel(1,0) + (1-alpha)*y;
	_avgNoseUpAccel(2,0) = alpha*_avgNoseUpAccel(2,0) + (1-alpha)*z;

}

void AccelCalibration::setNoseDownAccel(float x, float y, float z){
	float alpha;
	_noseDownIndex++;
	alpha = (float)(_noseDownIndex-1)/_noseDownIndex;

	_avgNoseDownAccel(0,0) = alpha*_avgNoseDownAccel(0,0) + (1-alpha)*x;
	_avgNoseDownAccel(1,0) = alpha*_avgNoseDownAccel(1,0) + (1-alpha)*y;
	_avgNoseDownAccel(2,0) = alpha*_avgNoseDownAccel(2,0) + (1-alpha)*z;

}

void AccelCalibration::setLeftSideAccel(float x, float y, float z){
	float alpha;
	_leftSideIndex++;
	alpha = (float)(_leftSideIndex-1)/_leftSideIndex;

	_avgLeftSideAccel(0,0) = alpha*_avgLeftSideAccel(0,0) + (1-alpha)*x;
	_avgLeftSideAccel(1,0) = alpha*_avgLeftSideAccel(1,0) + (1-alpha)*y;
	_avgLeftSideAccel(2,0) = alpha*_avgLeftSideAccel(2,0) + (1-alpha)*z;

}


void AccelCalibration::setRightSideAccel(float x, float y, float z){
	float alpha;
	_rightSideIndex++;
	alpha = (float)(_rightSideIndex-1)/_rightSideIndex;

	_avgRightSideAccel(0,0) = alpha*_avgRightSideAccel(0,0) + (1-alpha)*x;
	_avgRightSideAccel(1,0) = alpha*_avgRightSideAccel(1,0) + (1-alpha)*y;
	_avgRightSideAccel(2,0) = alpha*_avgRightSideAccel(2,0) + (1-alpha)*z;
}

void AccelCalibration::setOnBackAccel(float x, float y, float z){
	float alpha;
	_onBackIndex++;
	alpha = (float)(_onBackIndex-1)/_onBackIndex;

	_avgOnBackAccel(0,0) = alpha*_avgOnBackAccel(0,0) + (1-alpha)*x;
	_avgOnBackAccel(1,0) = alpha*_avgOnBackAccel(1,0) + (1-alpha)*y;
	_avgOnBackAccel(2,0) = alpha*_avgOnBackAccel(2,0) + (1-alpha)*z;
}

void AccelCalibration::setLevelAccel(float x, float y, float z){
	float alpha;
	_levelIndex++;
	alpha = (float)(_levelIndex-1)/_levelIndex;

	_avgLevelAccel(0,0) = alpha*_avgLevelAccel(0,0) + (1-alpha)*x;
	_avgLevelAccel(1,0) = alpha*_avgLevelAccel(1,0) + (1-alpha)*y;
	_avgLevelAccel(2,0) = alpha*_avgLevelAccel(2,0) + (1-alpha)*z;
}

void AccelCalibration::calculate(){
	matrix::SquareMatrix<float, 3> accel;
	matrix::SquareMatrix<float, 3> accelInv;
	matrix::SquareMatrix<float, 3> g;
	g.setIdentity();
	g *= FC_GRAVITY_ACCEERATION;

	_offset(0,0) = (_avgNoseUpAccel(0,0) 	+ _avgNoseDownAccel(0,0))	/2;
	_offset(1,0) = (_avgLeftSideAccel(1,0) 	+ _avgRightSideAccel(1,0))	/2;
	_offset(2,0) = (_avgOnBackAccel(2,0) 	+ _avgLevelAccel(2,0))		/2;

	for(uint8_t i=0; i<3; i++){
		accel(i,0) = (_avgNoseUpAccel(i,0) 		- _offset(i,0));
		accel(i,1) = (_avgLeftSideAccel(i,0) 	- _offset(i,0));
		accel(i,2) = (_avgOnBackAccel(i,0) 		- _offset(i,0));
	}

	inv(accel, accelInv);

	_transform = g * accelInv;
}

void AccelCalibration::reset(){
	_transform.setZero();
	_offset.setZero();

	_noseUpIndex = -1;
	_noseDownIndex = -1;
	_leftSideIndex = -1;
	_rightSideIndex = -1;
	_onBackIndex = -1;
	_levelIndex = -1;
}

}
