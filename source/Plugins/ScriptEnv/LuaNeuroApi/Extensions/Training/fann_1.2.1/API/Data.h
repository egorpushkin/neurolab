#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_FannTrainDataFromDataFile(lua_State *L);
int				LuaFann121_ReleaseFannTrainData(lua_State *L);

