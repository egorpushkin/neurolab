#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaSimpleNoise_GetWhite(lua_State *L);
int				LuaSimpleNoise_GetPink(lua_State *L);
int				LuaSimpleNoise_GetBrown(lua_State *L);

