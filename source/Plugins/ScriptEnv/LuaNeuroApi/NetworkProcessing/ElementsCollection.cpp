#include "StdAfx.h"
#include "ElementsCollection.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

int	LuaElementsCollection_GetNetworkElement(lua_State *L)
{
	if (!CLuaStorage_NetworkProcessor::pElementsCollection)
		return false;

	CHECK_ARGUMENTS_COUNT(2)

	CString csElementSysName = lua_tostring(L, 1);
	int iElementID = lua_tonumber(L, 2);

	CLuaStorage_NetworkProcessor::pElementsCollection->CreateElementsEnumerator(
		USER_ENUMERATOR_RANGE_FROM);
	while (IElement* pElement = CLuaStorage_NetworkProcessor::pElementsCollection->
		GetNextElement(USER_ENUMERATOR_RANGE_FROM))
		if (pElement->GetElementID() == iElementID && 
			pElement->GetSysName() == csElementSysName)
		{
			PUSH_ARGUMENT(IElement*, pElement, -2)

            return true;		
		}	

	return false;
}

int	LuaElementsCollection_GetInputsCount(lua_State *L)
{
	if (!CLuaStorage_NetworkProcessor::pElementsCollection)
		return false;

	int iInputsCount = CLuaStorage_NetworkProcessor::
		pElementsCollection->GetInputsCount();
	lua_pushnumber(L, iInputsCount);

	return true;
}

int	LuaElementsCollection_GetOutputsCount(lua_State *L)
{
	if (!CLuaStorage_NetworkProcessor::pElementsCollection)
		return false;

	int iOutputsCount = CLuaStorage_NetworkProcessor::
		pElementsCollection->GetOutputsCount();
	lua_pushnumber(L, iOutputsCount);

	return true;
}

int	LuaElementsCollection_CreateElementsEnumerator(lua_State *L)
{
	if (!CLuaStorage_NetworkProcessor::pElementsCollection)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	POP_ENUMERATOR_INDEX(iEnumeratorPosition, 1)

	CLuaStorage_NetworkProcessor::
		pElementsCollection->CreateElementsEnumerator(iEnumeratorPosition);

	return true;
}

int	LuaElementsCollection_GetNextElement(lua_State *L)
{
	if (!CLuaStorage_NetworkProcessor::pElementsCollection)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	POP_ENUMERATOR_INDEX(iEnumeratorPosition, 1)

	IElement* pElement = 
		CLuaStorage_NetworkProcessor::pElementsCollection->GetNextElement(iEnumeratorPosition);
	if (!pElement)
		return false;
    
	PUSH_ARGUMENT(IElement*, pElement, -2)

	return true;
}