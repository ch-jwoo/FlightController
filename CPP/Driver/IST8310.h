/*
 * IST8310.h
 *
 *  Created on: 2020. 7. 26.
 *      Author: cjb88
 */

#ifndef IST8310_H_
#define IST8310_IST8310_H_

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
 *
 *   Copyright (c) 2012-2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file ist8310.cpp
 *
 * Driver for the IST8310 magnetometer connected via I2C.
 *
 * @author David Sidrane
 * @author Maelok Dong
 */

/*
 * IST8310 internal constants and data structures.
 */

/* Max measurement rate is 160Hz, however with 160 it will be set to 166 Hz, therefore workaround using 150
 * The datasheet gives 200Hz maximum measurement rate, but it's not true according to tech support from iSentek*/
#define IST8310_CONVERSION_INTERVAL	(1000000 / 100) /* microseconds */

#define IST8310_BUS_I2C_ADDR		0xE<<1
#define IST8310_DEFAULT_BUS_SPEED	400000

/*
 * FSR:
 *   x, y: +- 1600 µT
 *   z:    +- 2500 µT
 *
 * Resolution according to datasheet is 0.3µT/LSB
 */
#define IST8310_RESOLUTION	0.3



/* Hardware definitions */

#define IST8310_ADDR_WAI                0		/* WAI means 'Who Am I'*/
#define IST8310_WAI_EXPECTED_VALUE     0x10

#define IST8310_ADDR_STAT1              0x02
#define IST8310_STAT1_DRDY_SHFITS      0x0
#define IST8310_STAT1_DRDY             (1 << IST8310_STAT1_DRDY_SHFITS)
#define IST8310_STAT1_DRO_SHFITS       0x1
#define IST8310_STAT1_DRO              (1 << IST8310_STAT1_DRO_SHFITS)

#define IST8310_ADDR_DATA_OUT_X_LSB     0x03
#define IST8310_ADDR_DATA_OUT_X_MSB     0x04
#define IST8310_ADDR_DATA_OUT_Y_LSB     0x05
#define IST8310_ADDR_DATA_OUT_Y_MSB     0x06
#define IST8310_ADDR_DATA_OUT_Z_LSB     0x07
#define IST8310_ADDR_DATA_OUT_Z_MSB     0x08

#define IST8310_ADDR_STAT2              0x09
#define IST8310_STAT2_INT_SHFITS       3
#define IST8310_STAT2_INT              (1 << IST8310_STAT2_INT_SHFITS)

#define IST8310_ADDR_CTRL1              0x0a
#define IST8310_CTRL1_MODE_SHFITS      0
#define IST8310_CTRL1_MODE_STDBY       (0 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_SINGLE      (1 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_8HZ  (0x2 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_10HZ  (0x3 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_20HZ  (0x5 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_100HZ  (0x6 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_50HZ  (0x7 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_0_5HZ  (0x9 << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_1HZ  (0xA << IST8310_CTRL1_MODE_SHFITS)
#define IST8310_CTRL1_MODE_CONT_200HZ  (0xB << IST8310_CTRL1_MODE_SHFITS)

#define IST8310_ADDR_CTRL2              0x0b
#define IST8310_CTRL2_SRST_SHFITS      0   /* Begin POR (auto cleared) */
#define IST8310_CTRL2_SRST             (1 << IST8310_CTRL2_SRST_SHFITS)
#define IST8310_CTRL2_DRP_SHIFTS       2
#define IST8310_CTRL2_DRP              (1 << IST8310_CTRL2_DRP_SHIFTS)
#define IST8310_CTRL2_DREN_SHIFTS      3
#define IST8310_CTRL2_DREN             (1 << IST8310_CTRL2_DREN_SHIFTS)

#define IST8310_ADDR_CTRL3				0x41
#define IST8310_CTRL3_SAMPLEAVG_16		0x24	/* Sample Averaging 16 */
#define IST8310_CTRL3_SAMPLEAVG_8		0x1b	/* Sample Averaging 8 */
#define IST8310_CTRL3_SAMPLEAVG_4		0x12	/* Sample Averaging 4 */
#define IST8310_CTRL3_SAMPLEAVG_2		0x09	/* Sample Averaging 2 */

#define IST8310_ADDR_CTRL4				0x42
#define IST8310_CTRL4_SRPD				0xC0	/* Set Reset Pulse Duration */

#define IST8310_ADDR_STR                0x0c
#define IST8310_STR_SELF_TEST_SHFITS   6
#define IST8310_STR_SELF_TEST_ON       (1 << IST8310_STR_SELF_TEST_SHFITS)
#define IST8310_STR_SELF_TEST_OFF      (0 << IST8310_STR_SELF_TEST_SHFITS)

#define IST8310_ADDR_Y11_Low			0x9c
#define IST8310_ADDR_Y11_High			0x9d
#define IST8310_ADDR_Y12_Low			0x9e
#define IST8310_ADDR_Y12_High			0x9f
#define IST8310_ADDR_Y13_Low			0xa0
#define IST8310_ADDR_Y13_High			0xa1
#define IST8310_ADDR_Y21_Low			0xa2
#define IST8310_ADDR_Y21_High			0xa3
#define IST8310_ADDR_Y22_Low			0xa4
#define IST8310_ADDR_Y22_High			0xa5
#define IST8310_ADDR_Y23_Low			0xa6
#define IST8310_ADDR_Y23_High			0xa7
#define IST8310_ADDR_Y31_Low			0xa8
#define IST8310_ADDR_Y31_High			0xa9
#define IST8310_ADDR_Y32_Low			0xaa
#define IST8310_ADDR_Y32_High			0xab
#define IST8310_ADDR_Y33_Low			0xac
#define IST8310_ADDR_Y33_High			0xad

#define IST8310_ADDR_TEMPL              0x1c
#define IST8310_ADDR_TEMPH              0x1d

#define IST8310_DEFAULT_TIMEOUT			100

typedef struct{
	uint8_t x[2];
	uint8_t y[2];
	uint8_t z[2];
} IST8310_buf_t;

typedef struct{
	int16_t x, y, z;
} IST8310_count_t;

typedef struct{
	I2C_HandleTypeDef *hi2c;
	IST8310_buf_t buf;
	IST8310_count_t count;
	float raw[3];
}IST8310_t;

/* internal instance */
IST8310_t ist8310;

void IST8310(I2C_HandleTypeDef *phi2c);
void IST8310_updataIT();
void IST8310_i2cRxCpltCallback();
/**
 * Write a register.
 *
 * @param reg       The register to write.
 * @param val       The value to write.
 * @return      OK on write success.
 */
void IST8310_write_reg(uint8_t reg, uint8_t val);

/**
 * Write to a register block.
 *
 * @param address   The register address to write to.
 * @param data      The buffer to write from.
 * @param count     The number of bytes to write.
 * @return      OK on write success.
 */
void IST8310_write(uint8_t address, uint8_t *data, uint8_t count);

/**
 * Read a register.
 *
 * @param reg       The register to read.
 * @param val       The value read.
 * @return      OK on read success.
 */
void IST8310_read_reg(uint8_t reg, uint8_t* val);

/**
 * read register block.
 *
 * @param address   The register address to read from.
 * @param data      The buffer to read into.
 * @param count     The number of bytes to read.
 * @return      OK on write success.
 */
void IST8310_read(uint8_t address, uint8_t *data, uint8_t count);

void IST8310_reset();


#ifdef __cplusplus
}
#endif
#endif /* IST8310_H_ */
