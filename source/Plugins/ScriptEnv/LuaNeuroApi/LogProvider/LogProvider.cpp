#include "StdAfx.h"
#include "LogProvider.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

int LuaLog_GetLogProvider(lua_State *L)
{
	if (!CLuaStorage_LogProvider::pLogProvider)
		return false;
	
	PUSH_ARGUMENT(ILogProvider*, CLuaStorage_LogProvider::pLogProvider, -2)

	return true;
}

int LuaLog_Notify(lua_State *L)
{
	if (!CLuaStorage_LogProvider::pLogProvider)
		return false;

	CHECK_ARGUMENTS_COUNT(1)

	CString tmMessage1(lua_tostring(L, 1));
	CString tmMessage2(_T(""));
	CString tmMessage3(_T(""));

	if (iNumber >= 2)
		tmMessage2 = CString(lua_tostring(L, 2));
	if (iNumber >= 3)
		tmMessage3 = CString(lua_tostring(L, 3));
    
	CLuaStorage_LogProvider::pLogProvider->AddLogMessage(
		tmMessage1,
		tmMessage2,
		tmMessage3);

	return true;	
}

int LuaLog_AddLogMessage(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(ILogProvider*, pLogProvider, 1)

	CString tmMessage1(lua_tostring(L, 2));
	CString tmMessage2(_T(""));
	CString tmMessage3(_T(""));

	if (iNumber >= 3)
		tmMessage2 = CString(lua_tostring(L, 3));
	if (iNumber >= 4)
		tmMessage3 = CString(lua_tostring(L, 4));
    
	pLogProvider->AddLogMessage(
		tmMessage1,
		tmMessage2,
		tmMessage3);

	return true;
}

int LuaLog_ClearLog(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(ILogProvider*, pLogProvider, 1)

	pLogProvider->ClearLog();

	return true;
}

// Percentage manipulations
int	LuaLog_SetPercentage(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	CLuaStorage_LogProvider::iCurPercentage = lua_tonumber(L, 1);    

	return true;
}

int	LuaLog_GetPercentage(lua_State *L)
{
	lua_pushnumber(L, CLuaStorage_LogProvider::iCurPercentage);
	
	return true;
}

// Package initialization
int	luaopen_log(lua_State *L)
{
	lua_register(L, "getLogProvider", LuaLog_GetLogProvider);
	lua_register(L, "notify", LuaLog_Notify);
	lua_register(L, "addLogMessage", LuaLog_AddLogMessage);
	lua_register(L, "clearLog", LuaLog_ClearLog);	

	lua_register(L, "setPercentage", LuaLog_SetPercentage);	
	lua_register(L, "getPercentage", LuaLog_GetPercentage);	

	return true;
}