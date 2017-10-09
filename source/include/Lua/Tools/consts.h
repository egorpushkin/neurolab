#ifndef CONSTS_H__LUATOOLS__INCLUDED_
#define CONSTS_H__LUATOOLS__INCLUDED_

typedef struct luaL_const {
	const char* name;
	float func;
} luaL_const;

void luaL_openenum(lua_State* L, const luaL_const* enums);

#endif // !CONSTS_H__LUATOOLS__INCLUDED_
