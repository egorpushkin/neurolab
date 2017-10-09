#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaCharting_SetAxesRanges(lua_State *L);
int				LuaCharting_SetScale(lua_State *L);


