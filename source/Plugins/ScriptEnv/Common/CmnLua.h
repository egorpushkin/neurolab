#pragma once

#define LUA_API		extern "C" __declspec(dllimport)
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
} 

// Lua customization libraries
#include "LuaDefinitions.h"

// Including Neuro Api Libraries
#include <Lua/LuaKit.h>
#include "..\LuaNeuroApi\NeuroApi.h"

static const luaL_reg lualibs[] = 
{
	{"base", luaopen_base},
	{"table", luaopen_table},
	{"io", luaopen_io},
	{"string", luaopen_string},
	{"math", luaopen_math},
	{"debug", luaopen_debug},
	{"loadlib", luaopen_loadlib}, 
	{NULL, NULL}
};


class CCmnLua
{
public:
	CCmnLua()
		: csFileName(_T(""))
	{
	}
	
	CCmnLua(CString& FileName)
		: csFileName(FileName)
	{
	}

	bool ExecuteScript()
	{	
		if (csFileName == _T(""))
			return false;
		
		lua_State* L = lua_open();   
		luaopen_stdlibs(L);

		// Open custom Api libraries
		luaopen_system(L);
		luaopen_globalenvironment(L);
		luaopen_log(L);
		luaopen_dataprocessing(L);
		luaopen_network(L);
		luaopen_network_ex(L);
		luaopen_charting(L);
		luaopen_fann_121(L);
		luaopen_simplenoise(L);
		luaopen_fft(L);

		LTILib::LTILibPackageSngl::Instance().Open(L);
		Drawing::DrawingPackageSngl::Instance().Open(L);

		// Run the script file
		int result = lua_dofile(L, csFileName);

		lua_close(L);	

		if (!result)
			return true;

		return false;
	}

	void SetFileName(CString& FileName)
	{
		csFileName = FileName;
	}

	CString	GetFileName()
	{
		return csFileName;
	}

private:
	static void luaopen_stdlibs(lua_State* L) 
	{
		const luaL_reg* lib = lualibs;
		for (; lib->func; lib++) 
		{
			lib->func(L);  
			lua_settop(L, 0);
		}
	}

	CString			csFileName;
};
