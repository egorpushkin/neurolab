#pragma once

#define LUA_API extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFann121_TrainOnFannData(lua_State *L);

int				LuaFann121_ClearTrainArrays(lua_State *L);

int				LuaFann121_UpdateWeightsQuickprop(lua_State *L);
int				LuaFann121_UpdateWeightsIrpropm(lua_State *L);
int				LuaFann121_UpdateWeightsBatch(lua_State *L);
int				LuaFann121_Train(lua_State *L);

int				LuaFann121_IsSlopesUpdateRequired(lua_State *L);
int				LuaFann121_UpdateSlopesBatch(lua_State *L);

