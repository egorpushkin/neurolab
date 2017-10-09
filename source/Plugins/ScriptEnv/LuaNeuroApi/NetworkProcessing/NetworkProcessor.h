#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Processing Functions
int				LuaNetworkProcessor_ProcessNetwork(lua_State *L);

// Data passing functions
int				LuaNetworkProcessor_SetInputData(lua_State *L);
int				LuaNetworkProcessor_SetOutputData(lua_State *L);
int				LuaNetworkProcessor_GetInputData(lua_State *L);
int				LuaNetworkProcessor_GetOutputData(lua_State *L);

// Package initialization
int				luaopen_network(lua_State *L);