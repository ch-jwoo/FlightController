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

namespace FC {
FlightMode ModuleAutoController::flightMode = FlightMode::AutoWaypoint;

float ModuleAutoController::MC_D = 0.7f;      /* D */
float ModuleAutoController::MC_L2 = 1.5f;      /* L2 */


ModuleAutoController::ModuleAutoController() {
   // TODO Auto-generated constructor stub
}

void ModuleAutoController::main(){
   uint8_t firstLoop;
   ModuleAutoController moduleAutoController;
   uint32_t tick;
   uint32_t s = 0;
   while (1) {
      firstLoop = 0;
      tick = millisecond();
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

         uint32_t s = 0;
         moduleAutoController.oneStep();
         //printf_("onestep %u\r\n", s);
         s++;
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
   switch (flightMode){
//   //printf_("first switch");
   case FlightMode::AutoWaypoint:
      switch (vehicleWpNED.wp[curSeq].command){
//      //printf_("second switch");
         case AutoCommand::Guidance:
            doGuidance();
            printf_("currrent seq %u  ",curSeq);
            printf_("Guidance\r\n");
            break;
         case AutoCommand::RTL:
            doRTL();
            printf_("currrent seq %u  ",curSeq);
            printf_("RTL\r\n");
            break;
         case AutoCommand::Takeoff:
            doTakeoff();
            printf_("currrent seq %u  ",curSeq);
            printf_("TakeOff\r\n");
            break;
         case AutoCommand::Land:
            doLand();
            printf_("currrent seq %u  ",curSeq);
            printf_("Land\r\n");
            break;
         case AutoCommand::Hovering:
            doHovering();
            printf_("currrent seq %u  ",curSeq);
            printf_("Hovering\r\n");
            break;
         case AutoCommand::Transition:
            doTransition();
            printf_("currrent seq %u   ",curSeq);
            printf_("Transition\r\n");
            break;
      }
      //printf_("endup auto waypoint\r\n");
      break;
   case FlightMode::AutoRTL:
      doRTL();
      printf_("autoRTL\r\n");
      break;
   case FlightMode::AutoTakeoff:
      doTakeoff();
      printf_("AutoTakeoff\r\n");
      break;
   case FlightMode::AutoLand:
      doLand();
      printf_("AutoLand\r\n");
      break;
   case FlightMode::AutoTransition:
      doTransition();
      printf_("AutoTransition\r\n");
      break;
   default:
      break;
   }
   //printf_("end switch\r\n");
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
   printf_("localPositionSub %f %f %f",localPositionSub.refLat,localPositionSub.refLon,localPositionSub.refAlt);
//   printf_("%f\r\n",localPositionSub.refAlt);
   for (int i = 0; i < getWaypointLength(); i++) {
      waypointLLA = getWaypointLLA(i);
      lla2LocalNed( waypointLLA.lat, waypointLLA.lon, waypointLLA.alt,
            localPositionSub.refLat, localPositionSub.refLon, localPositionSub.refAlt,
                 &vehicleWpNED.wp[i].x, &vehicleWpNED.wp[i].y, &vehicleWpNED.wp[i].z);
      vehicleWpNED.wp[i].command = waypointLLA.command;
      vehicleWpNED.wp[i].param = waypointLLA.param;
//      printf_("param %u\r\n",waypointLLA.param);
//      printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[i].x,&vehicleWpNED.wp[i].y,&vehicleWpNED.wp[i].z);
   }
//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[0].x,&vehicleWpNED.wp[0].y,&vehicleWpNED.wp[0].z);
//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[0].x,&vehicleWpNED.wp[0].y,&vehicleWpNED.wp[0].z);

//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[1].x,&vehicleWpNED.wp[1].y,&vehicleWpNED.wp[1].z);

   curSeq = 0;
   nextSeq = 1;
   flag = 0;
}

/*
*  ModuleAutoController::guidance();
*  step1: calculate unit vectors(track, normal)
*  step2: calculate crossTrackError, l2, D_dt, target position
*  step3: calculate target yaw, roll
*  step4: setting position with msgBus
*/
void ModuleAutoController::guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
   float nextWaypointX, float nextWaypointY, float nextWaypointZ,
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
   double crossTrackError, l2, D_dt, targetDist, aCmd;
   double crossAng, dotAng, tempAng;
   double roll;

   /* vectors */
   matrix::Vector3f nextPos(nextWaypointX, nextWaypointY, nextWaypointZ);
   matrix::Vector3f lastPos(previousWaypointX, previousWaypointY, previousWaypointZ);
   matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
   matrix::Vector3f distance(nextWaypointX - vehicleX, nextWaypointY - vehicleY, nextWaypointZ - vehicleZ);
   matrix::Vector3f velocity(vehicleVelX, vehicleVelY, vehicleVelZ);
   /* unit vectors */
   matrix::Vector3f T = (nextPos - lastPos) / (nextPos - lastPos).norm();
   printf_("T uniy vectot : %f %f %f \r\n",T(0),T(1),T(2));
   matrix::Vector3f N(-T(1), T(0), 0.0f);
   printf_("N uniy vectot : %f %f %f \r\n",N(0),N(1),N(2));

   crossTrackError = N.dot(curPos - lastPos);
   printf_("CrossTracl error %f\r\n",crossTrackError);
   l2 = velocity.norm() * MC_L2;
   printf_("l2 %f\r\n",l2);
   /* calculate D_dt */
   if (crossTrackError > l2)
      D_dt = std::min<double>(crossTrackError / tan(ceptAngle), l2 * MC_D);
   else
      D_dt = std::max<double>(std::min<double>(crossTrackError / tan(ceptAngle), l2 * MC_D), sqrt(pow(l2, 2) - pow(crossTrackError, 2)));
   printf_("D_dt %f\r\n",D_dt);
   targetDist = T.dot(nextPos - curPos) - D_dt;
   printf_("targetDist %f\r\n",targetDist);
   matrix::Vector3f targetPos = -T * std::max<double>(0, targetDist) + nextPos;
   printf_("targetPos : %f %f %f \r\n",targetPos(0),targetPos(1),targetPos(2));

   crossAng = asin(((targetPos - curPos).cross(velocity)).norm()) / ((velocity).norm() * (targetPos - curPos).norm());
   printf_("crossang %f\r\n",crossAng);
   dotAng = acos((targetPos - curPos).dot(velocity)) / ((velocity).norm() * (targetPos - curPos).norm());
   printf_("dotang %f\r\n",dotAng);
   /* calculate heading -pi/2 < yaw < pi/2 */
   if (dotAng > 90.0f)
      tempAng = 90.0f;
   else
      tempAng = crossAng;
   printf_("tmpang %f\r\n",tempAng);
   aCmd = 2.0f * sin(tempAng) * velocity.norm() / MC_L2;
   /* setting target position */
   roll = atan(aCmd / FC_GRAVITY_ACCEERATION);
   printf_("roll %f\r\n",roll);

   *targetRoll = roll;
   if(roll > 45.0f * FC_PI / 180.0f)
   {
      *targetRoll = 45.0f * FC_PI / 180.0f;
   }
   *targetYaw = tempAng * FC_PI / 180.0f;
   *targetX = targetPos(0);
   *targetY = targetPos(1);
   *targetZ = targetPos(2);
   *dist = distance.norm();
//   printf_("%f %f %f %f %f ",targetPos(0),targetPos(1),targetPos(2),tempAng * FC_PI / 180,*targetRoll);
}

/* ModuleAutoController::setPosition */
/* setting target position */
void ModuleAutoController::setPosition() {

   vehiclePositionSpPub.timestamp = microsecond();
   vehiclePositionSpPub.x = targetX;
   vehiclePositionSpPub.y = targetY;
   vehiclePositionSpPub.z = targetZ;
   vehiclePositionSpPub.yaw = targetYaw;
   //    VehicleWP.targetRoll = &targetRoll;

   msgBus.setVehiclePositionSP(vehiclePositionSpPub);
}

/* ModuleAutoController::doLand*/
/* do landing with current position x, y, z+3 until current velocity z is zero */

void ModuleAutoController::doLand() {


   msgBus.getLocalPosition(&this->localPositionSub);

   vehiclePositionSpPub.timestamp = microsecond();
   vehiclePositionSpPub.x = 0.0f;
   vehiclePositionSpPub.y = 0.0f;
   vehiclePositionSpPub.z = localPositionSub.z + 3;
   vehiclePositionSpPub.yaw = 0.0f;
//   vehiclePositionSpPub.targetRoll = 0.0;

   msgBus.setVehiclePositionSP(vehiclePositionSpPub);

   if (localPositionSub.vz <= 0.0) flag = SET;
}

/* ModuleAutoController::doTakeoff */
/* step1: doing takeoff (0, 0, -5) until current position z >= 4.5*/
/* step2: doing navigate home -> waypoint0 */
void ModuleAutoController::doTakeoff() {

   float dist;
   msgBus.getLocalPosition(&this->localPositionSub);

   if (flag == SET) {
      vehiclePositionSpPub.timestamp = microsecond();
      vehiclePositionSpPub.x = 0.0f;
      vehiclePositionSpPub.y = 0.0f;
      vehiclePositionSpPub.z = -5.0f;
      vehiclePositionSpPub.yaw = 0.0f;
      //    VehicleWP.targetRoll = 0.0;
      msgBus.setVehiclePositionSP(vehiclePositionSpPub);


      if (localPositionSub.z >= -1.5f) flag = 3;
   }
   else {
      guidance(0.0f, 0.0f, localPositionSub.z,
            vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
            localPositionSub.x, localPositionSub.y, localPositionSub.z,
            localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
            &targetYaw, &targetRoll,
            &targetX, &targetY, &targetZ, &dist);

      setPosition();
      if (dist < 3) {
         curSeq++;
         nextSeq++;
         flag = SET;
      }
   }
}

/* ModuleAutoController::doGuidance */
/* do navigate previous waypoint -> next waypoint */
void ModuleAutoController::doGuidance() {

   float dist;

   msgBus.getLocalPosition(&this->localPositionSub);

   guidance(vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
         vehicleWpNED.wp[nextSeq].x, vehicleWpNED.wp[nextSeq].y, vehicleWpNED.wp[nextSeq].z,
         localPositionSub.x, localPositionSub.y, localPositionSub.z,
         localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
         &targetYaw, &targetRoll,
         &targetX, &targetY, &targetZ, &dist);

   if (dist < 3) {
      curSeq++;
      nextSeq++;
   }

   setPosition();
}

/* MoudleAutoController::doRTL */
/* step1: do navigate current position -> home (0,0,current position z) */
/* step2: do landing */
void ModuleAutoController::doRTL() {
   float dist;

   msgBus.getLocalPosition(&this->localPositionSub);

   if (flag == SET) {
      guidance(localPositionSub.x, localPositionSub.y, localPositionSub.z, localPositionSub.x, localPositionSub.y, localPositionSub.z, 0.0, 0.0, localPositionSub.z, localPositionSub.vx, localPositionSub.vy, localPositionSub.vz, &targetYaw, &targetRoll, &targetX, &targetY, &targetZ, &dist);
      setPosition();
      if (dist < 0.05) flag = 3;
   }
   else
      doLand();
}

/* ModuleAutoController::doHovering */
/* setting position with current position x,y,z while holding time*/
void ModuleAutoController::doHovering() {

   msgBus.getLocalPosition(&this->localPositionSub);

   vehiclePositionSpPub.timestamp = microsecond();
   vehiclePositionSpPub.x = localPositionSub.x;
   vehiclePositionSpPub.y = localPositionSub.y;
   vehiclePositionSpPub.z = localPositionSub.z;
   vehiclePositionSpPub.yaw = 0.0f;

   osDelay(5);

   curSeq++;
   nextSeq++;
   //TODO Get winch finish flag or get holding time, hal_gettick?
}

/* ModuleAutoController::doTransition */
/* step1: reading fw or mc state parameter from waypoint */
/* step2: depending on state and contion, curSeq++ nextSeq++ */
void ModuleAutoController::doTransition() {

   msgBus.getLocalPosition(&this->localPositionSub);

   matrix::Vector3f speed(localPositionSub.vx, localPositionSub.vy, localPositionSub.vz);

   switch (vehicleWpNED.wp[curSeq].param) {
   case 1: {
      //TODO sending starting transition signal
      if (speed.norm() > 20) {
         //TODO set virtual setpoint(?)
         curSeq++;
         nextSeq++;

      }
      break;
   }
   case 2: {
      //TODO sending starting transition signal
      //TODO set virtual setpoint(?)
      if (speed.norm() < 5) {
         curSeq++;
         nextSeq++;
      }
      break;
   }
   }
   //TODO Front transition -> position conroller off -> if( cruise speead<20) seq++
   //TODO Back transition -> position controller off -> if() seq++
}


} /* namespace FC */
