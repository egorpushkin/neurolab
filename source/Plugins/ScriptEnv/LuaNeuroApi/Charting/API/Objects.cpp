#include "StdAfx.h"
#include "Charting.h"

#include "..\..\GlobalStorage.h"
#include "..\..\ApiMacro.h"

#include "../../../ScriptEnv.h"
#include "../ui/ChartsViewDlg.h"

int LuaCharting_CreateAutomaticLocator(lua_State *L)
{
	PUSH_ARGUMENT(Simple2dCharting::BasicLocator*, new Simple2dCharting::AutomaticLocator, -2);
	return 1;
}

int LuaCharting_CreateCartesiansLocator(lua_State *L)
{
	PUSH_ARGUMENT(Simple2dCharting::BasicLocator*, new Simple2dCharting::CartesiansLocator, -2);
	return 1;
}

int LuaCharting_CreateChart(lua_State *L)
{
	PUSH_ARGUMENT(Simple2dCharting::FloatPointChart*, new Simple2dCharting::FloatPointChart, -2);
	return 1;
}

unsigned long HexToDec(const char* buf)
{
	unsigned long num = 0;

	unsigned char table[256];
	
	memset(table, 0, 256);
	for ( unsigned int i = 0 ; i < 10 ; i++ ) 
		table['0' + i] = (unsigned char)i;

	for ( unsigned int i = 0 ; i < 6 ; i++) 
	{
		table['A' + i] = (unsigned char)(i + 10);
		table['a' + i] = (unsigned char)(i + 10);
	}

	unsigned int offset = 0;
	for ( int len = strlen(buf) - 1 ; len >= 0 ; --len, offset += 4 )
		num |= table[buf[len]] << offset;

	return num;
}

int LuaCharting_CreateFunctionRenderer(lua_State *L)
{
	int argumentsCount = lua_gettop(L);
	if ( argumentsCount < 1 )  
		return 0;

	Simple2dCharting::Color color = Simple2dCharting::BasicDevice::BlueViolet;

	if ( lua_isnumber(L, 1) )
	{
		color = (unsigned long)lua_tonumber(L, 1);
	}
	else if ( lua_isstring(L, 1) )
	{
		const char* colorBuf = lua_tostring(L, 1);
		
		if ( strlen(colorBuf) == 8 )
			color = HexToDec(colorBuf);
	}

	float width = 1.0f;
	if ( argumentsCount >= 2 )
		width = (float)lua_tonumber(L, 2);

	PUSH_ARGUMENT(Simple2dCharting::BasicRenderer*, new Simple2dCharting::FunctionRenderer(color, width), -2);    

	return 1;
}

int	LuaCharting_AddChart(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(5)	

	POP_ARGUMENT(CChartsViewDlg*, pChartsView, 1)
	POP_ARGUMENT(Simple2dCharting::FloatPointChart*, pChart, 2)
	POP_ARGUMENT(Simple2dCharting::BasicRenderer*, pRenderer, 3)
	POP_ARGUMENT(Simple2dCharting::BasicLocator*, pLocator, 4)
	const char* name = lua_tostring(L, 5);

	pChartsView->chartCtrl_.AddChart(pChart, pRenderer, pLocator, name);
	pChartsView->SafeInvalideteChart();

    return 0;
}

int LuaCharting_AddChartPoint(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(4)

	POP_ARGUMENT(CChartsViewDlg*, pChartsView, 1)
	POP_ARGUMENT(Simple2dCharting::FloatPointChart*, pChart, 2)
	float x = (float)lua_tonumber(L, 3);
	float y = (float)lua_tonumber(L, 4);

	pChart->Insert(Simple2dCharting::FloatPoint(x, y));	
	pChartsView->SafeInvalideteChart();
    
	return 0;
}

