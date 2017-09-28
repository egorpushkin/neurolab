#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaElementsCollection_GetNetworkElement(lua_State *L);

int				LuaElementsCollection_GetInputsCount(lua_State *L);
int				LuaElementsCollection_GetOutputsCount(lua_State *L);

int				LuaElementsCollection_CreateElementsEnumerator(lua_State *L);
int				LuaElementsCollection_GetNextElement(lua_State *L);