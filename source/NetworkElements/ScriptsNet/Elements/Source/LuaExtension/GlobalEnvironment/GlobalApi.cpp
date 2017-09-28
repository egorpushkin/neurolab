#include "StdAfx.h"
#include "GlobalApi.h"

#include "..\..\LuaEngine\LuaApiMacro.h"
#include "..\GlobalStorage.h"

int	LuaGlobalApi_This(lua_State *L)
{
	PUSH_ARGUMENT(IElement*, CLuaStorage_ThisElement::pElement, -2)
		
	return true;
}

int	LuaGlobalApi_GetInputsFactory(lua_State *L)
{
	PUSH_ARGUMENT(IDataFactory*, CLuaStorage_ThisElement::pInputData, -2)
		
	return true;
}

int	LuaGlobalApi_GetOutputsFactory(lua_State *L)
{
	PUSH_ARGUMENT(IDataFactory*, CLuaStorage_ThisElement::pOutputData, -2)
		
	return true;
}

// Package initialization
int	luaopen_globalenvironment(lua_State *L)
{
	// Gloabal Environment API		
	lua_register(L, "this", LuaGlobalApi_This);
	lua_register(L, "getInputsFactory", LuaGlobalApi_GetInputsFactory);
	lua_register(L, "getOutputsFactory", LuaGlobalApi_GetOutputsFactory);

	return true;
}