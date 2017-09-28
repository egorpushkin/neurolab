#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaCharting_DisplayCtrl(lua_State *L);
int				LuaCharting_ReleaseCtrl(lua_State *L);


// Package initialization
int				luaopen_charting (lua_State *L);
