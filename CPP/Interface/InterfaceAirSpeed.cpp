/*
 * RC.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */


#include <Interface/InterfaceAirSpeed.h>
#include "printf.h"

namespace FC{

InterfaceAirSpeed interfaceAirSpeed;

InterfaceAirSpeed::InterfaceAirSpeed()
: startCalibrationFlag(false)
, endCalibrationFlag(false)
, lastIAS(0.0f)
{

}

float InterfaceAirSpeed::lowPassFiltering(float diffPressure){
	static float lastIAS = 0.0f;
	float IAS;
	float filteredIAS;

	// IAS formular
	IAS = 1.3106 * sqrt(diffPressure);

	// Lowpass filtering
	filteredIAS = lastIAS * (1 - SENSITIVITY) + SENSITIVITY * IAS;
	lastIAS = filteredIAS;

	return filteredIAS;
}

void InterfaceAirSpeed::setAirSpeed(float diffPressure){
	if(isnan(diffPressure) || diffPressure < 0) return;

	msgBus.getLocalPosition(&localPositionSub);

	float IAS = 1.3106 * sqrt(diffPressure);
	float filteredIAS = (1-0.13)*lastIAS + 0.13*IAS;
	lastIAS = filteredIAS;

//	float filteredIAS = lowPassFiltering(diffPressure);
//	float filteredIAS = 1.3106 * sqrt(diffPressure);
	// IAS to TAS formular
	// TAS = IAS + IAS * (0.02 * ALT /1000)
	airSpeedPub.TAS = filteredIAS + filteredIAS * (0.02 * 10.0 / 1000.0);
	airSpeedPub.timestamp = microsecond();
	msgBus.setAirSpeed(airSpeedPub);

	freqCount();
}

}
