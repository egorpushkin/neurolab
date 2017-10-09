#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaCharting_CreateAutomaticLocator(lua_State *L);
int				LuaCharting_CreateCartesiansLocator(lua_State *L);
int				LuaCharting_CreateChart(lua_State *L);
int				LuaCharting_CreateFunctionRenderer(lua_State *L);
int				LuaCharting_AddChart(lua_State *L);
int				LuaCharting_AddChartPoint(lua_State *L);


