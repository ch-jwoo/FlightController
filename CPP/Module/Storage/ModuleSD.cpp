/*
 * ModuleSD.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include "ModuleSD.h"
#include "MsgBus/Params.h"
#include "MsgBus/Waypoint.h"
#include "printf.h"
#include <cstdlib>
#include "Module/Etc/ModuleBuzzer.h"

namespace FC {

enum WaypointParse{
	ParseWaypointLength,
	ParseWaypointIndex,
	ParseWaypointCommand,
	ParseWaypointParam,
	ParseWaypointLattitude,
	ParseWaypointLongitude,
	ParseWaypointAltitude,
};

enum ParameterParse{
	ParseParameterIndex,
	ParseParameterID,
	ParseParameterValue
};

ModuleSD::ModuleSD(LED* led)
: led(led)
{}

void ModuleSD::main(){
   /* 1. Mount - 0 */
//   res=f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);

   ModuleSD moduleSD(&led3);

	moduleSD.mount();
//   osDelay(1000);

   moduleSD._loadParm();
   moduleSD._loadWP();

   while(1){
	   if(osThreadFlagsGet() & SD_saveParam){
		   osThreadFlagsClear(SD_saveParam);
		   moduleSD._saveParam();
	   }
	   else if(osThreadFlagsGet() & SD_saveWP){
		   osThreadFlagsClear(SD_saveWP);
		   moduleSD._saveWP();
	   }
	   else{
//		   moduleSD._saveLog();
		   moduleSD._saveTest();
	   }

      osDelay(5);         /* 10hz */
   }
}

void ModuleSD::_saveParam(){
	if(_openFile("0:/params.txt", FA_CREATE_ALWAYS | FA_WRITE)){
		for(int i=0; i< ParameterEnd; i++){
			writeLen = sprintf_((char*)writeBuf, "%u %s %f\r\n", i, getParamID(i), getParamValue(i));
			_write(writeBuf, writeLen);
		}
		_closeFile();
		ModuleBuzzer::sendCommand(BuzzerCommand::Success);
		return;
	}
	ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
	return;
}

void ModuleSD::_saveWP(){
	WaypointLLA waypointLLA;
	if(_openFile("0:/waypoint.txt", FA_CREATE_ALWAYS | FA_WRITE)){
		writeLen = sprintf_((char*)writeBuf, "%u\r\n", getWaypointLength());
		_write(writeBuf, writeLen);
		for(uint8_t i=0; i<getWaypointLength(); i++){
			waypointLLA = getWaypointLLA(i);
			writeLen = sprintf_((char*)writeBuf, "%u %u %u %d %d %f\r\n",
												i, (unsigned int)waypointLLA.command, waypointLLA.param,
												(int32_t)(waypointLLA.lat*10000000), (int32_t)(waypointLLA.lon*10000000), waypointLLA.alt);
			_write(writeBuf, writeLen);
		}
		_closeFile();
		ModuleBuzzer::sendCommand(BuzzerCommand::Success);
		return;
	}
	ModuleBuzzer::sendCommand(BuzzerCommand::Denied);
	return;
}

void ModuleSD::_saveLog(){

}

void ModuleSD::_loadParm(){
	char readBuf[20];
	uint8_t index = 0;
	uint8_t paramIndex = 0;
	uint8_t parseStep = ParseWaypointLength;
//	res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
	if(_openFile("0:/params.txt", FA_READ)){
		while(!f_eof(&SDFile)){
			readBuf[index++] = _readByte();
			if(readBuf[index-1] == ' ' || readBuf[index-1] == '\n') {
				readBuf[index-1] = '\0';
				index = 0;
				switch(parseStep){
				case ParseParameterIndex:
					paramIndex = std::atoi(readBuf);
					parseStep = ParseParameterID;
//					printf_("%u ", paramIndex);
					break;
				case ParseParameterID:
					/* nothing */
					parseStep = ParseParameterValue;
//					printf_("%s ", readBuf);
					break;
				case ParseParameterValue:
					setParamValue(paramIndex, (float)std::atof(readBuf));
					parseStep = ParseParameterIndex;
//					printf_("%f\r\n", getParamValue(paramIndex));
					break;
				default:
					break;
				}
			}
		}
		_closeFile();
	}
}

