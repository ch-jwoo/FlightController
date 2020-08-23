/*
* ModuleGCS.h
*
*  Created on: 2020. 8. 18.
*      Author: cjb88
*/

#ifndef MODULE_MODULEGCS_H_
#define MODULE_MODULEGCS_H_
#include "Mavlink/common/mavlink.h"
#include "Utils/Constants.h"
#include "main.h"
#include "cmsis_os.h"

//#define PARAM_TOTAL_NUMBER 46
namespace FC {
/*
 *  pram id (string)
 *  pram value
 *  pram type
 *  pram count index (0 ~ )
 */
struct Parameters{
	char id[40];
	float value;
	uint8_t index;
};

class ModuleGCS {
public:
	/* UART2 Callback Function */
	void GCS_uartRxCpltCallback();

	ModuleGCS();

	/*
	 *  essentially send this packet
	 *  must need to communicate width GCS (1 ~ 5hz)
	 */
	static void sendHeartbeat(){
		ModuleGCS moduleGCS;
		while(1){
			moduleGCS.handle_heartbeat();
			osDelay(1000);
		}
	}

	/*
	 *  originally 50hz but we adopted 20hz because 50hz is so fast
	 *  for vehicle attitude visualization
	 *  not essential
	 */
	static void sendAttitude(){
		ModuleGCS moduleGCS;
		while(1){
			moduleGCS.handle_attitude();
			osDelay(50);
		}
	}

	/*
	 *  for vehicle position visualization
	 *  not essential
	 *  we adopted hz
	 */
	static void sendGlobalPositionNed(){
		ModuleGCS moduleGCS;
		while(1){
			moduleGCS.handle_global_position_ned();
			osDelay(50);
		}
	}

	/*
	 *  push/pull waypoints
	 *  push/pull parameter
	 *  deal command :
	 *  	send ACK autopilot version, protocol version etc.
	 */
	static void interactionGCS(){
		ModuleGCS moduleGCS;
		while(1){
			moduleGCS.handle_GCS();
		}
	}

	~ModuleGCS() = default;
	ModuleGCS(const ModuleGCS &other) = delete;
	ModuleGCS(ModuleGCS &&other) = delete;
	ModuleGCS& operator=(const ModuleGCS &other) = delete;
	ModuleGCS& operator=(ModuleGCS &&other) = delete;
private:

	/* Input */
	struct BodyAngularVelocity bodyAngleVelocitySub{0};
	struct GlobalPosition globalPositionSub = { 0 };		/* for position visualization */
	struct LocalPosition localPositionSub = { 0 };			/* for NED velocity */
	struct Attitude attitudeSub = { 0 };					/* for attitude visualization */

	/* Main Handle Functions */
	void handle_heartbeat();
	void handle_attitude();
	void handle_global_position_ned();
	void handle_GCS();

	/* Handle Functions (call by handle_GCS()) */
	/* Handle Mission Message */
	void handle_mission_request_list();
	void handle_mission_count();
	void handle_mission_item_int();
	void handle_mission_clear_all();

	/* Handle Command Message */
	void handle_command_long();

	/* Handle Parameter Message */
	void handle_param_request_list();
	void handle_param_request_read();
	void handle_param_set();

	/* Variables */
	mavlink_message_t sendMsg;
	mavlink_message_t receiveMsg;
	mavlink_status_t status;
	uint8_t tx_buf[MAVLINK_MAX_PACKET_LEN];
	uint8_t tx_buf1[MAVLINK_MAX_PACKET_LEN];
	uint8_t rx_buf[MAVLINK_MAX_PACKET_LEN];
	uint8_t sysId = 1;
	uint8_t compId = 1;
	uint8_t target_system = 255;
	uint8_t target_component = 1;
	uint8_t len;							/* tx buffer length */
	uint8_t param_count = 0;
	uint8_t mission_seq = 0;
	uint8_t mission_count = 0;
	uint8_t flag = 0;
	static const uint8_t PARAM_TOTAL_NUMBER = 46;
	struct Parameters params[PARAM_TOTAL_NUMBER] = {{"PC_YAW_P\0", 0.04f,0},
	                                     {"PC_X_P\0", 0.7f,1},{"PC_X_I\0", 0.0f,2},{"PC_X_D\0", 0.1f,3},
	                                     {"PC_VX_P\0", 0.17f,4},{"PC_VX_I\0", 0.0f,5},{"PC_VX_D\0", 0.11f,6},
	                                     {"PC_Y_P\0", 0.88f,7},{"PC_Y_I\0", 0.0f,8},{"PC_Y_D\0", 0.252f,9},
	                                     {"PC_VY_P\0", 0.17f,10},{"PC_VY_I\0", 0.3f,11},{"PC_VY_D\0", 0.11f,12},
	                                     {"PC_Z_P\0", 2.7f,13},{"PC_Z_I\0", 0.2f,14},{"PC_Z_D\0", 0.01f,15},
	                                     {"PC_VZ_P\0", 3.0f,16},{"PC_VZ_I\0", 0.2f,17},{"PC_VZ_D\0", 0.01f,18},
	                                     {"PE_POS_PROC\0", 0.3f,19},{"PE_INIT\0", 0.3f,20},{"PE_IMU\0", 0.3f,21},{"PE_GPS_POS\0", 0.3f,22},
	                                     {"PE_ALT_PROC\0", 0.3f,23},{"PE_ALT_INIT\0", 0.3f,24},{"PE_IMU_ALT\0", 0.3f,25},{"PE_GPS_ALT\0", 0.3f,26},
	                                     {"RC_VEL\0", 20.0f,27},{"RC_RISE_VEL\0", 10.0f,28},{"RC_YAW_SCALE\0", 3.14f,29},
	                                     {"AC_MAX_ANG\0", 0.3f,30},
	                                     {"AC_ANG_RATE_ROLL_P\0", 0.3f,31},{"AC_ANG_RATE_ROLL_I\0", 0.3f,32},{"AC_ANG_RATE_PITCH_P\0", 0.3f,33},{"AC_ANG_RATE_ROLL_I\0", 0.3f,34},
	                                     {"AC_ROLL_RATE_P\0", 0.3f,35},{"AC_ROLL_RATE_I\0", 0.3f,36},{"AC_ROLL_RATE_D\0", 0.3f,37},
	                                     {"AC_PITCH_RATE_P\0", 0.3f,38},{"AC_PITCH_RATE_I\0", 0.3f,39},{"AC_PITCH_RATE_D\0", 0.3f,40},
	                                     {"AC_YAW_ANG_RATE_P\0", 0.3f,41},{"AC_YAW_RATE_P\0", 0.3f,42},{"AC_YAW_RATE_I\0", 0.3f,43},
	                                     {"G_TAU\0", 1.5f,44},{"G_M\0", 0.6f,45}};
}; 

}/* namespace FC */
#endif /* MODULE_GCS_H_ */
