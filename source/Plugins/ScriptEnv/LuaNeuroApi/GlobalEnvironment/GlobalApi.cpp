#include "StdAfx.h"
#include "GlobalApi.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

int LuaGlobalEnvironment_SetCurrentDirectory(lua_State *L)
{
   	CHECK_ARGUMENTS_COUNT(1)	

	CLuaStorage_GlobalEnvironment::csCurrentDirectory = lua_tostring(L, 1);

	return true;
}

int LuaGlobalEnvironment_GetUpLevelDir(lua_State *L)
{
   	CHECK_ARGUMENTS_COUNT(1)	

	CString csDirectoryName = lua_tostring(L, 1);

	int iSlashPos = csDirectoryName.ReverseFind(_T('\\'));
	if (iSlashPos == -1)
		iSlashPos = csDirectoryName.ReverseFind(_T('/'));

	if (iSlashPos != -1)
		csDirectoryName = csDirectoryName.Left(iSlashPos);

	lua_pushstring(L, csDirectoryName);

	return true;
}

int LuaGlobalEnvironment_Alert(lua_State *L)
{
	const char* errorMsg = lua_tostring(L, 1);

	CLuaStorage_LogProvider::pLogProvider->AddLogMessage(
		CString(_T("E")),
		CString(errorMsg),
		CString(_T("Scripting Environment")));

	return 0;
}

// Package initialization
int luaopen_globalenvironment(lua_State *L)
{
	lua_register(L, "setCurrentDirectory", LuaGlobalEnvironment_SetCurrentDirectory);
	lua_register(L, "getUpLevelDir", LuaGlobalEnvironment_GetUpLevelDir);

	lua_pushstring(L, "SOLUTION_DIR");
	lua_pushstring(L, CLuaStorage_GlobalEnvironment::csSolutionDirectory);	
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "SCRIPT_DIR");
	lua_pushstring(L, CLuaStorage_GlobalEnvironment::csScriptDirectory);	
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "REPOS");
	lua_pushstring(L, CLuaStorage_GlobalEnvironment::csAppDirectory + "\\Research\\Repository");	
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushstring(L, "_ALERT");
	lua_pushcfunction(L, LuaGlobalEnvironment_Alert);
	lua_settable(L, LUA_GLOBALSINDEX);

	return true;
}
