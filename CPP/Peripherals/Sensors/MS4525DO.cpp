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
, caliFlag(false)
, caliCount(0)
, pressureHigh(0.0f)
, pressureLow(0.0f)
, temperatureHigh(0.0f)
, temperatureLow(0.0f)
, countAverage(0)
, difPressureSumValue(0)
, smoothAdc(0)
, airSpeedDataAdc0(0.0f)
, absDifPressureAdc(0.0f)
, expSmoothAdc(0.0f)
, smoothAirSpeed(0.0f)
, difPressureAdc(0.0f)
, difPressureAdc0(0.0f)
, offset4525(0.0f)
, difPressureSum(0.0f)
{

}


bool MS4525DO::update(){
	i2c->read(MS4525DO_ADDRESS, 0x00, buffer, 4);
	pressureHigh = buffer[0];
	pressureLow = buffer[1];
	temperatureHigh = buffer[2];
	temperatureLow = buffer[3];

	//check buffer[0] for checking data is correct
	if((pressureHigh & 0xC0) == 0){
		difPressureAdc = (((pressureHigh << 8) + pressureLow) & 0x3FFF) - 0x2000;
		// start calibration
		if(!caliFlag){
			caliCount++;
			if(caliCount == 256){
				offset4525 = (float) difPressureSum / 128.0f;
				caliFlag = true;
			}
			/* calibCount 128~256 */
			else if(caliCount >= 128){
				difPressureSum += difPressureAdc;
			}
			/* calibCount 0~128 */
			else{
				/* dump the data */
			}
			return false;
		}
		// end calibration
		else{
			//voltage correction
			difPressureAdc0 = (float)difPressureAdc - offset4525;
			difPressureSumValue += difPressureAdc - difPressureAdcArray[0];

			difPressureAdcArray[countAverage] = difPressureAdc;

			if(((++countAverage) >= 4)) countAverage = 0;

			airSpeedDataAdc0 = (float) difPressureSumValue * 0.25 - offset4525;

			absDifPressureAdc = abs(difPressureAdc0 - smoothAdc);
			if(absDifPressureAdc <= FILTERING4525_ADC_MIN_AT){
			   expSmoothAdc = FILTERING4525_ADC_MIN;
			}
			else if( absDifPressureAdc >= FILTERING4525_ADC_MAX_AT){
			   expSmoothAdc = FILTERING4525_ADC_MAX;
			}
			else{
			   expSmoothAdc = FILTERING4525_ADC_MIN + ( FILTERING4525_ADC_MAX - FILTERING4525_ADC_MIN) * (absDifPressureAdc - FILTERING4525_ADC_MIN_AT) / (FILTERING4525_ADC_MAX_AT - FILTERING4525_ADC_MIN_AT);
			}
			smoothAdc += expSmoothAdc * (difPressureAdc0 - smoothAdc);

			if(smoothAdc < 0) smoothAdc = -smoothAdc;
			diffPressure = smoothAdc;
		}
		return true;
	}
	return false;
}

} /* namespace FC */
