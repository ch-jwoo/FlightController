/*
* ModuleGCS.h
*
*  Created on: 2020. 8. 18.
*      Author: cjb88
*/

#ifndef MODULE_MODULEGCS_H_
#define MODULE_MODULEGCS_H_
#include "Mavlink/common/mavlink.h"
#include "cmsis_os.h"
#include "Peripherals/Coms/Telemetry.h"
namespace FC {

class ModuleGCS {
public:
	ModuleGCS(Telemetry *ptelem);

	static void main();

	/*
	 *  send essential packet (heartbeat, attitude, globalPosition)
	 *  heartbeat		1hz
	 *  attitude		50hz
	 *  globalPosition	50ha
	 */
	static void periodicSendTask(void *instance);

private:
	Telemetry *ptelem;

	/* Main Handle Functions */
	void sendHeartbeat(uint8_t *txBuffer, mavlink_message_t *sendMsg);
	void sendAttitude(uint8_t *txBuffer, mavlink_message_t *sendMsg);
	void sendGlobalPosition(uint8_t *txBuffer, mavlink_message_t *sendMsg);


	void communicateGCS();

	void handleRcvMSG(const mavlink_message_t &mavMsg);

	/* Handle Functions (call by handle_GCS()) */
	/* Handle Mission Message */
	void handle_mission_request_list();
	void handle_mission_request_int();
	void handle_mission_request();
	void handle_mission_count();
	void handle_mission_item_int();
	void handle_mission_clear_all();

	/* Handle Command Message */
	void handle_command_long();

	/* Handle Parameter Message */
	void handle_param_request_list();
	void handle_param_request_read();
	void handle_param_set();

	/*
	 * member variable. these variable is used in handle receive message
	 * this variable must not be used in sendHeartbeat or attitude or globalPositionNED
	 */
	mavlink_message_t sendMsg;
	mavlink_message_t receiveMsg;
	mavlink_status_t status;
	uint8_t txBuffer[MAVLINK_MAX_PACKET_LEN];
	uint8_t rxBuffer[MAVLINK_MAX_PACKET_LEN];

	/* vehicle system, component id */
	uint8_t sysId = 1;
	uint8_t compId = 1;

	/* gps system, component id */
	uint8_t target_system = 255;
	uint8_t target_component = 1;

	/* waypoint communication */
	uint8_t mission_count = 0;		/* total waypoint size */
	uint8_t mission_seq = 0;		/* current send waypoint */

public:
	~ModuleGCS() = default;
	ModuleGCS(const ModuleGCS &other) = delete;
	ModuleGCS(ModuleGCS &&other) = delete;
	ModuleGCS& operator=(const ModuleGCS &other) = delete;
	ModuleGCS& operator=(ModuleGCS &&other) = delete;
};


/*
 *  change member function to c
 */
extern "C"{
void ModuleGCS_PeriodicSendTask(void *param);
}

}/* namespace FC */
#endif /* MODULE_GCS_H_ */
