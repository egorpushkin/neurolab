#pragma once

#define LUA_API extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_SetTrainingAlgorithm(lua_State *L);
int				LuaFann121_GetTrainingAlgorithm(lua_State *L);

int				LuaFann121_SetActivationFunctionHidden(lua_State *L);
int				LuaFann121_SetActivationFunctionOutput(lua_State *L);

