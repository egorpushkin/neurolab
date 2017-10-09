#include "StdAfx.h"
#include "Initialization.h"

#include "..\..\..\..\ApiMacro.h"

#include "../Engine/fann.h"

int LuaFann121_RandomizeWeights(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(fann*, pAnn, 1);
	float minWeigth = (float)lua_tonumber(L, 2);
	float maxWeight = (float)lua_tonumber(L, 3);

	fann_randomize_weights(pAnn, minWeigth, maxWeight);

	return true;
}

int LuaFann121_InitWeights(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)
	
	POP_ARGUMENT(fann*, pAnn, 1);
	POP_ARGUMENT(fann_train_data*, pTrainData, 1)

	fann_init_weights(pAnn, pTrainData);

	return true;
}