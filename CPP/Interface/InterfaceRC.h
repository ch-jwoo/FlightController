#ifndef __RC__H
#define __RC__H

#include <MsgBus/MsgType.h>
#include "Module/Manager/ModuleCommander.h"
#include "Usec.h"
#include "Utils/Freq.h"

namespace FC{

#define ARMING_THRESHOLD 1500

class InterfaceRC : public Freq<InterfaceRC>{
public:
	InterfaceRC() : start(false) {}

    void setRC(uint16_t roll=0, uint16_t pitch=0, uint16_t yaw=0, uint16_t throttle=0,
    		   uint16_t armming=0,
			   uint16_t mode=0);
private:
    struct Controller controllerPub;
    uint32_t lastArmReq;
    uint32_t lastModeReq;

    bool start;

    static const uint16_t MOTOR_CALIBRATION_THROTLE = 1950;

    static const uint16_t FLIGHT_ATTITUDE_MODE_THRSHOLD = 1900;
    static const uint16_t FLIGHT_POSITION_MODE_THRSHOLD = 1700;
    static const uint16_t FLIGHT_AUTO_MODE_THRSHOLD = 1500;

    static const uint16_t FLIGHT_RTL_MODE_THRSHOLD = 1350;
    static const uint16_t FLIGHT_ALT_MODE_THRSHOLD = 950;

};



extern InterfaceRC interfaceRC;

}
#endif