void ModuleSD::_loadWP(){
	VehicleWpLLA vehicleWpLLA = {0,};
	char readBuf[20];
	uint8_t index = 0;
	uint8_t waypointIndex = 0;
	uint8_t parseStep = ParseWaypointLength;
//	res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
	if(_openFile("0:/waypoint.txt", FA_READ)){
		while(!f_eof(&SDFile)){
			readBuf[index++] = _readByte();
			if(readBuf[index-1] == ' ' || readBuf[index-1] == '\n') {
				readBuf[index-1] = '\0';
				index = 0;
				switch(parseStep){
				case ParseWaypointLength:
					vehicleWpLLA.len = (uint8_t)std::atoi(readBuf);
					parseStep = ParseWaypointIndex;
//					printf_("%u\r\n", vehicleWpLLA.len);
					break;
				case ParseWaypointIndex:
					waypointIndex = std::atoi(readBuf);
					parseStep = ParseWaypointCommand;
//					printf_("%u ", waypointIndex);
					break;
				case ParseWaypointCommand:
					vehicleWpLLA.wp[waypointIndex].command = (AutoCommand)std::atoi(readBuf);
					parseStep = ParseWaypointParam;
//					printf_("%u ", (unsigned int)vehicleWpLLA.wp[waypointIndex].command);
					break;
				case ParseWaypointParam:
					vehicleWpLLA.wp[waypointIndex].param = (uint16_t)std::atoi(readBuf);
					parseStep = ParseWaypointLattitude;
//					printf_("%u ", vehicleWpLLA.wp[waypointIndex].param);
					break;
				case ParseWaypointLattitude:
					vehicleWpLLA.wp[waypointIndex].lat = (float)std::atoi(readBuf) / 10000000.0;
					parseStep = ParseWaypointLongitude;
//					printf_("%f ", vehicleWpLLA.wp[waypointIndex].lat);
					break;
				case ParseWaypointLongitude:
					vehicleWpLLA.wp[waypointIndex].lon = (float)std::atoi(readBuf) / 10000000.0;
					parseStep = ParseWaypointAltitude;
//					printf_("%f ", vehicleWpLLA.wp[waypointIndex].lon);
					break;
				case ParseWaypointAltitude:
					vehicleWpLLA.wp[waypointIndex].alt = (float)std::atoi(readBuf);
					parseStep = ParseWaypointIndex;
//					printf_("%f\r\n", vehicleWpLLA.wp[waypointIndex].alt);
					break;
				default:
					break;
				}
			}
		}
		setVehicleWpLLA(vehicleWpLLA);
		_closeFile();
	}
}

void ModuleSD::_saveTest(){
	static struct Attitude attitude;
	static struct NedAccel nedAccel;
	static struct GPS gps;
	static struct Barometer baro;
	static struct BodyAngularVelocity gyro;

	/* sdopen */
	if(_openFile("0:/log.txt", FA_OPEN_APPEND | FA_WRITE)){
		if(msgBus.getAttitude(&attitude)){
			writeLen = sprintf_((char*)writeBuf, "att %u %f %f %f\n", (unsigned int)attitude.timestamp, (attitude.roll),
										  (attitude.pitch),
										  (attitude.yaw));
			_write((void const*)writeBuf, writeLen);
		}

		if(msgBus.getNedAccel(&nedAccel)){
			writeLen=sprintf_((char*)writeBuf,"accNED %u %f %f %f\n",(unsigned int)nedAccel.timestamp,(nedAccel.xyz[0]),
													  (nedAccel.xyz[1]),
													  (nedAccel.xyz[2]));
			_write((void const*)writeBuf, writeLen);
		 }

		 if(msgBus.getBodyAngularVelocity(&gyro)){
			writeLen = sprintf_((char*)writeBuf,"gyro %u %f\n",(unsigned int)gyro.timestamp, (gyro.xyz[2]));
			_write(writeBuf, writeLen);
		 }

		 if(msgBus.getGPS(&gps)){
//			int32_t latDecimal = (int32_t)gps.lat;
//			int32_t latFraction = (int32_t)((gps.lat-latDecimal)*100000000);
//			int32_t lonDecimal = (int32_t)gps.lon;
//			int32_t lonFraction = (int32_t)((gps.lon-lonDecimal)*100000000);
			writeLen=sprintf_((char*)writeBuf, "GPS %u %f %f %f %f %f %f\n", gps.timestamp,
												  gps.lat,
												  gps.lon,
												  (gps.alt),
												  (gps.velN),
												  (gps.velE),
												  (gps.velD));
			_write(writeBuf, writeLen);
		 }   // Lat Lon Alt velN velE velD

		 if(msgBus.getBarometer(&baro)){
			writeLen=sprintf_((char*)writeBuf,"Baro %u %f\n",(unsigned int)baro.timestamp,(baro.pressure));
			_write(writeBuf, writeLen);
		 }
		_closeFile();
	}
}

bool ModuleSD::_openFile(const char* file, BYTE mode){
	  res=f_open(&SDFile, file, mode);
	  if(res != FR_OK){
		 /* fail to open file */
		  led->reset();
		  return false;
	  }
	  else{
		  led->set();
		  return true;
	  }
}

bool ModuleSD::_closeFile(){
	  res=f_close(&SDFile);
	  if(res != FR_OK){
		 /* fail to open file */
		  led->reset();
		  return false;
	  }
	  else{
		  led->set();
		  return true;
	  }
}

uint32_t ModuleSD::_write(const void* writeBuf, uint32_t writeLen){
	res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
	if((bytesWritten == 0) || (res != FR_OK)){
		/* fail to write file */
	  led->reset();
	  return 0;
	}
	else{
	   led->set();
	   return bytesWritten;
	}
}

char ModuleSD::_readByte(){
	char res;
	UINT byteRead;
	f_read(&SDFile, &res, 1, &byteRead);
	return res;
}

} /* namespace FC */
