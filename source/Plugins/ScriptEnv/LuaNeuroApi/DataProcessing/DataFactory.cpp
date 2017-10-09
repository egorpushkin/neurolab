#include "StdAfx.h"
#include "DataFactory.h"

#include "CmnDecl.h"
#include "CmnDataFactory.h"
#include "CmnPGMFactory.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

#include "Math.h"

#include "UITools\DataFactoryDisplayToolDlg.h"

// Serialization functions
int	LuaDataFactory_LoadDataFactoryFromPGM(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	CString tmFileName = lua_tostring(L, 1);
	if (tmFileName.Find(":") == -1)
		tmFileName = 
			CLuaStorage_GlobalEnvironment::csCurrentDirectory + 
			CString("\\") + 
			tmFileName;

	CPGMFactory* pPGMFactory = new CPGMFactory;
	bool bRet = pPGMFactory->LoadPGMFile(tmFileName);
	if (!bRet)
	{
		delete pPGMFactory;
        return false;
	}

	IDataFactory* pDataFactory = NULL;
	pPGMFactory->QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);

	CLuaStorage_FactoriesContainer::AddObject(pDataFactory);

	PUSH_ARGUMENT(IDataFactory*, pDataFactory, -2)

	return true;
}

int	LuaDataFactory_SaveDataFactoryToPGM(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(4)	

	// Receive arguments
	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	CString fileName = lua_tostring(L, 2);
	int width = lua_tonumber(L, 3);
	int height = lua_tonumber(L, 4);

	int colorDepth = 255;
	if (iNumber == 5)
		colorDepth = lua_tonumber(L, 5);	

	// Process arguments
	if (fileName.Find(":") == -1)
		fileName = 
			CLuaStorage_GlobalEnvironment::csCurrentDirectory + 
			CString("\\") + 
			fileName;

	// Perform operation
	CPGMBitmap tmPGMBitmap; 
	tmPGMBitmap.ConstructFromDataFactory(pDataFactory, width, height);
	tmPGMBitmap.SavePGMBitmap(fileName);

	return true;
}

// Creation/Destruction functions
int	LuaDataFactory_CreateFactoryObject(lua_State *L)
{
	CDataFactory* pDataFactory = new CDataFactory();
	CLuaStorage_FactoriesContainer::AddObject(pDataFactory);

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

	IDataFactory* pDataFactoryIn = NULL;
	pDataFactory->QueryInterface(IDD_IDataFactory, (void**)&pDataFactoryIn);

	PUSH_ARGUMENT(IDataFactory*, pDataFactoryIn, -2)

	return true;
}

int	LuaDataFactory_ReleaseFactoryObject(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)

	bool bRemoved = CLuaStorage_FactoriesContainer::RemoveObject(pDataFactory);
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

// UI Tools
int LuaDataFactory_DisplayFactory(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(IDataFactory*, pDataFactory, 1)
	CString tmName = lua_tostring(L, 2);
	
	int iWidth = 0, iHeight = 0;
	if (iNumber == 4)
	{
		iWidth = lua_tonumber(L, 3);
		iHeight = lua_tonumber(L, 4);
	} 
	else if (pDataFactory->GetDataLength() != 0)
	{
		iWidth = sqrt((pDataFactory->GetDataLength() - 1)*1.0f) + 1;		
		iHeight = (pDataFactory->GetDataLength() - 1)/iWidth + 1;	
	}

	sDataFactoryDisplayStruct* pData = new sDataFactoryDisplayStruct;
	pData->iWidth = iWidth;
	pData->iHeight = iHeight;
	pData->csName = tmName;

	pData->mDataFactory.CreateFactory(pDataFactory->GetDataLength());
	pData->mDataFactory.SetData(pDataFactory->GetData(), pDataFactory->GetDataLength());

	 __beginthreadex(NULL, 0, DisplayDataFactoryThread, pData, 0, NULL);

	return true;
}

// Data Factory Toolbox Internal utilities
DWORD WINAPI DisplayDataFactoryThread(PVOID Param)
{
	sDataFactoryDisplayStruct* pData = (sDataFactoryDisplayStruct*)Param;

	CDataFactoryDisplayToolDlg mDlg;
	mDlg.pData = pData;
	mDlg.DoModal();
    
	delete pData;

	return 0;
}