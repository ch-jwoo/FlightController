/*
 * Functions.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: cjb88
 */

#include "Functions.h"

#include <Utils/Constants.h>
#include "Lib/Matrix/matrix/Dcm.hpp"
#include "Lib/Matrix/matrix/Matrix.hpp"
#include <cmath>
#define _USE_MATH_DEFINES

namespace FC{

float map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max){
	return (float)(value - in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}


float radianThreshold(float radian, float min, float max){
	float interval = max - min;
	while(radian >= max){
		radian -= interval;
	}
	while(radian <= min){
		radian += interval;
	}
	return radian;
}

float deg2rad(float num){
	return num * (float)M_PI / 180.0;
}

float rad2deg(float num){
	return num * 180.0 / (float)M_PI;
}

/*
*  ModuleAutoController::geoToECEF();
*  step1: calculating radius of curvature
*  step2: converting geodetic position to ECEF position
*/
void geo2ECEF(double lat, double lon, float alt, double *ecefX, double *ecefY, double *ecefZ) {
	/* radus of curvature */
	double radius = (uint32_t)EARTH_RADIUS / (1 - sqrt(1 - pow((float)EARTH_ECCENTRICTIY * sin(lat), 2)));

	/*cosine sine function with latitude and longitude*/
	double cosLat = cos(lat);
	double cosLon = cos(lon);
	double sinLat = sin(lat);
	double sinLon = sin(lon);
	/*ECEF position*/
	*ecefX = (radius + alt)*cosLat * cosLon;
	*ecefY = (radius + alt)*cosLat * sinLon;
	*ecefZ = (radius * (1 - pow((double)EARTH_ECCENTRICTIY, 2)) + alt) * sinLat;
}

/*
*  ModuleAutoController::lla2LocalNed();
*  step1: calculating direction cosine matrix for local ned position
*  step2: subtracting ECEF position Reference ECEF position
*  step3: calculating local ned position
*/
void lla2LocalNed(double lat, double lon, float alt,
      double refLat, double refLon, float refAlt,
      float *localNedX, float *localNedY, float *localNedZ){

   /* reference ecef axis */
   double refEcefX, refEcefY, refEcefZ;
   geo2ECEF(refLat, refLon, refAlt, &refEcefX, &refEcefY, &refEcefZ);

   /* target ecef axis */
   double ecefX, ecefY, ecefZ;
   geo2ECEF(lat, lon, alt, &ecefX, &ecefY, &ecefZ);

   /*
   *  z axis rotate 'longitude'
   *  y axis rotate '-latitude-90'
   */
   double dcm[9] = { -sin(refLat) * cos(refLon), -sin(refLat) * sin(refLon),  cos(refLat),
               -sin(refLon)             ,  cos(refLon)             ,  0,
               -cos(refLat) * cos(refLon), -cos(refLat) * sin(refLon), -sin(refLat) };

   matrix::Matrix<double, 3, 3> dcmMatrix(dcm);
//
   /*ECEF - RefECEF*/
   double temp[3] = { ecefX - refEcefX,
               ecefY - refEcefY,
               ecefZ - refEcefZ };
//
   matrix::Matrix<double, 3, 1> tempMatrix(temp);
   matrix::Matrix<double, 3, 1> nedMatrix = dcmMatrix * tempMatrix;
//
//   /*local ned position*/
   *localNedX = nedMatrix(0,0);
   *localNedY = nedMatrix(1,0);
   *localNedZ = nedMatrix(2,0);
}

}
