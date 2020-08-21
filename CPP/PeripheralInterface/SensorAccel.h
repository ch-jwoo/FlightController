#ifndef __SENSORACCEL__H
#define __SENSORACCEL__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include <Utils/Constants.h>
#include "main.h"
#include "Usec.h"
#include "Module/ModuleAHRS.h"
#include "Utils/Freq.h"

namespace FC{

class SensorAccel : public Freq<SensorAccel>{
public:
	SensorAccel();

	/*
	 *  set acceleration from sensor.
	 *  \pram[in]		x		x-axis acceleration in [m/s^2]
	 *  \pram[in]		y		y-axis acceleration in [m/s^2]
	 *  \pram[in]		z		z-axis acceleration in [m/s^2]
	 */
    void setAccel(float x, float y, float z);

    /*
     *  calculate bias
     *  this function call when arming vehicle
     *  after calling this function, the commander must delay some time to setting bias
     */
    void setBias();
private:
    struct BodyAccel bodyAccel;

    float biasX;
    float biasY;
    float biasZ;

    float averX;
    float averY;
    float averZ;

    bool calBiasFlag;
    uint8_t averageIndex;

    void calAverage(float x, float y, float z);

    const static uint8_t AVERAGE_SIZE = 20;
};

extern SensorAccel sensorAccel;


}



#endif
