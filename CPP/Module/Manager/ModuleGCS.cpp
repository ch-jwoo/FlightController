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
#include "Usec.h"
#include "usart.h"
#include "main.h"
#include "cstring"
#include "Usec.h"

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

	printf_("thread create\r\n");

	if(osThreadNew(ModuleGCS_PeriodicSendTask, (void*)&moduleGCS, &taskAtt) == NULL){
		printf_("thread fail\r\n");
	}

	/* make task */

	printf_("thread create complete\r\n");

	/* while */
	moduleGCS.communicateGCS();
//	while(1){
//		osDelay(1000);
//	}
}

void ModuleGCS::periodicSendTask(void *instance){
	uint32_t lastTick = 0;
	ModuleGCS *moduleGCS = (ModuleGCS*)instance;
	uint8_t txBuffer[MAVLINK_MAX_PACKET_LEN];
	mavlink_message_t sendMsg;

	while(1){
		if(millisecond() - lastTick > 1000){
			moduleGCS->sendHeartbeat(txBuffer, &sendMsg);
			lastTick = millisecond();
		}
		moduleGCS->sendAttitude(txBuffer, &sendMsg);
		moduleGCS->sendGlobalPositionNED(txBuffer, &sendMsg);
		osDelay(20);
	}
}

//void ModuleGCS::heartbeatTask(void *instance){
//	ModuleGCS *moduleGCS = (ModuleGCS*)instance;
//	while(1){
//		moduleGCS->sendHeartbeat();
////		printf_("hb\r\n");
//		osDelay(1000);
//	}
//}
//
//void ModuleGCS::attitudeTask(void *instance){
//	ModuleGCS *moduleGCS = (ModuleGCS*)instance;
//
//	while(1){
//		moduleGCS->sendAttitude();
//		osDelay(50);
//	}
//}
//
//void ModuleGCS::globalPositionNedTask(void *instance){
//	ModuleGCS *moduleGCS = (ModuleGCS*)instance;
//	while(1){
//		moduleGCS->sendGlobalPositionNED();
//		osDelay(50);
//	}
//}

void ModuleGCS::sendHeartbeat(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	uint16_t len;

	mavlink_msg_heartbeat_pack(sysId, compId, sendMsg, MAV_TYPE_HEXAROTOR, MAV_AUTOPILOT_PX4,
			MAV_MODE_FLAG_TEST_ENABLED, MAV_STATE_STANDBY, 3);

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

void ModuleGCS::sendGlobalPositionNED(uint8_t *txBuffer, mavlink_message_t *sendMsg){
	static struct GlobalPosition globalPositionSub = {0,};
	static struct LocalPosition localPositionSub = {0,};
	uint16_t len;

	msgBus.getGlobalPosition(&globalPositionSub);
	msgBus.getLocalPosition(&localPositionSub);

	mavlink_msg_global_position_int_pack(sysId, compId, sendMsg, millisecond(),
										 globalPositionSub.lat, globalPositionSub.lon, globalPositionSub.alt,
										 localPositionSub.refAlt,
										 localPositionSub.vx, localPositionSub.vy, localPositionSub.vz, globalPositionSub.yaw);

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
	mavlink_msg_mission_count_pack(sysId, compId, &sendMsg, target_system, target_component, 0, MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
}
void ModuleGCS::handle_mission_count(){
	mavlink_mission_count_t packet;
	mavlink_msg_mission_count_decode(&receiveMsg, &packet);
	mission_count = packet.count;
//	osDelay(50);
	mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);

	ptelem->send(txBuffer, len);
//	osDelay(50);
}
void ModuleGCS::handle_mission_item_int(){
	mavlink_mission_item_int_t packet;
	mavlink_msg_mission_item_int_decode(&receiveMsg, &packet);
	mission_seq=packet.seq;
//	osDelay(59);
	if(mission_seq != mission_count-1){
		mission_seq++;
		mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
		uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		ptelem->send(txBuffer, len);
	}
	else if(mission_seq == mission_count-1){
		mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
		uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		ptelem->send(txBuffer, len);
		mission_seq=0;
	}
}
void ModuleGCS::handle_mission_clear_all(){
	mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
	ptelem->send(txBuffer, len);
//	osDelay(10);
}
void ModuleGCS::handle_command_long(){
	mavlink_command_long_t packet;
	mavlink_msg_command_long_decode(&receiveMsg, &packet);
	mavlink_msg_command_ack_pack(sysId, compId, &sendMsg, packet.command, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, target_system, target_component);
	uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
	ptelem->send(txBuffer, len);
}
void ModuleGCS::handle_param_request_list(){
   for(int i = 0; i< PARAM_TOTAL_NUMBER;i++){
		mavlink_msg_param_value_pack(sysId, compId, &sendMsg, params[i].id, params[i].value, MAV_PARAM_TYPE_REAL32, PARAM_TOTAL_NUMBER, params[i].index);
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
	while(i < PARAM_TOTAL_NUMBER){
		if(strcmp(packet.param_id,params[i].id)){
		   mavlink_msg_param_value_pack(sysId, compId, &sendMsg, params[i].id, params[i].value, MAV_PARAM_TYPE_REAL32, PARAM_TOTAL_NUMBER, params[i].index);
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
	for(int i =0; i<PARAM_TOTAL_NUMBER;i++){
		if(strcmp(packet.param_id, params[i].id)){
		   mavlink_msg_param_value_pack(sysId, compId, &sendMsg, packet.param_id, packet.param_value, MAV_PARAM_TYPE_REAL32, PARAM_TOTAL_NUMBER, params[i].index);
		   uint16_t len = mavlink_msg_to_send_buffer(txBuffer, &sendMsg);
		   ptelem->send(txBuffer, len);
		   //TODO: printf_ is not executed
		   break;
		}
	}
}

void ModuleGCS_PeriodicSendTask(void *param){
	ModuleGCS::periodicSendTask(param);
}

//void heartbeatThread(void *param){
//	ModuleGCS::heartbeatTask(param);
//}
//
//void attitudeThread(void *param){
//	ModuleGCS::attitudeTask(param);
//}
//
//void globalPositionNedThread(void *param){
//	ModuleGCS::globalPositionNedTask(param);
//}

//void ModuleGCS::GCS_uartRxCpltCallback(){
//	  mavlink_parse_char(MAVLINK_COMM_0, rxBuffer[0], &receiveMsg, &status);
////	         memcpy(tx_buf,txBuffer,MAVLINK_MAX_PACKET_LEN);
////          printf_("message: %d\r\n",rev_msg.msgid);
//
//	  HAL_UART_Receive_IT(&huart2, rxBuffer, 1);
//}

/*
*  ModuleGCS::oneStep()
*/

}/* namespace FC */

