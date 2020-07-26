/*
 * MPU9250.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */


#include "MPU9250.h"
#include "stdio.h"
#include "i2c.h"
#include "cmsis_os.h"
#include "math.h"

#define MPU9250_I2C mpu9250.hi2c

void RTOS_MPU9250(){
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5;

	MPU9250(&hi2c1);

	xLastWakeTime = xTaskGetTickCount();
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		MPU9250_updateDMA();
//		printf("%d %d %d\r\n", (int)(mpu9250.mag[0]), (int)(mpu9250.mag[1]), (int)(mpu9250.mag[2]));
	}
}

void MPU9250(I2C_HandleTypeDef *hi2c){
	//configuration
	MPU9250_I2C = hi2c;
	mpu9250.Ascale = MPU9250_AFS_8G;
	mpu9250.Gscale = MPU9250_GFS_2000DPS;
	mpu9250.Mscale = MPU9250_MFS_14BITS;
	mpu9250.Mmode = MPU9250_M_100HZ;

	// set to 0
	mpu9250.aRes = 0; mpu9250.gRes = 0; mpu9250.mRes = 0;
	memset(mpu9250.accelCount, 0, sizeof(mpu9250.accelCount));
	memset(mpu9250.gyroCount, 0, sizeof(mpu9250.gyroCount));
	memset(mpu9250.magCount, 0, sizeof(mpu9250.magCount));
	mpu9250.tmpCount = 0;
	memset(mpu9250.magBias, 0, sizeof(mpu9250.magBias));
	memset(mpu9250.accel, 0, sizeof(mpu9250.accel));
	memset(mpu9250.gyro, 0, sizeof(mpu9250.gyro));
	memset(mpu9250.mag, 0, sizeof(mpu9250.mag));
	mpu9250.tmp = 0;
	memset(mpu9250.q, 0, sizeof(mpu9250.q)); mpu9250.q[0] = 1.0;		// set initial quaternion to (1, 0, 0, 0)
	mpu9250.roll = 0; mpu9250.pitch = 0; mpu9250.yaw = 0;
	memset(mpu9250.MPU9250_buffer, 0, sizeof(mpu9250.MPU9250_buffer));
	memset(mpu9250.AK8963_buffer, 0, sizeof(mpu9250.AK8963_buffer));
	mpu9250.MPU9250_lastUpdate = 0, mpu9250.AK8963_lastUpdate = 0;
	mpu9250.MPU9250_hz = 0; mpu9250.AK8963_hz = 0; mpu9250.MPU9250_hzCnt = 0; mpu9250.AK8963_hzCnt = 0;
	mpu9250.dmaFlag = MPU9250_dmaIdle;

	mpu9250.magBias[0] = 280.0f;
	mpu9250.magBias[1] = 285.0f;
	mpu9250.magBias[2] = 330.0f;

	MPU9250_getMres();
	MPU9250_getGres();
	MPU9250_getAres();

	MPU9250_resetMPU9250();
	MPU9250_calibrateMPU9250();

	MPU9250_initMPU9250();	// calculate ay, ac bias
	MPU9250_initAK8963();	//
}

void MPU9250_calHz(){
	if(xTaskGetTickCount() - mpu9250.hz_lastUpdate > MPU9250_HZ_CHECK_TICK){
		mpu9250.MPU9250_hz = mpu9250.MPU9250_hzCnt;
		mpu9250.AK8963_hz = mpu9250.AK8963_hzCnt;
		mpu9250.MPU9250_hzCnt = 0;
		mpu9250.AK8963_hzCnt = 0;
		mpu9250.hz_lastUpdate = xTaskGetTickCount();
	}
}

void MPU9250_updateDMA(){
	MPU9250_calHz();
	if(mpu9250.dmaFlag != MPU9250_dmaIdle) return;
	mpu9250.dmaFlag = MPU9250_dmaMPU9250;
	HAL_I2C_Mem_Read_DMA(MPU9250_I2C, MPU9250_ADDRESS, ACCEL_XOUT_H, 1, mpu9250.MPU9250_buffer, 14);
}


