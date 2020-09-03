/*
 * function.h
 *
 *  Created on: Aug 17, 2020
 *      Author: cjb88
 */

#ifndef UTILS_FUNCTIONS_H_
#define UTILS_FUNCTIONS_H_

#include <cstdint>

namespace FC{

float map(uint16_t value, uint16_t in_min, uint16_t in_max, float out_min, float out_max);

float radianThreshold(float radian, float min, float max);

float deg2rad(float);

float rad2deg(float);

/*
*  LLA axis -(geoToECEF)-> ecef axis --> local ned axis
*  param[in]      lat            latitude
*  param[in]      lon            longitude
*  param[in]      alt            altitude
*  param[in]      refLat         reference latitude
*  param[in]      refLon         reference longitude
*  param[in]      refAlt         reference altitude
*  param[out]      localNedX      local ned x
*  param[out]      localNedY      local ned y
*  param[out]      localNedZ      local ned z
*/
void lla2LocalNed(double lat, double lon, float alt,
				   double refLat, double refLon, float refAlt,
				   float *localNedX, float *localNedY, float *localNedZ);

/*
*  geo axis -> ecef axis
*  param[in]      lat         latitude
*  param[in]      lon         longitude
*  param[in]      alt         altitude
*  param[out]      ecefX      ecef-x
*  param[out]      ecefY      ecef-y
*  param[out]      ecefZ      ecef-z
*/
void geo2ECEF(double lat, double lon, float alt, double *ecefX, double *ecefY, double *ecefZ);


}

#endif /* UTILS_FUNCTIONS_H_ */
