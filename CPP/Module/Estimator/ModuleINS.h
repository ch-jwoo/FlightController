/*
 * ModuleINS.h
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEINS_H_
#define MODULE_MODULEINS_H_

#include "MsgBus/MsgBus.h"
#include "cmsis_os.h"

#include "Utils/Freq.h"
#include <MatlabPositionEstimator/positionEstimator.h>

namespace FC {

enum InsSignal{
	INS_fromAHRS = 0x1
};

class ModuleINS : public positionEstimatorModelClass, public Freq<ModuleINS> {
public:
	ModuleINS();

	static void main();

//	static inline void setSignal(enum InsSignal signal){
//		if(signal == INS_fromAHRS) osThreadFlagsSet(AC_TaskHandle, INS_fromAHRS);
//	}

	void onestep();

	static void setAvgLLA();


	static bool calGpsHomeFlag;
	static uint8_t avgIndexGPS;
	static double avgLat;
	static double avgLon;
	static float avgAlt;

private:
	struct Attitude attitudeSub;
	struct NedAccel nedAccelSub;
	struct GPS gpsSub;
	struct Barometer baroSub;
	struct Lidar lidar;

	struct LocalPosition localPositionPub;

	double refLat;
	double refLon;
	float refAlt;


	void calAvgLLA(double lat, double lon, float alt);
    const static uint8_t AVERAGE_SIZE = 20;

public:
	~ModuleINS() = default;
	ModuleINS(const ModuleINS &other) = delete;
	ModuleINS(ModuleINS &&other) = delete;
	ModuleINS& operator=(const ModuleINS &other) = delete;
	ModuleINS& operator=(ModuleINS &&other) = delete;
};


} /* namespace FC */

#endif /* MODULE_MODULEINS_H_ */
