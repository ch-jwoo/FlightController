/*
 * Params.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: cjb88
 */

#include <MsgBus/Params.h>
#include "Module/Estimator/ModuleAHRS.h"
#include "Module/Storage/ModuleSD.h"
#include "Module/Controller/ModuleAttitudeController.h"
#include "Module/Estimator/ModuleINS.h"

#include "Interface/InterfaceMag.h"
#include "Interface/InterfaceAccel.h"

#include <array>
#include <cstdio>
#include <cstring>

namespace FC {

typedef struct{
	char id[40];
	void* variable;
	ParamType type;
} Param_t;

std::array<Param_t, sizeof(ParamIndex_t) * 256> params;		/* 1byte = 256 */

#define PARAM_INIT(index , paramVariable, dataType)	std::sprintf(params.at(index).id, #index);\
										params.at(index).variable = (void*)&paramVariable;\
										params.at(index).type = dataType;


void paramInit(){
	PARAM_INIT(MAG_BiasX, InterfaceMag::bias[0], PARAM_FLOAT);
	PARAM_INIT(MAG_BiasY, InterfaceMag::bias[1], PARAM_FLOAT);
	PARAM_INIT(MAG_BiasZ, InterfaceMag::bias[2], PARAM_FLOAT);
//
	PARAM_INIT(MAG_ScaleX, InterfaceMag::scale[0], PARAM_FLOAT);
	PARAM_INIT(MAG_ScaleY, InterfaceMag::scale[1], PARAM_FLOAT);
	PARAM_INIT(MAG_ScaleZ, InterfaceMag::scale[2], PARAM_FLOAT);
//
	PARAM_INIT(Madgwick_beta, ModuleAHRS::beta, PARAM_FLOAT);
//
	PARAM_INIT(ACCEL_TRANSFORM_0_0, InterfaceAccel::transform[0][0], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_0_1, InterfaceAccel::transform[0][1], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_0_2, InterfaceAccel::transform[0][2], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_1_0, InterfaceAccel::transform[1][0], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_1_1, InterfaceAccel::transform[1][1], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_1_2, InterfaceAccel::transform[1][2], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_2_0, InterfaceAccel::transform[2][0], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_2_1, InterfaceAccel::transform[2][1], PARAM_FLOAT);
	PARAM_INIT(ACCEL_TRANSFORM_2_2, InterfaceAccel::transform[2][2], PARAM_FLOAT);

	PARAM_INIT(ACCEL_OFFSET_0, InterfaceAccel::offset[0], PARAM_FLOAT);
	PARAM_INIT(ACCEL_OFFSET_1, InterfaceAccel::offset[1], PARAM_FLOAT);
	PARAM_INIT(ACCEL_OFFSET_2, InterfaceAccel::offset[2], PARAM_FLOAT);
//
	PARAM_INIT(MC_Roll_P, Angle_rate_roll_PI_kP, PARAM_FLOAT);
	PARAM_INIT(MC_Roll_I, Angle_rate_roll_PI_kI, PARAM_FLOAT);

	PARAM_INIT(MC_Pitch_P, Angle_rate_pitch_kP, PARAM_FLOAT);
	PARAM_INIT(MC_Pitch_I, Angle_rate_pitch_kI, PARAM_FLOAT);

	PARAM_INIT(MC_RollRate_P, kP_Roll_rate_PID, PARAM_FLOAT);
	PARAM_INIT(MC_RollRate_I, kI_Roll_rate_PID, PARAM_FLOAT);
	PARAM_INIT(MC_RollRate_D, kD_Roll_rate_PID, PARAM_FLOAT);

	PARAM_INIT(MC_PitchRate_P, kP_Pitch_rate_PID, PARAM_FLOAT);
	PARAM_INIT(MC_PitchRate_I, kI_Pitch_rate_PID, PARAM_FLOAT);
	PARAM_INIT(MC_PitchRate_D, kD_Pitch_rate_PID, PARAM_FLOAT);

	PARAM_INIT(MC_YawRate_P, kP_Yaw_rate_PID, PARAM_FLOAT);
	PARAM_INIT(MC_YawRate_I, kI_Yaw_rate_PID, PARAM_FLOAT);
//
	PARAM_INIT(FW_Roll_P, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_Angle_rate_roll_PI_kP, PARAM_FLOAT);
	PARAM_INIT(FW_Roll_I, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_Angle_rate_roll_PI_kI, PARAM_FLOAT);

	PARAM_INIT(FW_Pitch_P, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_Angle_rate_pitch_kP, PARAM_FLOAT);
	PARAM_INIT(FW_Pitch_I, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_Angle_rate_pitch_kI, PARAM_FLOAT);

	PARAM_INIT(FW_RollRate_P, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kP_Roll_rate_PID, PARAM_FLOAT);
	PARAM_INIT(FW_RollRate_I, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kI_Roll_rate_PID, PARAM_FLOAT);
	PARAM_INIT(FW_RollRate_D, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kD_Roll_rate_PID, PARAM_FLOAT);

	PARAM_INIT(FW_PitchRate_P, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kP_Pitch_rate_PID, PARAM_FLOAT);
	PARAM_INIT(FW_PitchRate_I, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kI_Pitch_rate_PID, PARAM_FLOAT);
	PARAM_INIT(FW_PitchRate_D, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kD_Pitch_rate_PID, PARAM_FLOAT);

	PARAM_INIT(FW_YawRate_P, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kP_Yaw_rate_PID, PARAM_FLOAT);
	PARAM_INIT(FW_YawRate_I, FW_px4_AlgorithmModelClass::FW_att_control_codeblock_fly_P.FW_kI_Yaw_rate_PID, PARAM_FLOAT);
//
	PARAM_INIT(TILT_TO_FW_THR, ModuleAttitudeController::vtolTransitionTHR, PARAM_FLOAT);
	PARAM_INIT(TILT_TO_FW_DT1, ModuleAttitudeController::vtolTransitionPhase1Time, PARAM_FLOAT);
	PARAM_INIT(TILT_TO_FW_DT2, ModuleAttitudeController::vtolTransitionPhase2Time, PARAM_FLOAT);
	PARAM_INIT(MC_SERVO_1, ModuleAttitudeController::MC_SERVO_1, PARAM_FLOAT);
	PARAM_INIT(MC_SERVO_2, ModuleAttitudeController::MC_SERVO_2, PARAM_FLOAT);
	PARAM_INIT(FW_SERVO_1, ModuleAttitudeController::FW_SERVO_1, PARAM_FLOAT);
	PARAM_INIT(FW_SERVO_2, ModuleAttitudeController::FW_SERVO_2, PARAM_FLOAT);
	PARAM_INIT(TRANS_SERVO_1, ModuleAttitudeController::TRANSITION_SERVO_1, PARAM_FLOAT);
	PARAM_INIT(TRANS_SERVO_2, ModuleAttitudeController::TRANSITION_SERVO_2, PARAM_FLOAT);
//
	PARAM_INIT(EKF_HAccCov_1, positionEstimatorModelClass::rtP.R1_Value[0], PARAM_DOUBLE);
	PARAM_INIT(EKF_HAccCov_2, positionEstimatorModelClass::rtP.R1_Value[3], PARAM_DOUBLE);

	PARAM_INIT(EKF_HGpsPCov_1, positionEstimatorModelClass::rtP.R2_Value[0], PARAM_DOUBLE);
	PARAM_INIT(EKF_HGpsPCov_2, positionEstimatorModelClass::rtP.R2_Value[5], PARAM_DOUBLE);

	PARAM_INIT(EKF_HGpsVCov_1, positionEstimatorModelClass::rtP.R2_Value[10], PARAM_DOUBLE);
	PARAM_INIT(EKF_HGpsVCov_2, positionEstimatorModelClass::rtP.R2_Value[15], PARAM_DOUBLE);

	PARAM_INIT(EKF_VAccCov, positionEstimatorModelClass::rtP.R1_Value_j, PARAM_DOUBLE);
	PARAM_INIT(EKF_VGpsCov, positionEstimatorModelClass::rtP.R2_Value_g, PARAM_DOUBLE);
	PARAM_INIT(EKF_VBaroCov, positionEstimatorModelClass::rtP.R3_Value, PARAM_DOUBLE);
	PARAM_INIT(EKF_VLidarCov, positionEstimatorModelClass::rtP.R4_Value, PARAM_DOUBLE);
}

const char* getParamID(uint8_t index){
	return params.at(index).id;
}

float getParamValue(uint8_t index){
	switch(params.at(index).type){
	case PARAM_FLOAT:
		return *(float*)(params.at(index).variable);
	case PARAM_DOUBLE:
		return (float)(*(double*)(params.at(index).variable));
	}

//	return *(params.at(index).variable);
}

uint16_t getParamLength(){
	return ParameterEnd;
}

uint16_t getParamIndexFromID(const char* id){
	for(uint16_t i=0; i<getParamLength(); i++){
		if(!strcmp(id, getParamID(i))){
			return i;
		}
	}
	return -1;
}

void setParamValue(uint16_t index, float value){
	switch(params.at(index).type){
	case PARAM_FLOAT:
		*((float*)(params.at(index).variable)) = value;
		break;
	case PARAM_DOUBLE:
		*((double*)(params.at(index).variable)) = (double)value;
		break;
	}
	ModuleSD::saveParam();
}


} /* namespace FC */
