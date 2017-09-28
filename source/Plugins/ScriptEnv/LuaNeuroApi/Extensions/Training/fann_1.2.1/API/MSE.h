#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_ResetMSE(lua_State *L);
int				LuaFann121_GetMSE(lua_State *L);
int				LuaFann121_ComputeMSE(lua_State *L);
int				LuaFann121_BackpropagateMSE(lua_State *L);

