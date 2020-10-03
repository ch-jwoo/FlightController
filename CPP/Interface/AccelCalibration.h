/*
 * AccelCalibration.h
 *
 *  Created on: 2020. 9. 24.
 *      Author: cjb88
 */

#ifndef INTERFACE_ACCELCALIBRATION_H_
#define INTERFACE_ACCELCALIBRATION_H_

#include "Lib/Matrix/matrix/Matrix.hpp"

namespace FC{

class AccelCalibration{
public:
	AccelCalibration();

	void setNoseUpAccel(float x, float y, float z);
	void setNoseDownAccel(float x, float y, float z);
	void setLeftSideAccel(float x, float y, float z);
	void setRightSideAccel(float x, float y, float z);
	void setOnBackAccel(float x, float y, float z);
	void setLevelAccel(float x, float y, float z);

	void calculate();
	void reset();

	inline matrix::Matrix<float, 3, 3> getTransformMatrix() { return _transform; };
	inline matrix::Matrix<float, 3, 1> getOffsetMatrix() { return _offset; };
private:
    matrix::Matrix<float, 3, 3> _transform;
    matrix::Matrix<float, 3, 1> _offset;

    uint16_t _noseUpIndex;
    uint16_t _noseDownIndex;
    uint16_t _leftSideIndex;
    uint16_t _rightSideIndex;
    uint16_t _onBackIndex;
    uint16_t _levelIndex;

    matrix::Matrix<float, 3, 1> _avgNoseUpAccel;
    matrix::Matrix<float, 3, 1> _avgNoseDownAccel;
    matrix::Matrix<float, 3, 1> _avgLeftSideAccel;
    matrix::Matrix<float, 3, 1> _avgRightSideAccel;
    matrix::Matrix<float, 3, 1> _avgOnBackAccel;
    matrix::Matrix<float, 3, 1> _avgLevelAccel;
};

}

#endif /* INTERFACE_ACCELCALIBRATION_H_ */
