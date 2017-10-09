#include "StdAfx.h"
#include "SignalsProcessor.h"

// Including Apis of othe data objects
#include "MLotTransform.h"

// Package initialization
int	luaopen_signalsprocessing(lua_State *L)
{
	// Data Factory API		
	lua_register(L, "mlot_fdcs4", LuaMLotTransform_FDCS4);

	return true;
}