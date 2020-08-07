/*
 * IST8310.c
 *
 *  Created on: 2020. 7. 26.
 *      Author: cjb88
 */


#include "main.h"
#include "IST8310.h"

/*
 *  i2c shared width bme280
 */
#include "bme280.h"

#define IST8310_I2C ist8310.hi2c

#define IST8310_MAX_VAL_XY ((1600 / IST8310_RESOLUTION) + 1)
#define IST8310_MIN_VAL_XY (-IST8310_MAX_VAL_XY)
#define IST8310_MAX_VAL_Z ((2500 / IST8310_RESOLUTION) + 1)
#define IST8310_MIN_VAL_Z (-IST8310_MAX_VAL_Z)

void IST8310(I2C_HandleTypeDef *hi2c){
	IST8310_I2C = hi2c;
	IST8310_reset();
	IST8310_write_reg(IST8310_ADDR_CTRL1, IST8310_CTRL1_MODE_CONT_200HZ);
}

/*
 *  150hz gogo
 */
void IST8310_updataIT(){
	while(1){
		if(bm_i2cFlag == bm_i2cIdle){
			HAL_I2C_Mem_Read_IT(IST8310_I2C, IST8310_BUS_I2C_ADDR, IST8310_ADDR_DATA_OUT_X_LSB, 1, (uint8_t*)&ist8310.buf, sizeof(ist8310.buf));
			bm_i2cFlag = bm_i2cIST8310;
			return;
		}
		else osDelay(1);
	}
}
void IST8310_i2cRxCpltCallback(){
	if(bm_i2cFlag != bm_i2cIST8310) return;

	bm_i2cFlag = bm_i2cIdle;

	/* swap the data we just received */
	ist8310.count.x = (((int16_t)ist8310.buf.x[1]) << 8) | (int16_t)ist8310.buf.x[0];
	ist8310.count.y = (((int16_t)ist8310.buf.y[1]) << 8) | (int16_t)ist8310.buf.y[0];
	ist8310.count.z = (((int16_t)ist8310.buf.z[1]) << 8) | (int16_t)ist8310.buf.z[0];

	if (ist8310.count.x > IST8310_MAX_VAL_XY || ist8310.count.x < IST8310_MIN_VAL_XY ||
		ist8310.count.y > IST8310_MAX_VAL_XY || ist8310.count.y < IST8310_MIN_VAL_XY ||
		ist8310.count.z > IST8310_MAX_VAL_Z  || ist8310.count.z < IST8310_MIN_VAL_Z)
	{
		return;
	}

	/*
	 * raw outputs
	 *
	 * Sensor doesn't follow right hand rule, swap x and y to make it obey
	 * it.
	 */
	ist8310.raw[0] = (float)(ist8310.count.y);
	ist8310.raw[1] = (float)(ist8310.count.x);
	ist8310.raw[2] = (float)(ist8310.count.z);
}

void IST8310_write(uint8_t address, uint8_t *data, uint8_t count){
	HAL_I2C_Mem_Write(IST8310_I2C, IST8310_BUS_I2C_ADDR, address, 1, data, count, IST8310_DEFAULT_TIMEOUT);
}

void IST8310_write_reg(uint8_t reg, uint8_t val){
	IST8310_write(reg, &val, 1);
}

void IST8310_read(uint8_t address, uint8_t *data, uint8_t count){
	HAL_I2C_Mem_Read(IST8310_I2C, IST8310_BUS_I2C_ADDR, address, 1, data, count, IST8310_DEFAULT_TIMEOUT);
}

void IST8310_read_reg(uint8_t reg, uint8_t* val){
	IST8310_read(reg, val, 1);
}

void IST8310_reset(){
	/* software reset */
	IST8310_write_reg(IST8310_ADDR_CTRL2, IST8310_CTRL2_SRST);

	/* configure control register 3 */
	IST8310_write_reg(IST8310_ADDR_CTRL3, IST8310_CTRL3_SAMPLEAVG_16);

	/* configure control register 4 */
	IST8310_write_reg(IST8310_ADDR_CTRL4, IST8310_CTRL4_SRPD);
}
