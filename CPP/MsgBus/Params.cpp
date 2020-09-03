/*
 * Params.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: cjb88
 */

#include <MsgBus/Params.h>
#include "Module/Estimator/ModuleAHRS.h"
#include "Module/Storage/ModuleSD.h"
#include "Interface/InterfaceMag.h"
#include <array>
#include <cstdio>
#include <cstring>

namespace FC {

typedef struct{
	char id[40];
	float* variable;
} Param_t;

std::array<Param_t, sizeof(ParamIndex_t) * 256> params;		/* 1byte = 256 */

#define PARAM_INIT(index , paramVariable)	std::sprintf(params.at(index).id, #index);\
										params.at(index).variable = &paramVariable;

void paramInit(){
//	std::sprintf(params.at(MAG_BiasX).id, "MAG_BiasX");
//	params.at(MAG_BiasX).variable = &InterfaceMag::bias[0];
	PARAM_INIT(MAG_BiasX, InterfaceMag::bias[0]);
	PARAM_INIT(MAG_BiasY, InterfaceMag::bias[1]);
	PARAM_INIT(MAG_BiasZ, InterfaceMag::bias[2]);
//
	PARAM_INIT(MAG_ScaleX, InterfaceMag::scale[0]);
	PARAM_INIT(MAG_ScaleY, InterfaceMag::scale[1]);
	PARAM_INIT(MAG_ScaleZ, InterfaceMag::scale[2]);
//
	PARAM_INIT(Madgwick_beta, ModuleAHRS::beta);
}

const char* getParamID(uint8_t index){
	return params.at(index).id;
}

float getParamValue(uint8_t index){
	return *(params.at(index).variable);
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
	*(params.at(index).variable) = value;
	ModuleSD::saveParam();
}


} /* namespace FC */
