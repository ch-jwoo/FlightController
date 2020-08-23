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
#include "Mavlink/common/mavlink.h"
#include "Usec.h"
#include "usart.h"
#include "main.h"
#include "cstring"

namespace FC {

ModuleGCS::ModuleGCS() {

}
void ModuleGCS::handle_heartbeat(){
	mavlink_msg_heartbeat_pack(sysId, compId, &sendMsg, MAV_TYPE_HEXAROTOR, MAV_AUTOPILOT_PX4,
			MAV_MODE_FLAG_TEST_ENABLED, MAV_STATE_STANDBY, 3);

	uint16_t len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);

	HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
}

void ModuleGCS::handle_attitude(){
	msgBus.getBodyAngularVelocity(&bodyAngleVelocitySub);
	msgBus.getAttitude(&this->attitudeSub);

	mavlink_msg_attitude_pack(sysId, compId, &sendMsg, attitudeSub.timestamp,
							  attitudeSub.roll, attitudeSub.pitch, attitudeSub.yaw,
							  bodyAngleVelocitySub.xyz[0], bodyAngleVelocitySub.xyz[1], bodyAngleVelocitySub.xyz[2]);

	uint16_t len = mavlink_msg_to_send_buffer(tx_buf1, &sendMsg);

	HAL_UART_Transmit_DMA(&huart2, tx_buf1, len);
}

void ModuleGCS::handle_global_position_ned(){
	msgBus.getGlobalPosition(&this->globalPositionSub);
	msgBus.getLocalPosition(&this->localPositionSub);

	mavlink_msg_global_position_int_pack(sysId, compId, &sendMsg, globalPositionSub.timestamp, globalPositionSub.lat, globalPositionSub.lon, globalPositionSub.alt, localPositionSub.refAlt, localPositionSub.vx, localPositionSub.vy, localPositionSub.vz, globalPositionSub.yaw);

	uint16_t len = mavlink_msg_to_send_buffer(tx_buf1, &sendMsg);

	HAL_UART_Transmit_DMA(&huart2, tx_buf1, len);
}

void ModuleGCS::handle_GCS(){
	   while(1){
		  osDelay(101);
		  switch(receiveMsg.msgid){
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
			}
		  }
}
void ModuleGCS::handle_mission_request_list(){

	mavlink_msg_mission_count_pack(sysId, compId, &sendMsg, target_system, target_component, 0, MAV_MISSION_TYPE_MISSION);
	len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
	HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
}
void ModuleGCS::handle_mission_count(){

	mavlink_mission_count_t packet;
	mavlink_msg_mission_count_decode(&receiveMsg, &packet);
	mission_count=packet.count;
	osDelay(50);
	mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
	len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
	HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
	osDelay(50);
}
void ModuleGCS::handle_mission_item_int(){
	mavlink_mission_item_int_t packet;
	mavlink_msg_mission_item_int_decode(&receiveMsg, &packet);
	mission_seq=packet.seq;
	osDelay(59);
   if(mission_seq!=mission_count-1){
   mission_seq++;
   mavlink_msg_mission_request_int_pack(sysId, compId, &sendMsg, target_system, target_component, mission_seq, MAV_MISSION_TYPE_MISSION);
	len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
	HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
   }
	else if(mission_seq==mission_count-1){
	   mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
	   len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
	   HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
	   mission_seq=0;
	}
}
void ModuleGCS::handle_mission_clear_all(){
	mavlink_msg_mission_ack_pack(sysId, compId, &sendMsg, target_system, target_component, MAV_MISSION_ACCEPTED, MAV_MISSION_TYPE_MISSION);
	len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
	HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
	osDelay(10);
}
void ModuleGCS::handle_command_long(){
	mavlink_command_long_t packet;
	mavlink_msg_command_long_decode(&receiveMsg, &packet);
   mavlink_msg_command_ack_pack(sysId, compId, &sendMsg, packet.command, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, MAV_RESULT_ACCEPTED, target_system, target_component);
   len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
   HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
}
void ModuleGCS::handle_param_request_list(){
   for(int i = 0; i< PARAM_TOTAL_NUMBER;i++){
		mavlink_msg_param_value_pack(sysId, compId, &sendMsg, params[i].id, params[i].value, MAV_PARAM_TYPE_REAL32, PARAM_TOTAL_NUMBER, params[i].index);
		len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
		HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
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
		   len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
		   HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
		   i++;
		}
	}
	lastReqMillis = millisecond();
}

void ModuleGCS::handle_param_set(){
	mavlink_param_set_t packet;
	mavlink_msg_param_set_decode(&receiveMsg, &packet);
	for(int i =0; i<PARAM_TOTAL_NUMBER;i++){
		if(strcmp(packet.param_id,params[i].id))
		{
		   mavlink_msg_param_value_pack(sysId, compId, &sendMsg, packet.param_id, packet.param_value, MAV_PARAM_TYPE_REAL32, PARAM_TOTAL_NUMBER, params[i].index);
		   len = mavlink_msg_to_send_buffer(tx_buf, &sendMsg);
		   HAL_UART_Transmit_DMA(&huart2, tx_buf, len);
		   //TODO: printf_ is not executed
		   break;
		}
	}
}
void ModuleGCS::GCS_uartRxCpltCallback(){
	  mavlink_parse_char(MAVLINK_COMM_0, rx_buf[0], &receiveMsg, &status);
//	         memcpy(tx_buf,tx_buf1,MAVLINK_MAX_PACKET_LEN);
//          printf_("message: %d\r\n",rev_msg.msgid);

	  HAL_UART_Receive_IT(&huart2, rx_buf, 1);
}

/*
*  ModuleGCS::oneStep()
*/

}/* namespace FC */

