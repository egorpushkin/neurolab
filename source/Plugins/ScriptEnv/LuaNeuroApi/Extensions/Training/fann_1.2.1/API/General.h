#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_CreateArray(lua_State *L);
int				LuaFann121_Destroy(lua_State *L);

int				LuaFann121_Run(lua_State *L);
int				LuaFann121_GetOutputData(lua_State *L);

int				LuaFann121_GetOutputsCount(lua_State *L);