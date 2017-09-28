#include "StdAfx.h"
#include "NetworkProcessor.h"

#include "..\..\LuaEngine\LuaApiMacro.h"
#include "..\GlobalStorage.h"

// IElement members
int	LuaElement_GetElementSysName(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)

	lua_pushstring(L, pElement->GetSysName());

	return true;
}

int LuaElement_GetElementType(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)

	lua_pushnumber(L, pElement->GetElementType());

	return true;
}

int LuaElement_GetElementID(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)

	lua_pushnumber(L, pElement->GetElementID());

	return true;
}

// Additional functionality
int	LuaElement_IsLayer(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)

	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

	lua_pushboolean(L, (pLayerControl != NULL));

	return true;
}

// sFunction members
int	LuaElement_ProcessFunction(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(sFunction*, pFunction, 1)
	float fValue = lua_tonumber(L, 2);

	float fResult = (*pFunction->pfnProcessFunction)(pFunction, fValue);
	lua_pushnumber(L, fResult);

	return true;
}

int LuaElement_ProcessDerivative(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(sFunction*, pFunction, 1)
	float fValue = lua_tonumber(L, 2);

	float fResult = (*pFunction->pfnProcessDerivative)(pFunction, fValue);
	lua_pushnumber(L, fResult);

	return true;
}

int	LuaElement_GetFunctionName(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)
	POP_ARGUMENT(sFunction*, pFunction, 1)

	lua_pushstring(L, pFunction->csName);

	return true;
}

// IDataFlow members
int	LuaElement_GetElementFunction(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	sFunction* pFunction = pDataFlow->GetElementFunction();
	PushDataParameter<sFunction*>(L, -2, pFunction, "sFunction*");		

	return true;
}

int	LuaElement_IsElementRequireData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	bool bIsRequireData = pDataFlow->RequireData();
	lua_pushboolean(L, bIsRequireData);

	return true;
}

int	LuaElement_SetElementWaitDataState(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->SetWaitDataState();

	return true;
}

int	LuaElement_IsElementReadyForProcessing(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	bool bIsReadyForProcessing = pDataFlow->IsReadyForProcessing();
	lua_pushboolean(L, bIsReadyForProcessing);

	return true;
}

int	LuaElement_ElementFlowData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->FlowData();

	return true;
}

int	LuaElement_ProcessElement(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->ProcessElement();

	return true;
}

int	LuaElement_IsElementReadyForTraining(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	bool bIsReadyForTraining = pDataFlow->IsReadyForTraining();
	lua_pushboolean(L, bIsReadyForTraining);

	return true;
}

int	LuaElement_ElementBackFlow(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->BackFlow();

	return true;
}

int	LuaElement_GetElementData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->GetElementData(pDataFactory);

	return true;
}

int	LuaElement_SetElementData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)
	
	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->SetElementData(pDataFactory);

	return true;
}

int	LuaElement_SplitElementConnectionsData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(IElement*, pElement, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)
	int iFactoryType = lua_tonumber(L, 3);

	IDataFlow* pDataFlow = NULL;
	pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

	pDataFlow->SplitConnectionsData(pDataFactory, iFactoryType);

	return true;
}

// IConnectionsFactory members
int LuaElement_GetConnectionsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IConnectionsFactory*, pConnectionsFactory, 1)

	lua_pushnumber(L, pConnectionsFactory->GetConnectionsCount());

	return true;
}

int	LuaElement_CreateConnectionsEnumerator(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IConnectionsFactory*, pConnectionsFactory, 1)
	POP_ENUMERATOR_INDEX(iEnumeratorPosition, 2)

	pConnectionsFactory->CreateEnumerator(iEnumeratorPosition);

	return true;
}

