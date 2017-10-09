#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
} 

// Creation/Destruction functions
int				LuaDataFactory_CreateFactoryObject(lua_State *L);
int				LuaDataFactory_ReleaseFactoryObject(lua_State *L);

int				LuaDataFactory_CreateFactory(lua_State *L);
int				LuaDataFactory_ReleaseFactory(lua_State *L);

// Data manipulation functions
int				LuaDataFactory_SetItemData(lua_State *L);
int				LuaDataFactory_FillFactory(lua_State *L);
int				LuaDataFactory_IncreaseValue(lua_State *L);

int				LuaDataFactory_GetItemData(lua_State *L);
int				LuaDataFactory_GetDataLength(lua_State *L);

int				LuaDataFactory_MoveFactoryData(lua_State *L);