void MPU9250_rxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance != MPU9250_I2C->Instance) return;

	if(mpu9250.dmaFlag == MPU9250_dmaMPU9250){
		if(MPU9250_calRawData() != MPU9250_Fail){
			MPU9250_calCalibValue();

			if( mpu9250.AK8963_hz != 0 ) MPU9250_madgwickAHRSupdate();
			else MPU9250_madgwickAHRSupdateIMU();
			MPU9250_calRPY();

			mpu9250.MPU9250_lastUpdate = xTaskGetTickCount();
			mpu9250.MPU9250_hzCnt++;
		}
		if(xTaskGetTickCount() - mpu9250.AK8963_lastUpdate > AK8963_UPDATE_TICK){
			mpu9250.dmaFlag = MPU9250_dmaAK8963;
			HAL_I2C_Mem_Read_DMA(MPU9250_I2C, AK8963_ADDRESS, AK8963_XOUT_L, 1, mpu9250.AK8963_buffer, 7);
			mpu9250.AK8963_lastUpdate = xTaskGetTickCount();
			return;
		}
	}
	else if(mpu9250.dmaFlag == MPU9250_dmaAK8963){
			if(AK8963_calRawData() == MPU9250_Success){
				AK8963_calCalibValue();
			    mpu9250.AK8963_hzCnt++;
			}
	}
	mpu9250.dmaFlag = MPU9250_dmaIdle;
}

MPU9250_Result_t MPU9250_calRawData(){
	// accel axis reverse
	mpu9250.accelCount[0] = -((((int16_t)mpu9250.MPU9250_buffer[0]) << 8) | mpu9250.MPU9250_buffer[1]);
	mpu9250.accelCount[1] = -((((int16_t)mpu9250.MPU9250_buffer[2]) << 8) | mpu9250.MPU9250_buffer[3]);
	mpu9250.accelCount[2] = -((((int16_t)mpu9250.MPU9250_buffer[4]) << 8) | mpu9250.MPU9250_buffer[5]);
	mpu9250.tmpCount = (int16_t) (mpu9250.MPU9250_buffer[6] << 8 | mpu9250.MPU9250_buffer[7]);
	mpu9250.gyroCount[0] = (((int16_t)mpu9250.MPU9250_buffer[8]) << 8) | mpu9250.MPU9250_buffer[9];
	mpu9250.gyroCount[1] = (((int16_t)mpu9250.MPU9250_buffer[10]) << 8) | mpu9250.MPU9250_buffer[11];
	mpu9250.gyroCount[2] = (((int16_t)mpu9250.MPU9250_buffer[12]) << 8) | mpu9250.MPU9250_buffer[13];

	if(mpu9250.accelCount[0] == 0 && mpu9250.accelCount[1] == 0 && mpu9250.accelCount[2] == 0) return MPU9250_Fail;

	return MPU9250_Success;
}

