#include "StdAfx.h"
#include "NetworkProcessorEx.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

#include "CmnDataFactory.h"

// Network procesors access functions
int	LuaNetworkProcessorEx_GetNetworkProcessor(lua_State *L)
{
	if (!CLuaStorage_Solution::pSolution)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	CString tmFileName = lua_tostring(L, 1);

	IImportManager* pImportManager = CLuaStorage_Solution::GetProject(tmFileName);

	if (!pImportManager)
		return false;

	PUSH_ARGUMENT(IImportManager*, pImportManager, -2)

	return true;
}

// Processing Functions
int	LuaNetworkProcessorEx_ProcessNetworkEx(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IImportManager*, pImportManager, 1)

	INetworkProcessor* pNetworkProcessor = NULL;
	pImportManager->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->ProcessNetwork();

	return true;
}

// Data passing functions
int	LuaNetworkProcessorEx_SetInputDataEx(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IImportManager*, pImportManager, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	INetworkProcessor* pNetworkProcessor = NULL;
	pImportManager->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->SetInputData(pDataFactory);

	return true;
}

int	LuaNetworkProcessorEx_SetOutputDataEx(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IImportManager*, pImportManager, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	INetworkProcessor* pNetworkProcessor = NULL;
	pImportManager->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->SetOutputData(pDataFactory);

	return true;
}

int	LuaNetworkProcessorEx_GetInputDataEx(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IImportManager*, pImportManager, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	INetworkProcessor* pNetworkProcessor = NULL;
	pImportManager->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->GetInputData(pDataFactory);

	return true;
}

int	LuaNetworkProcessorEx_GetOutputDataEx(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IImportManager*, pImportManager, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	INetworkProcessor* pNetworkProcessor = NULL;
	pImportManager->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->GetOutputData(pDataFactory);

	return true;
}

// Package initialization
int luaopen_network_ex(lua_State *L)
{
	// Network Processor API
	lua_register(L, "getNetworkProcessor", LuaNetworkProcessorEx_GetNetworkProcessor);

	lua_register(L, "processNetworkEx", LuaNetworkProcessorEx_ProcessNetworkEx);
	lua_register(L, "setInputDataEx", LuaNetworkProcessorEx_SetInputDataEx);
	lua_register(L, "setOutputDataEx", LuaNetworkProcessorEx_SetOutputDataEx);
	lua_register(L, "getInputDataEx", LuaNetworkProcessorEx_GetInputDataEx);
	lua_register(L, "getOutputDataEx", LuaNetworkProcessorEx_GetOutputDataEx);

	return true;
}