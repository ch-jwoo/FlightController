/*
 * ModuleINS.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: cjb88
 */

#include "ModuleINS.h"
#include <Utils/Constants.h>
#include <Module/Controller/ModulePositionController.h>
#include "Usec.h"

namespace FC {

bool ModuleINS::calGpsHomeFlag = true;
uint8_t ModuleINS::avgIndexGPS = 0;
double ModuleINS::avgLat = 0;
double ModuleINS::avgLon = 0;
float ModuleINS::avgAlt = 0;

ModuleINS::ModuleINS()
	: refLat(0)
	, refLon(0)
	, refAlt(0)
{}

void ModuleINS::main(){
	uint32_t tick;
	tick = osKernelGetTickCount();

	ModuleINS moduleINS;
	moduleINS.initialize();
	osDelay(2000);
	while(1){
		tick += 10;
		osDelayUntil(tick);

		moduleINS.onestep();
		ModulePositionController::setSignal(PC_fromEKF);
	}
}
void ModuleINS::onestep(){
   ExtU input = {0,};

   if(msgBus.getNedAccel(&nedAccelSub)){
      input.AhrsFlag = true;
      input.ax = nedAccelSub.xyz[0];
      input.ay = nedAccelSub.xyz[1];
      input.az = nedAccelSub.xyz[2] + FC_GRAVITY_ACCEERATION;      /* subtract gravity */
   }
   else input.AhrsFlag = false;

   if(msgBus.getGPS(&gpsSub)){
	   /* not fixed */
      if(gpsSub.fixType == false){
         input.GpsFlag = false;
      }

      /* calculate home LLA */
      else if(calGpsHomeFlag == true){
         input.GpsFlag = false;
         calAvgLLA(gpsSub.lat, gpsSub.lon, gpsSub.alt);
      }

      /* there is home LLA */
      else{
         input.GpsFlag = true;
         input.lat=gpsSub.lat;
         input.lon=gpsSub.lon;
         input.alt=gpsSub.alt;
         input.vx=gpsSub.velN;
         input.vy=gpsSub.velE;
         input.GPS_switch=true;
      }
   }
   else input.GpsFlag = false;

   input.HOME_lla[0]=refLat;
   input.HOME_lla[1]=refLon;
   input.HOME_lla[2]=refAlt;

   if(msgBus.getBarometer(&baroSub)){
      input.BaroFlag = true;
      input.baroZ = baroSub.altitude;
   }
   else input.BaroFlag = false;

   if(msgBus.getLidar(&lidar) && lidar.valid){
      input.LidarFlag = true;
      input.Lidar_height = lidar.altitude;
   }
   else input.LidarFlag = false;

   setExternalInputs(&input);
   step();
   ExtY output = getExternalOutputs();

   /* local position (local NED) */
   localPositionPub.timestamp = microsecond();
   localPositionPub.ax = (float)output.estiAX;
   localPositionPub.ay = (float)output.estiAY;
   localPositionPub.az = (float)output.estiAZ;

   localPositionPub.vx = (float)output.estiVX;
   localPositionPub.vy = (float)output.estiVY;
   localPositionPub.vz = (float)output.estiVZ;

   localPositionPub.x = (float)output.estiX;
   localPositionPub.y = (float)output.estiY;
   localPositionPub.z = (float)output.estiZ;
//   localPositionPub.gpsrawx=(float)output.GPSrawX;
//   localPositionPub.gpsrawy=(float)output.GPSrawY;

   /* global position (LLA) */
   globalPositionPub.lat=output.Estim_LatLon[0];
   globalPositionPub.lon=output.Estim_LatLon[1];
   globalPositionPub.alt=(float)output.Estim_Alt;

   globalPositionPub.refAlt=refAlt;
   globalPositionPub.timestamp = microsecond();


   /* heading */
   msgBus.getAttitude(&attitudeSub);
   localPositionPub.yaw = attitudeSub.yaw;
   globalPositionPub.yaw=attitudeSub.yaw;

   msgBus.setLocalPosition(localPositionPub);
   msgBus.setGlobalPosition(globalPositionPub);

   freqCount();
}


void ModuleINS::setAvgLLA(){
	calGpsHomeFlag = true;
	avgIndexGPS = 0;
	avgLat = 0;
	avgLon = 0;
	avgAlt = 0;
}

void ModuleINS::calAvgLLA(double lat, double lon, float alt){
	float alpha = (avgIndexGPS-1)/avgIndexGPS;
	avgLat = alpha*avgLat + (1-alpha)*lat;
	avgLon = alpha*avgLon + (1-alpha)*lon;
	avgAlt = alpha*avgAlt + (1-alpha)*alt;

	avgIndexGPS++;

	if(avgIndexGPS > AVERAGE_SIZE){
		calGpsHomeFlag = false;
		refLat = avgLat;
		refLon = avgLon;
		refAlt = avgAlt;
	}
}

} /* namespace FC */
