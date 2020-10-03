#ifndef __SENSORACCEL__H
#define __SENSORACCEL__H

#include <MsgBus/MsgBus.h>
#include "Utils/Freq.h"
#include "AccelCalibration.h"
#include "MsgBus/Params.h"

namespace FC{

class InterfaceAccel : public Freq<InterfaceAccel>{
public:
	InterfaceAccel();

	/*
	 *  set acceleration from sensor.
	 *  \pram[in]		x		x-axis acceleration in [m/s^2]
	 *  \pram[in]		y		y-axis acceleration in [m/s^2]
	 *  \pram[in]		z		z-axis acceleration in [m/s^2]
	 */
    void setAccel(float x, float y, float z, bool calibFlag = false);

    /*
     *  calculate bias
     *  this function call when arming vehicle
     *  after calling this function, the commander must delay some time to setting bias
     */
    void setBias();

    PARAM(transform[3][3]);
    PARAM(offset[3]);
private:
    struct BodyAccel bodyAccel;

    float biasX;
    float biasY;
    float biasZ;

    float averX;
    float averY;
    float averZ;

//    float scale;
//    float scaleFactor;

    bool calBiasFlag;
    uint8_t averageIndex;

    AccelCalibration accelCalibration;
    bool calibStart;

    /*
     *  1. nose up
     *  2. nose down
     *  3. left side down
     *  4. right side down
     *  5. on back
     *  6. level
     */
    uint8_t calibStep;
    uint8_t calibCnt;

    void calAverage(float x, float y, float z);

    const static uint8_t AVERAGE_SIZE = 20;
};

extern InterfaceAccel interfaceAccel;


}



#endif
