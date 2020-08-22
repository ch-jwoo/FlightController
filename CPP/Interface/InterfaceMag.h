#ifndef __SENSORMAG__H
#define __SENSORMAG__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "Utils/Freq.h"

namespace FC{

class InterfaceMag : public Freq<InterfaceMag>{
public:
	InterfaceMag();

    void setMag(float x, float y, float z);

    void startCalibration();
    void endCalibration();

    struct BodyMag bodyMag;

    bool startCalibrationFlag;

private:
    bool endCalibrationFlag;

    float bias[3];
    float scale[3];
    float min[3];
    float max[3];

    /*
     *  calibration mag
     *  reference : https://github.com/kriswiner/MPU6050/wiki/Simple-and-Effective-Magnetometer-Calibration
     */
    void calCalibration(float x, float y, float z);
};

extern InterfaceMag interfaceMag;

}


#endif
