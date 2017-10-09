#include "StdAfx.h"
#include "Charting.h"

#include "..\..\GlobalStorage.h"
#include "..\..\ApiMacro.h"

#include "../API/Objects.h"
#include "../API/Parameters.h"

#include "CmnDecl.h"

#include "../../../ScriptEnv.h"
#include "../UI/ChartsViewDlg.h"	

#include "../Manager/DisplayMngThread.h"

#include "../Manager/DataBuffer.h"

int LuaCharting_DisplayCtrl(lua_State *L)
{
	int argumentsNumber = lua_gettop(L);
	
	std::string chartName = _T("");
	if (argumentsNumber >= 1)
		chartName = lua_tostring(L, 1);

	DataBuffer* pBuffer = new DataBuffer;
	
	pBuffer->name_ = chartName;
	pBuffer->event_ = CreateEvent(NULL, TRUE, FALSE, NULL);

	__beginthreadex(NULL, 0, DisplayMngThread, pBuffer, 0, NULL);    

	WaitForSingleObject(pBuffer->event_, INFINITE);
	CloseHandle(pBuffer->event_);

	PUSH_ARGUMENT(CChartsViewDlg*, pBuffer->pChartsView_, -2);

	delete pBuffer;

	return 1;
}

int LuaCharting_ReleaseCtrl(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(CChartsViewDlg*, pChartsView, 1)

	pChartsView->HandleRemove();
	
	return 0;
}


// Package initialization
static const luaL_reg chartinglib[] = {
	{"displayCtrl",				LuaCharting_DisplayCtrl},
	{"releaseCtrl",				LuaCharting_ReleaseCtrl},

	{"createAutoLocator",		LuaCharting_CreateAutomaticLocator},
	{"createLocator",			LuaCharting_CreateCartesiansLocator},
	{"createChart",				LuaCharting_CreateChart},
	{"createRenderer",			LuaCharting_CreateFunctionRenderer},
	{"addChart",				LuaCharting_AddChart},
	{"addChartPoint",			LuaCharting_AddChartPoint},

	{"setAxesRanges",			LuaCharting_SetAxesRanges},
	{"setScale",				LuaCharting_SetScale},	
	
	{NULL, NULL}
}; 

int luaopen_charting (lua_State *L) 
{
	luaL_openlib(L, "charting", chartinglib, 0);

	return 1;
} 
