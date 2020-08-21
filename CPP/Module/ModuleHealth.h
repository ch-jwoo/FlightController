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
#include "ModulePositionController.h"
#include "ModuleINS.h"

namespace FC {

class ModuleHealth {
public:
	static void main(){
		uint32_t tick;
		tick = osKernelGetTickCount();

		struct Health health;
		while(1){
			tick += 1000;
			osDelayUntil(tick);		/* 1hz */

			health.accel = SensorAccel::checkFreq();
			health.gyro = SensorGyro::checkFreq();
			health.rc = RC::checkFreq();

			health.mag = SensorMag::checkFreq();
			health.gps = SensorGPS::checkFreq();

			health.baro = SensorBaro::checkFreq();
			health.lidar = SensorLidar::checkFreq();

			health.ahrs = ModuleAHRS::checkFreq();
			health.ins = ModuleINS::checkFreq();

			health.attitudeController = ModuleAttitudeController::checkFreq();
			health.positionController = ModulePositionController::checkFreq();
			//TODO auto, lidar health check
			health.autoController = 0;

			msgBus.setHealth(health);

			if(health.accel > ACCEL_THRESHOLD &&
			   health.gyro > GYRO_THRESHOLD &&
			   health.rc > RC_THRESHOLD &&
			   health.ahrs > AHRS_THRESHOLD &&
			   health.attitudeController > ATTITUDE_CTL_THRESHOLD){
				/* arm(attitude controller) enable */

				if(health.mag > MAG_THRESHOLD &&
						health.gps > GPS_THRESHOLD &&
						health.ins > INS_THRESHOLD){
					/* position controller enable */

				}
			}
		}
	}

	ModuleHealth() = delete;
	~ModuleHealth() = default;
	ModuleHealth(const ModuleHealth &other) = delete;
	ModuleHealth(ModuleHealth &&other) = delete;
	ModuleHealth& operator=(const ModuleHealth &other) = delete;
	ModuleHealth& operator=(ModuleHealth &&other) = delete;

	static const uint8_t ACCEL_THRESHOLD = 150;
	static const uint8_t GYRO_THRESHOLD = 150;
	static const uint8_t RC_THRESHOLD = 100;

	static const uint8_t MAG_THRESHOLD = 50;
	static const uint8_t GPS_THRESHOLD = 3;

	static const uint8_t BARO_THRESHOLD = 40;

	static const uint8_t AHRS_THRESHOLD = 150;
	static const uint8_t INS_THRESHOLD = 30;

	static const uint8_t ATTITUDE_CTL_THRESHOLD = 150;
	static const uint8_t POSITION_CTL_THRESHOLD = 30;
	static const uint8_t AUTO_CTL_THRESHOLD = 15;

};


} /* namespace FC */

#endif /* MODULE_MODULEHEALTH_H_ */
