/*
 * ModulePositionController.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEPOSITIONCONTROLLER_H_
#define MODULE_MODULEPOSITIONCONTROLLER_H_
#include "MatlabPositionControl/positionControl_ert_rtw/positionControl.h"
#include "Utils/Freq.h"
#include "freertosVariable.h"
#include "MsgBus/MsgBus.h"
#include "Utils/Constant.h"
#include "ModuleCommander.h"

namespace FC {

enum PcSignal{
	PC_fromEKF = 0x01,		/* wait EKF data */
	PC_start = 0x02,		/* synchronized command */
	PC_stop = 0x04,			/* asynchronized command */
	PC_reset = 0x08			/* asynchronized command */
};

class ModulePositionController : public positionControlModelClass, public Freq<ModulePositionController> {
public:
	ModulePositionController();

	static void main(){
		bool firstLoop;
		ModulePositionController positionController;
		while(1){
			firstLoop = true;
			/* wait position controller start */
			osThreadFlagsWait(PC_start, osFlagsWaitAny, osWaitForever);
			while(1){
				/* if first loop or reset command, initialize */
				if(firstLoop || (osThreadFlagsGet() & PC_reset)){
					osThreadFlagsClear(PC_reset);
					positionController.initialize();
				}

				/* wait EKF data */
				osThreadFlagsWait(PC_fromEKF, osFlagsWaitAny, osWaitForever);
				positionController.oneStep();

				/* check position controller stop */
				if(osThreadFlagsGet() & PC_stop){
					osThreadFlagsClear(PC_stop);
					break;
				}

				/* if first loop, send ACK */
				if(firstLoop){
					ModuleCommander::sendSignal(CMD_ACK);
					firstLoop = false;
				}
				freqCnt++;
			}
		}
	}

	void oneStep();

	static inline void setSignal(enum PcSignal signal){
		osThreadFlagsSet(PC_TaskHandle, signal);
	}

	~ModulePositionController() = default;
	ModulePositionController(const ModulePositionController &other) = delete;
	ModulePositionController(ModulePositionController &&other) = delete;
	ModulePositionController& operator=(const ModulePositionController &other) = delete;
	ModulePositionController& operator=(ModulePositionController &&other) = delete;
private:
	struct LocalPosition localPositionSub;
	struct ModeFlag modeFlagSub;
	struct Controller controllerSub;
	struct VehiclePositionSP vehiclePositionSpSub;

	struct VehicleAttitueSP vehicleAttitudeSpPub;

//	bool startFlag;

	float targetX;
	float targetY;
	float targetZ;
	float targetYaw;

	void setFromRC();

	void setFromAutoController();

	static constexpr float MAX_HORISION = 1.0;
	static constexpr float MAX_VELTICAL = 1.0;
	static constexpr float MAX_YAW = 1.570796f;			/* pi/2 */

	static const uint16_t STICK_THRESHOLD = 100;
};

} /* namespace FC */

#endif /* MODULE_MODULEPOSITIONCONTROLLER_H_ */
