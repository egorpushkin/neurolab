#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Data Conversion
int				LuaBinDataManipulations_ConvertBin2Float(lua_State *L);
int				LuaBinDataManipulations_ConvertBin2Int(lua_State *L);

