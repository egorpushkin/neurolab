#include "StdAfx.h"
#include "DataProcessor.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

// Including Apis of othe data objects
#include "DataFile.h"
#include "DataFactory.h"
#include "DataBitmap.h"

int LuaDataProcessor_GetDataFilesCount(lua_State *L)
{
	if (!CLuaStorage_Solution::pSolution)
		return false;

	lua_pushnumber(L, CLuaStorage_Solution::pSolution->GetDataFilesCount());

    return true;
}

int LuaDataProcessor_GetDataFile(lua_State *L)
{
	if (!CLuaStorage_Solution::pSolution)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	IDataFile* pDataFile = NULL;

	if (lua_isnumber(L, 1))
		pDataFile = CLuaStorage_Solution::GetDataFile(lua_tonumber(L, 1));
	else
		pDataFile = CLuaStorage_Solution::GetDataFile(CString(lua_tostring(L, 1)));

	if (!pDataFile)
		return false;

	PushDataParameter<IDataFile*>(L, -2, pDataFile, "IDataFile*");

	return true;
}

int LuaDataProcessor_GetDataFileName(lua_State *L)
{
	if (!CLuaStorage_Solution::pSolution)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	int iDataFileIndex = lua_tonumber(L, 1);

	CString tmFileName = CLuaStorage_Solution::GetDataFileName(iDataFileIndex);
	if (tmFileName == _T(""))
		return false;

	lua_pushstring(L, tmFileName);

	return true;
}

int LuaDataProcessor_GetBitmap(lua_State *L)
{
	if (!CLuaStorage_Solution::pSolution)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	CString tmFileName = lua_tostring(L, 1);

	IDataBitmap* pDataBitmap = CLuaStorage_Solution::GetBitmap(tmFileName);

	if (!pDataBitmap)
		return false;

	PUSH_ARGUMENT(IDataBitmap*, pDataBitmap, -2);

	return true;
}

// Package initialization
int	luaopen_dataprocessing(lua_State *L)
{
	// Data Processor API
	lua_register(L, "getDataFilesCount", LuaDataProcessor_GetDataFilesCount);
	lua_register(L, "getDataFile", LuaDataProcessor_GetDataFile);
	lua_register(L, "getDataFileName", LuaDataProcessor_GetDataFileName);
	lua_register(L, "getBitmap", LuaDataProcessor_GetBitmap);
	
	// Data File API
	//		Serialization functions
	lua_register(L, "loadDataFile", LuaDataFile_LoadDataFile);
	lua_register(L, "saveDataFile", LuaDataFile_SaveDataFile);
	//		Creation/Destruction functions
	lua_register(L, "createDataFileObject", LuaDataFile_CreateDataFileObject);
	lua_register(L, "releaseDataFileObject", LuaDataFile_ReleaseDataFileObject);
	//		Data File structure building
	lua_register(L, "addDataFileInputSymbol", LuaDataFile_AddDataFileInputSymbol);
	lua_register(L, "addDataFileOutputSymbol", LuaDataFile_AddDataFileOutputSymbol);
	//		Data manipulation functions
	lua_register(L, "getInputSymbolsCount", LuaDataFile_GetInputSymbolsCount);
	lua_register(L, "getOutputSymbolsCount", LuaDataFile_GetOutputSymbolsCount);
	lua_register(L, "getInputSymbolLength", LuaDataFile_GetInputSymbolLength);
	lua_register(L, "getOutputSymbolLength", LuaDataFile_GetOutputSymbolLength);
	lua_register(L, "getInputSymbol", LuaDataFile_GetInputSymbol);
	lua_register(L, "getOutputSymbol", LuaDataFile_GetOutputSymbol);

	// Data Factory API	
	lua_register(L, "loadDataFactoryFromPGM", LuaDataFactory_LoadDataFactoryFromPGM);
	lua_register(L, "saveDataFactoryToPGM", LuaDataFactory_SaveDataFactoryToPGM);
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
	//		UI Tools
	lua_register(L, "displayFactory", LuaDataFactory_DisplayFactory);

	// Data Bitmap API
	lua_register(L, "loadDataBitmapFromPGM", LuaDataBitmap_LoadDataBitmapFromPGM);
	lua_register(L, "releaseBitmapObject", LuaDataBitmap_ReleaseBitmapObject);
	lua_register(L, "getBitmapWidth", LuaDataBitmap_GetBitmapWidth);
	lua_register(L, "getBitmapHeight", LuaDataBitmap_GetBitmapHeight);
	lua_register(L, "getBitmapColorDepth", LuaDataBitmap_GetBitmapColorDepth);

	// PGM Data Bitmap API
	lua_register(L, "getFactoryFromBitmap", LuaDataBitmap_GetFactoryFromBitmap);

	return true;
}