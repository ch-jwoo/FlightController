/*
 * mpu6050.c
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :  leech001@gmail.com
 */

/*
 * |---------------------------------------------------------------------------------
 * | Copyright (C) Bulanov Konstantin,2019
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |
 * | Kalman filter algorithm used from https://github.com/TKJElectronics/KalmanFilter
 * |---------------------------------------------------------------------------------
 */

#include <math.h>
#include <cstdio>
#include "main.h"
#include "mpu6050.h"

//#define RAD_TO_DEG 57.295779513082320876798154814105
#define MPU_MAX_VALUE 16384

//Kalman_t KalmanX = {
//        .Q_angle = 0.001f,
//        .Q_bias = 0.003f,
//        .R_measure = 0.03f
//};
//
//Kalman_t KalmanY = {
//        .Q_angle = 0.001f,
//        .Q_bias = 0.003f,
//        .R_measure = 0.03f,
//};


float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
//float invSqrt(float x) {
//	float halfx = 0.5f * x;
//	float y = x;
//	long i = *(long*)&y;
//	i = 0x5f3759df - (i>>1);
//	y = *(float*)&i;
//	y = y * (1.5f - (halfx * y * y));
//	return y;
//}

MPU6050::MPU6050(I2C_HandleTypeDef *I2Cx, uint8_t address)
: i2c(I2Cx)
, devAddr(address)
{
}

void MPU6050::initialize(){
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
    setDLPFMode(2);
    setRate(7);
	CalibAccelGyro();
}
bool MPU6050::testConnection(){
	return getDeviceID() == 0x34;
}
void MPU6050::updateRawMotion(){
    i2c.readBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 14, buffer);
    rawAx = (((int16_t)buffer[0]) << 8) | buffer[1];
    rawAy = (((int16_t)buffer[2]) << 8) | buffer[3];
    rawAz = (((int16_t)buffer[4]) << 8) | buffer[5];
    rawGx = (((int16_t)buffer[8]) << 8) | buffer[9];
    rawGy = (((int16_t)buffer[10]) << 8) | buffer[11];
    rawGz = (((int16_t)buffer[12]) << 8) | buffer[13];
}

// initialize function
void MPU6050::setClockSource(uint8_t source) {
    i2c.writeBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}
void MPU6050::setFullScaleGyroRange(uint8_t range) {
    i2c.writeBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}
void MPU6050::setFullScaleAccelRange(uint8_t range) {
    i2c.writeBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}
void MPU6050::setSleepEnabled(bool enabled) {
    i2c.writeBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

// calibration
void MPU6050::CalibAccelGyro(){
	int32_t sumAcX = 0;
	int32_t sumAcY = 0;
	int32_t sumAcZ = 0;
	int32_t sumGyX = 0;
	int32_t sumGyY = 0;
	int32_t sumGyZ = 0;
    for(int i=0; i<10; i++)
	{
		 updateRawMotion();
		 HAL_Delay(100);
	}
//	printf("raw : \r\n", baseGyX, baseGyY, baseGyZ);
    for(int i=0; i<10; i++)
	{
//    	printf("%d, %d, %d\r\n", rawGx, rawGy, rawGz);
		 updateRawMotion();
		 sumAcX += rawAx;
		 sumAcY += rawAy;
		 sumAcZ += rawAz;
		 sumGyX += rawGx;
		 sumGyY += rawGy;
		 sumGyZ += rawGz;
//		printf("%d\r\n", rawAz);
		 HAL_Delay(100);
	}
	baseAcX = sumAcX / 10.0;
	baseAcY = sumAcY / 10.0;
	baseAcZ = sumAcZ / 10.0;
	baseGyX = sumGyX / 10.0;
	baseGyY = sumGyY / 10.0;
	baseGyZ = sumGyZ / 10.0;
//	printf("%d\r\n", baseAcZ);
}


uint8_t MPU6050::getDeviceID() {
    i2c.readBits(devAddr, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, buffer);
    return buffer[0];
}

uint8_t MPU6050::getDLPFMode() {
    i2c.readBits(devAddr, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, buffer);
    return buffer[0];
}

void MPU6050::setDLPFMode(uint8_t mode) {
    i2c.writeBits(devAddr, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, mode);
}

void MPU6050::setRate(uint8_t rate) {
    i2c.writeByte(devAddr, MPU6050_RA_SMPLRT_DIV, rate);
}

//calibration

void MPU6050::CalibrateGyro(uint8_t Loops ) {
  double kP = 0.3;
  double kI = 90;
  float x;
  x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
  kP *= x;
  kI *= x;

  PID( 0x43,  kP, kI,  Loops);
}

/**
  @brief      Fully calibrate Accel from ZERO in about 6-7 Loops 600-700 readings
*/
void MPU6050::CalibrateAccel(uint8_t Loops ) {

//	float kP = 0.3;
	float kP = 0.5;
	float kI = 20;
	float x;
	x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
	kP *= x;
	kI *= x;
	PID( 0x3B, kP, kI,  Loops);
}

void MPU6050::PID(uint8_t ReadAddress, float kP,float kI, uint8_t Loops){
	uint8_t SaveAddress = (ReadAddress == 0x3B)?((getDeviceID() < 0x38 )? 0x06:0x77):0x13;

	int16_t  Data;
	float Reading;
	int16_t BitZero[3];
	uint8_t shift =(SaveAddress == 0x77)?3:2;
	float Error, PTerm, ITerm[3];
	int16_t eSample;
	uint32_t eSum ;
	printf(">");
	for (int i = 0; i < 3; i++) {
		i2c.readWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
		Reading = Data;
		if(SaveAddress != 0x13){
			BitZero[i] = Data & 1;										 // Capture Bit Zero to properly handle Accelerometer calibration
			ITerm[i] = ((float)Reading) * 8;
			} else {
			ITerm[i] = Reading * 4;
		}
	}
	for (int L = 0; L < Loops; L++) {
		eSample = 0;
		for (int c = 0; c < 100; c++) {// 100 PI Calculations
			eSum = 0;
			for (int i = 0; i < 3; i++) {
				i2c.readWords(devAddr, ReadAddress + (i * 2), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
				Reading = Data;
				if ((ReadAddress == 0x3B)&&(i == 2)) Reading -= 16384;	//remove Gravity
				Error = -Reading;
				eSum += abs(Reading);
				PTerm = kP * Error;
				ITerm[i] += (Error * 0.001) * kI;				// Integral term 1000 Calculations a second = 0.001
				if(SaveAddress != 0x13){
					Data = round((PTerm + ITerm[i] ) / 8);		//Compute PID Output
					Data = ((Data)&0xFFFE) |BitZero[i];			// Insert Bit0 Saved at beginning
				} else Data = round((PTerm + ITerm[i] ) / 4);	//Compute PID Output
				i2c.writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
			}
			if((c == 99) && eSum > 1000){						// Error is still to great to continue
				c = 0;
				printf("*");
			}
			if((eSum * ((ReadAddress == 0x3B)?.05: 1)) < 5) eSample++;	// Successfully found offsets prepare to  advance
			if((eSum < 100) && (c > 10) && (eSample >= 10)) break;		// Advance to next Loop
			HAL_Delay(1);
		}
		printf(".");
		kP *= .75;
		kI *= .75;
		for (int i = 0; i < 3; i++){
			if(SaveAddress != 0x13) {
				Data = round((ITerm[i] ) / 8);		//Compute PID Output
				Data = ((Data)&0xFFFE) |BitZero[i];	// Insert Bit0 Saved at beginning
			} else Data = round((ITerm[i]) / 4);
			i2c.writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
		}
	}
	printf("end\r\n");
	resetFIFO();
	reset();
}

void MPU6050::resetFIFO() {
    i2c.writeBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_FIFO_RESET_BIT, true);
}
void MPU6050::reset() {
    i2c.writeBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_DEVICE_RESET_BIT, true);
}
// XA_OFFS_* registers

