/*
 * bme280.c
 *
 *  Created on: Jul 26, 2020
 *      Author: cjb88
 */

#include "main.h"
#include "bme280.h"
#include "math.h"

BME280_t bme280 = {0,};

void BME280_init(I2C_HandleTypeDef *hi2c, uint8_t Posr, uint8_t Hosr, uint8_t Tosr, uint8_t Mode, uint8_t IIRFilter, uint8_t SBy){
	bme280.hi2c = hi2c;
	BME280_reset();
	// Configure the BME280
	// Set H oversampling rate
	BME280_writeByte(BME280_ADDRESS, BME280_CTRL_HUM, 0x07 & Hosr);
	// Set T and P oversampling rates and sensor mode
	BME280_writeByte(BME280_ADDRESS, BME280_CTRL_MEAS, Tosr << 5 | Posr << 2 | Mode);
	// Set standby time interval in normal mode and bandwidth
	BME280_writeByte(BME280_ADDRESS, BME280_CONFIG, SBy << 5 | IIRFilter << 2);

	//wait.
	HAL_Delay(50);
	uint8_t calib[26];
	BME280_readBytes(BME280_ADDRESS, BME280_CALIB00, 26, &calib[0]);
	bme280._dig_T1 = (uint16_t)(((uint16_t) calib[1] << 8) | calib[0]);
	bme280._dig_T2 = ( int16_t)((( int16_t) calib[3] << 8) | calib[2]);
	bme280._dig_T3 = ( int16_t)((( int16_t) calib[5] << 8) | calib[4]);
	bme280._dig_P1 = (uint16_t)(((uint16_t) calib[7] << 8) | calib[6]);
	bme280._dig_P2 = ( int16_t)((( int16_t) calib[9] << 8) | calib[8]);
	bme280._dig_P3 = ( int16_t)((( int16_t) calib[11] << 8) | calib[10]);
	bme280._dig_P4 = ( int16_t)((( int16_t) calib[13] << 8) | calib[12]);
	bme280._dig_P5 = ( int16_t)((( int16_t) calib[15] << 8) | calib[14]);
	bme280._dig_P6 = ( int16_t)((( int16_t) calib[17] << 8) | calib[16]);
	bme280._dig_P7 = ( int16_t)((( int16_t) calib[19] << 8) | calib[18]);
	bme280._dig_P8 = ( int16_t)((( int16_t) calib[21] << 8) | calib[20]);
	bme280._dig_P9 = ( int16_t)((( int16_t) calib[23] << 8) | calib[22]);
	bme280._dig_H1 = calib[25];
	BME280_readBytes(BME280_ADDRESS, BME280_CALIB26, 7, &calib[0]);
	bme280._dig_H2 = ( int16_t)((( int16_t) calib[1] << 8) | calib[0]);
	bme280._dig_H3 = calib[2];
	bme280._dig_H4 = ( int16_t)(((( int16_t) calib[3] << 8) | (0x0F & calib[4]) << 4) >> 4);
	bme280._dig_H5 = ( int16_t)(((( int16_t) calib[5] << 8) | (0xF0 & calib[4]) ) >> 4 );
	bme280._dig_H6 = calib[6];
}

void BME280_readIT(){
	if(bm_i2cFlag == bm_i2cIdle){
		HAL_I2C_Mem_Read_IT(bme280.hi2c, BME280_ADDRESS, BME280_PRESS_MSB, 1, bme280.buf, 6);
		bm_i2cFlag = bm_i2cBME280;
		return;
	}

}

void BME280_i2cRxCpltCallback(){
	if(bm_i2cFlag != bm_i2cBME280) return;
    bme280.countP = (int32_t) (((int32_t) bme280.buf[0] << 24 | (int32_t) bme280.buf[1] << 16 | (int32_t) bme280.buf[2] << 8) >> 12);
    bme280.countT = (int32_t) (((int32_t) bme280.buf[3] << 24 | (int32_t) bme280.buf[4] << 16 | (int32_t) bme280.buf[5] << 8) >> 12);

    // change to hPa
    bme280.P = BME280_compensate_P(bme280.countP)/25600.0;	/*[hPa]*/
    bme280.T = BME280_compensate_T(bme280.countT)/100.0;	/*[degC]*/

//    bme280.alt = 44330 * (1.0 - pow(bme280.P / bme280.base_P, 0.1903));

    bm_i2cFlag = bm_i2cIdle;
}

uint8_t BME280_getChipID(){
	  uint8_t c = BME280_readByte(BME280_ADDRESS, BME280_ID);
	  return c;
}
void BME280_reset(){
	BME280_writeByte(BME280_ADDRESS, BME280_RESET, 0xB6);
}

