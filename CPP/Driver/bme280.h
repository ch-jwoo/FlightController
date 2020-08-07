/*
 * bme280.h
 *
 *  Created on: Jul 26, 2020
 *      Author: cjb88
 */

#ifndef BME280_H_
#define BME280_H_


#ifdef __cplusplus
extern "C" {
#endif


/* 06/16/2017 Copyright Tlera Corporation
 *
 *  Created by Kris Winer
 *
 This sketch uses SDA/SCL on pins 42/43 (back pads), respectively, and it uses the Dragonfly STM32L476RE Breakout Board.
 The BME280 is a simple but high resolution pressure/humidity/temperature sensor, which can be used in its high resolution
 mode but with power consumption of 20 microAmp, or in a lower resolution mode with power consumption of
 only 1 microAmp. The choice will depend on the application.

 Library may be used freely and without limit with attribution.

*/

/* BME280 registers
*  http://www.mouser.com/ds/2/783/BST-BME280_DS001-11-844833.pdf
*/
#define BME280_HUM_LSB    0xFE
#define BME280_HUM_MSB    0xFD
#define BME280_TEMP_XLSB  0xFC
#define BME280_TEMP_LSB   0xFB
#define BME280_TEMP_MSB   0xFA
#define BME280_PRESS_XLSB 0xF9
#define BME280_PRESS_LSB  0xF8
#define BME280_PRESS_MSB  0xF7
#define BME280_CONFIG     0xF5
#define BME280_CTRL_MEAS  0xF4
#define BME280_STATUS     0xF3
#define BME280_CTRL_HUM   0xF2
#define BME280_RESET      0xE0
#define BME280_ID         0xD0  // should be 0x60
#define BME280_CALIB00    0x88
#define BME280_CALIB26    0xE1

#define BME280_ADDRESS           0x76<<1   // Address of BMP280 altimeter when ADO = 0


#define  P_OSR_01 0x01
#define  P_OSR_02 0x02
#define  P_OSR_04 0x03
#define  P_OSR_08 0x04
#define  P_OSR_16 0x05

#define  H_OSR_00 0x01
#define  H_OSR_01 0x01
#define  H_OSR_02 0x02
#define  H_OSR_04 0x03
#define  H_OSR_08 0x04
#define  H_OSR_16 0x05

#define  T_OSR_01 0x01
#define  T_OSR_02 0x02
#define  T_OSR_04 0x03
#define  T_OSR_08 0x04
#define  T_OSR_16 0x05

#define  full       0x00
#define  BW0_223ODR 0x01
#define  BW0_092ODR 0x02
#define  BW0_042ODR 0x03
#define  BW0_021ODR 0x04

#define  BME280Sleep 0x00
#define  forced      0x01
#define  forced2     0x02
#define  normal      0x03

#define  t_00_5ms 0x00
#define  t_62_5ms 0x01
#define  t_125ms  0x02
#define  t_250ms  0x03
#define  t_500ms  0x04
#define  t_1000ms 0x05
#define  t_10ms   0x06
#define  t_20ms   0x07

#define BME_DEFAULT_TIMEOUT 100

typedef enum {
	bm_i2cIdle = 0,
	bm_i2cBME280 = 1,
	bm_i2cIST8310 = 2,
}baro_mag_i2cFlag_t;

baro_mag_i2cFlag_t bm_i2cFlag;

typedef struct{
	I2C_HandleTypeDef *hi2c;

	uint8_t buf[9];
	uint8_t  _dig_H1, _dig_H3, _dig_H6;
	uint16_t _dig_T1, _dig_P1, _dig_H4, _dig_H5;
	int16_t  _dig_T2, _dig_T3, _dig_P2, _dig_P3, _dig_P4, _dig_P5, _dig_P6, _dig_P7, _dig_P8, _dig_P9, _dig_H2;
	int32_t  _t_fine;

	int32_t countT;
	uint32_t countP, countH;

	float T;			/*[degC]*/
	float P;			/*[hPa]*/
	float H;

} BME280_t;

extern BME280_t bme280;

void BME280_init(I2C_HandleTypeDef *hi2c, uint8_t Posr, uint8_t Hosr, uint8_t Tosr, uint8_t Mode, uint8_t IIRFilter, uint8_t SBy);
void BME280_readIT();
void BME280_i2cRxCpltCallback();

int32_t BME280_readTemperature();
int32_t BME280_readPressure();
int16_t BME280_readHumidity();

int32_t BME280_compensate_T(int32_t adc_T);
uint32_t BME280_compensate_P(int32_t adc_P);
uint32_t BME280_compensate_H(int32_t adc_H);

uint8_t BME280_getChipID();
void BME280_reset();

void BME280_writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
uint8_t BME280_readByte(uint8_t address, uint8_t subAddress);
void BME280_readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);

#ifdef __cplusplus
}
#endif

#endif /* BME280_H_ */
