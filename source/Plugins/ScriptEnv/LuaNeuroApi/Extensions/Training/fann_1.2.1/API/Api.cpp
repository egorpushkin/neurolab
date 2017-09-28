#include "StdAfx.h"
#include "Api.h"

#include "../../../../ApiMacro.h"

#include "General.h"
#include "Initialization.h"
#include "Parser.h"
#include "Training.h"
#include "Parameters.h"
#include "MSE.h"
#include "Data.h"

#include "../Engine/fann.h"

// Package initialization
static const luaL_reg fann121lib[] = {
	{"createArray",				LuaFann121_CreateArray},
	{"destroy",					LuaFann121_Destroy},
	{"run",						LuaFann121_Run},
	{"getOutputData",			LuaFann121_GetOutputData},
	{"getOutputsCount",			LuaFann121_GetOutputsCount},

	{"randomizeWeights",		LuaFann121_RandomizeWeights},
	{"initWeights",				LuaFann121_InitWeights},

	{"getLayersCount",			LuaFann121_GetLayersCount},
	{"getLayer",				LuaFann121_GetLayer},
	{"getLayerDimension",		LuaFann121_GetLayerDimension},
	{"getLayerInputsCount",		LuaFann121_GetLayerInputsCount},
	{"getNeuron",				LuaFann121_GetNeuron},
	{"getNeuronInputsCount",	LuaFann121_GetNeuronInputsCount},
	{"getNeuronWeight",			LuaFann121_GetNeuronWeight},
	{"getLayerWeight",			LuaFann121_GetLayerWeight},

	{"trainOnFannData",			LuaFann121_TrainOnFannData},
	{"clearTrainArrays",		LuaFann121_ClearTrainArrays},
	{"updateWeightsQuickprop",	LuaFann121_UpdateWeightsQuickprop},
	{"updateWeightsIrpropm",	LuaFann121_UpdateWeightsIrpropm},
	{"updateWeightsBatch",		LuaFann121_UpdateWeightsBatch},
	{"isSlopesUpdateRequired",	LuaFann121_IsSlopesUpdateRequired},
	{"updateSlopesBatch",		LuaFann121_UpdateSlopesBatch},
	{"train",					LuaFann121_Train},

	{"setTrainingAlgorithm",	LuaFann121_SetTrainingAlgorithm},
	{"getTrainingAlgorithm",	LuaFann121_GetTrainingAlgorithm},
	{"setActivationFunctionHidden",		LuaFann121_SetActivationFunctionHidden},
	{"setActivationFunctionOutput",		LuaFann121_SetActivationFunctionOutput},

	{"resetMSE",				LuaFann121_ResetMSE},
	{"getMSE",					LuaFann121_GetMSE},
	{"computeMSE",				LuaFann121_ComputeMSE},
	{"backpropagateMSE",		LuaFann121_BackpropagateMSE},

	{"fannTrainDataFromDataFile",		LuaFann121_FannTrainDataFromDataFile},
	{"releaseFannTrainData",			LuaFann121_ReleaseFannTrainData},

	{NULL, NULL}
}; 

static const luaL_const fann121enums[] = {
	{"FANN_TRAIN_INCREMENTAL",	0},
	{"FANN_TRAIN_BATCH",		1},
	{"FANN_TRAIN_RPROP",		2},
	{"FANN_TRAIN_QUICKPROP",	3},

	{"FANN_LINEAR",							0},
	{"FANN_THRESHOLD",						1},
	{"FANN_THRESHOLD_SYMMETRIC",			2},
	{"FANN_SIGMOID",						3},
	{"FANN_SIGMOID_STEPWISE",				4},
	{"FANN_SIGMOID_SYMMETRIC",				5},
	{"FANN_SIGMOID_SYMMETRIC_STEPWISE",		6},
	{"FANN_GAUSSIAN",						7},
	{"FANN_GAUSSIAN_STEPWISE",				8},
	{"FANN_ELLIOT",							9},
	{"FANN_ELLIOT_SYMMETRIC",				10},

	{"FULL_CONNECTED",						1},

	{NULL, NULL}

};

int luaopen_fann_121(lua_State *L) 
{
	luaL_openlib(L, "fann121", fann121lib, 0);

	lua_pushstring(L, "fann121");
	lua_gettable(L, LUA_GLOBALSINDEX);  
	lua_insert(L, -1);

	for (const luaL_const* l = fann121enums; l->name_; l++) {
		lua_pushstring(L, l->name_);
		lua_pushnumber(L, l->value_);
		lua_settable(L, -3);
	} 

	lua_pop(L, 0);

	return 1;
} 
