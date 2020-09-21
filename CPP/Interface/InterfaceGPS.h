#ifndef __SENSORGPS__H
#define __SENSORGPS__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "cmath"
#include "Utils/Freq.h"

namespace FC{

class InterfaceGPS : public Freq<InterfaceGPS>{
public:
	void setGPS(double lat, double lon, float alt, float vel, float direction,
			float hdop, float vdop, uint8_t usedSat, uint8_t visibleSat, uint8_t fixType,
			uint64_t UtcUsec);
private:
    struct GPS gps;

    double refLat;
    double refLon;
    float refAlt;
};

extern InterfaceGPS interfaceGPS;

}


#endif
