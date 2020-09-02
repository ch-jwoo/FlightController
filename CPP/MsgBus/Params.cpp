/*
 * Params.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: cjb88
 */

#include <MsgBus/Params.h>
#include "Module/Estimator/ModuleAHRS.h"
#include "Interface/InterfaceMag.h"
#include <cstdio>


namespace FC {

typedef struct{
	char id[40];
	float* variable;
} Param_t;

std::array<Param_t, sizeof(ParamIndex_t)> params;

#define PARAM_INIT(index , paramVariable)	std::sprintf(params.at(index).id, #index);\
										params.at(index).variable = &paramVariable;

void paramInit(){
	PARAM_INIT(MAG_BiasX, InterfaceMag::bias[0]);
	PARAM_INIT(MAG_BiasY, InterfaceMag::bias[1]);
	PARAM_INIT(MAG_BiasZ, InterfaceMag::bias[2]);

	PARAM_INIT(MAG_ScaleX, InterfaceMag::scale[0]);
	PARAM_INIT(MAG_ScaleY, InterfaceMag::scale[1]);
	PARAM_INIT(MAG_ScaleZ, InterfaceMag::scale[2]);

	PARAM_INIT(Madgwick_beta, ModuleAHRS::beta);
}

float getParamValue(uint8_t index){
	return *params.at(index).variable;
}

void setParamValue(uint8_t index, float value){
	*params.at(index).variable = value;
}

} /* namespace FC */
