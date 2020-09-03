/*
 * Waypoint.h
 *
 *  Created on: 2020. 9. 3.
 *      Author: cjb88
 */

#ifndef MSGBUS_WAYPOINT_H_
#define MSGBUS_WAYPOINT_H_
#include <cstdint>
#include "Mavlink/common/mavlink.h"

namespace FC{

static const uint8_t WAYPOINT_MAX_NUMBER = 32;

/* command for auto mode */
enum class AutoCommand {
	Guidance,      /* waypoint flight */
	RTL,            /* return to launch */

	Land,         /* auto land */
	Takeoff,         /* auto takeoff */
	Hovering,      /* hovering in place */
	Transition      /* tilting */
};

typedef struct {
	double lat;
	double lon;
	float alt;
	AutoCommand command;
	uint16_t param;
} WaypointLLA;

typedef struct{
	WaypointLLA wp[WAYPOINT_MAX_NUMBER];
	uint8_t len;
} VehicleWpLLA;


WaypointLLA getWaypointLLA(uint8_t index);

uint8_t getWaypointLength();

void setVehicleWpLLA(const VehicleWpLLA &vehicleWpLLA);

bool waypointMav2FC(const mavlink_mission_item_int_t &item, WaypointLLA* waypointLLA);

uint16_t waypointFC2Mav(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
		uint8_t target_system, uint8_t target_component, uint16_t seq);

}

#endif /* MSGBUS_WAYPOINT_H_ */