int16_t MPU6050::getXAccelOffset() {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_XA_OFFS_H:0x77); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setXAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_XA_OFFS_H:0x77); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.writeWord(devAddr, SaveAddress, offset);
}

// YA_OFFS_* register

int16_t MPU6050::getYAccelOffset() {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_YA_OFFS_H:0x7A); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setYAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_YA_OFFS_H:0x7A); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.writeWord(devAddr, SaveAddress, offset);
}

// ZA_OFFS_* register

int16_t MPU6050::getZAccelOffset() {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_ZA_OFFS_H:0x7D); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.readBytes(devAddr, SaveAddress, 2, buffer);
	return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setZAccelOffset(int16_t offset) {
	uint8_t SaveAddress = ((getDeviceID() < 0x38 )? MPU6050_RA_ZA_OFFS_H:0x7D); // MPU6050,MPU9150 Vs MPU6500,MPU9250
	i2c.writeWord(devAddr, SaveAddress, offset);
}

// XG_OFFS_USR* registers

int16_t MPU6050::getXGyroOffset() {
    i2c.readBytes(devAddr, MPU6050_RA_XG_OFFS_USRH, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setXGyroOffset(int16_t offset) {
    i2c.writeWord(devAddr, MPU6050_RA_XG_OFFS_USRH, offset);
}

// YG_OFFS_USR* register

int16_t MPU6050::getYGyroOffset() {
    i2c.readBytes(devAddr, MPU6050_RA_YG_OFFS_USRH, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setYGyroOffset(int16_t offset) {
    i2c.writeWord(devAddr, MPU6050_RA_YG_OFFS_USRH, offset);
}

// ZG_OFFS_USR* register

int16_t MPU6050::getZGyroOffset() {
    i2c.readBytes(devAddr, MPU6050_RA_ZG_OFFS_USRH, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
void MPU6050::setZGyroOffset(int16_t offset) {
    i2c.writeWord(devAddr, MPU6050_RA_ZG_OFFS_USRH, offset);
}
void MPU6050::PrintActiveOffsets() {
	uint8_t AOffsetRegister = (getDeviceID() < 0x38 )? MPU6050_RA_XA_OFFS_H:0x77;
	int16_t Data[3];
	//printf(F("Offset Register 0x"));
	//printf(AOffsetRegister>>4,HEX);printf(AOffsetRegister&0x0F,HEX);
	printf("\n//           X Accel  Y Accel  Z Accel   X Gyro   Y Gyro   Z Gyro\n//OFFSETS   ");
	if(AOffsetRegister == 0x06)	i2c.readWords(devAddr, AOffsetRegister, 3, (uint16_t *)Data);
	else {
		i2c.readWords(devAddr, AOffsetRegister, 1, (uint16_t *)Data);
		i2c.readWords(devAddr, AOffsetRegister+3, 1, (uint16_t *)Data+1);
		i2c.readWords(devAddr, AOffsetRegister+6, 1, (uint16_t *)Data+2);
	}
	//	A_OFFSET_H_READ_A_OFFS(Data);
	printf("%d, %d, %d, ", (float)(Data[0]), float(Data[1]), float(Data[2]));
	i2c.readWords(devAddr, 0x13, 3, (uint16_t *)Data);
	//	XG_OFFSET_H_READ_OFFS_USR(Data);
	printf("%f, %f, %f\r\n", (float)(Data[0]), (float)(Data[1]), float(Data[2]));
}
