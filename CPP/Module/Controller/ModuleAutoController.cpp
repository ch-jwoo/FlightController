/*
* ModuleAutoController.cpp
*
*  Created on: 2020. 8. 18.
*      Author: choi jun woo is pig
*/

#include "MsgBus/MsgBus.h"
#include <Module/Manager/ModuleCommander.h>
#include "Lib/Matrix/matrix/Dcm.hpp"
#include "Lib/Matrix/matrix/Matrix.hpp"
#include "cmath"
#include <algorithm>
#include "ModuleAutoController.h"

#include <Utils/Constants.h>
#include "Utils/Functions.h"
#include "Usec.h"
#include "cmsis_os.h"

#include "printf.h"
#include "Utils/Constants.h"
#include "Module/Estimator/ModuleINS.h"

namespace FC {
FlightMode ModuleAutoController::flightMode = FlightMode::AutoWaypoint;

float ModuleAutoController::MC_D = 0.7f;      /* D */
float ModuleAutoController::L1_MAG = 5.0f;      /* L1 */
float ModuleAutoController::MC_L2 = 1.5f;      /* L2 */
float ModuleAutoController::TAKEOFF_ALT = 2.0;

float ModuleAutoController::WP_ACQ_R = 3.0;
float ModuleAutoController::RTL_ALT = 10.0;
float ModuleAutoController::ROLL_MAX_ANGLE = 60.0f;
float ModuleAutoController::INTERCEPT_ANGLE = 45.0f;

ModuleAutoController::ModuleAutoController()
: curSeq(0)
, homeX(0.0)
, homeY(0.0)
, homeZ(0.0)
{}


void ModuleAutoController::main(){
   uint8_t firstLoop;
   ModuleAutoController moduleAutoController;
   while (1) {
      firstLoop = 0;
//      //printf_("tick %d\rn",tick);
      /* wait auto controller start */
      osThreadFlagsWait(AUTO_start, osFlagsWaitAny, osWaitForever);

      osThreadFlagsClear(AUTO_reset | AUTO_stop | AUTO_start);
//      //printf_("whilebefore\r\n");
//      uint32_t s = 0;
      while(1){
         /* if first loop or reset command, initialize */
         if(osThreadFlagsGet() & AUTO_reset){
//            //printf_("step6\r\n");
            osThreadFlagsClear(AUTO_reset);
//            //printf_("step7\r\n");
            moduleAutoController.waypointLla2LocalNed();
//            //printf_("step8\r\n");
         }

//         uint32_t s = 0;
         moduleAutoController.oneStep();
//         printf_("onestep %u\r\n", s);
//         s++;
         /* check position controller stop */
         if(osThreadFlagsGet() & AUTO_stop){
            osThreadFlagsClear(AUTO_stop);
            break;
         }

         /* if first loop, send ACK */
         if(firstLoop < 2){
            firstLoop++;
            printf_("%u\r\n", firstLoop);
         }
         else if(firstLoop == 2){
            ModuleCommander::sendSignal(CMD_ACK);
            printf_("auto ACK\r\n");
            firstLoop++;
         }
         osDelay(30);       /* 30hz */
      }
   }
}

void ModuleAutoController::start(FlightMode tempFlightMode){
   flightMode = tempFlightMode;
   setSignal(AUTO_start);
}

/*
*  ModuleAutoController::oneStep()
*/
void ModuleAutoController::oneStep() {
//   msgBus.getModeFlag(&modeFlag);
//   //printf_("before first switch");
//   osDelay(1000);

   /* mission complete */
   if(curSeq == vehicleWpNED.len) return;

   switch (flightMode){
//   //printf_("first switch");
   case FlightMode::AutoWaypoint:
      switch (vehicleWpNED.wp[curSeq].command){
//      //printf_("second switch");
         case AutoCommand::Guidance:
            doGuidance();
//            printf_("guidance : %u %f, %f %f %f, %f %f\r\n",curSeq, targetX, targetY, targetZ, targetYaw * FC_RAD2DEG, targetRoll * FC_RAD2DEG);
            break;
         case AutoCommand::RTL:
            doRTL();
           break;
         case AutoCommand::Takeoff:
            // aquisition, next step
            doTakeoff();
//            printf_("TakeOff, currrent seq %u\r\n",curSeq);
            break;
         case AutoCommand::Land:
            doLand();
//            printf_("Land, currrent seq %u\r\n",curSeq);
            break;
         case AutoCommand::Hovering:
            doHovering();
//            printf_("hover, currrent seq %u\r\n",curSeq);
            break;
         case AutoCommand::Transition:
            doTransition();
//            printf_("currrent seq %u   ",curSeq);
//            printf_("Transition\r\n");
            break;
      }
      //printf_("endup auto waypoint\r\n");
      break;
   case FlightMode::AutoRTL:
      doRTL();
//      printf_("autoRTL\r\n");
      break;
   case FlightMode::AutoTakeoff:
      doTakeoff();
//      printf_("AutoTakeoff\r\n");
      break;
   case FlightMode::AutoLand:
      doLand();
//      printf_("AutoLand\r\n");
      break;
   case FlightMode::AutoTransition:
      doTransition();
//      printf_("AutoTransition\r\n");
      break;
   default:
      break;
   }
   freqCount();
}

/*
*  ModuleAutoController::waypointToLocalNed();
*  step1: getting localPosition waypoints with msgBus
*  step2: calculating waypoints position in ned
*/
void ModuleAutoController::waypointLla2LocalNed() {
	WaypointLLA waypointLLA;
	msgBus.getLocalPosition(&localPositionSub);
	for (int i = 0; i < getWaypointLength(); i++) {
		waypointLLA = getWaypointLLA(i);
		lla2LocalNed(waypointLLA.lat, waypointLLA.lon, waypointLLA.alt,
					 localPositionSub.refLat, localPositionSub.refLon, localPositionSub.refAlt,
					 &vehicleWpNED.wp[i].x, &vehicleWpNED.wp[i].y, &vehicleWpNED.wp[i].z);

		vehicleWpNED.wp[i].command = waypointLLA.command;
		vehicleWpNED.wp[i].param = waypointLLA.param;

		/* change altitude to local NED z */
		vehicleWpNED.wp[i].z = -waypointLLA.alt;
	}
}

/*
*  ModuleAutoController::guidance();
*  step1: calculate unit vectors(track, normal)
*  step2: calculate crossTrackError, l2, D_dt, target position
*  step3: calculate target yaw, roll
*  step4: setting position with msgBus
*/
void ModuleAutoController::L2guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
									  float curWaypointX, float curWaypointY, float curWaypointZ,
									  float vehicleX, float vehicleY, float vehicleZ,
									  float vehicleVelX, float vehicleVelY, float vehicleVelZ,
									  float *targetYaw, float *targetRoll,
									  float *targetX, float *targetY, float *targetZ, float *dist) {

	/*
	* variables
	* crossTrackError  distance vehicle to track with perpendicular
	* l2               magnitude of line of sight vector, vector of vehicle -> target position
	* D_dt             l2 inner product track, distance vehicle to target position
	* targetDist       distance target position to next waypoint
	* aCmd             centripetal acceleration
	* crossAng         angle of cross product l2 vector with velocity vector
	* dotAng           angle of inner product l2 vector with velocity vector
	* tau              constant for l2
	*
	*/
	float crossTrackError, l2, D_dt, targetDist, aCmd;
	float crossAng, dotAng;
	float roll;

	msgBus.getLocalPosition(&localPositionSub);

	/* vectors */
	matrix::Vector3f nextPos(curWaypointX, curWaypointY, curWaypointZ);
	matrix::Vector3f lastPos(previousWaypointX, previousWaypointY, previousWaypointZ);
	matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
	matrix::Vector3f distance(curWaypointX - vehicleX, curWaypointY - vehicleY, curWaypointZ - vehicleZ);
	matrix::Vector3f velocity(vehicleVelX, vehicleVelY, vehicleVelZ);

	/* unit vectors */
	matrix::Vector3f T = (nextPos - lastPos) / (nextPos - lastPos).norm();
	matrix::Vector3f N(-T(1), T(0), 0.0f);
	matrix::Vector3f signCheck = T.cross(N);

	crossTrackError = N.dot(curPos - lastPos);

	l2 = velocity.norm() * MC_L2;

	/* calculate D_dt */
	if (crossTrackError > l2)
		D_dt = std::min<float>(crossTrackError / tan(INTERCEPT_ANGLE), l2 * MC_D);
	else
		D_dt = std::max<float>(std::min<float>(crossTrackError / tan(INTERCEPT_ANGLE), l2 * MC_D), sqrt(pow(l2, 2) - pow(crossTrackError, 2)));

	targetDist = T.dot(nextPos - curPos) - D_dt;

	matrix::Vector3f targetPos = -T * std::max<float>(0, targetDist) + nextPos;


	crossAng = asin((float)(((targetPos - curPos).cross(velocity)).norm()) / ((velocity).norm() * (targetPos - curPos).norm()));
	printf_("body %f",crossAng);

	/* transform body yaw to ned yaw */
	if(signCheck(2) > 0){
		crossAng *= -1;
	}
	crossAng += localPositionSub.yaw;
	crossAng = radianThreshold(localPositionSub.yaw + crossAng, -FC_PI, FC_PI);

	printf_("cy %f  final %f\r\n",localPositionSub.yaw,crossAng);

	//   printf_("yaw angles %f\r\n",tempAng);
	aCmd = 2.0f * sin(crossAng) * velocity.norm() / MC_L2;
	//   printf_("acmd %f\r\n",aCmd);
	/* setting target position */
	roll = atan(aCmd / FC_GRAVITY_ACCEERATION);
	//   printf_("roll %f\r\n",roll);

	//   *targetRoll = roll;
	if(roll > ROLL_MAX_ANGLE * FC_DEG2RAD){
		roll = ROLL_MAX_ANGLE * FC_DEG2RAD;
	}
	//   printf_("roll %f\r\n",*targetRoll);

	*targetRoll = roll;
	*targetYaw = crossAng;
	*targetX = targetPos(0);
	*targetY = targetPos(1);
	*targetZ = targetPos(2);
	*dist = distance.norm();
	printf_("dist %f\r\n",distance.norm());
}

