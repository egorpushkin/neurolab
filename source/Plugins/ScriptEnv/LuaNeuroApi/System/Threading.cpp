#include "StdAfx.h"
#include "Threading.h"

#include "..\GlobalStorage.h"
#include "..\ApiMacro.h"

int LuaThreading_Sleep(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	DWORD delay = (DWORD)lua_tonumber(L, 1);

	::Sleep(delay);

	return 0;
}
