#ifndef __MSGTYPE__H
#define __MSGTYPE__H
#include "main.h"

namespace FC{

enum class Command{
	ControlAttitude,
	ControlPosition,
	AutoWaypoint,
	AutoRTL,
	AutoTakeoff,
	AutoLand,

	Arm,
	DisArm
};

/*
 *  Peripheral data
 */
struct BodyAccel {
    uint64_t timestamp;
    float xyz[3];
};

struct BodyAngularVelocity {
    uint64_t timestamp;
    float xyz[3];
};

struct BodyMag{
    uint64_t timestamp;
    float xyz[3];
};

struct GPS{
    uint64_t timestamp;
    uint64_t timestampUTC;  /* timestamp of UTC in microsecond */

    double lat;             /* Latitude position from GPS, -90 to 90 degrees response. */
    double lon;             /* Longitude position from GPS, -180 to 180 degrees response. */
    float alt;              /* Altitude in meters above MSL (meter) */

    float vel;
    float velN;             /* GPS ground speed (m/s) */
    float velE;             /* GPS North velocity (m/s) */
    float velD;             /* GPS Down velocity (m/s) */
    float direction;        /* direction of velocity from North (rad) */

    float hdop;             /* Horizontal dilution of precision */
    float vdop;             /* Vertical dilution of precision */

    uint8_t numSatellites;  /*  Number of satellites used */
    uint8_t fixType;        /* 1: no fix, 2: 2D fix, 3: 3D fix */
};

struct Barometer{
    uint64_t timestamp;
    float pressure;			/* hPa */
    float temperature;		/* degC */
};

struct Controller{
    uint64_t timestamp;
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;
};

/*
 *  Estimate
 */
struct Attitude{
    uint64_t timestamp;
    float q[4];	/* quaternion */
    float roll, pitch, yaw;	/* roll pitch yaw */
};

struct NedAccel{
    uint64_t timestamp;
    float xyz[3];
};

/*
 *  Command State Flag
 */
enum class FlightModeType{
	ControlAttitude,
	ControlPosition,
	AutoWaypoint,
	AutoRTL,
	AutoTakeoff,
	AutoLand,
};
struct ModeFlag{
	uint64_t timestamp;
	Command armMode;
	Command flightMode;
};

enum class ArmModeType{
	Arm,
	DisArm
};


}

#endif
