/*
 * Waypoint.cpp
 *
 *  Created on: 2020. 9. 3.
 *      Author: cjb88
 */
#include "Waypoint.h"
#include "Utils/Functions.h"
#include "Module/Storage/ModuleSD.h"
#include <cstring>

#define MAV_CMD_NAV_WAYPOINT 			16		/* guidance */
#define MAV_CMD_NAV_RETURN_TO_LAUNCH 	20		/* RTL */
#define MAV_CMD_NAV_LAND 				21		/* Land */
#define MAV_CMD_NAV_TAKEOFF 			22		/* Takeoff */
#define MAV_CMD_NAV_DELAY 				93		/* hovering */
#define MAV_CMD_DO_VTOL_TRANSITION 		3000	/* transition */

namespace FC{

VehicleWpLLA _vehicleWpLLA = {0};

WaypointLLA getWaypointLLA(uint8_t index){
	return _vehicleWpLLA.wp[index];
}

uint8_t getWaypointLength(){
	return _vehicleWpLLA.len;
}

void setVehicleWpLLA(const VehicleWpLLA &vehicleWpLLA){
	std::memset((void*)&_vehicleWpLLA, 0, sizeof(_vehicleWpLLA));

	_vehicleWpLLA.len = vehicleWpLLA.len;
	for(int i=0; i < _vehicleWpLLA.len; i++){
		_vehicleWpLLA.wp[i] = vehicleWpLLA.wp[i];
	}
	ModuleSD::saveWP();
}

bool waypointMav2FC(const mavlink_mission_item_int_t &item, WaypointLLA* waypointLLA){
	switch(item.command){
	case MAV_CMD_NAV_WAYPOINT:
		if(item.frame != MAV_FRAME_GLOBAL_RELATIVE_ALT) return false;
//		PARAM5 / local: x position in meters * 1e4, global: latitude in degrees * 10^7
		waypointLLA->lat = (double)item.x / 10000000.0;

//		PARAM6 / y position: local: x position in meters * 1e4, global: longitude in degrees *10^7
		waypointLLA->lon = (double)item.y / 10000000.0;

//		PARAM7 / z position: global: altitude in meters (relative or absolute, depending on frame.
		waypointLLA->alt = item.z;

		waypointLLA->command = AutoCommand::Guidance;
		waypointLLA->param = 0;
		return true;
	case MAV_CMD_NAV_RETURN_TO_LAUNCH:
		waypointLLA->lat = 0;
		waypointLLA->lon = 0;
		waypointLLA->alt = 0;
		waypointLLA->command = AutoCommand::RTL;
		waypointLLA->param = 0;
		return true;
	case MAV_CMD_NAV_LAND:
		waypointLLA->lat = 0;
		waypointLLA->lon = 0;
		waypointLLA->alt = 0;
		waypointLLA->command = AutoCommand::Land;
		waypointLLA->param = 0;
		return true;
	case MAV_CMD_NAV_TAKEOFF:
		waypointLLA->lat = (double)item.x / 10000000.0;
		waypointLLA->lon = (double)item.y / 10000000.0;
		waypointLLA->alt = item.z;
		waypointLLA->command = AutoCommand::Takeoff;
		waypointLLA->param = 0;
		return true;
	case MAV_CMD_NAV_DELAY:
		waypointLLA->lat = 0;
		waypointLLA->lon = 0;
		waypointLLA->alt = 0;
		waypointLLA->command = AutoCommand::Hovering;
		waypointLLA->param = (uint16_t)item.param1;
		return true;
	case MAV_CMD_DO_VTOL_TRANSITION:
		waypointLLA->lat = 0;
		waypointLLA->lon = 0;
		waypointLLA->alt = 0;
		waypointLLA->command = AutoCommand::Transition;
		waypointLLA->param = 0;
		return true;
	default:
		return false;
	}
}

uint16_t waypointFC2Mav(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
		uint8_t target_system, uint8_t target_component, uint16_t seq){
	uint8_t frame = 0;
	uint16_t command = 0;
	uint8_t autocontinue = 1;
	float param1 = 0.0f;
	uint8_t mission_type = MAV_MISSION_TYPE_MISSION;
	uint32_t x = 0, y = 0;
	float z = 0.0f;
	uint8_t current = 0;

	WaypointLLA waypointLLA = getWaypointLLA(seq);

	switch(waypointLLA.command){
	case AutoCommand::Guidance:
		frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
		command = MAV_CMD_NAV_WAYPOINT;
		x = (uint32_t)(waypointLLA.lat * 10000000);
		y = (uint32_t)(waypointLLA.lon * 10000000);
		z = waypointLLA.alt;
		break;
	case AutoCommand::Hovering:
		frame = MAV_FRAME_MISSION;
		command = MAV_CMD_NAV_DELAY;
		param1 = (float)waypointLLA.param;
		break;
	case AutoCommand::Land:
		frame = MAV_FRAME_MISSION;
		command = MAV_CMD_NAV_LAND;
		break;
	case AutoCommand::RTL:
		frame = MAV_FRAME_MISSION;
		command = MAV_CMD_NAV_RETURN_TO_LAUNCH;
		break;
	case AutoCommand::Takeoff:
		frame = MAV_FRAME_MISSION;
		command = MAV_CMD_NAV_TAKEOFF;
		x = (uint32_t)(waypointLLA.lat * 10000000);
		y = (uint32_t)(waypointLLA.lon * 10000000);
		z = waypointLLA.alt;
		break;
	case AutoCommand::Transition:
		frame = MAV_FRAME_MISSION;
		command = MAV_CMD_DO_VTOL_TRANSITION;
		break;
	}

	return mavlink_msg_mission_item_int_pack(system_id, component_id, msg, target_system, target_component, seq, frame, command, current, autocontinue, param1, 0.0f, 0.0f, 0.0f, x, y, z, mission_type);
}

}
