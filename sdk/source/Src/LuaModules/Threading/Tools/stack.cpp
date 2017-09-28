#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include "stack.h"

const unsigned int maxPath = 1024;

int stack_parsesequence(lua_State *L, const char* sequence, bool firstLevel)
{	
	char buffer[maxPath];
	
	char* dotPos = strstr(sequence, ".");
	if ( !dotPos )
		strcpy(buffer, sequence);
	else
	{
		size_t length = dotPos - sequence;
		memcpy(buffer, sequence, length);
		buffer[length] = '\x0';
	}

	if ( firstLevel )
	{
		lua_getglobal(L, buffer);
	}
	else
	{
		lua_pushstring(L, buffer);
		lua_gettable(L, -2);
		lua_remove(L, -2);
	}

	if ( !dotPos )	
		return 0;

	if ( !lua_istable(L, -1) )
		return luaL_error(L, "Failed to parse sequence: %s.", sequence);
	
	return stack_parsesequence(L, dotPos + 1, false);
}

void stack_pushasstring(lua_State *L, int value)
{
	char buffer[16];
	itoa(value, buffer, 10);
	lua_pushstring(L, buffer);
}

