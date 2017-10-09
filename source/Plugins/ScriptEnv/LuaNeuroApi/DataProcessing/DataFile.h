#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Serialization functions
int				LuaDataFile_LoadDataFile(lua_State *L);
int				LuaDataFile_SaveDataFile(lua_State *L);

// Creation/Destruction functions
int				LuaDataFile_CreateDataFileObject(lua_State *L);
int				LuaDataFile_ReleaseDataFileObject(lua_State *L);

// Data File structure building
int				LuaDataFile_AddDataFileInputSymbol(lua_State *L);
int				LuaDataFile_AddDataFileOutputSymbol(lua_State *L);

// Data manipulation functions
int				LuaDataFile_GetInputSymbolsCount(lua_State *L);
int				LuaDataFile_GetOutputSymbolsCount(lua_State *L);

int				LuaDataFile_GetInputSymbolLength(lua_State *L);
int				LuaDataFile_GetOutputSymbolLength(lua_State *L);

int				LuaDataFile_GetInputSymbol(lua_State *L);
int				LuaDataFile_GetOutputSymbol(lua_State *L);