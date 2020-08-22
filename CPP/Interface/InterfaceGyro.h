#ifndef __SENSORGYRO__H
#define __SENSORGYRO__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "Module/Estimator/ModuleAHRS.h"
#include "Utils/Freq.h"


namespace FC{

class InterfaceGyro : public Freq<InterfaceGyro>{
public:
	InterfaceGyro();

    void setGyro(float x, float y, float z);

    /*
     *  calculate bias
     *  this function call when arming vehicle
     *  after calling this function, the commander must delay some time to setting bias
     */
    void setBias();
private:
    struct BodyAngularVelocity bodyAngularVelocity;

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

extern InterfaceGyro interfaceGyro;

}


#endif