void MPU9250_calCalibValue(){
//	MPU9250_a[0] = ((float)MPU9250_accelCount[0]*MPU9250_aRes - MPU9250_accelBias[0]);  // get actual g value, this depends on scale being set
//	MPU9250_a[1] = ((float)MPU9250_accelCount[1]*MPU9250_aRes - MPU9250_accelBias[1]);
//	MPU9250_a[2] = ((float)MPU9250_accelCount[2]*MPU9250_aRes - MPU9250_accelBias[2]);
//	// Calculate the gyro value into actual degrees per second
//	MPU9250_g[0] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[0]*MPU9250_gRes - MPU9250_gyroBias[0]);  // get actual gyro value, this depends on scale being set
//	MPU9250_g[1] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[1]*MPU9250_gRes - MPU9250_gyroBias[1]);
//	MPU9250_g[2] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[2]*MPU9250_gRes - MPU9250_gyroBias[2]);

	mpu9250.accel[0] = ((float)mpu9250.accelCount[0]*mpu9250.aRes);  // get actual g value, this depends on scale being set
	mpu9250.accel[1] = ((float)mpu9250.accelCount[1]*mpu9250.aRes);
	mpu9250.accel[2] = ((float)mpu9250.accelCount[2]*mpu9250.aRes);
	// Calculate the gyro value into actual degrees per second
	mpu9250.gyro[0] = MPU9250_DEG2RAD*((float)mpu9250.gyroCount[0]*mpu9250.gRes);  // get actual gyro value, this depends on scale being set
	mpu9250.gyro[1] = MPU9250_DEG2RAD*((float)mpu9250.gyroCount[1]*mpu9250.gRes);
	mpu9250.gyro[2] = MPU9250_DEG2RAD*((float)mpu9250.gyroCount[2]*mpu9250.gRes);
}

void MPU9250_madgwickAHRSupdateIMU(){
	static float beta = 0.1;

	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	float q0 = mpu9250.q[0];
	float q1 = mpu9250.q[1];
	float q2 = mpu9250.q[2];
	float q3 = mpu9250.q[3];

	float ax = mpu9250.accel[0];
	float ay = mpu9250.accel[1];
	float az = mpu9250.accel[2];

	float gx = mpu9250.gyro[0];
	float gy = mpu9250.gyro[1];
	float gz = mpu9250.gyro[2];

	float dt = (xTaskGetTickCount() - mpu9250.MPU9250_lastUpdate)/1000.0;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
//	if((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)) return 0;

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;


	// Integrate rate of change of quaternion to yield quaternion
//	q0 += qDot1 * (1.0f / sampleFreq);
//	q1 += qDot2 * (1.0f / sampleFreq);
//	q2 += qDot3 * (1.0f / sampleFreq);
//	q3 += qDot4 * (1.0f / sampleFreq);

	q0 += qDot1 * (dt);
	q1 += qDot2 * (dt);
	q2 += qDot3 * (dt);
	q3 += qDot4 * (dt);


	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;

	mpu9250.q[0] = q0;
	mpu9250.q[1] = q1;
	mpu9250.q[2] = q2;
	mpu9250.q[3] = q3;
}

