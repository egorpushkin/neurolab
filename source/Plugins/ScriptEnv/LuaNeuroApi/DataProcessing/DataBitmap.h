#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Serialization functions
int				LuaDataBitmap_LoadDataBitmapFromPGM(lua_State *L);

// Creation/Destruction functions
int				LuaDataBitmap_ReleaseBitmapObject(lua_State *L);

// Bitmaps general information
int				LuaDataBitmap_GetBitmapWidth(lua_State *L);
int				LuaDataBitmap_GetBitmapHeight(lua_State *L);
int				LuaDataBitmap_GetBitmapColorDepth(lua_State *L);

// Data manipulations
int				LuaDataBitmap_GetFactoryFromBitmap(lua_State *L);
