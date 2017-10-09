#include "StdAfx.h"
#include "System.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

// Including Apis this package
#include "BinDataManipulations.h"
#include "Threading.h"

// Package initialization
int luaopen_system(lua_State *L)
{
	lua_register(L, "sleep", LuaThreading_Sleep);

	lua_register(L, "convertBin2Float", LuaBinDataManipulations_ConvertBin2Float);
	lua_register(L, "convertBin2Int", LuaBinDataManipulations_ConvertBin2Int);

	lua_pushstring(L, "INT_SIZE");
	lua_pushnumber(L, sizeof(int));
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "BOOL_SIZE");
	lua_pushnumber(L, sizeof(bool));
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "FLOAT_SIZE");
	lua_pushnumber(L, sizeof(float));
	lua_settable(L, LUA_GLOBALSINDEX);

	return true;
}