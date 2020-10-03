#ifndef __AIRSPEED__H
#define __AIRSPEED__H

#include <MsgBus/MsgType.h>
#include "Module/Manager/ModuleCommander.h"
#include "Usec.h"
#include "Utils/Freq.h"

namespace FC{

#define SENSITIVITY 0.13

class InterfaceAirSpeed{
public:
	InterfaceAirSpeed();

	void setAirSpeed(float filteredIAS);

    bool startCalibrationFlag;

    bool endCalibrationFlag;

private:
	struct LocalPosition localPositionSub;

	struct AirSpeed airSpeedPub;

	float lowPassFiltering(float diffPressure);

	float lastIAS;

};



extern InterfaceAirSpeed interfaceAirSpeed;

}
#endif
