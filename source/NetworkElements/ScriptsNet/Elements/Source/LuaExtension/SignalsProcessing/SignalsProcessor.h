#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
} 

// Package initialization
int				luaopen_signalsprocessing(lua_State *L);