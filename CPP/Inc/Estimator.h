
#ifndef __ESTIMATOR_H
#define __ESTIMATOR_H

#include "mpu6050.h"
#include "cmath"

const float RAD2DEG = 180/3.14159;

extern MPU6050 mpu;

class Estimator{
public:
	float roll;
	float pitch;

	float alpha;


	void update(){

	}

	void calGyroAngle(){

		float ax, ay, az, gx, gy, gz;
//		float tempR, tempP;
		mpu.getData(&ax, &ay, &az, &gx, &gy, &gz);


//		// Roll angle [deg]
//		float accel_xz = sqrt(ax*ax + az*az);
//		tempR = atan( ax/ accel_xz)*RAD2DEG;
//
//		// Pitch angle [deg]
//		float accel_xy = sqrt(ax*ax + ay*ay);
//		tempP = atan(ax / accel_xy)*RAD2DEG;

		float accel_x = -ay;
		float accel_y = az;
		float accel_z = ax;

		// Roll angle [deg]
		double accel_yz = sqrt(pow(accel_y,2) + pow((double)accel_z,2));
		double accel_angle_y = atan(-accel_x / accel_yz)*RAD2DEG;

		// Pitch angle [deg]
		float accel_xz = sqrt(pow(accel_x,2) + pow((double)accel_z,2));
		float accel_angle_x = atan(accel_y / accel_xz)*RAD2DEG;

		float gyro_x = -gy;
		float gyro_y = gz;
		float gyro_z = gx;

//		float gyro_angle_x += gyro_x*dt;
//		float gyro_angle_y += gyro_x*dt;
//		float gyro_angle_z += gyro_x*dt;

//		accel_angle_z = 0;

//		printf("%f, %f, %f\r\n", accel_x, accel_y, accel_z);
//		printf("%f, %f\r\n", accel_angle_y, accel_angle_x);
	}
	void calFilteredAngle();
};


#endif
