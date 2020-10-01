/*
 * IST8310.cpp
 *
 *  Created on: Aug 23, 2020
 *      Author: cjb88
 */

#include <Peripherals/Sensors/IST8310.h>

namespace FC {

#define IST8310_MAX_VAL_XY ((1600 / IST8310_RESOLUTION) + 1)
#define IST8310_MIN_VAL_XY (-IST8310_MAX_VAL_XY)
#define IST8310_MAX_VAL_Z ((2500 / IST8310_RESOLUTION) + 1)
#define IST8310_MIN_VAL_Z (-IST8310_MAX_VAL_Z)

IST8310::IST8310(RtosI2C *i2c)
: i2c(i2c)
{
}

void IST8310::init(){
	reset();
//	writeByte(IST8310_BUS_I2C_ADDR, IST8310_ADDR_CTRL1, IST8310_CTRL1_MODE_CONT_200HZ);
	writeByte(IST8310_BUS_I2C_ADDR, IST8310_ADDR_CTRL1, IST8310_CTRL1_MODE_CONT_100HZ);
}

void IST8310::reset(){
	/* software reset */
	writeByte(IST8310_BUS_I2C_ADDR, IST8310_ADDR_CTRL2, IST8310_CTRL2_SRST);

	/* configure control register 3 */
	writeByte(IST8310_BUS_I2C_ADDR, IST8310_ADDR_CTRL3, IST8310_CTRL3_SAMPLEAVG_16);

	/* configure control register 4 */
	writeByte(IST8310_BUS_I2C_ADDR, IST8310_ADDR_CTRL4, IST8310_CTRL4_SRPD);
}

bool IST8310::update(){
	readBytes(IST8310_BUS_I2C_ADDR, IST8310_ADDR_DATA_OUT_X_LSB, sizeof(buf), (uint8_t*)&buf);

	/* swap the data we just received */
	count.x = (((int16_t)buf.x[1]) << 8) | (int16_t)buf.x[0];
	count.y = (((int16_t)buf.y[1]) << 8) | (int16_t)buf.y[0];
	count.z = (((int16_t)buf.z[1]) << 8) | (int16_t)buf.z[0];

	if (count.x > IST8310_MAX_VAL_XY || count.x < IST8310_MIN_VAL_XY ||
		count.y > IST8310_MAX_VAL_XY || count.y < IST8310_MIN_VAL_XY ||
		count.z > IST8310_MAX_VAL_Z  || count.z < IST8310_MIN_VAL_Z)
	{
		return false;
	}

	/*
	 * raw outputs
	 *
	 * Sensor doesn't follow right hand rule, swap x and y to make it obey
	 * it.
	 */
	raw[0] = (float)(count.y);
	raw[1] = (float)(count.x);
	raw[2] = (float)(count.z);

	return true;
}

} /* namespace FC */
