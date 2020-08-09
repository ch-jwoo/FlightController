/*
 * ModuleAttitudeController.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULEATTITUDECONTROLLER_H_
#define MODULE_MODULEATTITUDECONTROLLER_H_

#include "MsgBus/MsgBus.h"
#include "Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.h"
#include "Actuator/Motor.h"
#include "freertosVariable.h"

namespace FC {

enum AcSignal{
	AcAHRS = 0x1
};

extern osThreadId_t AC_TaskHandle;

class ModuleAttitudeController {
public:
	static void main(){
		ModuleAttitudeController attitudeController;
		while(1){
			/* wait AHRS set */
			osThreadFlagsWait(0x1U, osFlagsWaitAll, osWaitForever);
			attitudeController.oneStep();
		}
	}

	void oneStep();

	static inline void setSignal(enum AcSignal signal){
		if(signal == AcAHRS) osThreadFlagsSet(AC_TaskHandle, AcAHRS);
	}

	ModuleAttitudeController() = default;
	~ModuleAttitudeController() = default;
	ModuleAttitudeController(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController(ModuleAttitudeController &&other) = delete;
	ModuleAttitudeController& operator=(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController& operator=(ModuleAttitudeController &&other) = delete;

private:
	struct Attitude attitudeSub;
	struct BodyAngularVelocity bodyAngularVelocitySub;
	struct Controller controllerSub;
	struct ModeFlag modeFlagSub;

	struct MotorPWM motorPwmSub;

	float targetRoll;
	float targetPitch;
	float targetYawRate;
	uint16_t throttle;

	void setFromPositionController();
	void setFromRC();

	void setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6);
};

} /* namespace FC */

#endif /* MODULE_MODULEATTITUDECONTROLLER_H_ */
