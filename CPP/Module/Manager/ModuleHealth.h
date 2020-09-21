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
#include <Module/Controller/ModulePositionController.h>
#include <Module/Estimator/ModuleINS.h>
#include "printf.h"
#include <cstring>

namespace FC {

class ModuleHealth {
public:
	static void main(){
		uint32_t tick;
		tick = osKernelGetTickCount();

		struct Health health = {0};
		struct StatusFlag statusFlag = {0};
		while(1){
			tick += 1000;
			osDelayUntil(tick);		/* 1hz */

			health.timestamp = microsecond();
			health.accel = InterfaceAccel::checkFreq();
			health.gyro = InterfaceGyro::checkFreq();
			health.rc = InterfaceRC::checkFreq();

			health.mag = InterfaceMag::checkFreq();
			health.gps = InterfaceGPS::checkFreq();

			health.baro = InterfaceBaro::checkFreq();
			health.lidar = InterfaceLidar::checkFreq();

			health.ahrs = ModuleAHRS::checkFreq();
			health.ins = ModuleINS::checkFreq();

			health.attitudeController = ModuleAttitudeController::checkFreq();
			health.positionController = ModulePositionController::checkFreq();
			//TODO auto, lidar health check
			health.autoController = 0;

//			printf("%d %d %d %d %d\r\n", health.accel, health.gyro, health.ahrs, health.ins, health.positionController);

			msgBus.setHealth(health);

			std::memset((void*)&statusFlag, 0, sizeof(statusFlag));
			statusFlag.timestamp = millisecond();
			if(health.gyro > GYRO_THRESHOLD) statusFlag.gyro = true;
			if(health.accel > ACCEL_THRESHOLD) statusFlag.accel = true;
			if(health.mag > MAG_THRESHOLD) statusFlag.mag = true;
			if(health.baro > BARO_THRESHOLD) statusFlag.barometer = true;
			//TODO differential pressure
			if(health.lidar > LIDAR_THRESHOLD) statusFlag.lidar = true;
			if(health.rc > RC_THRESHOLD) statusFlag.receiver = true;

			if(health.ahrs > AHRS_THRESHOLD
			&& statusFlag.accel && statusFlag.gyro && statusFlag.receiver){
				statusFlag.attitudeCTL = true;

				if(health.ins > INS_THRESHOLD){
					if(statusFlag.barometer || statusFlag.lidar) statusFlag.altitudeCTL = true;
					if(statusFlag.gps && statusFlag.mag) statusFlag.positionCTL = true;
				}
			}

			msgBus.setStatusFlag(statusFlag);

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
	static const uint8_t RC_THRESHOLD = 25;

	static const uint8_t MAG_THRESHOLD = 25;
	static const uint8_t GPS_THRESHOLD = 2;

	static const uint8_t BARO_THRESHOLD = 30;
	static const uint8_t LIDAR_THRESHOLD = 30;

	static const uint8_t AHRS_THRESHOLD = 150;
	static const uint8_t INS_THRESHOLD = 30;

	static const uint8_t ATTITUDE_CTL_THRESHOLD = 150;
	static const uint8_t POSITION_CTL_THRESHOLD = 30;
	static const uint8_t AUTO_CTL_THRESHOLD = 15;

};


} /* namespace FC */

#endif /* MODULE_MODULEHEALTH_H_ */
