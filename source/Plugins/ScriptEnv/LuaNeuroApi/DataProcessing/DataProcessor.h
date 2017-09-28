#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaDataProcessor_GetDataFilesCount(lua_State *L);
int				LuaDataProcessor_GetDataFile(lua_State *L);
int				LuaDataProcessor_GetDataFileName(lua_State *L);
int				LuaDataProcessor_GetBitmap(lua_State *L);

// Package initialization
int				luaopen_dataprocessing(lua_State *L);