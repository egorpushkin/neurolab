#include "StdAfx.h"
#include "DataBitmap.h"

#include "CmnBitmap.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

// Serialization functions
int LuaDataBitmap_LoadDataBitmapFromPGM(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	CString tmFileName = lua_tostring(L, 1);
	if (tmFileName.Find(":") == -1)
		tmFileName = 
			CLuaStorage_GlobalEnvironment::csCurrentDirectory + 
			CString("\\") + 
			tmFileName;

	CPGMBitmap* pPGMBitmap = new CPGMBitmap;
	bool bRet = pPGMBitmap->LoadPGMBitmap(tmFileName);
	if (!bRet)
	{
		delete pPGMBitmap;
        return false;
	}

	IDataBitmap* pDataBitmap = NULL;
	pPGMBitmap->QueryInterface(IDD_IDataBitmap, (void**)&pDataBitmap);

	CLuaStorage_BitmapsContainer::AddObject(pDataBitmap);

	PUSH_ARGUMENT(IDataBitmap*, pDataBitmap, -2)

	return true;
}

// Creation/Destruction functions
int	LuaDataBitmap_ReleaseBitmapObject(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataBitmap*, pDataBitmap, 1)

	bool bRemoved = CLuaStorage_BitmapsContainer::RemoveObject(pDataBitmap);
	lua_pushboolean(L, bRemoved);

	return true;
}

// Bitmaps general information
int LuaDataBitmap_GetBitmapWidth(lua_State *L)
{	
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(IDataBitmap*, pDataBitmap, 1)

	lua_pushnumber(L, pDataBitmap->GetWidth());

	return true;
}

int LuaDataBitmap_GetBitmapHeight(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(IDataBitmap*, pDataBitmap, 1)

	lua_pushnumber(L, pDataBitmap->GetHeight());

	return true;
}

int LuaDataBitmap_GetBitmapColorDepth(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(IDataBitmap*, pDataBitmap, 1)

	lua_pushnumber(L, pDataBitmap->GetColorDepth());

	return true;
}

// Data manipulations
int LuaDataBitmap_GetFactoryFromBitmap(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(6)

	POP_ARGUMENT(IDataBitmap*, pDataBitmap, 1)
	int iXOffset = lua_tonumber(L, 2);
	int iYOffset = lua_tonumber(L, 3);
	int iWidth = lua_tonumber(L, 4);
	int iHeight = lua_tonumber(L, 5);
	POP_ARGUMENT(IDataFactory*, pDataFactory, 6)

    pDataBitmap->GetDataFactory(iXOffset, iYOffset, iWidth, iHeight, pDataFactory);

	lua_pushboolean(L, true);

	return true;
}

