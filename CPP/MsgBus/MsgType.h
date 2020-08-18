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
	AutoTransition,

	Arm,
	DisArm,

	MotorCalibration
};

/*
 *  Peripheral data
 */
struct BodyAccel {
    uint64_t timestamp;
    float xyz[3];			/* [m/s^2] */
};

struct BodyAngularVelocity {
    uint64_t timestamp;		/* [rad/s] */
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

struct LocalPosition{
	uint64_t timestamp;

	float x;
	float y;
	float z;

	float vx;
	float vy;
	float vz;

	float ax;
	float ay;
	float az;

	float yaw;

	double refLat;
	double refLon;
	float refAlt;
};

struct Barometer{
    uint64_t timestamp;
    float pressure;			/* hPa */
    float temperature;		/* degC */
    float altitude;			/* meter */
};


/* vehicle control */
struct Controller{
    uint64_t timestamp;
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;
};

struct VehicleAttitueSP{
	uint64_t timestamp;
	float roll;				/* rad */
	float pitch;			/* rad */
	float yawRate;			/* rad/s */
	float throttle;			/* 0~1 */
};

struct VehiclePositionSP{
	uint64_t timestamp;
	float x;				/* [m] */
	float y;				/* [m] */
	float alt;				/* [m] */
	float yaw;				/* rad */
	float roll;				/* rad */
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

struct ModeFlag{
	uint64_t timestamp;
	Command armMode;
	Command flightMode;
};


/*
 *  health check
 */
struct Health{
	uint64_t timestamp;

	uint16_t accel;
	uint16_t gyro;
	uint16_t rc;

	uint16_t mag;
	uint16_t gps;

	uint16_t baro;
	uint16_t lidar;

	uint16_t ahrs;
	uint16_t ins;

	uint16_t attitudeController;
	uint16_t positionController;
	uint16_t autoController;
};

/*
 *  Actuator
 */
struct MotorPWM{
	uint64_t timestamp;
	uint16_t m1;
	uint16_t m2;
	uint16_t m3;
	uint16_t m4;
	uint16_t m5;
	uint16_t m6;
};


/* waypoint */
struct Waypoint{
	double lat;
	double lon;
	float alt;
	uint16_t command;
	uint16_t param;
};

struct VehicleWP{
	uint64_t timestamp;
	Waypoint wp[20];
	uint8_t len;
};

}

#endif