int32_t BME280_readTemperature(){
	  uint8_t rawData[3];  // 20-bit pressure register data stored here
	  BME280_readBytes(BME280_ADDRESS, BME280_TEMP_MSB, 3, &rawData[0]);
	  return (int32_t) (((int32_t) rawData[0] << 24 | (int32_t) rawData[1] << 16 | (int32_t) rawData[2] << 8) >> 12);
}

int32_t BME280_readPressure(){
	  uint8_t rawData[3];  // 20-bit pressure register data stored here
	  BME280_readBytes(BME280_ADDRESS, BME280_PRESS_MSB, 3, &rawData[0]);
	  return (int32_t) (((int32_t) rawData[0] << 24 | (int32_t) rawData[1] << 16 | (int32_t) rawData[2] << 8) >> 12);
}
int16_t BME280_readHumidity(){
	  uint8_t rawData[3];  // 20-bit pressure register data stored here
	  BME280_readBytes(BME280_ADDRESS, BME280_HUM_MSB, 2, &rawData[0]);
	  return (int16_t) (((int16_t) rawData[0] << 8 | rawData[1]) );
}



// Returns temperature in DegC, resolution is 0.01 DegC. Output value of
// “5123” equals 51.23 DegC.
int32_t BME280_compensate_T(int32_t adc_T){
	  int32_t var1, var2, T;
	  var1 = ((((adc_T >> 3) - ((int32_t)bme280._dig_T1 << 1))) * ((int32_t)bme280._dig_T2)) >> 11;
	  var2 = (((((adc_T >> 4) - ((int32_t)bme280._dig_T1)) * ((adc_T >> 4) - ((int32_t)bme280._dig_T1))) >> 12) * ((int32_t)bme280._dig_T3)) >> 14;
	  bme280._t_fine = var1 + var2;
	  T = (bme280._t_fine * 5 + 128) >> 8;
	  return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8
//fractional bits).
//Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t BME280_compensate_P(int32_t adc_P){
	  int64_t var1, var2, p;
	  var1 = ((int64_t)bme280._t_fine) - 128000;
	  var2 = var1 * var1 * (int64_t)bme280._dig_P6;
	  var2 = var2 + ((var1*(int64_t)bme280._dig_P5)<<17);
	  var2 = var2 + (((int64_t)bme280._dig_P4)<<35);
	  var1 = ((var1 * var1 * (int64_t)bme280._dig_P3)>>8) + ((var1 * (int64_t)bme280._dig_P2)<<12);
	  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)bme280._dig_P1)>>33;
	  if(var1 == 0)
	  {
	    return 0;
	    // avoid exception caused by division by zero
	  }
	  p = 1048576 - adc_P;
	  p = (((p<<31) - var2)*3125)/var1;
	  var1 = (((int64_t)bme280._dig_P9) * (p>>13) * (p>>13)) >> 25;
	  var2 = (((int64_t)bme280._dig_P8) * p)>> 19;
	  p = ((p + var1 + var2) >> 8) + (((int64_t)bme280._dig_P7)<<4);
	  return (uint32_t)p;
}

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22integer and 10fractional bits).
// Output value of “47445”represents 47445/1024= 46.333%RH
uint32_t BME280_compensate_H(int32_t adc_H){
	int32_t var;

	var = (bme280._t_fine - ((int32_t)76800));
	var = (((((adc_H << 14) - (((int32_t)bme280._dig_H4) << 20) - (((int32_t)bme280._dig_H5) * var)) +
	((int32_t)16384)) >> 15) * (((((((var * ((int32_t)bme280._dig_H6)) >> 10) * (((var *
	((int32_t)bme280._dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)bme280._dig_H2) + 8192) >> 14));
	var = (var - (((((var >> 15) * (var >> 15)) >> 7) * ((int32_t)bme280._dig_H1)) >> 4));
	var = (var < 0 ? 0 : var);
	var = (var > 419430400 ? 419430400 : var);
	return(uint32_t)(var >> 12);
}

void BME280_writeByte(uint8_t address, uint8_t subAddress, uint8_t data){
	HAL_I2C_Mem_Write(bme280.hi2c, address, subAddress, 1, &data, 1, BME_DEFAULT_TIMEOUT);
}
void BME280_readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest){
	HAL_I2C_Mem_Read(bme280.hi2c, address, subAddress, 1, (uint8_t*)dest, count, BME_DEFAULT_TIMEOUT);
}
uint8_t BME280_readByte(uint8_t address, uint8_t subAddress){
	uint8_t data;
	BME280_readBytes(address, subAddress, 1, &data);
	return data;
}
