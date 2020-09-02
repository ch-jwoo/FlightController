/*
 * Params.h
 *
 *  Created on: Sep 1, 2020
 *      Author: cjb88
 */

#ifndef MSGBUS_PARAMS_H_
#define MSGBUS_PARAMS_H_

#include <cstdint>
#include <array>

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

	/* ins covariance */
	EKF_VerticalAccelCov,
	EKF_VerticalBaroCov,
	EKF_VerticalLidarCov,
	EKF_VerticalGpsCov,

	EKF_HorisionAccelCov,
	EKF_HorisionGpsCov,

	/* attitude controller */
	/* multicopter */
	MC_Roll_P,
	MC_Roll_I,
	MC_Roll_D,

	MC_Pitch_P,
	MC_Pitch_I,
	MC_Pitch_D,

	MC_RollRate_P,
	MC_RollRate_I,
	MC_RollRate_D,

	MC_PitchRate_P,
	MC_PitchRate_I,
	MC_PitchRate_D,

	MC_YawRate_P,
	MC_YawRate_I,
	MC_YawRate_D,

	/* fixedwing*/
	FW_Roll_P,
	FW_Roll_I,
	FW_Roll_D,

	FW_Pitch_P,
	FW_Pitch_I,
	FW_Pitch_D,

	FW_RollRate_P,
	FW_RollRate_I,
	FW_RollRate_D,

	FW_PitchRate_P,
	FW_PitchRate_I,
	FW_PitchRate_D,

	FW_YawRate_P,
	FW_YawRate_I,
	FW_YawRate_D,

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
} ParamIndex_t;

void paramInit();

float getParamValue(uint8_t index);

void setParamValue(uint8_t index, float value);

#define PARAM(parameter) static float parameter;

} /* namespace FC */

#endif /* MSGBUS_PARAMS_H_ */
