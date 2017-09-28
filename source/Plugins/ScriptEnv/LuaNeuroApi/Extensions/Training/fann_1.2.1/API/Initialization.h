#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_RandomizeWeights(lua_State *L);
int				LuaFann121_InitWeights(lua_State *L);
