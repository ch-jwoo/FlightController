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
#include "Utils/Freq.h"

namespace FC {

enum AcSignal{
	AC_fromAHRS = 0x01,
	AC_reset = 0x02,			/* asynchronized command */
//	AC_start = 0x04,
//	AC_stop = 0x08
};

class ModuleAttitudeController : public px4_AlgorithmModelClass, public Freq<ModuleAttitudeController>{
public:
	static void main(){
		ModuleAttitudeController attitudeController;
		while(1){
			/* check reset command */
			if(osThreadFlagsGet() & AC_reset){
				osThreadFlagsClear(AC_reset);
				attitudeController.initialize();
			}

			/* wait AHRS set */
			osThreadFlagsWait(AC_fromAHRS, osFlagsWaitAny, osWaitForever);
			attitudeController.oneStep();
			freqCnt++;
		}
	}

	void oneStep();

	static inline void setSignal(enum AcSignal signal){
		osThreadFlagsSet(AC_TaskHandle, signal);
	}

	ModuleAttitudeController();
	~ModuleAttitudeController() = default;
	ModuleAttitudeController(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController(ModuleAttitudeController &&other) = delete;
	ModuleAttitudeController& operator=(const ModuleAttitudeController &other) = delete;
	ModuleAttitudeController& operator=(ModuleAttitudeController &&other) = delete;

private:
	struct Attitude attitudeSub;
	struct BodyAngularVelocity bodyAngularVelocitySub;
	struct ModeFlag modeFlagSub;
	struct Controller controllerSub;
	struct VehicleAttitueSP vehicleAttitudeSpSub;

	struct MotorPWM motorPwmSub;

	float targetRoll;
	float targetPitch;
	float targetYawRate;
	float targetThrottle;

	/* previous arm flag */
//	bool armFlag;

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
	void setMotor(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3, uint16_t pwm4, uint16_t pwm5, uint16_t pwm6);
};

} /* namespace FC */

#endif /* MODULE_MODULEATTITUDECONTROLLER_H_ */
