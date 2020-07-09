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

#define RAD_TO_DEG 57.295779513082320876798154814105
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
	int16_t sumAcX = 0;
	int16_t sumAcY = 0;
	int16_t sumAcZ = 0;
	int16_t sumGyX = 0;
	int16_t sumGyY = 0;
	int16_t sumGyZ = 0;
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
		 HAL_Delay(100);
	}
	baseAcX = sumAcX / 10.0;
	baseAcY = sumAcY / 10.0;
	baseAcZ = sumAcZ / 10.0;
	baseGyX = sumGyX / 10.0;
	baseGyY = sumGyY / 10.0;
	baseGyZ = sumGyZ / 10.0;
//	printf("base : \r\n%d, %d, %d\r\n", baseGyX, baseGyY, baseGyZ);
}
//void MPU6050::CalibrateGyro(uint8_t Loops) // Fine tune after setting offsets with less Loops.
//{
//	  float kP = 0.3;
//	  float kI = 90;
//	  float x;
//	  x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
//	  kP *= x;
//	  kI *= x;
//
//	  PID( 0x43,  kP, kI,  Loops);
//}
//void MPU6050::CalibrateAccel(uint8_t Loops)// Fine tune after setting offsets with less Loops.
//{
//	float kP = 0.3;
//	float kI = 20;
//	float x;
//	x = (100 - map(Loops, 1, 5, 20, 0)) * .01;
//	kP *= x;
//	kI *= x;
//	PID( 0x3B, kP, kI,  Loops);
//}
//void MPU6050::PID(uint8_t ReadAddress, float kP,float kI, uint8_t Loops) // Does the math
//{
//	uint8_t SaveAddress = (ReadAddress == 0x3B)?((getDeviceID() < 0x38 )? 0x06:0x77):0x13;
//
//	int16_t  Data;
//	float Reading;
//	int16_t BitZero[3];
//	uint8_t shift =(SaveAddress == 0x77)?3:2;
//	float Error, PTerm, ITerm[3];
//	int16_t eSample;
//	uint32_t eSum ;
//	printf(">");
//	for (int i = 0; i < 3; i++) {
//		i2c.readWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
//		Reading = Data;
//		if(SaveAddress != 0x13){
//			BitZero[i] = Data & 1;										 // Capture Bit Zero to properly handle Accelerometer calibration
//			ITerm[i] = ((float)Reading) * 8;
//			} else {
//			ITerm[i] = Reading * 4;
//		}
//	}
//	for (int L = 0; L < Loops; L++) {
//		eSample = 0;
//		for (int c = 0; c < 100; c++) {// 100 PI Calculations
//			eSum = 0;
//			for (int i = 0; i < 3; i++) {
//				i2c.readWords(devAddr, ReadAddress + (i * 2), 1, (uint16_t *)&Data); // reads 1 or more 16 bit integers (Word)
//				Reading = Data;
//				if ((ReadAddress == 0x3B)&&(i == 2)) Reading -= 16384;	//remove Gravity
//				Error = -Reading;
//				eSum += abs(Reading);
//				PTerm = kP * Error;
//				ITerm[i] += (Error * 0.001) * kI;				// Integral term 1000 Calculations a second = 0.001
//				if(SaveAddress != 0x13){
//					Data = round((PTerm + ITerm[i] ) / 8);		//Compute PID Output
//					Data = ((Data)&0xFFFE) |BitZero[i];			// Insert Bit0 Saved at beginning
//				} else Data = round((PTerm + ITerm[i] ) / 4);	//Compute PID Output
//				i2c.writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
//			}
//			if((c == 99) && eSum > 1000){						// Error is still to great to continue
//				c = 0;
//				printf("*");
//			}
//			if((eSum * ((ReadAddress == 0x3B)?.05: 1)) < 5) eSample++;	// Successfully found offsets prepare to  advance
//			if((eSum < 100) && (c > 10) && (eSample >= 10)) break;		// Advance to next Loop
//			HAL_Delay(1);
//		}
//		printf(".");
//		kP *= .75;
//		kI *= .75;
//		for (int i = 0; i < 3; i++){
//			if(SaveAddress != 0x13) {
//				Data = round((ITerm[i] ) / 8);		//Compute PID Output
//				Data = ((Data)&0xFFFE) |BitZero[i];	// Insert Bit0 Saved at beginning
//			} else Data = round((ITerm[i]) / 4);
//			i2c.writeWords(devAddr, SaveAddress + (i * shift), 1, (uint16_t *)&Data);
//		}
//	}
////	resetFIFO();
////	resetDMP();
//}
//void MPU6050::PrintActiveOffsets()
//{
//	uint8_t AOffsetRegister = (getDeviceID() < 0x38 )? MPU6050_RA_XA_OFFS_H:0x77;
//	int16_t Data[3];
//	printf("X Accel  Y Accel  Z Accel   X Gyro   Y Gyro   Z Gyro\r\n");
//	if(AOffsetRegister == 0x06)	i2c.readWords(devAddr, AOffsetRegister, 3, (uint16_t *)Data);
//	else {
//		i2c.readWords(devAddr, AOffsetRegister, 1, (uint16_t *)Data);
//		i2c.readWords(devAddr, AOffsetRegister+3, 1, (uint16_t *)Data+1);
//		i2c.readWords(devAddr, AOffsetRegister+6, 1, (uint16_t *)Data+2);
//	}
//	//	A_OFFSET_H_READ_A_OFFS(Data);
//	printf("%d, %d, %d, ", Data[0], Data[1], Data[2]);
////	printfloatx("", Data[0], 5, 0, ",  ");
////	printfloatx("", Data[1], 5, 0, ",  ");
////	printfloatx("", Data[2], 5, 0, ",  ");
//	i2c.readWords(devAddr, 0x13, 3, (uint16_t *)Data);
//	printf("%d, %d, %d\r\n", Data[3], Data[4], Data[5]);
//	//	XG_OFFSET_H_READ_OFFS_USR(Data);
////	printfloatx("", Data[0], 5, 0, ",  ");
////	printfloatx("", Data[1], 5, 0, ",  ");
////	printfloatx("", Data[2], 5, 0, "\n");
//}


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


