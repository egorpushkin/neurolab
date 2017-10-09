#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_GetLayersCount(lua_State *L);
int				LuaFann121_GetLayer(lua_State *L);
int				LuaFann121_GetLayerDimension(lua_State *L);
int				LuaFann121_GetLayerInputsCount(lua_State *L);
int				LuaFann121_GetNeuron(lua_State *L);
int				LuaFann121_GetNeuronInputsCount(lua_State *L);
int				LuaFann121_GetNeuronWeight(lua_State *L);
int				LuaFann121_GetLayerWeight(lua_State *L);