int	LuaElement_GetNextConnection(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IConnectionsFactory*, pConnectionsFactory, 1)
	POP_ENUMERATOR_INDEX(iEnumeratorPosition, 2)

	CConnection* pConnection = pConnectionsFactory->GetNextConnection(iEnumeratorPosition);
	if (!pConnection)
		return false;

	PushDataParameter<CConnection*>(L, -2, pConnection, "CConnection*");

	return true;
}

// CConnection members
int LuaElement_GetConnectionElement(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	PUSH_ARGUMENT(IElement*, pConnection->pElement, -2)

	return true;
}

int LuaElement_GetOppositeConnection(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	PUSH_ARGUMENT(CConnection*, pConnection->pOpposite, -2)

	return true;
}

int LuaElement_GetWeightsFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	IDataFactory* pDataFactory = NULL;
	pConnection->mWeights.QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);

	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

int LuaElement_GetOldWeightsFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	IDataFactory* pDataFactory = NULL;
	pConnection->mOldWeights.QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);

	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

int LuaElement_GetConnectionData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	IDataFactory* pDataFactory = NULL;
	pConnection->mData.QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);

	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

int LuaElement_IsConnectionHasData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	lua_pushboolean(L, pConnection->bHasData);

	return true;
}

int LuaElement_GetConnectionDeltas(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(CConnection*, pConnection, 1)

	IDataFactory* pDataFactory = NULL;
	pConnection->mDeltas.QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);

	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

// IDataConnector members
int	LuaElement_GetConnectionsFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	int iFactoryType = lua_tonumber(L, 2);
	
	IDataConnector* pDataConnector = NULL;
	pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

	IConnectionsFactory* pFactory = 
		pDataConnector->GetConnectionsFactory(iFactoryType);
	if (!pFactory)
		return false;

	PushDataParameter<IConnectionsFactory*>(L, -2, pFactory, "IConnectionsFactory*");

	return true;
}

// ILayerControl members
int	LuaElement_SetLayerInputData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)
	
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->SetInputData(pDataFactory);

	return true;
}

int	LuaElement_SetLayerOutputData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)
	
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->SetOutputData(pDataFactory);

	return true;
}

int	LuaElement_ModifyLayerWeights(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->ModifyWeights();

	return true;
}

int	LuaElement_ResetLayerWeights(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	float fValue = lua_tonumber(L, 2);
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->ResetWeights(fValue);

	return true;
}

int	LuaElement_GetLayerDimension(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	int iDimension = pLayerControl->GetDimension();
	lua_pushnumber(L, iDimension);

	return true;
}

int	LuaElement_GetLayerInputsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IElement*, pElement, 1)
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	int iInputsCount = pLayerControl->GetInputsCount();
	lua_pushnumber(L, iInputsCount);

	return true;
}

int	LuaElement_GetLayerWeight(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(IElement*, pElement, 1)
	int iInput = lua_tonumber(L, 2);
	int iNeuron = lua_tonumber(L, 3);
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	float fWeight = pLayerControl->GetWeight(iInput, iNeuron);
	lua_pushnumber(L, fWeight);

	return true;
}

int	LuaElement_SetLayerWeight(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(4)

	POP_ARGUMENT(IElement*, pElement, 1)
	int iInput = lua_tonumber(L, 2);
	int iNeuron = lua_tonumber(L, 3);
	float fWeight = lua_tonumber(L, 4);
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->SetWeight(iInput, iNeuron, fWeight);
	
	return true;
}

int	LuaElement_SetLayerDelta(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(IElement*, pElement, 1)
	int iNeuron = lua_tonumber(L, 2);
	float fDelta = lua_tonumber(L, 3);
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	pLayerControl->SetDelta(iNeuron, fDelta);

	return true;
}

int	LuaElement_GetLayerDelta(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IElement*, pElement, 1)
	int iNeuron = lua_tonumber(L, 2);
		
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
	if (!pLayerControl)
		return false;

	float fDelta = pLayerControl->GetDelta(iNeuron);
	lua_tonumber(L, fDelta);

	return true;
}