void MPU9250_madgwickAHRSupdate()
{
	static float beta = 0.9; // ???
    float q1 = mpu9250.q[0], q2 = mpu9250.q[1], q3 = mpu9250.q[2], q4 = mpu9250.q[3];   // short name local variable for readability

	float recipNorm;;
    float hx, hy, _2bx, _2bz;
    float s1, s2, s3, s4;
    float qDot1, qDot2, qDot3, qDot4;

    // Auxiliary variables to avoid repeated arithmetic
    float _2q1mx;
    float _2q1my;
    float _2q1mz;
    float _2q2mx;
    float _4bx;
    float _4bz;
    float _2q1 = 2.0f * q1;
    float _2q2 = 2.0f * q2;
    float _2q3 = 2.0f * q3;
    float _2q4 = 2.0f * q4;
    float _2q1q3 = 2.0f * q1 * q3;
    float _2q3q4 = 2.0f * q3 * q4;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q1q4 = q1 * q4;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q2q4 = q2 * q4;
    float q3q3 = q3 * q3;
    float q3q4 = q3 * q4;
    float q4q4 = q4 * q4;

    //input value
    float ax = mpu9250.accel[0];
    float ay = mpu9250.accel[1];
    float az = mpu9250.accel[2];
    float gx = mpu9250.gyro[0];
    float gy = mpu9250.gyro[1];
    float gz = mpu9250.gyro[2];
    float mx = mpu9250.mag[0];
    float my = mpu9250.mag[1];
    float mz = mpu9250.mag[2];

    // Normalise accelerometer measurement
    recipNorm = invSqrt(ax * ax + ay * ay + az * az);
//    if (norm == 0.0f) return; // handle NaN
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;

    // Normalise magnetometer measurement
    recipNorm = invSqrt(mx * mx + my * my + mz * mz);
//    if (norm == 0.0f){	// handle NaN
//    	MPU9250_madgwickAHRSupdateIMU(); // not use magnetometer
//    	return;
//    }
    mx *= recipNorm;
    my *= recipNorm;
    mz *= recipNorm;

    // Reference direction of Earth's magnetic field
    _2q1mx = 2.0f * q1 * mx;
    _2q1my = 2.0f * q1 * my;
    _2q1mz = 2.0f * q1 * mz;
    _2q2mx = 2.0f * q2 * mx;
    hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
    hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
    _2bx = sqrt(hx * hx + hy * hy);
    _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
    _4bx = 2.0f * _2bx;
    _4bz = 2.0f * _2bz;

    // Gradient decent algorithm corrective step
    s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    recipNorm = invSqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
    s1 *= recipNorm;
    s2 *= recipNorm;
    s3 *= recipNorm;
    s4 *= recipNorm;

    // Compute rate of change of quaternion
    qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
    qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
    qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
    qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

    float deltat = (xTaskGetTickCount() - mpu9250.MPU9250_lastUpdate)/1000.0;
    // Integrate to yield quaternion
    q1 += qDot1 * deltat;
    q2 += qDot2 * deltat;
    q3 += qDot3 * deltat;
    q4 += qDot4 * deltat;
    recipNorm = invSqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
    mpu9250.q[0] = q1 * recipNorm;
    mpu9250.q[1] = q2 * recipNorm;
    mpu9250.q[2] = q3 * recipNorm;
    mpu9250.q[3] = q4 * recipNorm;
}

void MPU9250_calRPY(){
    mpu9250.roll = atan2(2.0f * (mpu9250.q[0] * mpu9250.q[1] + mpu9250.q[2] * mpu9250.q[3]), mpu9250.q[0] * mpu9250.q[0]- mpu9250.q[1] * mpu9250.q[1] - mpu9250.q[2] * mpu9250.q[2] + mpu9250.q[3] * mpu9250.q[3]);		//roll
    mpu9250.pitch = -asin(2.0f * (mpu9250.q[1] * mpu9250.q[3] - mpu9250.q[0] * mpu9250.q[2]));												//pitch
    mpu9250.yaw = atan2(2.0f * (mpu9250.q[1] * mpu9250.q[2] + mpu9250.q[0] * mpu9250.q[3]), mpu9250.q[0] * mpu9250.q[0] + mpu9250.q[1] * mpu9250.q[1] - mpu9250.q[2] * mpu9250.q[2] - mpu9250.q[3] * mpu9250.q[3]);		//yaw
}

MPU9250_Result_t AK8963_calRawData(){
	if(mpu9250.AK8963_buffer[6] & 0x08) return MPU9250_Fail; // Check if magnetic sensor overflow set, if not then report data

	mpu9250.magCount[1] = (int16_t)(((int16_t)mpu9250.AK8963_buffer[1] << 8) | mpu9250.AK8963_buffer[0]);  // Turn the MSB and LSB into a signed 16-bit value
	mpu9250.magCount[0] = (int16_t)(((int16_t)mpu9250.AK8963_buffer[3] << 8) | mpu9250.AK8963_buffer[2]);  // Data stored as little Endian
	mpu9250.magCount[2] = -(int16_t)(((int16_t)mpu9250.AK8963_buffer[5] << 8) | mpu9250.AK8963_buffer[4]);
	return MPU9250_Success;
}

