#include "StdAfx.h"
#include "NetworkProcessor.h"

#include "CmnElement.h"

// Including Apis of othe network objects
#include "Element.h"

// Package initialization
int luaopen_network(lua_State *L)
{
	// Element API
	//     IElement members
	lua_register(L, "getElementSysName", LuaElement_GetElementSysName);
	lua_register(L, "getElementType", LuaElement_GetElementType);
	lua_register(L, "getElementID", LuaElement_GetElementID);
	//     Additional functionality
	lua_register(L, "isLayer", LuaElement_IsLayer);
	//     sFunction members
	lua_register(L, "processFunction", LuaElement_ProcessFunction);
	lua_register(L, "processDerivative", LuaElement_ProcessDerivative);
	lua_register(L, "getFunctionName", LuaElement_GetFunctionName);
	//     IDataFlow members
	lua_register(L, "getElementFunction", LuaElement_GetElementFunction);
	lua_register(L, "isElementRequireData", LuaElement_IsElementRequireData);
	lua_register(L, "setElementWaitDataState", LuaElement_SetElementWaitDataState);
	lua_register(L, "isElementReadyForProcessing", LuaElement_IsElementReadyForProcessing);
	lua_register(L, "elementFlowData", LuaElement_ElementFlowData);
	lua_register(L, "processElement", LuaElement_ProcessElement);
	lua_register(L, "isElementReadyForTraining", LuaElement_IsElementReadyForTraining);
	lua_register(L, "elementBackFlow", LuaElement_ElementBackFlow);
	lua_register(L, "getElementData", LuaElement_GetElementData);
	lua_register(L, "setElementData", LuaElement_SetElementData);
	lua_register(L, "splitElementConnectionsData", LuaElement_SplitElementConnectionsData);
	//     IConnectionsFactory members
	lua_register(L, "getConnectionsCount", LuaElement_GetConnectionsCount);
	lua_register(L, "createConnectionsEnumerator", LuaElement_CreateConnectionsEnumerator);
	lua_register(L, "getNextConnection", LuaElement_GetNextConnection);
	//		CConnection members
	lua_register(L, "getConnectionElement", LuaElement_GetConnectionElement);
	lua_register(L, "getOppositeConnection", LuaElement_GetOppositeConnection);
	lua_register(L, "getWeightsFactory", LuaElement_GetWeightsFactory);
	lua_register(L, "getOldWeightsFactory", LuaElement_GetOldWeightsFactory);
	lua_register(L, "getConnectionData", LuaElement_GetConnectionData);
	lua_register(L, "isConnectionHasData", LuaElement_IsConnectionHasData);
	lua_register(L, "getConnectionDeltas", LuaElement_GetConnectionDeltas);
	//     IDataConnector members
	lua_register(L, "getConnectionsFactory", LuaElement_GetConnectionsFactory);
	//     ILayerControl members
	lua_register(L, "setLayerInputData", LuaElement_SetLayerInputData);
	lua_register(L, "setLayerOutputData", LuaElement_SetLayerOutputData);
	lua_register(L, "modifyLayerWeights", LuaElement_ModifyLayerWeights);
	lua_register(L, "resetLayerWeights", LuaElement_ResetLayerWeights);
	lua_register(L, "getLayerDimension", LuaElement_GetLayerDimension);
	lua_register(L, "getLayerInputsCount", LuaElement_GetLayerInputsCount);
	lua_register(L, "getLayerWeight", LuaElement_GetLayerWeight);
	lua_register(L, "setLayerWeight", LuaElement_SetLayerWeight);
	lua_register(L, "setLayerDelta", LuaElement_SetLayerDelta);
	lua_register(L, "getLayerDelta", LuaElement_GetLayerDelta);

	// Registring global constants 
	lua_pushstring(L, "DC_INPUTS_FACTORY");
	lua_pushnumber(L, DC_INPUTS_FACTORY);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "DC_OUTPUTS_FACTORY");
	lua_pushnumber(L, DC_OUTPUTS_FACTORY);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "ET_INPUT");
	lua_pushnumber(L, ET_INPUT);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "ET_OUTPUT");
	lua_pushnumber(L, ET_OUTPUT);	
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "ET_PROCESSOR");
	lua_pushnumber(L, ET_PROCESSOR);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "ET_BENCHMARK");
	lua_pushnumber(L, ET_BENCHMARK);
	lua_settable(L, LUA_GLOBALSINDEX);

	return true;
}