void ModuleAutoController::L1guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
         	 	 	 	 	 	 	  float curWaypointX, float curWaypointY, float curWaypointZ,
									  float vehicleX, float vehicleY, float vehicleZ,
									  float vehicleVelX, float vehicleVelY, float vehicleVelZ,
									  float *targetYaw, float *targetRoll,
									  float *targetX, float *targetY, float *targetZ, float *dist){

	float D_dt, aCmd;
	float tempAng;
	float errorMag;		/* error magnitude */

	msgBus.getLocalPosition(&localPositionSub);

	/* make input vectors */
	matrix::Vector3f prevWP(previousWaypointX, previousWaypointY, previousWaypointZ);
	matrix::Vector3f curWP(curWaypointX, curWaypointY, curWaypointZ);
	matrix::Vector3f vehiclePos(vehicleX, vehicleY, vehicleZ);
	matrix::Vector3f vehicleVel(vehicleVelX, vehicleVelY, vehicleVelZ);

	/* vectors */
	matrix::Vector3f distance(curWaypointX - vehicleX, curWaypointY - vehicleY, curWaypointZ - vehicleZ);
	matrix::Vector3f T = (curWP - prevWP);
	T.normalize();
	matrix::Vector3f N(-T(1), T(0), 0.0f);
	N.normalize();
	errorMag = N.dot(vehiclePos - prevWP);
	D_dt = sqrt(L1_MAG*L1_MAG - errorMag*errorMag);
	matrix::Vector3f L1(D_dt * T - errorMag * N);

	tempAng= asin(L1.cross(vehicleVel).norm() / (L1.norm() * vehicleVel.norm()));
	if(localPositionSub.vx  > 0){
		if(localPositionSub.vy > 0){
			printf_("1 quadrant\r\n");
			tempAng += localPositionSub.yaw;
		}
		else if(localPositionSub.vy < 0){
			printf_("4 quadrant\r\n");
			tempAng = localPositionSub.yaw - tempAng;
		}
		else{
			tempAng = localPositionSub.yaw;
		}
	}
	else{
		if(localPositionSub.vy > 0){
			printf_("2 quadrant\r\n");
			tempAng = localPositionSub.yaw - tempAng;
		}
		else if(localPositionSub.vy < 0){
			printf_("3 quadrant\r\n");
			tempAng = localPositionSub.yaw + tempAng;
		}
		else{
			tempAng = localPositionSub.yaw;
		}
	}

//	printf_("cy%f \r\n by %f",localPositionSub.yaw,tempAng);
	tempAng = radianThreshold(localPositionSub.yaw + tempAng, -FC_PI, FC_PI);
	*targetYaw = tempAng;
	aCmd = 2 * pow(vehicleVel.norm(), 2) * sin(*targetYaw) / L1.norm();
	*targetRoll = atan(aCmd / FC_GRAVITY_ACCEERATION);
	*targetX = L1(0);
	*targetY = L1(1);
	*targetZ = L1(2);
	*dist = distance.norm();
}
void ModuleAutoController::directGuidance(float vehicleX, float vehicleY, float vehicleZ,
										  float nextX, float nextY, float nextZ,
										  float velX, float velY, float velZ,
										  float *targetYaw, float *targetRoll,
										  float *targetX, float *targetY, float *targetZ, float *dist){

	double tempAng;
	matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
	matrix::Vector3f targetPos(nextX, nextY, nextZ);
	matrix::Vector3f distance(velX,velY,velZ);
	matrix::Vector3f L1(nextX- vehicleX, nextY - vehicleY, nextZ - vehicleZ);

	tempAng = asin(L1.cross(distance).norm() / (L1.norm() * distance.norm()));

	if(localPositionSub.vx  > 0){
		if(localPositionSub.vy > 0){
			printf_("1 quadrant\r\n");
			tempAng += localPositionSub.yaw;
		}
		else if(localPositionSub.vy < 0){
			printf_("4 quadrant\r\n");
			tempAng = localPositionSub.yaw - tempAng;
		}
		else{
			tempAng = localPositionSub.yaw;
		}
	}
	else{
		if(localPositionSub.vy > 0){
			printf_("2 quadrant\r\n");
			tempAng = localPositionSub.yaw - tempAng;
		}
		else if(localPositionSub.vy < 0){
			printf_("3 quadrant\r\n");
			tempAng = localPositionSub.yaw + tempAng;
		}
		else{
			tempAng = localPositionSub.yaw;
		}
	}

	tempAng = radianThreshold(tempAng, -FC_PI, FC_PI);
	printf_("cy%f  final %f\r\n",localPositionSub.yaw,tempAng*FC_RAD2DEG);
	//    tempAng = radianThreshold(localPositionSub.yaw + tempAng, -FC_PI, FC_PI);
	float aCmd = 2 * pow(distance.norm(), 2) * sin(*targetYaw) / L1.norm();

	*targetYaw = tempAng;
	*targetRoll = atan(aCmd / FC_GRAVITY_ACCEERATION);
	*targetX = nextX;
	*targetY = nextY;
	*targetZ = nextZ;
	*dist = L1.norm();
}