void AK8963_calCalibValue(){
	// mag have different axis with acc, gyr -> ax = my, ay = mx, az = -mz
    mpu9250.mag[0] = (float)mpu9250.magCount[0]*mpu9250.mRes*mpu9250.magCalibration[0] - mpu9250.magBias[1];  // get actual magnetometer value, this depends on scale being set
    mpu9250.mag[1] = (float)mpu9250.magCount[1]*mpu9250.mRes*mpu9250.magCalibration[1] - mpu9250.magBias[0];
    mpu9250.mag[2] = ((float)mpu9250.magCount[2]*mpu9250.mRes*mpu9250.magCalibration[2] - mpu9250.magBias[2]);
}

uint16_t MPU9250_getHz(){return mpu9250.MPU9250_hz;}
float MPU9250_getAx(){return mpu9250.accel[0];}
float MPU9250_getYx(){return mpu9250.accel[1];}
float MPU9250_getZx(){return mpu9250.accel[2];}
float MPU9250_getGx(){return mpu9250.gyro[0];}
float MPU9250_getGy(){return mpu9250.gyro[1];}
float MPU9250_getGz(){return mpu9250.gyro[2];}


void MPU9250_getMres() {
	switch (mpu9250.Mscale)
	{
	// Possible magnetometer scales (and their register bit settings) are:
	// 14 bit resolution (0) and 16 bit resolution (1)
	case MPU9250_MFS_14BITS:
		  mpu9250.mRes = 10.0*4912.0/8190.0; // Proper scale to return milliGauss
		  break;
	case MPU9250_MFS_16BITS:
		  mpu9250.mRes = 10.0*4912.0/32760.0; // Proper scale to return milliGauss
		  break;
	}
}

void MPU9250_getGres() {
  switch (mpu9250.Gscale)
  {
    // Possible gyro scales (and their register bit settings) are:
    // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
    case MPU9250_GFS_250DPS:
    	  mpu9250.gRes = 250.0/32768.0;
          break;
    case MPU9250_GFS_500DPS:
    	  mpu9250.gRes = 500.0/32768.0;
          break;
    case MPU9250_GFS_1000DPS:
    	  mpu9250.gRes = 1000.0/32768.0;
          break;
    case MPU9250_GFS_2000DPS:
    	  mpu9250.gRes = 2000.0/32768.0;
          break;
  }
}


void MPU9250_getAres() {
  switch (mpu9250.Ascale)
  {
    // Possible accelerometer scales (and their register bit settings) are:
    // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
    case MPU9250_AFS_2G:
    	  mpu9250.aRes = 2.0/32768.0;
          break;
    case MPU9250_AFS_4G:
    	  mpu9250.aRes = 4.0/32768.0;
          break;
    case MPU9250_AFS_8G:
    	  mpu9250.aRes = 8.0/32768.0;
          break;
    case MPU9250_AFS_16G:
    	  mpu9250.aRes = 16.0/32768.0;
          break;
  }
}


