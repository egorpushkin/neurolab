#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
}

// Package initialization
int				luaopen_network(lua_State *L);