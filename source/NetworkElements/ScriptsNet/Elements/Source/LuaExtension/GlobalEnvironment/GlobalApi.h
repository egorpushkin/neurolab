#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
} 

// Package routines
int				LuaGlobalApi_This(lua_State *L);

int				LuaGlobalApi_GetInputsFactory(lua_State *L);
int				LuaGlobalApi_GetOutputsFactory(lua_State *L);

// Package initialization
int				luaopen_globalenvironment(lua_State *L);