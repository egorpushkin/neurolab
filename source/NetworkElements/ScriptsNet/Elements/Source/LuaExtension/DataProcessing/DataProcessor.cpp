#include "StdAfx.h"
#include "DataProcessor.h"

// Including Apis of othe data objects
#include "DataFactory.h"

// Package initialization
int	luaopen_dataprocessing(lua_State *L)
{
	// Data Factory API		
	lua_register(L, "createFactoryObject", LuaDataFactory_CreateFactoryObject);
	lua_register(L, "releaseFactoryObject", LuaDataFactory_ReleaseFactoryObject);
	lua_register(L, "createFactory", LuaDataFactory_CreateFactory);
	lua_register(L, "releaseFactory", LuaDataFactory_ReleaseFactory);
	lua_register(L, "setItemData", LuaDataFactory_SetItemData);
	lua_register(L, "fillFactory", LuaDataFactory_FillFactory);
	lua_register(L, "increaseValue", LuaDataFactory_IncreaseValue);
	lua_register(L, "getItemData", LuaDataFactory_GetItemData);
	lua_register(L, "getDataLength", LuaDataFactory_GetDataLength);
	lua_register(L, "moveFactoryData", LuaDataFactory_MoveFactoryData);

	return true;
}