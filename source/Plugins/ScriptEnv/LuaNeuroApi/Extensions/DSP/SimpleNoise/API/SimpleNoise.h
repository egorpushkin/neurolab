#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaSimpleNoise_CreateGenerator(lua_State *L);
int				LuaSimpleNoise_ReleaseGenerator(lua_State *L);

// Package initialization
int				luaopen_simplenoise(lua_State *L);
