#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Initialization section
int				LuaLog_GetLogProvider(lua_State *L);

// Operations
int				LuaLog_Notify(lua_State *L);
int				LuaLog_AddLogMessage(lua_State *L);
int				LuaLog_ClearLog(lua_State *L);

// Percentage manipulations
int				LuaLog_SetPercentage(lua_State *L);
int				LuaLog_GetPercentage(lua_State *L);

// Package initialization
int				luaopen_log(lua_State *L);
