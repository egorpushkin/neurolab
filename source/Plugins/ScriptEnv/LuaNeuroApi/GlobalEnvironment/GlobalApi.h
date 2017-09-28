#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaGlobalEnvironment_SetCurrentDirectory(lua_State *L);
int				LuaGlobalEnvironment_GetUpLevelDir(lua_State *L);

// Package initialization
int				luaopen_globalenvironment(lua_State *L);