void ModuleAutoController::lateralTrackControl(float prevWpX, float prevWpY, float prevWpZ,
   	   	   	   	   	   	   	   	   	   	   	   float curWpX, float curWpY, float curWpZ,
											   float vehicleX, float vehicleY, float vehicleZ,
											   float velX, float velY, float velZ,
											   float* targetX, float* targetY, float* targetZ, float* targetYaw){

	matrix::Vector3f prevWP(prevWpX, prevWpY, prevWpZ);
	matrix::Vector3f curWP(curWpX, curWpY, curWpZ);
	matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
	matrix::Vector3f trackVector = curWP - prevWP;
	matrix::Vector3f curRelPos = curPos - prevWP;
}

/* ModuleAutoController::setPosition */
/* setting target position */
void ModuleAutoController::setPosition() {

	vehiclePositionSpPub.timestamp = microsecond();
	vehiclePositionSpPub.x = targetX;
	vehiclePositionSpPub.y = targetY;
	vehiclePositionSpPub.z = targetZ;
	vehiclePositionSpPub.yaw = targetYaw;
	msgBus.setVehiclePositionSP(vehiclePositionSpPub);
}

/* ModuleAutoController::doLand*/
/* do landing with current position x, y, z+3 until current velocity z is zero */

void ModuleAutoController::doLand() {
	static bool firstRun = true;
	static float startX, startY, startYaw;

	msgBus.getLocalPosition(&this->localPositionSub);

	if(firstRun){
		startX = localPositionSub.x;
		startY = localPositionSub.y;
		startYaw = localPositionSub.yaw;
		firstRun = false;
	}

	vehiclePositionSpPub.timestamp = microsecond();
	vehiclePositionSpPub.x = startX;
	vehiclePositionSpPub.y = startY;
	vehiclePositionSpPub.z = localPositionSub.z + 3.0f;
	vehiclePositionSpPub.yaw = startYaw;

	msgBus.setVehiclePositionSP(vehiclePositionSpPub);

	if (localPositionSub.vz <= 0.0f) curSeq++;
}

