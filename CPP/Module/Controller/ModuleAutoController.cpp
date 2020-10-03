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
float ModuleAutoController::MC_L2 = 1.5f;      /* L2 */


ModuleAutoController::ModuleAutoController()
   // TODO Auto-generated constructor stub
:
   curSeq(0),
   nextSeq(1),
   flag(0),
   missionFlag(RESET),
   hoveringFlag(0),
   transitionFlag(0),
   RTLFlag(0),
   readyLandFlag(0)
   {}


void ModuleAutoController::main(){
   uint8_t firstLoop;
   ModuleAutoController moduleAutoController;
   uint32_t tick;
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
           if(readyLandFlag == SET){
            doRTL();
//            printf_("currrent seq %u  ",curSeq);
            printf_("RTL\r\n");
           }
           else{
            printf_("NOT HOME LOCATION");
           }
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
//   printf_("localPositionSub %f %f %f",localPositionSub.refLat,localPositionSub.refLon,localPositionSub.refAlt);
//   printf_("%f\r\n",localPositionSub.refAlt);
   for (int i = 0; i < getWaypointLength(); i++) {
      waypointLLA = getWaypointLLA(i);
//      printf_("%d %f %f %f",i,waypointLLA.lat,waypointLLA.lon,waypointLLA.alt);
      lla2LocalNed( waypointLLA.lat, waypointLLA.lon, waypointLLA.alt,
            localPositionSub.refLat, localPositionSub.refLon, localPositionSub.refAlt,
                 &vehicleWpNED.wp[i].x, &vehicleWpNED.wp[i].y, &vehicleWpNED.wp[i].z);
      vehicleWpNED.wp[i].command = waypointLLA.command;
      vehicleWpNED.wp[i].param = waypointLLA.param;
      if(vehicleWpNED.wp[i].command == AutoCommand::Hovering)
      {
         hoveringFlag = i;
      }
      if(vehicleWpNED.wp[i].command == AutoCommand::RTL)
      {
         RTLFlag = i;
      }
      if(vehicleWpNED.wp[i].command == AutoCommand::Transition)
      {
         transitionFlag = i;
      }
      vehicleWpNED.wp[i].z = -waypointLLA.alt;
//      printf_("lla, ned wp : %f %f %f, %f %f %f, %f %f %f\r\n", waypointLLA.lat, waypointLLA.lon, waypointLLA.alt, vehicleWpNED.wp[i].x, vehicleWpNED.wp[i].y, vehicleWpNED.wp[i].z
//            ,localPositionSub.refLat, localPositionSub.refLon, localPositionSub.refAlt );
//      printf_("param %u\r\n",waypointLLA.param);
//      printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[i].x,&vehicleWpNED.wp[i].y,&vehicleWpNED.wp[i].z);
   }
//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[0].x,&vehicleWpNED.wp[0].y,&vehicleWpNED.wp[0].z);
//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[0].x,&vehicleWpNED.wp[0].y,&vehicleWpNED.wp[0].z);

//   printf_("ned xyz %f %f %f \r\n",&vehicleWpNED.wp[1].x,&vehicleWpNED.wp[1].y,&vehicleWpNED.wp[1].z);

//   curSeq = 0;
//   nextSeq = 1;
//   flag = 0;
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
//   printf_("current %f %f %f \r\n",vehicleX,vehicleVelY,vehicleVelZ);
//   printf_("next %f %f %f \r\n",nextWaypointX,nextWaypointY,nextWaypointZ);

   matrix::Vector3f nextPos(nextWaypointX, nextWaypointY, nextWaypointZ);
   matrix::Vector3f lastPos(previousWaypointX, previousWaypointY, previousWaypointZ);
   matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
   matrix::Vector3f distance(nextWaypointX - vehicleX, nextWaypointY - vehicleY, nextWaypointZ - vehicleZ);
   matrix::Vector3f velocity(vehicleVelX, vehicleVelY, vehicleVelZ);
   /* unit vectors */
   matrix::Vector3f T = (nextPos - lastPos) / (nextPos - lastPos).norm();
//   printf_("T uniy vectot : %f %f %f \r\n",T(0),T(1),T(2));
   matrix::Vector3f N(-T(1), T(0), 0.0f);
//   printf_("N uniy vectot : %f %f %f \r\n",N(0),N(1),N(2));

   crossTrackError = N.dot(curPos - lastPos);
//   printf_("CrossTracl error %f\r\n",crossTrackError);
   l2 = velocity.norm() * MC_L2;
//   printf_("l2 %f\r\n",l2);
   /* calculate D_dt */
   if (crossTrackError > l2)
      D_dt = std::min<double>(crossTrackError / tan(ceptAngle), l2 * MC_D);
   else
      D_dt = std::max<double>(std::min<double>(crossTrackError / tan(ceptAngle), l2 * MC_D), sqrt(pow(l2, 2) - pow(crossTrackError, 2)));
//   printf_("D_dt %f\r\n",D_dt);
   targetDist = T.dot(nextPos - curPos) - D_dt;
//   printf_("targetDist %f %f %f\r\n",targetDist,nextPos.norm(),curPos.norm());
   matrix::Vector3f targetPos = -T * std::max<double>(0, targetDist) + nextPos;
//   printf_("targetPos : %f %f %f %f\r\n",targetPos(0),targetPos(1),targetPos(2),targetPos.norm());

   crossAng = asin((float)(((targetPos - curPos).cross(velocity)).norm()) / ((velocity).norm() * (targetPos - curPos).norm()));

   dotAng = (float)((targetPos - curPos).dot(velocity)) / ((velocity).norm() * (targetPos - curPos).norm());
   if(dotAng < 0)
   {
      dotAng = -dotAng;
   }
   dotAng = acos((float)dotAng);
//   printf_("angles %f %f\r\n",dotAng,crossAng);
   if((float)abs(crossAng-dotAng) < 0.1){
      tempAng = dotAng;
   }
   else
      tempAng = 999;
//   printf_("yaw angles %f\r\n",tempAng);
   aCmd = 2.0f * sin(tempAng) * velocity.norm() / MC_L2;
//   printf_("acmd %f\r\n",aCmd);
   /* setting target position */
   roll = atan(aCmd / FC_GRAVITY_ACCEERATION);
//   printf_("roll %f\r\n",roll);

//   *targetRoll = roll;
   if(roll > 60.0f * FC_PI / 180.0f)
   {
      roll = 60.0f * FC_PI / 180.0f;
   }
//   printf_("roll %f\r\n",*targetRoll);

   *targetRoll = roll;
   *targetYaw = tempAng;
   *targetX = targetPos(0);
   *targetY = targetPos(1);
   *targetZ = targetPos(2);
   *dist = distance.norm();
   printf_("guidance value %f %f %f %f %f %f",targetPos(0),targetPos(1),targetPos(2),tempAng * FC_PI / 180, roll*FC_PI / 180,distance.norm());
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
   vehiclePositionSpPub.x = homeX;
   vehiclePositionSpPub.y = homeY;
   vehiclePositionSpPub.z = localPositionSub.z + 3;
   vehiclePositionSpPub.yaw = 0.0f;
//   vehiclePositionSpPub.targetRoll = 0.0;

   msgBus.setVehiclePositionSP(vehiclePositionSpPub);

   if (localPositionSub.vz <= 0.0) flag = SET;
}