void MPU9250_readAccelData()
{
    uint8_t rawData[6];  // x/y/z accel register data stored here
    MPU9250_readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
    mpu9250.accelCount[0] = -(int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
    mpu9250.accelCount[1] = -(int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
    mpu9250.accelCount[2] = -(int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
}

void MPU9250_readGyroData()
{
    uint8_t rawData[6];  // x/y/z gyro register data stored here
    MPU9250_readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
    mpu9250.gyroCount[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
    mpu9250.gyroCount[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
    mpu9250.gyroCount[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
}

void MPU9250_readMagData()
{
    uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
    if(MPU9250_readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // HAL_Delay for magnetometer data ready bit to be set
		MPU9250_readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
		uint8_t c = rawData[6]; // End data read by reading ST2 register
		if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
			mpu9250.magCount[1] = (int16_t)(((int16_t)rawData[1] << 8) | rawData[0]);  // Turn the MSB and LSB into a signed 16-bit value
			mpu9250.magCount[0] = (int16_t)(((int16_t)rawData[3] << 8) | rawData[2]);  // Data stored as little Endian
			mpu9250.magCount[2] = -(int16_t)(((int16_t)rawData[5] << 8) | rawData[4]);
        }
    }
}

uint16_t MPU9250_readTempData()
{
  uint8_t rawData[2];  // x/y/z gyro register data stored here
  MPU9250_readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array
  mpu9250.tmpCount = (int16_t)(((int16_t)rawData[0]) << 8 | rawData[1]) ;  // Turn the MSB and LSB into a 16-bit value
  return mpu9250.tmpCount;
}


void MPU9250_resetMPU9250() {
    // reset device
    MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
    HAL_Delay(10);
}

void MPU9250_initAK8963()
{
	// First extract the factory calibration for each magnetometer axis
	uint8_t rawData[3];  // x/y/z gyro calibration data stored here
	MPU9250_writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	HAL_Delay(10);
	MPU9250_writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
	HAL_Delay(10);
	MPU9250_readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values

	// set axis to accel axis
	mpu9250.magCalibration[1] =  (float)(rawData[0] - 128)/256.0f + 1.0f;   // Return x-axis sensitivity adjustment values, etc.
	mpu9250.magCalibration[0] =  (float)(rawData[1] - 128)/256.0f + 1.0f;
	mpu9250.magCalibration[2] =  ((float)(rawData[2] - 128)/256.0f + 1.0f);
	MPU9250_writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	HAL_Delay(10);
	// Configure the magnetometer for continuous read and highest resolution
	// set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
	// and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
	MPU9250_writeByte(AK8963_ADDRESS, AK8963_CNTL, mpu9250.Mscale << 4 | mpu9250.Mmode); // Set magnetometer data resolution and sample ODR
	HAL_Delay(10);
}


void MPU9250_initMPU9250()
{
 // Initialize MPU9250 device
 // wake up device
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
  HAL_Delay(100); // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt

 // get stable time source
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

 // Configure Gyro and Accelerometer
 // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
 // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
 // Maximum delay is 4.9 ms which is just over a 200 Hz maximum rate
  MPU9250_writeByte(MPU9250_ADDRESS, CONFIG, 0x03);

 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
  MPU9250_writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; the same rate set in CONFIG above

 // Set gyroscope full scale range
 // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  uint8_t c = MPU9250_readByte(MPU9250_ADDRESS, GYRO_CONFIG); // get current GYRO_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5]
  c = c & ~0x02; // Clear Fchoice bits [1:0]
  c = c & ~0x18; // Clear AFS bits [4:3]
  c = c | mpu9250.Gscale << 3; // Set full scale range for the gyro
 // c =| 0x00; // Set Fchoice for the gyro to 11 by writing i
  MPU9250_writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c ); // Write new GYRO_CONFIG value to regts inverse to bits 1:0 of GYRO_CONFIGister

 // Set accelerometer full-scale range configuration
  c = MPU9250_readByte(MPU9250_ADDRESS, ACCEL_CONFIG); // get current ACCEL_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5]
  c = c & ~0x18;  // Clear AFS bits [4:3]
  c = c | mpu9250.Ascale << 3; // Set full scale range for the accelerometer
  MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value

 // Set accelerometer sample rate configuration
 // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
 // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
  c = MPU9250_readByte(MPU9250_ADDRESS, ACCEL_CONFIG2); // get current ACCEL_CONFIG2 register value
  c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
  c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
  MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value

 // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
 // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips
  // can join the I2C bus and all can be controlled by the Arduino as master
  MPU9250_writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
  MPU9250_writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
}


// Function which accumulates gyro and accelerometer data after device initialization. It calculates the average
// of the at-rest readings and then loads the resulting offsets into accelerometer and gyro bias registers.
void MPU9250_calibrateMPU9250()
{
  uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
  uint16_t ii, packet_count, fifo_count;
  int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

// reset device, reset all registers, clear gyro and accelerometer bias registers
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
  HAL_Delay(100);

// get stable time source
// Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
  HAL_Delay(200);

// Configure device for bias calculation
  MPU9250_writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
  MPU9250_writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
  MPU9250_writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
  MPU9250_writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
  MPU9250_writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
  MPU9250_writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
  HAL_Delay(15);

// Configure MPU9250 gyro and accelerometer for bias calculation
  MPU9250_writeByte(MPU9250_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
  MPU9250_writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
  MPU9250_writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
  MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

// Configure FIFO to capture accelerometer and gyro data for bias calculation
  MPU9250_writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO
  MPU9250_writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO (max size 512 bytes in MPU-9250)
  HAL_Delay(40); // accumulate 40 samples in 80 milliseconds = 480 bytes

// At end of sample accumulation, turn off FIFO sensor read
  MPU9250_writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
  MPU9250_readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
  fifo_count = ((uint16_t)data[0] << 8) | data[1];
  packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

  for (ii = 0; ii < packet_count; ii++) {
    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
    MPU9250_readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
    accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
    accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
    accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;
    gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
    gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
    gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;

    accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
    accel_bias[1] += (int32_t) accel_temp[1];
    accel_bias[2] += (int32_t) accel_temp[2];
    gyro_bias[0]  += (int32_t) gyro_temp[0];
    gyro_bias[1]  += (int32_t) gyro_temp[1];
    gyro_bias[2]  += (int32_t) gyro_temp[2];

  }
    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;

    uint16_t accelsensitivity = (uint16_t)(1/mpu9250.aRes);
//    uint16_t gyrosensitivity = (uint16_t)(1/mpu9250.gRes);
//    printf("%u, %u", accelsensitivity, gyrosensitivity);

  if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
  else {accel_bias[2] += (int32_t) accelsensitivity;}

// Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
  data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
  data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
  data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
  data[3] = (-gyro_bias[1]/4)       & 0xFF;
  data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
  data[5] = (-gyro_bias[2]/4)       & 0xFF;

/// Push gyro biases to hardware registers
  MPU9250_writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
  MPU9250_writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
  MPU9250_writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
  MPU9250_writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
  MPU9250_writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
  MPU9250_writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);


//  MPU9250_gyroBias[0] = (float) gyro_bias[0]/(float) gyrosensitivity; // construct gyro bias in deg/s for later manual subtraction
//  MPU9250_gyroBias[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
//  MPU9250_gyroBias[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

// Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
// factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
// non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
// compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
// the accelerometer biases calculated above must be divided by 8.

  int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
  MPU9250_readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
  accel_bias_reg[0] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  MPU9250_readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[1] = (int16_t) ((int16_t)data[0] << 8) | data[1];
  MPU9250_readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[2] = (int16_t) ((int16_t)data[0] << 8) | data[1];

  uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
  uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

  for(ii = 0; ii < 3; ii++) {
    if(accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
  }

  // Construct total accelerometer bias, including calculated average accelerometer bias from above
  accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
  accel_bias_reg[1] -= (accel_bias[1]/8);
  accel_bias_reg[2] -= (accel_bias[2]/8);

  data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  data[1] = (accel_bias_reg[0])      & 0xFF;
  data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  data[3] = (accel_bias_reg[1])      & 0xFF;
  data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
  data[5] = (accel_bias_reg[2])      & 0xFF;
  data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

// Apparently this is not working for the acceleration biases in the MPU-9250
// Are we handling the temperature correction bit properly?
// Push accelerometer biases to hardware registers
  MPU9250_writeByte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
  MPU9250_writeByte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
  MPU9250_writeByte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
  MPU9250_writeByte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
  MPU9250_writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
  MPU9250_writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);

// Output scaled accelerometer biases for manual subtraction in the main program
//    MPU9250_accelBias[0] = (float)accel_bias[0]/(float)accelsensitivity;
//    MPU9250_accelBias[1] = (float)accel_bias[1]/(float)accelsensitivity;
//    MPU9250_accelBias[2] = (float)accel_bias[2]/(float)accelsensitivity;
}

// Accelerometer and gyroscope self test; check calibration wrt factory settings
void MPU9250_SelfTest(float * destination) // Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
{
   uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
   uint8_t selfTest[6];
   int32_t gAvg[3] = {0}, aAvg[3] = {0}, aSTAvg[3] = {0}, gSTAvg[3] = {0};
   float factoryTrim[6];
   uint8_t FS = 0;

  MPU9250_writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00); // Set gyro sample rate to 1 kHz
  MPU9250_writeByte(MPU9250_ADDRESS, CONFIG, 0x02); // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
  MPU9250_writeByte(MPU9250_ADDRESS, GYRO_CONFIG, FS<<3); // Set full scale range for the gyro to 250 dps
  MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
  MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, FS<<3); // Set full scale range for the accelerometer to 2 g

  for( int ii = 0; ii < 200; ii++) { // get average current values of gyro and acclerometer

	  MPU9250_readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]); // Read the six raw data registers into data array
	  aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ; // Turn the MSB and LSB into a signed 16-bit value
	  aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
	  aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

	  MPU9250_readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]); // Read the six raw data registers sequentially into data array
	  gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ; // Turn the MSB and LSB into a signed 16-bit value
	  gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
	  gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  for (int ii =0; ii < 3; ii++) { // Get average of 200 values and store as average current readings
	  aAvg[ii] /= 200;
	  gAvg[ii] /= 200;
  }