/* ModuleAutoController::doTakeoff */
/* step1: doing takeoff (current x, current y, -5) until current position z >= 4.5*/
/* step2: doing navigate home -> waypoint0 */
void ModuleAutoController::doTakeoff() {
	static bool firstRun = true;
	static float startX, startY, startYaw;
	// get home position through average while 2 seconds
	msgBus.getLocalPosition(&this->localPositionSub);


	if(firstRun){
		startX = localPositionSub.x;
		startY = localPositionSub.y;
		startYaw = localPositionSub.yaw;
		firstRun = false;
	}

	vehiclePositionSpPub.timestamp = microsecond();
	vehiclePositionSpPub.x = startX;
	vehiclePositionSpPub.y = startY;
	vehiclePositionSpPub.z = localPositionSub.z - 5.0f;
	vehiclePositionSpPub.yaw = startYaw;
	vehiclePositionSpPub.roll = 0.0f;

	msgBus.setVehiclePositionSP(vehiclePositionSpPub);

	/* takeoff complete */
	if (localPositionSub.z < -TAKEOFF_ALT ) {
		curSeq++;
		firstRun = true;
	}

}
/* ModuleAutoController::doGuidance */
/* do navigate previous waypoint -> next waypoint */
void ModuleAutoController::doGuidance(){
//	static uint8_t lastSeq = 0;
//	static bool firstRun = true;
//	static float startX, startY, startZ;
//	float dist;

	msgBus.getLocalPosition(&localPositionSub);

	float relX = vehicleWpNED.wp[curSeq].x - localPositionSub.x;
	float relY = vehicleWpNED.wp[curSeq].y - localPositionSub.y;
	float relZ = vehicleWpNED.wp[curSeq].z - localPositionSub.z;

	float cosVal = relX/(sqrt(relX*relX + relY*relY));
	cosVal = constraints(cosVal, -1, 1);
	float yaw = std::acos(cosVal);
	if(relY < 0.0f){
		yaw  = -yaw;
	}

	vehiclePositionSpPub.timestamp = microsecond();
	vehiclePositionSpPub.x = vehicleWpNED.wp[curSeq].x;
	vehiclePositionSpPub.y = vehicleWpNED.wp[curSeq].y;
	vehiclePositionSpPub.z = vehicleWpNED.wp[curSeq].z;
	vehiclePositionSpPub.yaw = yaw;

	msgBus.setVehiclePositionSP(vehiclePositionSpPub);

	float dist = sqrt(relX*relX + relY*relY + relZ*relZ);

	if (dist < WP_ACQ_R){
//		lastSeq = curSeq;
		curSeq++;
//		firstRun = true;
	}

//	matrix::Vector3f lastwp(localPositionSub.vx,localPositionSub.vy,localPositionSub.vz);

	// HOME TO WP1
//	if(lastSeq == 0){
//		if(firstRun){
//			startX = localPositionSub.x;
//			startY = localPositionSub.y;
//			startZ = localPositionSub.z;
//			firstRun = false;
//		}
//		if(lastwp.norm() < 5){
//			directGuidance(localPositionSub.x, localPositionSub.y, localPositionSub.z,
//					       vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
//						   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
//						   &targetYaw, &targetRoll, &targetX, &targetY, &targetZ,
//						   &dist);
//		}
//		else{
//			L1guidance(startX, startY, startZ,
//					   vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
//					   localPositionSub.x, localPositionSub.y, localPositionSub.z,
//					   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
//					   &targetYaw, &targetRoll,
//					   &targetX, &targetY, &targetZ, &dist);
//
//			L2guidance(startX, startY, startZ,
//					   vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
//					   localPositionSub.x, localPositionSub.y, localPositionSub.z,
//					   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
//					   &targetYaw, &targetRoll,
//					   &targetX, &targetY, &targetZ, &dist);
//		}
//
//
//		if (dist < WP_ACQ_R){
//			lastSeq = curSeq;
//			curSeq++;
//			firstRun = true;
//		}
//	}
//	else{
//		if(lastwp.norm() < 5){
//			directGuidance(localPositionSub.x, localPositionSub.y, localPositionSub.z, vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z, startX, startY, startZ, &targetYaw, &targetRoll, &targetX, &targetY, &targetZ, &dist);
//		}
//		else{
//			L1guidance(startX, startY, startZ,
//					   vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
//					   localPositionSub.x, localPositionSub.y, localPositionSub.z,
//					   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
//					   &targetYaw, &targetRoll,
//					   &targetX, &targetY, &targetZ, &dist);
//			L2guidance(startX, startY, startZ,
//					   vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
//					   localPositionSub.x, localPositionSub.y, localPositionSub.z,
//					   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
//					   &targetYaw, &targetRoll,
//					   &targetX, &targetY, &targetZ, &dist);
//		}
//		if (dist < WP_ACQ_R) {
//			lastSeq = curSeq;
//			curSeq++;
//		}
//	}
//	setPosition();
}

