#include "StdAfx.h"
#include "DataFile.h"

#include "CmnDataFile.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

// Serialization functions
int LuaDataFile_LoadDataFile(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	// Receiving and processing Data File name argument 
	CString csFileName = lua_tostring(L, 1);
	if (csFileName.Find(":") == -1)
		csFileName = 
			CLuaStorage_GlobalEnvironment::csCurrentDirectory + 
			CString("\\") + 
			csFileName;

	// Creating new Data File object and loading content from the specified file
	CDataFile* pDataFile = new CDataFile;
	bool bRet = pDataFile->LoadFile(csFileName);
	if (!bRet)
	{
		// Releasing object and returning no value in case of unsuccessful loading
		delete pDataFile;
		return false;
	}

	// Preparing object control interface
	IDataFile* pDataFileIn = NULL;
	pDataFile->QueryInterface(IDD_IDataFile, (void**)&pDataFileIn);

	// Registring new Data File object
	CLuaStorage_DataFilesContainer::AddObject(pDataFileIn);

	// Returning IDataFile wrapper object
	PUSH_ARGUMENT(IDataFile*, pDataFileIn, -2)

	return true;
}

int LuaDataFile_SaveDataFile(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	// Receiving Data File object to be saved
	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	// Receiving and processing Data File name argument 
	CString csFileName = lua_tostring(L, 2);
	if (csFileName.Find(":") == -1)
		csFileName = 
			CLuaStorage_GlobalEnvironment::csCurrentDirectory + 
			CString("\\") + 
			csFileName;

	// Perforning object serialization
	bool bRet = pDataFile->SaveToFile(csFileName);
	
	return bRet;
}

// Creation/Destruction functions
int LuaDataFile_CreateDataFileObject(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)
    
	// Receiving and verifying arguments
	int iInputSymbolLength = lua_tonumber(L, 1);
	int iOutputSymbolLength = lua_tonumber(L, 2);

	if (iInputSymbolLength < 0 ||
		iOutputSymbolLength < 0)
		return false;

	// Creating new Data File object 
	CDataFile* pDataFile = new CDataFile();
	
	// Initializing object
	pDataFile->CreateNewFile(
		iInputSymbolLength,
		iOutputSymbolLength);

	// Preparing object control interface
	IDataFile* pDataFileIn = NULL;
	pDataFile->QueryInterface(IDD_IDataFile, (void**)&pDataFileIn);	

	// Registring new Data File object
	CLuaStorage_DataFilesContainer::AddObject(pDataFileIn);
	
	// Returning IDataFile wrapper object
	PUSH_ARGUMENT(IDataFile*, pDataFileIn, -2)

	return true;
}

int LuaDataFile_ReleaseDataFileObject(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	bool bRemoved = CLuaStorage_DataFilesContainer::RemoveObject(pDataFile);
	lua_pushboolean(L, bRemoved);

	return true;
}

// Data File structure building
int LuaDataFile_AddDataFileInputSymbol(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	if (pDataFactory->GetDataLength() != pDataFile->GetInputSymbolLength())
		return false;

	pDataFile->AddInputSymbol(pDataFactory);

	return true;
}

int LuaDataFile_AddDataFileOutputSymbol(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)
	POP_ARGUMENT(IDataFactory*, pDataFactory, 2)

	if (pDataFactory->GetDataLength() != pDataFile->GetOutputSymbolLength())
		return false;

	pDataFile->AddOutputSymbol(pDataFactory);

	return true;
}

// Data manipulation functions
int LuaDataFile_GetInputSymbolsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	lua_pushnumber(L, pDataFile->GetInputSymbolsCount());

	return true;
}

int	LuaDataFile_GetOutputSymbolsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	lua_pushnumber(L, pDataFile->GetOutputSymbolsCount());

	return true;
}

int	LuaDataFile_GetInputSymbolLength(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	lua_pushnumber(L, pDataFile->GetInputSymbolLength());

	return true;
}

int	LuaDataFile_GetOutputSymbolLength(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	lua_pushnumber(L, pDataFile->GetOutputSymbolLength());
	
	return true;
}

int	LuaDataFile_GetInputSymbol(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)
	int iSymbolIndex = lua_tonumber(L, 2);

	IDataFactory* pDataFactory = pDataFile->GetInputSymbol(iSymbolIndex);
	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)
	
	return true;
}

int	LuaDataFile_GetOutputSymbol(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)
	int iSymbolIndex = lua_tonumber(L, 2);

	IDataFactory* pDataFactory = pDataFile->GetOutputSymbol(iSymbolIndex);
	if (!pDataFactory)
		return false;

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)
	
	return true;
}