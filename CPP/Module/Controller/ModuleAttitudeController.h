/*
 * ModuleAttitudeController.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEATTITUDECONTROLLER_H_
#define MODULE_MODULEATTITUDECONTROLLER_H_

#include <MatlabMcAttitudeController/Second_att_control_codeblock_fly.h>
#include <MatlabFwAttitudeController/FW_att_control_codeblock_fly.h>
#include "MsgBus/MsgBus.h"
#include "MsgBus/Params.h"
#include "freertosVariable.h"
#include "Utils/Freq.h"

#define AC_TASK_FREQUENCY 200

namespace FC {

enum AcSignal{
	AC_fromAHRS = 0x01,
	AC_reset = 0x02,			/* asynchronized command */
	AC_transitionMC = 0x04,
	AC_transitionFW = 0x08
};

enum class TiltingPhase{
	MC2FW_Phase1,
	MC2FW_Phase2,

	FW2MC_Phase1,
	FW2MC_Phase2,

	FixedWing,
	MultiCopter
};

class ModuleAttitudeController : public MC_px4_AlgorithmModelClass, public FW_px4_AlgorithmModelClass, public Freq<ModuleAttitudeController>{
public:
	static void main();

	void oneStep();

	static inline void setSignal(enum AcSignal signal){
		osThreadFlagsSet(AC_TaskHandle, signal);
	}

	/*
	 *  ref : https://docs.px4.io/master/en/config_vtol/vtol_quad_configuration.html
	 */
	PARAM(vtolTransitionTHR);
	PARAM(vtolTransitionPhase1Time);
//	PARAM(vtolTransitionCpltAirSpeed);
	PARAM(vtolTransitionPhase2Time);

	PARAM(MC_SERVO_1);
	PARAM(MC_SERVO_2);

	PARAM(FW_SERVO_1);
	PARAM(FW_SERVO_2);

	PARAM(TRANSITION_SERVO_1);
	PARAM(TRANSITION_SERVO_2);

	static TiltingPhase phase;

private:
	struct Attitude attitudeSub;
	struct BodyAngularVelocity bodyAngularVelocitySub;
	struct ArmFlag armFlagSub;
	struct ModeFlag modeFlagSub;
	struct Controller controllerSub;
	struct VehicleAttitueSP vehicleAttitudeSpSub;

	struct MotorPWM motorPwmPub;
	struct ServoPWM servoPwmPub;
	struct AirframeStatus airframeStatusPub;

	float targetRoll;
	float targetPitch;
	float targetYawRate;
	float targetThrottle;

	uint16_t phase1TotalStep;
	uint16_t phase2TotalStep;
	uint16_t phase1Step;
	uint16_t phase2Step;
	float phase1Ratio;
	float phase2Ratio;

	uint8_t tiltingRisingThrottle;
	uint8_t tiltingRisingTime;


	/*
	 *  set targetRoll, targetPitch, targetYawRate, throttle from Position Controller
	 *  this function change private member variable
	 */
	void setFromPositionController();

	/*
	 *  set targetRoll, targetPitch, targetYawRate, throttle from Remote Controller
	 *  this function change private member variable
	 */
	void setFromRC();

	/*
	 *  set motor pwm
	 *  \param[in]		pwm1 ~ pwm6		motor pwm
	 */
//	void setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6);


	void mcOneStep();

	void fwOneStep();

public:
	ModuleAttitudeController();
	~ModuleAttitudeController() = default;
	ModuleAttitudeController(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController(ModuleAttitudeController &&other) = delete;
	ModuleAttitudeController& operator=(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController& operator=(ModuleAttitudeController &&other) = delete;
};

} /* namespace FC */

#endif /* MODULE_MODULEATTITUDECONTROLLER_H_ */