/* ModuleAutoController::doTakeoff */
/* step1: doing takeoff (current x, current y, -5) until current position z >= 4.5*/
/* step2: doing navigate home -> waypoint0 */
void ModuleAutoController::doTakeoff() {
   // get home position through average while 2 seconds
   homeX = 0.0f;
   homeY = 0.0f;
   homeZ = 0.0f;
   uint32_t tick = millisecond();
   uint8_t avg = 0;
   msgBus.getLocalPosition(&this->localPositionSub);
   if(tick - 2000 > 0){
      homeX += localPositionSub.x;
      homeY += localPositionSub.y;
      homeZ += localPositionSub.z;
      avg++;
   }
   else{
   homeX = homeX / avg;
   homeX = homeY / avg;
   homeX = homeZ / avg;
   printf_("HOME %f %f %f \r\n",homeX,homeY,homeZ);
   vehiclePositionSpPub.timestamp = microsecond();
   vehiclePositionSpPub.x = homeX;
   vehiclePositionSpPub.y = homeY;
   vehiclePositionSpPub.z = homeZ - 5.0f;
   vehiclePositionSpPub.yaw = localPositionSub.yaw;
   vehiclePositionSpPub.roll = 0.0f;

   msgBus.setVehiclePositionSP(vehiclePositionSpPub);
   if (localPositionSub.z <= -1.0) curSeq++;
   }
}
/* ModuleAutoController::doGuidance */
/* do navigate previous waypoint -> next waypoint */
void ModuleAutoController::doGuidance() {

   float dist;
   msgBus.getLocalPosition(&this->localPositionSub);
   // HOME TO WP1
   if(missionFlag == RESET){
      guidance(homeX, homeY, homeZ,
            vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
            localPositionSub.x, localPositionSub.y, localPositionSub.z,
            localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
            &targetYaw, &targetRoll,
            &targetX, &targetY, &targetZ, &dist);
      if (dist < 3) missionFlag = SET;
//      printf_("%f\r\n", dist);
      }
   else{
      // As possible as go mission location radius 0.05
   if(curSeq == hoveringFlag - 2){
      guidance(vehicleWpNED.wp[curSeq].x, vehicleWpNED.wp[curSeq].y, vehicleWpNED.wp[curSeq].z,
          vehicleWpNED.wp[nextSeq].x, vehicleWpNED.wp[nextSeq].y, vehicleWpNED.wp[nextSeq].z,
          localPositionSub.x, localPositionSub.y, localPositionSub.z,
          localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
          &targetYaw, &targetRoll,
          &targetX, &targetY, &targetZ, &dist);
      if (dist < 0.05) {
        osDelay(1500);
        curSeq++;
        curSeq++;
        nextSeq++;
        nextSeq++;
      }
   }
   // guidance before hovering waypoint to next hovering waypoint
   else if(curSeq == hoveringFlag + 1){
         guidance(vehicleWpNED.wp[curSeq - 2].x, vehicleWpNED.wp[curSeq - 2].y, vehicleWpNED.wp[curSeq - 2].z,
             vehicleWpNED.wp[nextSeq - 1].x, vehicleWpNED.wp[nextSeq - 1].y, vehicleWpNED.wp[nextSeq - 1].z,
             localPositionSub.x, localPositionSub.y, localPositionSub.z,
             localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
             &targetYaw, &targetRoll,
             &targetX, &targetY, &targetZ, &dist);
         if (dist < 3) {
           curSeq++;
           nextSeq++;
         }
   }
   // guidance RTL waypoint to HOME
   else if(curSeq == RTLFlag){
         guidance(vehicleWpNED.wp[curSeq - 1].x, vehicleWpNED.wp[curSeq - 1].y, vehicleWpNED.wp[curSeq - 1].z,
             homeX,homeY,homeZ,
             localPositionSub.x, localPositionSub.y, localPositionSub.z,
             localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
             &targetYaw, &targetRoll,
             &targetX, &targetY, &targetZ, &dist);
         if (dist < 0.05) {
            readyLandFlag =SET;
         }
   }
   else{
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
   }
   }
//   printf_("%f\r\n", dist);
   setPosition();
}

/* MoudleAutoController::doRTL */
/* step1: do navigate current position -> home (0,0,current position z) */
/* step2: do landing */
void ModuleAutoController::doRTL() {
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
