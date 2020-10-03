/*
 * ModulePositionController.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEPOSITIONCONTROLLER_H_
#define MODULE_MODULEPOSITIONCONTROLLER_H_
#include "MatlabPositionControl/positionControl.h"
#include "Utils/Freq.h"
#include "freertosVariable.h"
#include "MsgBus/MsgBus.h"

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

	static void main();

	void oneStep();

	static inline void setSignal(enum PcSignal signal){
		osThreadFlagsSet(PC_TaskHandle, signal);
	}

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

	static constexpr float MAX_HORISION = 5.0;
	static constexpr float MAX_VELTICAL = 1.0;
	static constexpr float MAX_YAW = 1.570796f;			/* pi/2 */

	static const uint16_t STICK_THRESHOLD = 100;

public:
	~ModulePositionController() = default;
	ModulePositionController(const ModulePositionController &other) = delete;
	ModulePositionController(ModulePositionController &&other) = delete;
	ModulePositionController& operator=(const ModulePositionController &other) = delete;
	ModulePositionController& operator=(ModulePositionController &&other) = delete;
};

} /* namespace FC */

#endif /* MODULE_MODULEPOSITIONCONTROLLER_H_ */
