/*
* ModuleAutoController.h
*
*  Created on: 2020. 8. 18.
*      Author: cjb88
*/

#ifndef MODULE_MODULEAUTOCONTROLLER_H_
#define MODULE_MODULEAUTOCONTROLLER_H_
#include "cmsis_os.h"
namespace FC {

typedef struct {
	float x;
	float y;
	float z;
	AutoCommand command;
	uint16_t param;
}WaypointNED;

class ModuleAutoController {
public:
	ModuleAutoController();

	static void main() {
		ModuleAutoController moduleAutoController ;
//		waypointToLocalNed();
		while (1) {
			moduleAutoController.oneStep();
			osDelay(30);                  /* 30hz */
		}
	}

	~ModuleAutoController() = default;
	ModuleAutoController(const ModuleAutoController &other) = delete;
	ModuleAutoController(ModuleAutoController &&other) = delete;
	ModuleAutoController& operator=(const ModuleAutoController &other) = delete;
	ModuleAutoController& operator=(ModuleAutoController &&other) = delete;

private:
	/* input */
	struct ModeFlag modeFlag { 0 };
	struct LocalPosition localPositionSub { 0 };
	struct VehicleWP vehicleWPSub { 0 };

	/* output */
	struct VehiclePositionSP vehiclePositionSpPub { 0 };

	/* variable */
	/*
	*  variable
	*  \curSeq        current sequence
	*  \nextSeq       next sequence
	*  \missionSeq    mission sequence
	*  \flag          using for processing in auto mission function
	*/
	uint8_t curSeq, nextSeq, missionSeq, flag;
	/*
	*  setting position variables
	*  \targetX     target x in ned
	*  \targetY     target y in ned
	*  \targetZ     target z in ned
	*  \targetRoll  target roll in ned
	*  \targetYaw   target yaw in ned
	*/
	float targetX;
	float targetY;
	float targetZ;
	float targetRoll;
	float targetYaw;

	/*
	*  using for saving waypoint ned position
	*/
	WaypointNED waypointNED[20];
	/* earth eccentricity */
	constexpr static float EARTH_ECCENTRICTIY = 0.08181919f;

	/* earth radius in [m] */
	const static uint32_t EARTH_RADIUS = 6378137;

	float M_dp = 0.7f;
	float tau = 1.5f;
	uint8_t ceptAngle = 45;

	/* onestep function */
	void oneStep();

	/* simple calculation function */
	void waypointToLocalNed();

	/*
	*  LLA axis -(geoToECEF)-> ecef axis --> local ned axis
	*  param[in]      lat            latitude
	*  param[in]      lon            longitude
	*  param[in]      alt            altitude
	*  param[in]      refLat         reference latitude
	*  param[in]      refLon         reference longitude
	*  param[in]      refAlt         reference altitude
	*  param[out]      localNedX      local ned x
	*  param[out]      localNedY      local ned y
	*  param[out]      localNedZ      local ned z
	*/
	void llaToLocalNed(double lat, double lon, float alt,
		double refLat, double refLon, float refAlt,
		float *localNedX, float *localNedY, float *localNedZ);

	/*
	*  geo axis -> ecef axis
	*  param[in]      lat         latitude
	*  param[in]      lon         longitude
	*  param[in]      alt         altitude
	*  param[out]      ecefX      ecef-x
	*  param[out]      ecefY      ecef-y
	*  param[out]      ecefZ      ecef-z
	*/
	void geoToECEF(double lat, double lon, float alt, double *ecefX, double *ecefY, double *ecefZ);

	/*
	*  generate set point for previous vehicle waypoint to next waypoint
	*  \param[in]      lastX      previous waypoint ned-x
	*  \param[in]      lastY      previous waypoint ned-y
	*  \param[in]      lastZ      previous waypoint ned-z
	*  \param[in]      curX      current vehicle position ned-x
	*  \param[in]      curX      current vehicle position ned-y
	*  \param[in]      curX      current vehicle position ned-z
	*  \param[in]      vX         current vehicle velocity of ned-x
	*  \param[in]      vY         current vehicle velocity of ned-y
	*  \param[in]      vZ         current vehicle velocity of ned-z
	*  \param[out]      targetYaw   target yaw
	*  \param[out]      targetRoll   target roll
	*  \param[out]      targetX      target X
	*  \param[out]      targetY      target Y
	*  \param[out]      targetZ      target Z
	*  \param[out]      dist      distance current position to waypoint
	*/
	void guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
		float nextWaypointX, float nextWaypointY, float nextWaypointZ,
		float vehicleX, float vehicleY, float vehicleZ,
		float vehicleVelX, float vehicleVelY, float vehicleVelZ,
		float *targetYaw, float *targetRoll,
		float *targetX, float *targetY, float *targetZ, float *dist);

	/*
	*  simple auto-mission command function
	*  \setPosition();   setting target position with msgBus
	*  \doLand();        doing land (0, 0, curZ+3) in ned
	*  \doTakeoff();     doing Takeoff (0, 0, -5) in ned
	*  \doGuidance();    calculating target position, heading and roll in ned
	*  \doRTL();         doGuidance current position to (0, 0, curZ) and doLand
	*  \doHovering();    waiting holding time and setting position with current position
	*  \doTransition();  getting Transition flag
	*  every function, except doLand(); doRTL();, increases curSeq, nextSeq
	*/
	void setPosition();

	void doLand();
	void doTakeoff();
	void doGuidance();
	void doRTL();
	void doHovering();
	void doTransition();
};

} /* namespace FC */

#endif /* MODULE_MODULEAUTOCONTROLLER_H_ */
