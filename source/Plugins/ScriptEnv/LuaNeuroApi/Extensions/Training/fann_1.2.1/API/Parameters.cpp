#include "StdAfx.h"
#include "Training.h"

#include "..\..\..\..\ApiMacro.h"

#include "../Engine/fann.h"

int LuaFann121_GetTrainingAlgorithm(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	unsigned int alg = fann_get_training_algorithm(pAnn);

	lua_pushnumber(L, (double)alg);
	
	return true;
}

int LuaFann121_SetTrainingAlgorithm(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	unsigned int alg = (unsigned int)lua_tonumber(L, 2);

	fann_set_training_algorithm(pAnn, alg);

	return true;
}

int LuaFann121_SetActivationFunctionHidden(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	unsigned int func = (unsigned int)lua_tonumber(L, 2);

	fann_set_activation_function_hidden(pAnn, func);

	return true;
}

int LuaFann121_SetActivationFunctionOutput(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	unsigned int func = (unsigned int)lua_tonumber(L, 2);

	fann_set_activation_function_output(pAnn, func);

	return true;
}
