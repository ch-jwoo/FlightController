/*
 * ModuleINS.h
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEINS_H_
#define MODULE_MODULEINS_H_

#include <MatlabPositionEstimator/positionEstimator.h>
#include "MsgBus/MsgBus.h"
#include "cmsis_os.h"
#include "Module/ModulePositionController.h"

namespace FC {

enum InsSignal{
	INS_fromAHRS = 0x1
};

class ModuleINS : public positionEstimatorModelClass, public Freq<ModuleINS> {
public:

	static void main(){
		ModuleINS moduleINS;
		moduleINS.initialize();
		osDelay(2000);
		while(1){
			moduleINS.onestep();
			ModulePositionController::setSignal(PC_fromEKF);
			freqCnt++;
			osDelay(20);
		}
	}

//	static inline void setSignal(enum InsSignal signal){
//		if(signal == INS_fromAHRS) osThreadFlagsSet(AC_TaskHandle, INS_fromAHRS);
//	}

	void onestep();

	ModuleINS();
	~ModuleINS() = default;
	ModuleINS(const ModuleINS &other) = delete;
	ModuleINS(ModuleINS &&other) = delete;
	ModuleINS& operator=(const ModuleINS &other) = delete;
	ModuleINS& operator=(ModuleINS &&other) = delete;

private:
	struct Attitude attitudeSub;
	struct NedAccel nedAccelSub;
	struct GPS gpsSub;
	struct Barometer baroSub;

	struct LocalPosition localPositionPub;

	double refLat;
	double refLon;
	float refAlt;

};

} /* namespace FC */

#endif /* MODULE_MODULEINS_H_ */
