/*
 * MPU9250.cpp
 *
 *  Created on: 2020. 8. 23.
 *      Author: cjb88
 */

#include <Peripherals/Sensors/MS4525DO.h>
namespace FC {

MS4525DO::MS4525DO(RtosI2C *i2c)
: i2c(i2c)
, pressureHigh(0.0f)
, pressureLow(0.0f)
, temperatureHigh(0.0f)
, temperatureLow(0.0f)
{

}


bool MS4525DO::update(){
//	readBytes(MS4525DO_ADDRESS, 0x00, 4, buffer);
	i2c->read(MS4525DO_ADDRESS, 0x00, buffer, 4);
	pressureHigh = buffer[0];
	pressureLow = buffer[1];
	temperatureHigh = buffer[2];
	temperatureLow = buffer[3];
	gettingPressure(pressureHigh, pressureLow, &difPressure);
	gettingTemperature(temperatureHigh, temperatureLow, &difTemperature);
	gettingTrueAirSpeed(difPressure, &TAS);
	return true;
}

void MS4525DO::gettingPressure(uint16_t pressureHigh, uint16_t pressureLow , float *difPressure){

	pressureHigh = pressureHigh & 0x03f;

	*difPressure = (float)((pressureHigh << 8) | pressureLow);

}
void MS4525DO::gettingTemperature(uint16_t temperatureHigh, uint16_t temperatureLow, float *difTemperature){
	float tmp;

	temperatureLow = temperatureLow >> 5;

	tmp = (float)((temperatureHigh << 3) | temperatureLow);
	tmp = tmp * 0.09770395701f - 50.0f ;

	*difTemperature = tmp;
}
void MS4525DO::gettingTrueAirSpeed(float pressure, float *TAS){

	msgBus.getGlobalPosition(&this->globalPositionSub);
	float tmp, IAS;

	tmp = (pressure - 819.15) / 14744.7;
	tmp = tmp - 0.49060678;
	if(tmp < 0) tmp = -tmp;
	IAS = sqrt(tmp * 13789.5144 / 1.225) - 7.71684477;
	*TAS = IAS + IAS * (0.2 + 1000 / 1000);
}
} /* namespace FC */
