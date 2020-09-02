/*
* ModuleAutoController.cpp
*
*  Created on: 2020. 8. 18.
*      Author: choi jun woo is pig
*/

#include "MsgBus/MsgBus.h">
#include <Module/Manager/ModuleCommander.h>
#include "Lib/Matrix/matrix/Dcm.hpp"
#include "Lib/Matrix/matrix/Matrix.hpp"
#include "cmath"
#include <algorithm>
#include "ModuleAutoController.h"

#include <Utils/Constants.h>
#include "Usec.h"
#include "cmsis_os.h"

#include "printf.h"

namespace FC {
FlightMode ModuleAutoController::flightMode = FlightMode::AutoWaypoint;

ModuleAutoController::ModuleAutoController() {
	// TODO Auto-generated constructor stub
}
	
void ModuleAutoController::main(){
	uint8_t firstLoop;
	ModuleAutoController moduleAutoController;
	while (1) {
		firstLoop = 0;
		/* wait auto controller start */
		osThreadFlagsWait(AUTO_start, osFlagsWaitAny, osWaitForever);
		osThreadFlagsClear(AUTO_reset | AUTO_stop | AUTO_start);
		while(1){
			/* if first loop or reset command, initialize */
			if(osThreadFlagsGet() & AUTO_reset){
				osThreadFlagsClear(AUTO_reset);
				moduleAutoController.waypointToLocalNed();
			}

			moduleAutoController.oneStep();

			/* check position controller stop */
			if(osThreadFlagsGet() & AUTO_stop){
				osThreadFlagsClear(AUTO_stop);
				break;
			}

			/* if first loop, send ACK */
			if(firstLoop < 2){
				firstLoop++;
			}
			else if(firstLoop == 2){
				ModuleCommander::sendSignal(CMD_ACK);
				printf_("auto ACK\r\n");
				firstLoop++;
			}

			osDelay(30);    	/* 30hz */
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
//	msgBus.getModeFlag(&modeFlag);

	switch (flightMode){
	case FlightMode::AutoWaypoint:
		switch (waypointNED[curSeq].command){
			case AutoCommand::Guidance:
				doGuidance();
				break;
			case AutoCommand::RTL:
				doRTL();
				break;
			case AutoCommand::Takeoff:
				doTakeoff();
				break;
			case AutoCommand::Land:
				doLand();
				break;
			case AutoCommand::Hovering:
				doHovering();
				break;
			case AutoCommand::Transition:
				doTransition();
				break;
		}
	case FlightMode::AutoRTL:
		doRTL();
		break;
	case FlightMode::AutoTakeoff:
		doTakeoff();
		break;
	case FlightMode::AutoLand:
		doLand();
		break;
	case FlightMode::AutoTransition:
		doTransition();
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
void ModuleAutoController::waypointToLocalNed() {

	msgBus.getLocalPosition(&this->localPositionSub);

	msgBus.getVehicleWP(&this->vehicleWPSub);

	for (int i = 0; i < vehicleWPSub.len; i++) {
		llaToLocalNed(localPositionSub.refLat, localPositionSub.refLat, localPositionSub.refAlt,
					  vehicleWPSub.wp[i].lat, vehicleWPSub.wp[i].lon, vehicleWPSub.wp[i].alt,
					  &waypointNED[i].x, &waypointNED[i].y, &waypointNED[i].z);
		waypointNED[i].command = waypointNED[i].command;
		waypointNED[i].param = waypointNED[i].param;
	}

	curSeq = 0;
	nextSeq = 1;
	flag = 0;
}

/*
*  ModuleAutoController::geoToECEF();
*  step1: calculating radius of curvature
*  step2: converting geodetic position to ECEF position
*/
void ModuleAutoController::geoToECEF(double lat, double lon, float alt, double *ecefX, double *ecefY, double *ecefZ) {
	/* radus of curvature */
	double radius = EARTH_RADIUS / (1 - sqrt(1 - pow(EARTH_ECCENTRICTIY * sin(lat), 2)));

	/*cosine sine function with latitude and longitude*/
	double cosLat = cos(lat);
	double cosLon = cos(lon);
	double sinLat = sin(lat);
	double sinLon = sin(lon);
	/*ECEF position*/
	*ecefX = (radius + alt)*cosLat * cosLon;
	*ecefY = (radius + alt)*cosLat * sinLon;
	*ecefZ = (radius * (1 - pow((double)EARTH_ECCENTRICTIY, 2)) + alt) * sinLat;
}

/*
*  ModuleAutoController::llaToLocalNed();
*  step1: calculating direction cosine matrix for local ned position
*  step2: subtracting ECEF position Reference ECEF position
*  step3: calculating local ned position
*/
void ModuleAutoController::llaToLocalNed(double lat, double lon, float alt,
		double refLat, double refLon, float refAlt,
		float *localNedX, float *localNedY, float *localNedZ){

	/* reference ecef axis */
	double refEcefX, refEcefY, refEcefZ;
	geoToECEF(refLat, refLon, refAlt, &refEcefX, &refEcefY, &refEcefZ);

	/* target ecef axis */
	double ecefX, ecefY, ecefZ;
	geoToECEF(lat, lon, alt, &ecefX, &ecefY, &ecefZ);

	/*
	*  z axis rotate 'longitude'
	*  y axis rotate '-latitude-90'
	*/
	double dcm[9] = { -sin(refLat) * cos(refLon), -sin(refLat) * sin(refLon),  cos(refLat),
				   -sin(refLon)             ,  cos(refLon)             ,  0,
				   -cos(refLat) * cos(refLon), -cos(refLat) * sin(refLon), -sin(refLat) };

	matrix::Matrix<double, 3, 3> dcmMatrix(dcm);

	/*ECEF - RefECEF*/
	double temp[3] = { ecefX - refEcefX,
					ecefY - refEcefY,
					ecefZ - refEcefZ };

	matrix::Matrix<double, 3, 1> tempMatrix(temp);
	matrix::Matrix<double, 3, 1> nedMatrix = dcmMatrix * tempMatrix;

	/*local ned position*/
	*localNedX = nedMatrix(1, 1);
	*localNedY = nedMatrix(2, 1);
	*localNedZ = nedMatrix(3, 1);
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

	/* vectors */
	matrix::Vector3f nextPos(nextWaypointX, nextWaypointY, nextWaypointZ);
	matrix::Vector3f lastPos(previousWaypointX, previousWaypointY, previousWaypointZ);
	matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
	matrix::Vector3f distance(nextWaypointX - vehicleX, nextWaypointY - vehicleY, nextWaypointZ - vehicleZ);
	matrix::Vector3f velocity(vehicleVelX, vehicleVelY, vehicleVelZ);
	/* unit vectors */
	matrix::Vector3f T = (nextPos - lastPos) / (nextPos - lastPos).norm();
	matrix::Vector3f N(-T(1), T(0), 0);


	crossTrackError = N.dot(curPos - lastPos);
	l2 = velocity.norm() * tau;
	/* calculate D_dt */
	if (crossTrackError > l2)
		D_dt = std::min<double>(crossTrackError / tan(ceptAngle), l2 * M_dp);
	else
		D_dt = std::max<double>(std::min<double>(crossTrackError / tan(ceptAngle), l2 * M_dp), sqrt(pow(l2, 2) - pow(crossTrackError, 2)));

	targetDist = T.dot(nextPos - curPos) - D_dt;
	matrix::Vector3f targetPos = -T * std::max<double>(0, targetDist) + nextPos;

	crossAng = asin(((targetPos - curPos).cross(velocity)).norm()) / ((velocity).norm() * (targetPos - curPos).norm());
	dotAng = acos((targetPos - curPos).dot(velocity)) / ((velocity).norm() * (targetPos - curPos).norm());
	/* calculate heading -pi/2 < yaw < pi/2 */
	if (dotAng > 90)
		tempAng = 90;
	else
		tempAng = crossAng;

	aCmd = 2 * sin(tempAng) * velocity.norm() / tau;
	/* setting target position */
	*targetRoll = atan(aCmd / FC_GRAVITY_ACCEERATION);
	*targetYaw = tempAng * FC_PI / 180;
	*targetX = targetPos(0);
	*targetY = targetPos(1);
	*targetZ = targetPos(2);
	*dist = distance.norm();
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
//	vehiclePositionSpPub.targetRoll = 0.0;

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


		if (localPositionSub.z >= 4.5) flag == 3;
	}
	else {
		guidance(0.0f, 0.0f, localPositionSub.z, localPositionSub.x, localPositionSub.y, localPositionSub.z, waypointNED[curSeq].x, waypointNED[curSeq].y, waypointNED[curSeq].z, localPositionSub.vx, localPositionSub.vy, localPositionSub.vz, &targetYaw, &targetRoll, &targetX, &targetY, &targetZ, &dist);
		setPosition();
		if (dist < 20) {
			flag = SET;
		}
	}
}

/* ModuleAutoController::doGuidance */
/* do navigate previous waypoint -> next waypoint */
void ModuleAutoController::doGuidance() {

	float dist;

	msgBus.getLocalPosition(&this->localPositionSub);

	guidance(waypointNED[curSeq].x, waypointNED[curSeq].y, waypointNED[curSeq].z, localPositionSub.x, localPositionSub.y, localPositionSub.z, waypointNED[nextSeq].x, waypointNED[nextSeq].y, waypointNED[nextSeq].z, localPositionSub.vx, localPositionSub.vy, localPositionSub.vz, &targetYaw, &targetRoll, &targetX, &targetY, &targetZ, &dist);

	if (dist < 20) {
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

	switch (waypointNED[curSeq].param) {
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
