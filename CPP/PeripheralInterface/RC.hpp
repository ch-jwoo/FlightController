#ifndef __RC__H
#define __RC__H

#include <MsgBus/MsgType.h>
#include "Module/ModuleCommander.h"
#include "Usec.h"
#include "Utils/Freq.h"

namespace FC{

#define ARMING_THRESHOLD 1500

class RC : public Freq<RC>{
public:
	RC() : start(false) {}

    void setRC(uint16_t roll=0, uint16_t pitch=0, uint16_t yaw=0, uint16_t throttle=0,
    		   uint16_t armming=0,
			   uint16_t mode=0, uint16_t subMode=0,
			   uint16_t calibration=0, uint16_t calibration_sub=0);
private:
    struct Controller controllerPub;
    uint32_t lastArmReq;

    bool start;

    static const uint16_t MOTOR_CALIBRATION_THROTLE = 1950;
};


void RC::setRC(uint16_t roll, uint16_t pitch, uint16_t yaw, uint16_t throttle,
    		   uint16_t armming,
			   uint16_t mode, uint16_t subMode,
			   uint16_t calibration, uint16_t calibration_sub)
{
	if(start == false && throttle > MOTOR_CALIBRATION_THROTLE){
		ModuleCommander::sendCommand(Command::MotorCalibration);
	}
	start = true;

	/* cotnroller publish */
	this->controllerPub.timestamp = microsecond();
	this->controllerPub.roll = roll;
	this->controllerPub.pitch = pitch;
	this->controllerPub.yaw = yaw;
	this->controllerPub.throttle = throttle;
	msgBus.setController(this->controllerPub);

	/* arming */
	struct ModeFlag modeFlag;
	msgBus.getModeFlag(&modeFlag);							/* current arm mode */
	Command rcvArmFlag = Command::DisArm;						/* request arm mode */
	if( armming > ARMING_THRESHOLD ) rcvArmFlag = Command::Arm;
	if(modeFlag.armMode != rcvArmFlag && millisecond()-lastArmReq > 500){
		ModuleCommander::sendCommand(rcvArmFlag); /* send command */
		lastArmReq = millisecond();
	}


	/* Freq class variable */
	freqCnt++;
}

}
#endif
