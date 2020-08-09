/*
 * ModuleHealth.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEHEALTH_H_
#define MODULE_MODULEHEALTH_H_

#include "cmsis_os.h"
#include "MsgBus/MsgBus.h"

namespace FC {

class ModuleHealth {
public:
	static void main(){
		uint32_t tick;
		tick = osKernelGetTickCount();

		struct Health health;
		while(1){
			tick += 1000;
			osDelayUntil(tick);

			health.accel = SensorAccel::checkFreq();
			health.gyro = SensorGyro::checkFreq();
			health.mag = SensorMag::checkFreq();
			health.baro = SensorBaro::checkFreq();
			health.gps = SensorGPS::checkFreq();
			health.rc = RC::checkFreq();

			health.ahrs = ModuleAHRS::checkFreq();

			//TODO ins, attitude, position, auto
			health.ins = 0;

			health.attitudeController = 0;
			health.positionController = 0;
			health.autoController = 0;

			msgBus.setHealth(health);
		}
	}

	ModuleHealth() = delete;
	~ModuleHealth() = default;
	ModuleHealth(const ModuleHealth &other) = delete;
	ModuleHealth(ModuleHealth &&other) = delete;
	ModuleHealth& operator=(const ModuleHealth &other) = delete;
	ModuleHealth& operator=(ModuleHealth &&other) = delete;
};


} /* namespace FC */

#endif /* MODULE_MODULEHEALTH_H_ */
