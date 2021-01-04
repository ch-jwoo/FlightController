/*
 * ModulePositionController.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#include <Module/Controller/ModulePositionController.h>
#include <Utils/Constants.h>
#include <Utils/Functions.h>
#include <Module/Manager/ModuleCommander.h>
#include "Usec.h"
#include "cmath"
#include "printf.h"
#include "Lib/Matrix/matrix/Matrix.hpp"

namespace FC {

ModulePositionController::ModulePositionController() {
	// TODO Auto-generated constructor stub
}

void ModulePositionController::main(){
	uint8_t firstLoop;
	ModulePositionController positionController;
	while(1){
		firstLoop = 0;
		/* wait position controller start */
		osThreadFlagsWait(PC_start, osFlagsWaitAny, osWaitForever);
		osThreadFlagsClear(PC_reset | PC_stop | PC_start);
		while(1){
			/* if first loop or reset command, initialize */
			if(osThreadFlagsGet() & PC_reset){
				osThreadFlagsClear(PC_reset);
				positionController.positionControlModelClass::initialize();
				positionController.fw_TECSModelClass::initialize();
			}

			/* wait EKF data */
			osThreadFlagsWait(PC_fromEKF, osFlagsWaitAny, osWaitForever);
			positionController.oneStep();

			/* check position controller stop */
			if(osThreadFlagsGet() & PC_stop){
				osThreadFlagsClear(PC_stop);
				break;
			}

			/* if first loop, send ACK */
			if(firstLoop < 2){
				firstLoop++;
			}
			else if(firstLoop == 2){
				ModuleCommander::sendSignal(CMD_ACK);
				firstLoop++;
			}
		}
	}
}

void ModulePositionController::oneStep(){
	msgBus.getModeFlag(&modeFlagSub);
	msgBus.getLocalPosition(&localPositionSub);
	msgBus.getAirframeStatus(&airframeStatusSub);
	msgBus.getController(&controllerSub);
	msgBus.getAirSpeed(&airSpeedSub);
	msgBus.getBodyAccel(&bodyAccelSub);
	msgBus.getAttitude(&vehicleAttitude);

//	if(modeFlagSub.flightMode == FlightMode::PositionControl || modeFlagSub.flightMode == FlightMode::AltitudeControl){
//		mcSetFromRC();
//	}
//	else{
//		setFromAutoController();
//		printf_("auto target : %f\t%f\t%f\t%f\r\n", targetX, targetY, targetZ, targetYaw);
//
//	}

	switch(airframeStatusSub.airframeMode){
	case AirframeMode::Multicopter:
		mcOneStep();
		break;
	case AirframeMode::FixedWing:
		fwOneStep();
		break;
	}


	freqCount();
}


float coordinatedTurnCompensation(float targetRoll, float targetPitch, float airspeed)
{
//   float dt = 0.01;

   float limitRoll, targetYawRate;
   bool inverted = false;

   if(abs(targetRoll) < FC_PI / 2)
	  limitRoll = constraints(targetRoll, deg2rad(-80.f), deg2rad(80.f));

   else{
	  inverted = true;

	  if(targetRoll > 0.f)
		 limitRoll = constraints(targetRoll, deg2rad(100.f), deg2rad(180.f));

	  else
		 limitRoll = constraints(targetRoll, deg2rad(-180.f), deg2rad(-100.f));
   }
   if(targetRoll < 0.f)
	  targetRoll = -targetRoll;
   limitRoll = constraints(limitRoll, -targetRoll, targetRoll);

   if(airspeed<10.0){
	   airspeed=10.0;
   }

   if(!inverted)
	  targetYawRate = tan(limitRoll) * cos(targetPitch) * FC_GRAVITY_ACCEERATION / airspeed;

   return targetYawRate;
}


