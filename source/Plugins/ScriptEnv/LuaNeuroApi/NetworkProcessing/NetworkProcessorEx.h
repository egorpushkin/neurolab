#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Network procesors access functions
int				LuaNetworkProcessorEx_GetNetworkProcessor(lua_State *L);

// Processing Functions
int				LuaNetworkProcessorEx_ProcessNetworkEx(lua_State *L);

// Data passing functions
int				LuaNetworkProcessorEx_SetInputDataEx(lua_State *L);
int				LuaNetworkProcessorEx_SetOutputDataEx(lua_State *L);
int				LuaNetworkProcessorEx_GetInputDataEx(lua_State *L);
int				LuaNetworkProcessorEx_GetOutputDataEx(lua_State *L);

// Package initialization
int				luaopen_network_ex(lua_State *L);