/*
 * MPU9250.h
 *
 *  Created on: 2020. 8. 23.
 *      Author: cjb88
 */

#ifndef PERIPHERALS_SENSORS_MS4525DO_H_
#define PERIPHERALS_SENSORS_MS4525DO_H_

#include "RtosI2C.h"
#include "MsgBus/MsgType.h"
#include "MsgBus/MsgBus.h"
namespace FC {

#define MS4525DO_ADDRESS 0x28 << 1
#define MAX_PRESSURE_SCALE 16383

class MS4525DO {
public:
	MS4525DO(RtosI2C *i2c);

	bool update();

	/* Reading data from MS4525DO */
	inline void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest){
		i2c->read(address, subAddress, dest, count);
	}
	/* Getting Temperature and pressure */
	void gettingTemperature(uint16_t temperatureMax, uint16_t temperatureMin, float *diffTemperature);
	void gettingPressure(uint16_t pressureMax, uint16_t pressureMin, float *diffPressure);

	/* Getting AirSpeed */
	void gettingTrueAirSpeed(float pressure, float *TAS);

	float TAS;
	float difTemperature;
	float difPressure;
private:
	RtosI2C *i2c;

	struct GlobalPosition globalPositionSub= { 0 };

	uint8_t buffer[4];
	uint16_t pressureHigh;
	uint16_t pressureLow;
	uint16_t temperatureHigh;
	uint16_t temperatureLow;
public:
	MS4525DO() = delete;
	~MS4525DO() = default;
	MS4525DO(const MS4525DO &other) = delete;
	MS4525DO(MS4525DO &&other) = delete;
	MS4525DO& operator=(const MS4525DO &other) = delete;
	MS4525DO& operator=(MS4525DO &&other) = delete;
};

} /* namespace FC */

#endif /* PERIPHERALS_SENSORS_MS4525DO_H_ */