//uint8_t MPU6050::Init(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct) {
//    uint8_t check;
//    uint8_t Data;
//
//    // check device ID WHO_AM_I
//    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);
//    printf("%d\r\n", I2Cx->State);
//    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
//    {
//        // power management register 0X6B we should write all 0's to wake the sensor up
//    	/*
//        Data = 0;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);
//		*/
//    	Data = MPU6050_CLOCK_PLL_XGYRO;
//    	HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 2, &Data, 3, i2c_timeout);
//
//        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
//        Data = 0x07;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);
//
//        // Set accelerometer configuration in ACCEL_CONFIG Register
//        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
//        Data = 0x00;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);
//
//        // Set Gyroscopic configuration in GYRO_CONFIG Register
//        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
//        Data = 0x00;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
//
//        // can't sleep
//        Data = MPU6050_PWR1_CLKSEL_BIT;
//        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);
//
//
//        pMPU6050 = DataStruct;
//        return 0;
//    }
//    HAL_Delay(100);
//    return 1;
//}
//
//
//void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct) {
//    uint8_t Rec_Data[6];
//
//    // Read 6 BYTES of data starting from ACCEL_XOUT_H register
//
//    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);
//
//    DataStruct->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
//    DataStruct->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
//    DataStruct->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
//
//    /*** convert the RAW values into acceleration in 'g'
//         we have to divide according to the Full scale value set in FS_SEL
//         I have configured FS_SEL = 0. So I am dividing by 16384.0
//         for more details check ACCEL_CONFIG Register              ****/
//
//    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
//    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
//    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
//}
//
//
//void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct) {
//    uint8_t Rec_Data[6];
//
//    // Read 6 BYTES of data starting from GYRO_XOUT_H register
//
//    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);
//
//    DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
//    DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
//    DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
//
//    /*** convert the RAW values into dps (�/s)
//         we have to divide according to the Full scale value set in FS_SEL
//         I have configured FS_SEL = 0. So I am dividing by 131.0
//         for more details check GYRO_CONFIG Register              ****/
//
//    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
//    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
//    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;
//}
//
//void MPU6050_Read_Temp(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct) {
//    uint8_t Rec_Data[2];
//    int16_t temp;
//
//    // Read 2 BYTES of data starting from TEMP_OUT_H_REG register
//
//    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, TEMP_OUT_H_REG, 1, Rec_Data, 2, i2c_timeout);
//
//    temp = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
//    DataStruct->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
//}
//
//void MPU6050_Read_All(I2C_HandleTypeDef *I2Cx) {
//    //uint8_t Rec_Data[14];
//    //int16_t temp;
//
//    // Read 14 BYTES of data starting from ACCEL_XOUT_H register
//
//    //HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14, i2c_timeout);
//	HAL_I2C_Mem_Read_IT(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14);
//
//    /*
//    pMPU6050->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
//    pMPU6050->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
//    pMPU6050->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
//    temp = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);
//    pMPU6050->Gyro_X_RAW = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
//    pMPU6050->Gyro_Y_RAW = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);
//    pMPU6050->Gyro_Z_RAW = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]);
//
//    pMPU6050->Ax = pMPU6050->Accel_X_RAW / 16384.0;
//    pMPU6050->Ay = pMPU6050->Accel_Y_RAW / 16384.0;
//    pMPU6050->Az = pMPU6050->Accel_Z_RAW / Accel_Z_corrector;
//    pMPU6050->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
//    pMPU6050->Gx = pMPU6050->Gyro_X_RAW / 131.0;
//    pMPU6050->Gy = pMPU6050->Gyro_Y_RAW / 131.0;
//    pMPU6050->Gz = pMPU6050->Gyro_Z_RAW / 131.0;
//
//    // Kalman angle solve
//    double dt = (double) (HAL_GetTick() - timer) / 1000;
//    timer = HAL_GetTick();
//    double roll;
//    double roll_sqrt = sqrt(
//            pMPU6050->Accel_X_RAW * pMPU6050->Accel_X_RAW + pMPU6050->Accel_Z_RAW * pMPU6050->Accel_Z_RAW);
//    if (roll_sqrt != 0.0) {
//        roll = atan(pMPU6050->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
//    } else {
//        roll = 0.0;
//    }
//    double pitch = atan2(-pMPU6050->Accel_X_RAW, pMPU6050->Accel_Z_RAW) * RAD_TO_DEG;
//    if ((pitch < -90 && pMPU6050->KalmanAngleY > 90) || (pitch > 90 && pMPU6050->KalmanAngleY < -90)) {
//        KalmanY.angle = pitch;
//        pMPU6050->KalmanAngleY = pitch;
//    } else {
//        pMPU6050->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, pMPU6050->Gy, dt);
//    }
//    if (fabs(pMPU6050->KalmanAngleY) > 90)
//        pMPU6050->Gx = -pMPU6050->Gx;
//    pMPU6050->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, pMPU6050->Gy, dt);
//    */
//}
//
//double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt) {
//    double rate = newRate - Kalman->bias;
//    Kalman->angle += dt * rate;
//
//    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
//    Kalman->P[0][1] -= dt * Kalman->P[1][1];
//    Kalman->P[1][0] -= dt * Kalman->P[1][1];
//    Kalman->P[1][1] += Kalman->Q_bias * dt;
//
//    double S = Kalman->P[0][0] + Kalman->R_measure;
//    double K[2];
//    K[0] = Kalman->P[0][0] / S;
//    K[1] = Kalman->P[1][0] / S;
//
//    double y = newAngle - Kalman->angle;
//    Kalman->angle += K[0] * y;
//    Kalman->bias += K[1] * y;
//
//    double P00_temp = Kalman->P[0][0];
//    double P01_temp = Kalman->P[0][1];
//
//    Kalman->P[0][0] -= K[0] * P00_temp;
//    Kalman->P[0][1] -= K[0] * P01_temp;
//    Kalman->P[1][0] -= K[1] * P00_temp;
//    Kalman->P[1][1] -= K[1] * P01_temp;
//
//    return Kalman->angle;
//};
//
//void MPU6050_update()
//{
//	int16_t temp;
//    pMPU6050->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
//    pMPU6050->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
//    pMPU6050->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
//    temp = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);
//    pMPU6050->Gyro_X_RAW = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
//    pMPU6050->Gyro_Y_RAW = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);
//    pMPU6050->Gyro_Z_RAW = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]);
//
//    pMPU6050->Ax = pMPU6050->Accel_X_RAW / 16384.0;
//    pMPU6050->Ay = pMPU6050->Accel_Y_RAW / 16384.0;
//    pMPU6050->Az = pMPU6050->Accel_Z_RAW / Accel_Z_corrector;
//    pMPU6050->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
//    pMPU6050->Gx = pMPU6050->Gyro_X_RAW / 131.0;
//    pMPU6050->Gy = pMPU6050->Gyro_Y_RAW / 131.0;
//    pMPU6050->Gz = pMPU6050->Gyro_Z_RAW / 131.0;
//
//    // Kalman angle solve
//    double dt = (double) (HAL_GetTick() - timer) / 1000;
//    timer = HAL_GetTick();
//    double roll;
//    double roll_sqrt = sqrt(
//            pMPU6050->Accel_X_RAW * pMPU6050->Accel_X_RAW + pMPU6050->Accel_Z_RAW * pMPU6050->Accel_Z_RAW);
//    if (roll_sqrt != 0.0) {
//        roll = atan(pMPU6050->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
//    } else {
//        roll = 0.0;
//    }
//    double pitch = atan2(-pMPU6050->Accel_X_RAW, pMPU6050->Accel_Z_RAW) * RAD_TO_DEG;
//    if ((pitch < -90 && pMPU6050->KalmanAngleY > 90) || (pitch > 90 && pMPU6050->KalmanAngleY < -90)) {
//        KalmanY.angle = pitch;
//        pMPU6050->KalmanAngleY = pitch;
//    } else {
//        pMPU6050->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, pMPU6050->Gy, dt);
//    }
//    if (fabs(pMPU6050->KalmanAngleY) > 90)
//        pMPU6050->Gx = -pMPU6050->Gx;
//    pMPU6050->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, pMPU6050->Gy, dt);
//
//    //printf("%f %f, %d\r\n", pMPU6050->KalmanAngleX, pMPU6050->KalmanAngleY, hi2c1.State);
//}
