/*
 * ModuleINS.h
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEINS_H_
#define MODULE_MODULEINS_H_

#include "MsgBus/MsgBus.h"


namespace FC {

enum InsSignal{
	INS_fromAHRS = 0x1
};

class ModuleINS {
public:

//	static inline void setSignal(enum InsSignal signal){
//		if(signal == INS_fromAHRS) osThreadFlagsSet(AC_TaskHandle, INS_fromAHRS);
//	}

	ModuleINS() = default;
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
};

} /* namespace FC */

#endif /* MODULE_MODULEINS_H_ */
