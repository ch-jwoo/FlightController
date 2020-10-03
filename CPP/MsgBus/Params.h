/*
 * Params.h
 *
 *  Created on: Sep 1, 2020
 *      Author: cjb88
 */

#ifndef MSGBUS_PARAMS_H_
#define MSGBUS_PARAMS_H_

#include <cstdint>

namespace FC {

typedef enum{
	/* mag bias, scale */
	MAG_BiasX,
	MAG_BiasY,
	MAG_BiasZ,

	MAG_ScaleX,
	MAG_ScaleY,
	MAG_ScaleZ,

	/* ahrs beta */
	Madgwick_beta,

	ACCEL_TRANSFORM_0_0,
	ACCEL_TRANSFORM_0_1,
	ACCEL_TRANSFORM_0_2,
	ACCEL_TRANSFORM_1_0,
	ACCEL_TRANSFORM_1_1,
	ACCEL_TRANSFORM_1_2,
	ACCEL_TRANSFORM_2_0,
	ACCEL_TRANSFORM_2_1,
	ACCEL_TRANSFORM_2_2,

	ACCEL_OFFSET_0,
	ACCEL_OFFSET_1,
	ACCEL_OFFSET_2,

	/* multicopter */
	MC_Roll_P,
	MC_Roll_I,

	MC_Pitch_P,
	MC_Pitch_I,

	MC_RollRate_P,
	MC_RollRate_I,
	MC_RollRate_D,

	MC_PitchRate_P,
	MC_PitchRate_I,
	MC_PitchRate_D,

	MC_YawRate_P,
	MC_YawRate_I,

	/* fixedwing*/
	FW_Roll_P,
	FW_Roll_I,

	FW_Pitch_P,
	FW_Pitch_I,

	FW_RollRate_P,
	FW_RollRate_I,
	FW_RollRate_D,

	FW_PitchRate_P,
	FW_PitchRate_I,
	FW_PitchRate_D,

	FW_YawRate_P,
	FW_YawRate_I,

	TILT_TO_FW_THR,
	TILT_TO_FW_DT1,
	TILT_TO_FW_DT2,
	MC_SERVO_1,
	MC_SERVO_2,
	FW_SERVO_1,
	FW_SERVO_2,
	TRANS_SERVO_1,
	TRANS_SERVO_2,

	/* ins covariance */
	EKF_VAccCov,
	EKF_VBaroCov,
	EKF_VLidarCov,
	EKF_VGpsCov,

	EKF_HAccCov_1,
	EKF_HAccCov_2,

	EKF_HGpsPCov_1,
	EKF_HGpsPCov_2,
	EKF_HGpsVCov_1,
	EKF_HGpsVCov_2,

	ParameterEnd,		/* temporary */
	/* attitude controller */




	/* position controller */
	/* multicopter */
	MC_PosX_P,
	MC_PosX_I,
	MC_PosX_D,

	MC_PosY_P,
	MC_PosY_I,
	MC_PosY_D,

	MC_PosZ_P,
	MC_PosZ_I,
	MC_PosZ_D,

	MC_VelX_P,
	MC_VelX_I,
	MC_VelX_D,

	MC_VelY_P,
	MC_VelY_I,
	MC_VelY_D,

	MC_VelZ_P,
	MC_VelZ_I,
	MC_VelZ_D,

	/* fixedwing */

	/* auto controller */
	MC_L2,					/* */
	MC_D,

	FW_L2,
	FW_D
} ParamIndex_t;

typedef enum {
	PARAM_FLOAT,
	PARAM_DOUBLE
} ParamType;

void paramInit();

const char* getParamID(uint8_t index);

float getParamValue(uint8_t index);

uint16_t getParamLength();

uint16_t getParamIndexFromID(const char* id);

void setParamValue(uint16_t index, float value);

#define PARAM(parameter) static float parameter;
//#define PARAM(parameter) static parameter_t parameter;

//#define PARAM_VALUE_INIT()


} /* namespace FC */

#endif /* MSGBUS_PARAMS_H_ */
