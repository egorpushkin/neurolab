#include "StdAfx.h"
#include "DataFactory.h"

#include "..\..\LuaEngine\LuaApiMacro.h"
#include "..\GlobalStorage.h"

#include "CmnDataFactory.h"

// Creation/Destruction functions
int	LuaDataFactory_CreateFactoryObject(lua_State *L)
{
	CDataFactory* pDataFactory = new CDataFactory();
	CLuaStorage_FactoriesContainer::AddFactory(pDataFactory);

	int iNumber = lua_gettop(L);
	if (iNumber == 1)
	{
		int iDataLength = lua_tonumber(L, 1);

		pDataFactory->CreateFactory(iDataLength);
	} else if (iNumber == 2)
	{
		int iDataLength = lua_tonumber(L, 1);
		float fValue = lua_tonumber(L, 2);

		pDataFactory->CreateFactory(iDataLength, fValue);	
	}

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

int	LuaDataFactory_ReleaseFactoryObject(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)

	bool bRemoved = CLuaStorage_FactoriesContainer::RemoveFactory(pDataFactory);
	lua_pushboolean(L, bRemoved);
    
	return true;
}

int	LuaDataFactory_CreateFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	int iDataLength = lua_tonumber(L, 2);
	float fValue = 0.0f;

	if (iNumber == 3)
		fValue = lua_tonumber(L, 3);

	pDataFactory->CreateFactory(iDataLength, fValue);

	return true;
}

int	LuaDataFactory_ReleaseFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)

	pDataFactory->ReleaseFactory();

	return true;
}

// Data manipulation functions
int LuaDataFactory_SetItemData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	int iIndex = lua_tonumber(L, 2);
	float fData = lua_tonumber(L, 3);
    
	pDataFactory->SetItemData(iIndex, fData);

	return true;
}

int LuaDataFactory_FillFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	float fData = lua_tonumber(L, 2);

	pDataFactory->FillFactory(fData);

	return true;
}

int LuaDataFactory_IncreaseValue(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	int iIndex = lua_tonumber(L, 2);
	float fData = lua_tonumber(L, 3);

	pDataFactory->IncreaseValue(iIndex, fData);

	return true;
}

int LuaDataFactory_GetItemData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	int iIndex = lua_tonumber(L, 2);

	float fData = pDataFactory->GetItemData(iIndex);
	lua_pushnumber(L, (double)fData);

	return true;
}

int LuaDataFactory_GetDataLength(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)

	lua_pushnumber(L, pDataFactory->GetDataLength());

	return true;
}

int LuaDataFactory_MoveFactoryData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(5)

	POP_ARGUMENT(IDataFactory*, pSourceDataFactory, 1)
	int iSourceOffset = lua_tonumber(L, 2);
	int iDataLength = lua_tonumber(L, 3);
	POP_ARGUMENT(IDataFactory*, pDestinationDataFactory, 4)
	int iDestinationOffset = lua_tonumber(L, 5);

	if (iSourceOffset < 0 || 
		iDataLength <= 0 || 
		iDestinationOffset < 0 || 
		!pSourceDataFactory->GetData() || 
		!pDestinationDataFactory->GetData())
		return false;

    if (iSourceOffset + iDataLength > pSourceDataFactory->GetDataLength())
		return false;

    if (iDestinationOffset + iDataLength > pDestinationDataFactory->GetDataLength())
		return false;

    memcpy(pDestinationDataFactory->GetData() + iDestinationOffset, 
		pSourceDataFactory->GetData() + iSourceOffset, 
		sizeof(float)*iDataLength);

	return true;
}