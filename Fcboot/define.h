/*
 * define.h
 *
 *  Created on: Jul 22, 2020
 *      Author: cjb88
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include "MPU9250.h"
#define imu1_ax MPU9250_getAx() // float
#define imu1_ay MPU9250_getAy() // float
#define imu1_az MPU9250_getAz()	// float
#define imu1_gx MPU9250_getGx() // float
#define imu1_gy MPU9250_getGy() // float
#define imu1_gz MPU9250_getGz()	// float
#define imu1_hz MPU9250_getHz()	// uint16_t

#include "sbus.h"
#define ch1 sbus_getChannel(1)		//uint16_t
#define ch2 sbus_getChannel(2)		//uint16_t
#define ch3 sbus_getChannel(3)		//uint16_t
#define ch4 sbus_getChannel(4)		//uint16_t
#define ch5 sbus_getChannel(5)		//uint16_t
#define ch6 sbus_getChannel(6)		//uint16_t
#define ch7 sbus_getChannel(7)		//uint16_t
#define ch8 sbus_getChannel(8)		//uint16_t
#define ch9 sbus_getChannel(9)		//uint16_t
#define ch10 sbus_getChannel(10)	//uint16_t
#define ch11 sbus_getChannel(11)	//uint16_t
#define ch12 sbus_getChannel(12)	//uint16_t
#define ch13 sbus_getChannel(13)	//uint16_t
#define ch14 sbus_getChannel(14)	//uint16_t
#define ch15 sbus_getChannel(15)	//uint16_t
#define ch16 sbus_getChannel(16)	//uint16_t

#define rc_throthle ch1
#define rc_roll ch2
#define rc_pitch ch3
#define rc_yaw ch4
#define rc_mode ch5


#endif /* DEFINE_H_ */
