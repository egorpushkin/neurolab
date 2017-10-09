#pragma once

// Lua customization libraries
#include "LuaDefinitions.h"

// Standart Lua APIs
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
		: csString(_T(""))
	{
	}
	
	CCmnLua(CString& String)
		: csString(csString)
	{
	}

	bool ExecuteScript(const luaL_reg custom_lualibs[])
	{	
		if (csString == _T(""))
			return false;
		
		lua_State* L = lua_open();   
		luaopen_stdlibs(L);

		// Open custom Api libraries
		const luaL_reg* lib = custom_lualibs;
		for (; lib->func; lib++) 
		{
			lib->func(L);  
			lua_settop(L, 0);
		}

		// Run the script file
		int result = lua_dostring(L, csString);

		lua_close(L);	

		if (!result)
			return true;

		return false;
	}

	void SetString(CString& String)
	{
		csString = String;
	}

	CString	GetString()
	{
		return csString;
	}

private:
	void luaopen_stdlibs(lua_State* L) 
	{
		const luaL_reg* lib = lualibs;
		for (; lib->func; lib++) 
		{
			lib->func(L);  
			lua_settop(L, 0);
		}
	}

	CString			csString;
};