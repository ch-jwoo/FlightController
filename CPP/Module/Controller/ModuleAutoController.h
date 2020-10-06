/*
* ModuleAutoController.h
*
*  Created on: 2020. 8. 18.
*      Author: cjb88
*/

#ifndef MODULE_MODULEAUTOCONTROLLER_H_
#define MODULE_MODULEAUTOCONTROLLER_H_

#include "Utils/Freq.h"
#include "freertosVariable.h"
#include "cmsis_os.h"

#include "MsgBus/Waypoint.h"
#include "MsgBus/Params.h"

namespace FC {

typedef struct{
   float x;
   float y;
   float z;
   AutoCommand command;
   uint16_t param;
} WaypointNED;

typedef struct{
   WaypointNED wp[20];
   uint8_t len;
} VehicleWpNED;

enum AutoSignal{
   AUTO_start = 0x01,
   AUTO_stop = 0x02,
   AUTO_reset = 0x04
};

class ModuleAutoController : public Freq<ModuleAutoController> {
public:
   ModuleAutoController();

   static void main();

   static void start(FlightMode tempFlightMode);

   static inline void setSignal(enum AutoSignal signal){
      osThreadFlagsSet(AUTO_TaskHandle, signal);
   }

   void L2guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
		   	   	   float curWaypointX, float curWaypointY, float curWaypointZ,
				   float vehicleX, float vehicleY, float vehicleZ,
				   float vehicleVelX, float vehicleVelY, float vehicleVelZ,
				   float *targetYaw, float *targetRoll,
				   float *targetX, float *targetY, float *targetZ, float *dist);

   void L1guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
		   	   	   float curWaypointX, float curWaypointY, float curWaypointZ,
				   float vehicleX, float vehicleY, float vehicleZ,
				   float vehicleVelX, float vehicleVelY, float vehicleVelZ,
				   float *targetYaw, float *targetRoll,
				   float *targetX, float *targetY, float *targetZ, float *dist);

   void directGuidance(float vehicleX, float vehicleY, float vehicleZ,
		   	   	   	   float nextX, float nextY, float nextZ,
					   float velX, float velY, float velZ,
					   float *targetYaw, float *targetRoll,
					   float *targetX, float *targetY, float *targetZ, float *dist);

   void lateralTrackControl(float prevWpX, float prevWpY, float prevWpZ,
  	   	   	   	   	   	    float curWpX, float curWpY, float curWpZ,
		   	   	   	   	    float vehicleX, float vehicleY, float vehicleZ,
		   	   	   	   	    float velX, float velY, float velZ,
							float* targetX, float* targetY, float* targetZ, float* targetYaw);

   PARAM(TAKEOFF_ALT);
   PARAM(WP_ACQ_R);
   PARAM(RTL_ALT);

   /* guidance parameters */
   PARAM(MC_D);            /* D */
   PARAM(L1_MAG);
   PARAM(MC_L2);            /* L2 */
   PARAM(ROLL_MAX_ANGLE);
   PARAM(INTERCEPT_ANGLE);

private:
   /* from commander */
   static FlightMode flightMode;

   /* input */
   struct LocalPosition localPositionSub { 0 };
//   struct VehicleWP vehicleWPSub { 0 };

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
   uint8_t curSeq, nextSeq, missionSeq;

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

   float homeX;
   float homeY;
   float homeZ;
   /*
   *  using for saving waypoint ned position
   */
   VehicleWpNED vehicleWpNED;


   uint8_t ceptAngle = 45;

   /* onestep function */
   void oneStep();


   /* simple calculation function */
   void waypointLla2LocalNed();

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
//   void guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
//      float nextWaypointX, float nextWaypointY, float nextWaypointZ,
//      float vehicleX, float vehicleY, float vehicleZ,
//      float vehicleVelX, float vehicleVelY, float vehicleVelZ,
//      float *targetYaw, float *targetRoll,
//      float *targetX, float *targetY, float *targetZ, float *dist);

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

public:
   ~ModuleAutoController() = default;
   ModuleAutoController(const ModuleAutoController &other) = delete;
   ModuleAutoController(ModuleAutoController &&other) = delete;
   ModuleAutoController& operator=(const ModuleAutoController &other) = delete;
   ModuleAutoController& operator=(ModuleAutoController &&other) = delete;

};


} /* namespace FC */

#endif /* MODULE_MODULEAUTOCONTROLLER_H_ */