// Configure the accelerometer for self-test
   MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
   MPU9250_writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
   HAL_Delay(25); // Delay a while to let the device stabilize

  for( int ii = 0; ii < 200; ii++) { // get average self-test values of gyro and acclerometer

	  MPU9250_readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]); // Read the six raw data registers into data array
	  aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ; // Turn the MSB and LSB into a signed 16-bit value
	  aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
	  aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

	  MPU9250_readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]); // Read the six raw data registers sequentially into data array
	  gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ; // Turn the MSB and LSB into a signed 16-bit value
	  gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
	  gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  for (int ii =0; ii < 3; ii++) { // Get average of 200 values and store as average self-test readings
	  aSTAvg[ii] /= 200;
	  gSTAvg[ii] /= 200;
  }

 // Configure the gyro and accelerometer for normal operation
   MPU9250_writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
   MPU9250_writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);
   HAL_Delay(25); // Delay a while to let the device stabilize

   // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
   selfTest[0] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_X_ACCEL); // X-axis accel self-test results
   selfTest[1] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
   selfTest[2] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
   selfTest[3] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_X_GYRO); // X-axis gyro self-test results
   selfTest[4] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_Y_GYRO); // Y-axis gyro self-test results
   selfTest[5] = MPU9250_readByte(MPU9250_ADDRESS, SELF_TEST_Z_GYRO); // Z-axis gyro self-test results

  // Retrieve factory self-test value from self-test code reads
   factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
   factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
   factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
   factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
   factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
   factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation

 // Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
 // To get percent, must multiply by 100
   for (int i = 0; i < 3; i++) {
     destination[i] = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i] - 100.; // Report percent differences
     destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3] - 100.; // Report percent differences
   }
}

void MPU9250_writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	HAL_I2C_Mem_Write(MPU9250_I2C, address, subAddress, 1, &data, 1, MPU9250_DEFAULT_TIMEOUT);
}

void MPU9250_readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{
	HAL_I2C_Mem_Read(MPU9250_I2C, address, subAddress, 1, (uint8_t*)dest, count, MPU9250_DEFAULT_TIMEOUT);
}

char MPU9250_readByte(uint8_t address, uint8_t subAddress)
{
	char data; // `data` will store the register data
	MPU9250_readBytes(address, subAddress, 1, (uint8_t*)&data);
	return data;
}

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