void ModulePositionController::fwSetFromRC(){
	static bool throtleStickSet = false;
	static bool yawStickSet = false;
	static bool rollStickSet = false;
	static bool pitchStickSet = false;
	static bool l1TargetSet = false;

	/* throttle stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.throttle && controllerSub.throttle < 1500 + STICK_THRESHOLD){
		// set airspeed
		if (!throtleStickSet){
			fwtargetAirspeed = airSpeedSub.TAS;
			throtleStickSet = true;
		}
	}
	else{
		fwtargetAirspeed = airSpeedSub.TAS +map(controllerSub.throttle,1000,2000,-VEL_INCREMENT, VEL_INCREMENT);
		if(fwtargetAirspeed <0.0) fwtargetAirspeed=0.0; //set minimum
		throtleStickSet = false;
	}

	/* pitch stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.pitch && controllerSub.pitch < 1500 + STICK_THRESHOLD){
		// set altitude
		if (!pitchStickSet){
			fwtargetAlt = - localPositionSub.z;
			pitchStickSet = true;
		}
	}
	else{
		fwtargetAlt = - localPositionSub.z - map(controllerSub.pitch,1000,2000,-MAX_CLIMB_ALT, MAX_CLIMB_ALT);
		pitchStickSet = false;
	}

	/* roll stick */ //roll manual override
//	if(1500 - STICK_THRESHOLD < controllerSub.roll && controllerSub.roll < 1500 + STICK_THRESHOLD){
//		if(!rollStickSet){
//			targetRoll = 0;
//			rollStickSet = true;
//		}
//	}
//	else{
//		targetRoll = map(controllerSub.roll, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* roll */
//		rollStickSet = false;
//	}
	fwtargetRoll = map(controllerSub.roll, 1000, 2000, -MAX_BANK_ANGLE_RAD, MAX_BANK_ANGLE_RAD);		/* roll */


	/* yaw stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.yaw && controllerSub.yaw < 1500 + STICK_THRESHOLD){
		fwtargetYawRate=coordinatedTurnCompensation(fwtargetRoll, vehicleAttitude.pitch, airSpeedSub.TAS); //Coordinate turn yaw command
		if(!yawStickSet){
			targetYaw = localPositionSub.yaw;
			yawStickSet = true;
		}
	}
	else{
		targetYaw = localPositionSub.yaw + map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);
		targetYaw = radianThreshold(targetYaw, -FC_PI, FC_PI);
		fwtargetYawRate = map(controllerSub.yaw, 1000, 2000, -1.0, 1.0);       // FW stabilize manual yaw input
		yawStickSet = false;
	}
}



void ModulePositionController::mcSetFromRC(){
	static bool throtleStickSet = false;
	static bool yawStickSet = false;
	static bool rollStickSet = false;
	static bool pitchStickSet = false;
	float roll;
	float pitch;

	/* throtle stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.throttle && controllerSub.throttle < 1500 + STICK_THRESHOLD){
		// set altitude
		if(!throtleStickSet){
			targetZ = localPositionSub.z;
			throtleStickSet = true;
		}
	}
	else{
		targetZ = localPositionSub.z - map(controllerSub.throttle, 1000, 2000, -MAX_VELTICAL, MAX_VELTICAL);
		throtleStickSet = false;
	}

	/* yaw stick */
	if( 1500 - STICK_THRESHOLD < controllerSub.yaw && controllerSub.yaw < 1500 + STICK_THRESHOLD){
		// set altitude
		if(!yawStickSet){
			targetYaw = localPositionSub.yaw;
			yawStickSet = true;
		}
	}
	else{
		targetYaw = localPositionSub.yaw + map(controllerSub.yaw, 1000, 2000, -MAX_YAW, MAX_YAW);
		targetYaw = radianThreshold(targetYaw, -FC_PI, FC_PI);
		yawStickSet = false;
	}

	/* roll stick */
	if(1500 - STICK_THRESHOLD < controllerSub.roll && controllerSub.roll < 1500 + STICK_THRESHOLD){
		if(!rollStickSet){
			roll = 0;
			rollStickSet = true;
		}
	}
	else{
		roll = map(controllerSub.roll, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* roll */
		rollStickSet = false;
	}

	/* pitch stick */
	if(1500 - STICK_THRESHOLD < controllerSub.pitch && controllerSub.pitch < 1500 + STICK_THRESHOLD){
		if(!pitchStickSet){
			pitch = 0;
			pitchStickSet = true;
		}
	}
	else{
		pitch = map(controllerSub.pitch, 1000, 2000, -MAX_HORISION, MAX_HORISION);		/* pitch */
		pitchStickSet = false;
	}

	if( !rollStickSet || !pitchStickSet){
		float cosYaw = cos(localPositionSub.yaw);
		float sinYaw = sin(localPositionSub.yaw);
		targetX = localPositionSub.x + pitch*cosYaw + -roll*sinYaw;
		targetY = localPositionSub.y + pitch*sinYaw + roll*cosYaw;
	}
}

void ModulePositionController::setFromAutoController(){
	//TODO add struct VehiclePositionSP, convert to target
	msgBus.getVehiclePositionSP(&vehiclePositionSpSub);
	targetX = vehiclePositionSpSub.x;
	targetY = vehiclePositionSpSub.y;
	targetYaw = vehiclePositionSpSub.yaw;
	targetZ = vehiclePositionSpSub.z;
}

void ModulePositionController::fwSetFromAuto(){
	msgBus.getVehiclePositionSP(&vehiclePositionSpSub);
	fwTargetX = vehiclePositionSpSub.x;
	fwTargetY = vehiclePositionSpSub.y;
	fwTargetZ = vehiclePositionSpSub.z;
}

void ModulePositionController::mcOneStep(){
	msgBus.getModeFlag(&modeFlagSub);

	if(modeFlagSub.flightMode == FlightMode::PositionControl || modeFlagSub.flightMode == FlightMode::AltitudeControl){
		mcSetFromRC();
	}
	else{
		setFromAutoController();
//		printf_("auto target : %f %f %f %f\r\n", targetX, targetY, targetZ, targetYaw);
	}

	positionControlModelClass::ExtU_positionControl_T input;

	input.set_x = targetX;
	input.set_y = targetY;
	input.set_z = targetZ;
	input.set_yaw = targetYaw;;

	input.estim_dx = localPositionSub.vx;
	input.estim_dy = localPositionSub.vy;
	input.estim_dz = localPositionSub.vz;
	input.estim_x = localPositionSub.x;
	input.estim_y = localPositionSub.y;
	input.estim_z = localPositionSub.z;
	input.estim_yaw = localPositionSub.yaw;

	positionControlModelClass::setExternalInputs(&input);
	positionControlModelClass::step();
	positionControlModelClass::ExtY_positionControl_T output = positionControlModelClass::getExternalOutputs();

	vehicleAttitudeSpPub.timestamp = microsecond();
	vehicleAttitudeSpPub.throttle = output.des_Thrust;

	/* position control mode */
	vehicleAttitudeSpPub.pitch = output.des_pitch;
	vehicleAttitudeSpPub.roll = output.des_roll;
	vehicleAttitudeSpPub.yawRate = output.des_yaw_rate;
	/* alt hold mode */
	if(modeFlagSub.flightMode == FlightMode::AltitudeControl){
		vehicleAttitudeSpPub.pitch = -map(controllerSub.pitch, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.roll = map(controllerSub.roll, 1000, 2000, -1.0, 1.0);
		vehicleAttitudeSpPub.yawRate = map(controllerSub.yaw, 1000, 2000, -1.0, 1.0);
	}

	msgBus.setVehicleAttitueSP(vehicleAttitudeSpPub);
//	printf_("%f %f %f %f\r\n", vehicleAttitudeSpPub.roll, vehicleAttitudeSpPub.pitch, vehicleAttitudeSpPub.yawRate, vehicleAttitudeSpPub.throttle);
}


void ModulePositionController::L1guidance(float previousWaypointX, float previousWaypointY, float previousWaypointZ,
									 	  float curWaypointX, float curWaypointY, float curWaypointZ,
										  float vehicleX, float vehicleY, float vehicleZ,
										  float vehicleVelX, float vehicleVelY, float vehicleVelZ,
										  float *targetRoll){
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
	float l1Mag = 15.0f;
	/* test */
	float velMag = 10.0f;
	matrix::Vector3f velocity(velMag*cos(localPositionSub.yaw), velMag*sin(localPositionSub.yaw), 0);
//	printf_("%f %f\r\n", velocity(0), velocity(1));
	/* vectors */
	matrix::Vector3f curWP(curWaypointX, curWaypointY, curWaypointZ);
	matrix::Vector3f prevWP(previousWaypointX, previousWaypointY, previousWaypointZ);
	matrix::Vector3f curPos(vehicleX, vehicleY, vehicleZ);
//	matrix::Vector3f distance(curWaypointX - vehicleX, curWaypointY - vehicleY, curWaypointZ - vehicleZ);
//	matrix::Vector3f velocity(vehicleVelX, vehicleVelY, vehicleVelZ);


	/* unit vectors */
	matrix::Vector3f T = (curWP - prevWP).normalized();
	matrix::Vector3f N(-T(1), T(0), 0.0f);
	N.normalize();

	float errMag = N.dot(curPos - prevWP);
//	printf_("error %f\r\n", errMag);
	if(errMag > l1Mag) errMag = l1Mag;
	float D_dt = sqrt(l1Mag*l1Mag - errMag*errMag);

	matrix::Vector3f L1 = D_dt*T - errMag*N;

	matrix::Vector3f crossCal = velocity.cross(L1)/velocity.norm()/L1.norm();

	float sinGamma = crossCal.norm();
	if(crossCal(2) > 0) sinGamma *= -1;

	float a_cmd = 2*pow(velocity.norm(),2)/L1.norm()*sinGamma;
//	printf_("a cmd : %f\r\n", a_cmd);
	*targetRoll = atan(a_cmd/FC_GRAVITY_ACCEERATION);
}



void ModulePositionController::fwOneStep(){
	static bool autoFirstRun = true;

	msgBus.getAirSpeed(&airSpeedSub);
	msgBus.getLocalPosition(&localPositionSub);

	if(modeFlagSub.flightMode == FlightMode::PositionControl || modeFlagSub.flightMode == FlightMode::AltitudeControl){
			fwSetFromRC();
			autoFirstRun = true;
		}
		/* auto control */
	else{
		msgBus.getVehiclePositionSP(&vehiclePositionSpSub);

		/* first run : current position -> wp1 */
		if(autoFirstRun){
			fwPrevX = localPositionSub.x;
			fwPrevY = localPositionSub.y;
			fwPrevZ = localPositionSub.z;

			fwTargetX = vehiclePositionSpSub.x;
			fwTargetY = vehiclePositionSpSub.y;
			fwTargetZ = vehiclePositionSpSub.z;
		}
		/* waypoint changed */
		if(fwTargetX != vehiclePositionSpSub.x && fwTargetY != vehiclePositionSpSub.y && fwTargetZ != vehiclePositionSpSub.z){
			fwPrevX = fwTargetX;
			fwPrevY = fwTargetY;
			fwPrevZ = fwTargetZ;

			fwTargetX = vehiclePositionSpSub.x;
			fwTargetY = vehiclePositionSpSub.y;
			fwTargetZ = vehiclePositionSpSub.z;
		}

		L1guidance(fwPrevX, fwPrevY, fwPrevZ,
					   fwTargetX, fwTargetY, fwTargetZ,
					   localPositionSub.x, localPositionSub.y, localPositionSub.z,
					   localPositionSub.vx, localPositionSub.vy, localPositionSub.vz,
					   &fwtargetRoll);
		fwtargetYawRate=coordinatedTurnCompensation(fwtargetRoll, vehicleAttitude.pitch, airSpeedSub.TAS); //Coordinate turn yaw command
		fwtargetAirspeed = 13.0f;
		fwtargetAlt = -fwTargetZ;
		printf_("R: %f Y: %f tAlt: %f \n\r",fwtargetRoll,fwtargetYawRate,fwtargetAlt);
		}


	ExtU_TECS_T fwInput;
    fwInput.set_ALT = fwtargetAlt;
    fwInput.set_Airspeed = fwtargetAirspeed;
    fwInput.Airspeed = airSpeedSub.TAS;
    fwInput.ALT = -localPositionSub.z;
    fwInput.ax = bodyAccelSub.xyz[0];
    fwInput.vz = -localPositionSub.vz;
//    printf_("setALT: %f ALT: %f setARSP: %f ARSP: %f ax: %f vz: %f \r\n",fwInput.set_ALT,
//    																	fwInput.ALT,
//																		fwInput.set_Airspeed,
//																		fwInput.Airspeed,
//																		fwInput.ax,
//																		fwInput.vz );
    fw_TECSModelClass::setExternalInputs(&fwInput);

	fw_TECSModelClass::step();

	ExtY_TECS_T output = fw_TECSModelClass::getExternalOutputs();
	vehicleAttitudeSpPub.timestamp = microsecond();
	vehicleAttitudeSpPub.pitch = output.pitch;
	vehicleAttitudeSpPub.throttle = output.throttle;
	vehicleAttitudeSpPub.roll = fwtargetRoll;
	vehicleAttitudeSpPub.yawRate = fwtargetYawRate;//targetYaw;

	msgBus.setVehicleAttitueSP(vehicleAttitudeSpPub);
}

} /* namespace FC */
