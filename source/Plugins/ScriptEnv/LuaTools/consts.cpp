#include "stdafx.h"

#include <Lua/LuaKit.h>

void luaL_openenum(lua_State* L, const luaL_const* enums)
{
	for (const luaL_const* l = enums; l->name; l++) {
		lua_pushstring(L, l->name);
		lua_pushnumber(L, l->func);
		lua_settable(L, -3);
	} 
}