/* MoudleAutoController::doRTL */
/* step1: do navigate current position -> home (0,0,current position z) */
/* step2: do landing */
void ModuleAutoController::doRTL() {
	static uint8_t RTLstep = 0;
	static float startX, startY, startZ;
	static bool firstRun = true;
	float dist;


	if(RTLstep == 0){
		if(firstRun){
			startX = localPositionSub.x;
			startY = localPositionSub.y;
			startZ = localPositionSub.z;
			firstRun = false;
		}

		L2guidance(startX, startY, startZ,
				   0.0f, 0.0f, -RTL_ALT,
				   localPositionSub.x, localPositionSub.y, localPositionSub.z,
				   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
				   &targetYaw, &targetRoll,
				   &targetX, &targetY, &targetZ, &dist);

		if(dist < WP_ACQ_R){
			RTLstep++;
		}
	}
	else{
		doLand();
	}
}

/* ModuleAutoController::doHovering */
/* setting position with current position x,y,z while holding time*/
void ModuleAutoController::doHovering() {
	static bool firstRun = true;
	static float delayTime = 0;
	static uint32_t startTime = 0;

	if(firstRun){
		msgBus.getLocalPosition(&localPositionSub);
		vehiclePositionSpPub.yaw = localPositionSub.yaw;
		delayTime = vehicleWpNED.wp[curSeq].param;
		firstRun = false;
		startTime = millisecond();
	}

	if((millisecond()-startTime) * 1000 > delayTime){
		vehiclePositionSpPub.timestamp = microsecond();
		vehiclePositionSpPub.x = vehicleWpNED.wp[curSeq - 1].x;
		vehiclePositionSpPub.y = vehicleWpNED.wp[curSeq - 1].y;
		vehiclePositionSpPub.z = vehicleWpNED.wp[curSeq - 1].z;
	}
	else{
		firstRun = true;
		curSeq++;
	}
}

/* ModuleAutoController::doTransition */
/* step1: reading fw or mc state parameter from waypoint */
/* step2: depending on state and contion, curSeq++ nextSeq++ */
void ModuleAutoController::doTransition() {

	msgBus.getLocalPosition(&this->localPositionSub);

	matrix::Vector3f speed(localPositionSub.vx, localPositionSub.vy, localPositionSub.vz);

	switch (vehicleWpNED.wp[curSeq].param) {
	case 1:
		//TODO sending starting transition signal
		if (speed.norm() > 20) {
		//TODO set virtual setpoint(?)
		curSeq++;
		}
		break;
	case 2:
		//TODO sending starting transition signal
		//TODO set virtual setpoint(?)
		if (speed.norm() < 5) {
			curSeq++;
		}
		break;
	}
	//TODO Front transition -> position conroller off -> if( cruise speead<20) seq++
	//TODO Back transition -> position controller off -> if() seq++
}


} /* namespace FC */
