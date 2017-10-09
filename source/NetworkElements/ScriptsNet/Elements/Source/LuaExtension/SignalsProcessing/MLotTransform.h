#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
} 

// Fast Discrete Cosine Transform, type IV
int				LuaMLotTransform_FDCS4(lua_State *L);
