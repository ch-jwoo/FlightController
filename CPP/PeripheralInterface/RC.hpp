#ifndef __RC__H
#define __RC__H

#include "MsgBus/MsgType.hpp"
#include "Module/ModuleCommander.h"
#include "Usec.h"
namespace FC{

#define ARMING_THRESHOLD 1500

class RC{
public:
//    void setRC(uint16_t *ch, uint8_t len);
    void setRC(uint16_t roll=0, uint16_t pitch=0, uint16_t yaw=0, uint16_t throttle=0,
    		   uint16_t armming=0,
			   uint16_t mode=0, uint16_t subMode=0,
			   uint16_t calibration=0, uint16_t calibration_sub=0);
private:
    struct Controller controllerPub;
};


void RC::setRC(uint16_t roll, uint16_t pitch, uint16_t yaw, uint16_t throttle,
    		   uint16_t armming,
			   uint16_t mode, uint16_t subMode,
			   uint16_t calibration, uint16_t calibration_sub)
{
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
	if( armming > ARMING_THRESHOLD )	rcvArmFlag = Command::Arm;
	if(modeFlag.armMode != rcvArmFlag) ModuleCommander::sendCommand(rcvArmFlag); /* send command */

}

}
#endif
