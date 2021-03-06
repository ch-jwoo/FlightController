/*
* ModuleGCS.cpp
*
*  Created on: 2020. 8. 18.
*      Author: choi jun woo is pig
*/

#include "MsgBus/MsgType.h"
#include "MsgBus/MsgBus.h"
#include <Module/Manager/ModuleGCS.h>
#include "Utils/Constants.h"
#include "Utils/Functions.h"
#include "Usec.h"
#include "usart.h"
#include "main.h"
#include "cstring"
#include "Usec.h"
#include "MsgBus/Params.h"
#include "MsgBus/Waypoint.h"

#include "printf.h"

namespace FC {

ModuleGCS::ModuleGCS(Telemetry *ptelem)
: ptelem(ptelem)
{
}

void ModuleGCS::main(){
	ModuleGCS moduleGCS(&telem);

	osThreadAttr_t taskAtt = {0};
	taskAtt.priority = osPriorityAboveNormal2;
	taskAtt.stack_size = 512 * 4;

	if(osThreadNew(ModuleGCS_PeriodicSendTask, (void*)&moduleGCS, &taskAtt) == NULL){
//		printf_("thread fail\r\n");
	}

	/* while */
	moduleGCS.communicateGCS();
//	while(1){
//		osDelay(1000);
//	}
}

void ModuleGCS::periodicSendTask(void *instance){
	uint32_t tick;
	uint32_t heartbeatTick;
	ModuleGCS *moduleGCS = (ModuleGCS*)instance;
	uint8_t txBuffer[MAVLINK_MAX_PACKET_LEN];
	mavlink_message_t sendMsg;

	heartbeatTick = millisecond();
	tick = osKernelGetTickCount();
	while(1){
		tick += 100;
		osDelayUntil(tick);		/* 10hz */

		if(millisecond() - heartbeatTick > 1000){
			moduleGCS->sendHeartbeat(txBuffer, &sendMsg);
			moduleGCS->sendGpsStatus(txBuffer, &sendMsg);
			moduleGCS->sendSysStatus(txBuffer, &sendMsg);

			heartbeatTick = millisecond();
		}
		moduleGCS->sendAttitude(txBuffer, &sendMsg);
		moduleGCS->sendGlobalPosition(txBuffer, &sendMsg);
	}
}

void ModuleGCS::sendHeartbeat(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	uint16_t len;

	mavlink_msg_heartbeat_pack(sysId, compId, sendMsg, MAV_TYPE_HEXAROTOR, MAV_AUTOPILOT_PX4,
			MAV_MODE_FLAG_TEST_ENABLED, MAV_STATE_STANDBY, 3);

	len = mavlink_msg_to_send_buffer(txBuffer, sendMsg);
	ptelem->send(txBuffer, len);
}

void ModuleGCS::sendGpsStatus(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	uint16_t len;
	GPS gpsSub = {0};

	/* not used */
	uint8_t satellite_prn[20] = {0};
	uint8_t satellite_used[20] = {0};
	uint8_t satellite_elevation[20] = {0};
	uint8_t satellite_azimuth[20] = {0};
	uint8_t satellite_snr[20] = {0};

	if(msgBus.getGPS(&gpsSub)){
		mavlink_msg_gps_status_pack(sysId, compId, sendMsg,
				gpsSub.visibleSatellites, satellite_prn, satellite_used, satellite_elevation, satellite_azimuth, satellite_snr);

		len = mavlink_msg_to_send_buffer(txBuffer, sendMsg);
		ptelem->send(txBuffer, len);
	}
}

void ModuleGCS::sendSysStatus(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	uint16_t len;
	StatusFlag flag = {0};
	uint32_t onboard_control_sensors_present = MAV_SYS_STATUS_SENSOR_3D_GYRO
											 | MAV_SYS_STATUS_SENSOR_3D_ACCEL
											 | MAV_SYS_STATUS_SENSOR_3D_MAG
											 | MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE
											 | MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE
											 | MAV_SYS_STATUS_SENSOR_GPS
											 | MAV_SYS_STATUS_SENSOR_LASER_POSITION
											 | MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION
											 | MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL
											 | MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL
											 | MAV_SYS_STATUS_SENSOR_RC_RECEIVER;
	uint32_t onboard_control_sensors_enabled = onboard_control_sensors_present;
	uint32_t onboard_control_sensors_health = 0;

	/* not used */
	uint16_t load = 0;
	uint16_t voltage_battery = 0;
	uint16_t current_battery = 0;
	int8_t battery_remaining = 0;
	uint16_t drop_rate_comm = 0;
	uint16_t errors_comm = 0;
	uint16_t errors_count1 = 0;
	uint16_t errors_count2 = 0;
	uint16_t errors_count3 = 0;
	uint16_t errors_count4 = 0;

	msgBus.getStatusFlag(&flag);
	if(flag.gyro) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_3D_GYRO;
	if(flag.accel) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_3D_ACCEL;
	if(flag.mag) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_3D_MAG;
	if(flag.barometer) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE;
	if(flag.airspeed) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE;
	if(flag.gps) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_GPS;
	if(flag.lidar) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_LASER_POSITION;
	if(flag.attitudeCTL) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION;
	if(flag.altitudeCTL) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL;
	if(flag.positionCTL) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL;
	if(flag.receiver) onboard_control_sensors_health |= MAV_SYS_STATUS_SENSOR_RC_RECEIVER;

//	onboard_control_sensors_health = onboard_control_sensors_enabled;

	mavlink_msg_sys_status_pack(sysId, compId, sendMsg, onboard_control_sensors_present, onboard_control_sensors_enabled, onboard_control_sensors_health
			, load, voltage_battery, current_battery, battery_remaining, drop_rate_comm, errors_comm, errors_count1, errors_count2, errors_count3, errors_count4);
	len = mavlink_msg_to_send_buffer(txBuffer, sendMsg);
	ptelem->send(txBuffer, len);
}

void ModuleGCS::sendAttitude(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	struct BodyAngularVelocity bodyAngleVelocitySub = {0,};
	struct Attitude attitudeSub = {0,};
	uint16_t len;

	msgBus.getBodyAngularVelocity(&bodyAngleVelocitySub);
	msgBus.getAttitude(&attitudeSub);

	mavlink_msg_attitude_pack(sysId, compId, sendMsg, millisecond(),
							  attitudeSub.roll, attitudeSub.pitch, attitudeSub.yaw,
							  bodyAngleVelocitySub.xyz[0], bodyAngleVelocitySub.xyz[1], bodyAngleVelocitySub.xyz[2]);

	len = mavlink_msg_to_send_buffer(txBuffer, sendMsg);

	ptelem->send(txBuffer, len);
}

void ModuleGCS::sendGlobalPosition(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	static struct GlobalPosition globalPositionSub = {0,};
	static struct LocalPosition localPositionSub = {0,};
	uint16_t len;
	float degYaw;

	msgBus.getGlobalPosition(&globalPositionSub);
	msgBus.getLocalPosition(&localPositionSub);

	degYaw = radianThreshold(localPositionSub.yaw, 0, FC_2PI);
	degYaw = rad2deg(degYaw);

	mavlink_msg_global_position_int_pack(sysId, compId, sendMsg, millisecond(),
										 (uint32_t)(globalPositionSub.lat * 10000000), (uint32_t)(globalPositionSub.lon * 10000000), (uint32_t)(globalPositionSub.alt * 1000),
										 (uint32_t)(localPositionSub.refAlt * 1000),
										 (uint16_t)(localPositionSub.vx * 100), (uint16_t)(localPositionSub.vy * 100), (uint16_t)(localPositionSub.vz * 100), (uint16_t)(degYaw * 100));


	len = mavlink_msg_to_send_buffer(txBuffer, sendMsg);
	ptelem->send(txBuffer, len);
}

void ModuleGCS::communicateGCS(){
	uint16_t len;
	while(1){
		len = telem.receive(rxBuffer, sizeof(rxBuffer));
		for(int i=0; i<len; i++){
			if(mavlink_parse_char(MAVLINK_COMM_0, rxBuffer[i], &receiveMsg, &status)){
				handleRcvMSG(receiveMsg);
			}
		}
	}
}

void ModuleGCS::handleRcvMSG(const mavlink_message_t &mavMsg){
	switch(mavMsg.msgid){
	case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
		handle_param_request_list();
		break;
	case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
		handle_param_request_read();
		break;
	case MAVLINK_MSG_ID_PARAM_SET:
		handle_param_set();
		break;
	case MAVLINK_MSG_ID_SET_MODE:
		//TODO: GETTING FLAG AUTOMISSIONW
		break;
	case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
		handle_mission_request_list();
		break;
	case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
		handle_mission_request_int();
		break;
	case MAVLINK_MSG_ID_MISSION_REQUEST:
		handle_mission_request();
		break;
	case MAVLINK_MSG_ID_MISSION_COUNT:
		handle_mission_count();
		break;
	case MAVLINK_MSG_ID_MISSION_ITEM_INT:
		handle_mission_item_int();
		break;
	case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
		handle_mission_clear_all();
		break;
	case MAVLINK_MSG_ID_COMMAND_LONG:
		handle_command_long();
		break;
	default:
		break;
	}
}
void ModuleGCS::handle_mission_request_list(){
	mavlink_mission_request_list_t packet;
	mavlink_msg_mission_request_list_decode(&receiveMsg, &packet);

	if(packet.target_system != sysId) return;

	mavlink_msg_mission_count_pack(sysId, compId, &sendMsg, target_system, target_component, getWaypointLength(), MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);

	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_mission_request_int(){
	mavlink_mission_request_int_t packet;
	mavlink_msg_mission_request_int_decode(&receiveMsg, &packet);

	if(packet.target_system != sysId) return;

	waypointFC2Mav(sysId, compId, &sendMsg, target_system, target_component, packet.seq);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);

	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_mission_request(){
	mavlink_mission_request_t packet;
	mavlink_msg_mission_request_decode(&receiveMsg, &packet);

	if(packet.target_system != sysId) return;

	waypointFC2Mav(sysId, compId, &sendMsg, target_system, target_component, packet.seq);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);

	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_mission_count(){
	mavlink_mission_count_t packet;
	mavlink_msg_mission_count_decode(&receiveMsg, &packet);

	/* prevent overflow */
	if(packet.count > WAYPOINT_MAX_NUMBER) return;

	mission_count = packet.count;
	mission_seq = 0;

	mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);

	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_mission_item_int(){
	static VehicleWpLLA vehicleWpLLA = {0,};

	mavlink_mission_item_int_t packet;
	mavlink_msg_mission_item_int_decode(&receiveMsg, &packet);

	/* prevent overflow */
	if(packet.seq >= mission_count) return;

	/* not correct waypoint */
	if(mission_seq != packet.seq) return;

	/* first waypoint -> reset struct */
	if(packet.seq == 0) {
		std::memset((void*)&vehicleWpLLA, 0, sizeof(vehicleWpLLA));
		vehicleWpLLA.len = mission_count;
	}

	/* not used packet */
	if(!waypointMav2FC(packet, &vehicleWpLLA.wp[packet.seq])) return;

	/* save waypoints */
	printf_("%u %u %u %f\r\n", packet.seq, mission_seq,  packet.command, packet.param1);

	mission_seq++;
	if(mission_seq != mission_count){
		mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
		uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		ptelem->send(txBuffer, len);
	}
	else{
		mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
		uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		ptelem->send(txBuffer, len);
		setVehicleWpLLA(vehicleWpLLA);
//		mission_seq = 0;
//		mission_count = 0;
	}

}
void ModuleGCS::handle_mission_clear_all(){
	mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_command_long(){
	mavlink_command_long_t packet;
	mavlink_msg_command_long_decode(&receiveMsg, &packet);
	mavlink_msg_command_ack_pack(sysId, compId, &sendMsg, packet.command, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, target_system, target_component);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
	ptelem->send(txBuffer, len);
}

void ModuleGCS::handle_param_request_list(){
   for(int i = 0; i< getParamLength(); i++){
		mavlink_msg_param_value_pack(sysId, compId, &sendMsg, getParamID(i), getParamValue(i), MAV_PARAM_TYPE_REAL32, getParamLength(), i);
		uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		ptelem->send(txBuffer, len);
		osDelay(10);
   }
}
void ModuleGCS::handle_param_request_read(){
	static uint32_t lastReqMillis;
	if(lastReqMillis - millisecond() > 10000) return;			/* timeout 10 second */

	mavlink_param_request_read_t packet;
	mavlink_msg_param_request_read_decode(&receiveMsg, &packet);

	uint8_t i = 0;
	while(i < getParamLength()){
		if(strcmp(packet.param_id, getParamID(i))){
		   mavlink_msg_param_value_pack(sysId, compId, &sendMsg, getParamID(i), getParamValue(i), MAV_PARAM_TYPE_REAL32, getParamLength(), i);
		   uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		   ptelem->send(txBuffer, len);
		   i++;
		}
	}
	lastReqMillis = millisecond();
}

void ModuleGCS::handle_param_set(){
	mavlink_param_set_t packet;
	mavlink_msg_param_set_decode(&receiveMsg, &packet);

	uint16_t paramIndex = getParamIndexFromID(packet.param_id);

	setParamValue(paramIndex, packet.param_value);

	mavlink_msg_param_value_pack(sysId, compId, &sendMsg, getParamID(paramIndex), getParamValue(paramIndex), MAV_PARAM_TYPE_REAL32, getParamLength(), paramIndex);
    uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
    ptelem->send(txBuffer, len);
}

void ModuleGCS_PeriodicSendTask(void *param){
	ModuleGCS::periodicSendTask(param);
}

}/* namespace FC */

