#include "lua.h"

#include "gnuccpp.h"

#include "Locker.h"

ost::Mutex* pMutex;

void lua_lock(lua_State* L)
{
	(void)L;

	if ( !pMutex )
		pMutex = new ost::Mutex;

    pMutex->enter();
}

void lua_unlock(lua_State* L)
{
	(void)L;

	if ( !pMutex ) 
		return;

	pMutex->leave();
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
