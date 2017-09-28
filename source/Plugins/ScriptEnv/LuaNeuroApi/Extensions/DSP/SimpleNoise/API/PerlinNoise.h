#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaSimpleNoise_PerlinStep(lua_State *L);
int				LuaSimpleNoise_SetPerlinSeed(lua_State *L);

