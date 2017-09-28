#include "StdAfx.h"
#include "BinDataManipulations.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

int LuaBinDataManipulations_ConvertBin2Float(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	// Receiving binary float data as string from first and the only function argument
	const char* pszBinFloatData = lua_tostring(L, 1);

	// Converting data
	float fDestination = 0.0f;
    memcpy(&fDestination, pszBinFloatData, sizeof(float));
	
	// Returning result
	lua_pushnumber(L, (double)fDestination);

	return true;
}

int LuaBinDataManipulations_ConvertBin2Int(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	// Receiving binary int data as string from first and the only function argument
	const char* pszBinIntData = lua_tostring(L, 1);

	// Converting data
	int iDestination = 0;
	memcpy(&iDestination, pszBinIntData, sizeof(int));

	// Returning result
	lua_pushnumber(L, (int)iDestination);

	return true;
}