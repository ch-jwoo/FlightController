/*
 * ModulePositionController.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEPOSITIONCONTROLLER_H_
#define MODULE_MODULEPOSITIONCONTROLLER_H_
#include "MatlabPositionControl/positionControl.h"
#include "MatlabTECS/TECS.h"
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

class ModulePositionController : public positionControlModelClass, public fw_TECSModelClass, public Freq<ModulePositionController> {
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
	struct BodyAccel bodyAccelSub;
	struct AirSpeed airSpeedSub;
	struct AirframeStatus airframeStatusSub;
	struct Attitude vehicleAttitude;

	struct VehicleAttitueSP vehicleAttitudeSpPub;
	
	/* multicopter rc control */
	float targetX;
	float targetY;
	float targetZ;
	float targetYaw;

	/* fixed wing rc control */
	float fwtargetAirspeed;
	float fwtargetAlt;
	float fwtargetRoll;
	float fwtargetYawRate=0;

	float fwPrevX, fwPrevY, fwPrevZ;
	float fwTargetX, fwTargetY, fwTargetZ;

	void setFromAutoController();

	/* multicopter */
	void mcOneStep();
	void mcSetFromRC();

	/* fixed wing */
	void fwOneStep();
	void fwSetFromRC();
	void fwSetFromAuto();
	void L1guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
					float curWaypointX, float curWaypointY, float curWaypointZ,
					float vehicleX, float vehicleY, float vehicleZ,
					float vehicleVelX, float vehicleVelY, float vehicleVelZ,
					float *targetRoll);

	/* multicopter constants */
	static constexpr float MAX_HORISION = 5.0;
	static constexpr float MAX_VELTICAL = 1.0;
	static constexpr float MAX_YAW = 1.570796f;			/* pi/2 */
	
	/* fixed wing constants */
	static constexpr float VEL_INCREMENT = 5.0;
	static constexpr float MAX_CLIMB_ALT = 5.0;
	static constexpr float MAX_BANK_ANGLE_RAD = 1.047;  //60deg

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
