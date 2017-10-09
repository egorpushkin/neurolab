#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// IElement members
int				LuaElement_GetElementSysName(lua_State *L);
int				LuaElement_GetElementType(lua_State *L);
int				LuaElement_GetElementID(lua_State *L);

// Additional functionality
int				LuaElement_IsLayer(lua_State *L);

// sFunction members
int				LuaElement_ProcessFunction(lua_State *L);
int				LuaElement_ProcessDerivative(lua_State *L);
int				LuaElement_GetFunctionName(lua_State *L);

// IDataFlow members
int				LuaElement_GetElementFunction(lua_State *L);
int				LuaElement_IsElementRequireData(lua_State *L);
int				LuaElement_SetElementWaitDataState(lua_State *L);
int				LuaElement_IsElementReadyForProcessing(lua_State *L);
int				LuaElement_ElementFlowData(lua_State *L);
int				LuaElement_ProcessElement(lua_State *L);
int				LuaElement_IsElementReadyForTraining(lua_State *L);
int				LuaElement_ElementBackFlow(lua_State *L);
int				LuaElement_GetElementData(lua_State *L);
int				LuaElement_SetElementData(lua_State *L);
int				LuaElement_SplitElementConnectionsData(lua_State *L);

// IConnectionsFactory members
int				LuaElement_GetConnectionsCount(lua_State *L);
int				LuaElement_CreateConnectionsEnumerator(lua_State *L);
int				LuaElement_GetNextConnection(lua_State *L);

// CConnection members
int				LuaElement_GetConnectionElement(lua_State *L);
int				LuaElement_GetOppositeConnection(lua_State *L);
int				LuaElement_GetWeightsFactory(lua_State *L);
int				LuaElement_GetOldWeightsFactory(lua_State *L);
int				LuaElement_GetConnectionData(lua_State *L);
int				LuaElement_IsConnectionHasData(lua_State *L);
int				LuaElement_GetConnectionDeltas(lua_State *L);

// IDataConnector members
int				LuaElement_GetConnectionsFactory(lua_State *L);

// ILayerControl members
int				LuaElement_SetLayerInputData(lua_State *L);
int				LuaElement_SetLayerOutputData(lua_State *L);
int				LuaElement_ModifyLayerWeights(lua_State *L);
int				LuaElement_ResetLayerWeights(lua_State *L);
int				LuaElement_GetLayerDimension(lua_State *L);
int				LuaElement_GetLayerInputsCount(lua_State *L);
int				LuaElement_GetLayerWeight(lua_State *L);
int				LuaElement_SetLayerWeight(lua_State *L);
int				LuaElement_SetLayerDelta(lua_State *L);
int				LuaElement_GetLayerDelta(lua_State *L);