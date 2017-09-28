#include "StdAfx.h"
#include "General.h"

#include "..\..\..\..\ApiMacro.h"

#include "../Engine/fann.h"

int LuaFann121_ResetMSE(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	fann_reset_MSE(pAnn);

	return true;
}

int	LuaFann121_GetMSE(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	float mse = fann_get_MSE(pAnn);

	lua_pushnumber(L, mse);

	return true;
}

int	LuaFann121_ComputeMSE(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);
	POP_ARGUMENT(IDataFactory*, piOutputData, 2);	

	fann_compute_MSE(pAnn, piOutputData->GetData());

    return true;
}

int	LuaFann121_BackpropagateMSE(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	fann_backpropagate_MSE(pAnn);

	return true;
}

