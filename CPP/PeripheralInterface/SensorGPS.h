#ifndef __SENSORGPS__H
#define __SENSORGPS__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "cmath"
#include "Utils/Freq.h"

namespace FC{

class SensorGPS : public Freq<SensorGPS>{
public:
    void setGPS(double lat, double lon, float alt/*sea level altitude [m]*/,
                float vel/*[m/s]*/, float direction/*[deg]*/, float hdop, float vdop,
                uint8_t numSat, uint8_t fixType, uint64_t UtcUsec);
private:
    struct GPS gps;

    double refLat;
    double refLon;
    float refAlt;
};



extern SensorGPS sensorGPS;

}


#endif
