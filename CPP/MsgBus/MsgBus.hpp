#ifndef __MSGBUS__H
#define __MSGBUS__H

#define SIMPLE_FUNC_IMPL(ret, fname, var) \
            bool get##fname(ret *tmp) \
            { \
                if(tmp->timestamp != var.timestamp){\
                    *tmp = var;\
                    return true; \
                }\
                return false;\
            } \
            void set##fname(const ret &tmp) \
            { \
                var = tmp; \
            }

#include "MsgType.hpp"

namespace FC{

class MsgBus {
public:
	MsgBus() = default;

    SIMPLE_FUNC_IMPL(BodyAccel, BodyAccel, bodyAccel);
    SIMPLE_FUNC_IMPL(BodyAngularVelocity, BodyAngularVelocity, bodyAngularVelocity);
    SIMPLE_FUNC_IMPL(BodyMag, BodyMag, bodyMag);
    SIMPLE_FUNC_IMPL(GPS, GPS, gps);
    SIMPLE_FUNC_IMPL(Barometer, Barometer, barometer);
    SIMPLE_FUNC_IMPL(Controller, Controller, controller);
    
    SIMPLE_FUNC_IMPL(Attitude, Attitude, attitude);
    SIMPLE_FUNC_IMPL(NedAccel, NedAccel, nedAccel);

    SIMPLE_FUNC_IMPL(ModeFlag, ModeFlag, modeFlag);
private:
    /* Peripheral Interface */
    struct BodyAccel bodyAccel{};
    struct BodyAngularVelocity bodyAngularVelocity{};
    struct BodyMag bodyMag{};
    struct GPS gps{};
    struct Barometer barometer{};
    struct Controller controller{};

    /* estimate */
    struct Attitude attitude{};
    struct NedAccel nedAccel{};

    /* flight state */
    struct ModeFlag modeFlag{0, Command::DisArm, Command::ControlAttitude};

};

MsgBus msgBus;		/* global variable */
}

#endif
