#include "StdAfx.h"

#include "lua.h"

#include "Locker.h"

CRITICAL_SECTION* pMutex = NULL;

void lua_lock(lua_State* L)
{
	if ( !pMutex )
	{
		// pMutex = new CRITICAL_SECTION;
		// ::InitializeCriticalSection(pMutex);
	}

	// ::EnterCriticalSection(pMutex);
}

void lua_unlock(lua_State* L)
{
	if ( !pMutex ) 
		return;

	// ::LeaveCriticalSection(pMutex);
}

void lua_lockfinal(lua_State* L)
{
	lua_unlock(L);

	if ( pMutex )
	{
		delete pMutex;
		pMutex = NULL;
	}
}
