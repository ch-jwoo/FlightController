#ifndef __MSGBUS__H
#define __MSGBUS__H

#define SIMPLE_FUNC_IMPL(ret, fname, var) \
            bool get##fname(ret *tmp) \
            { \
				bool res = false;\
                if(tmp->timestamp != var.timestamp){\
                    res = true; \
                }\
				*tmp = var;\
                return res;\
            } \
            void set##fname(const ret &tmp) \
            { \
                var = tmp; \
            }

#include <MsgBus/MsgType.h>

namespace FC{

class MsgBus {
public:
	MsgBus()
		: bodyAccel{0}, bodyAngularVelocity{0}, bodyMag{0}, gps{0}, barometer{0}, controller{0}
		, attitude{0}, nedAccel{0}
		, armFlag{0, ArmMode::DisArm}
		, modeFlag{0, FlightMode::AttitudeControl}
		, health{0}
	{}

	/*
	 *  get, set function define
	 *
	 *  getFunction :
	 *  \param[out]		&variable		variable change to updated data
	 *  \return variable is updated(true), variable is not updated(false)
	 *
	 *  setFunction :
	 *  \param[in]		variable		msgBus data is changed to input data
	 */
    SIMPLE_FUNC_IMPL(BodyAccel, BodyAccel, bodyAccel)
    SIMPLE_FUNC_IMPL(BodyAngularVelocity, BodyAngularVelocity, bodyAngularVelocity)
    SIMPLE_FUNC_IMPL(BodyMag, BodyMag, bodyMag)
    SIMPLE_FUNC_IMPL(GPS, GPS, gps)
    SIMPLE_FUNC_IMPL(Barometer, Barometer, barometer)
    SIMPLE_FUNC_IMPL(Lidar, Lidar, lidar)

    SIMPLE_FUNC_IMPL(Controller, Controller, controller)
    SIMPLE_FUNC_IMPL(VehicleAttitueSP, VehicleAttitueSP, vehicleAttitudeSP)
    SIMPLE_FUNC_IMPL(VehiclePositionSP, VehiclePositionSP, vehiclePositionSP)
    
    SIMPLE_FUNC_IMPL(Attitude, Attitude, attitude)
    SIMPLE_FUNC_IMPL(NedAccel, NedAccel, nedAccel)

    SIMPLE_FUNC_IMPL(LocalPosition, LocalPosition, localPosition)
    SIMPLE_FUNC_IMPL(GlobalPosition, GlobalPosition, globalPosition)

    SIMPLE_FUNC_IMPL(ArmFlag, ArmFlag, armFlag)
    SIMPLE_FUNC_IMPL(ModeFlag, ModeFlag, modeFlag)

    SIMPLE_FUNC_IMPL(Health, Health, health)

    SIMPLE_FUNC_IMPL(MotorPWM, MotorPWM, motorPWM)

    SIMPLE_FUNC_IMPL(VehicleWP, VehicleWP, vehicleWP)

private:
    /* Peripheral Interface */
    struct BodyAccel bodyAccel;
    struct BodyAngularVelocity bodyAngularVelocity;
    struct BodyMag bodyMag;
    struct GPS gps;
    struct Barometer barometer;
    struct Lidar lidar;

    /* control */
    struct Controller controller;
    struct VehicleAttitueSP vehicleAttitudeSP;
    struct VehiclePositionSP vehiclePositionSP;

    /* AHRS */
    struct Attitude attitude;
    struct NedAccel nedAccel;

    /* INS */
    struct LocalPosition localPosition;
    struct GlobalPosition globalPosition;

    /* flight state */
    struct ArmFlag armFlag;
    struct ModeFlag modeFlag;

    /* frequency of sensor and module etc. */
    struct Health health;

    /* actuator */
    struct MotorPWM motorPWM;

    /* waypoints */
    struct VehicleWP vehicleWP;
};

extern MsgBus msgBus;

}

#endif
