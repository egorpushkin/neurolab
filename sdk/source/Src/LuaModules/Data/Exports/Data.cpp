#include "Common/Includes.h"

#include "NISDK/DataFactory/DataFactory.h"
#include "NISDK/DataBitmap/DataBitmap.h"

static int global_skip(lua_State *L);
static int global_unload(lua_State *L);
static int base_open(lua_State *L); 

static const char* moduleName = "data";
static const char* version = "Data 1.0.1";

static const luaL_reg moduleApis[] = {
	{"base",				base_open},
	{"datafactory",			NISDK::datafactory_open},
	{"databitmap",			NISDK::databitmap_open},
	{NULL, NULL}
};

static luaL_reg globalApi[] = {
	{"skip",				global_skip},
	{"__unload",			global_unload},
	{NULL, NULL}
};

static int global_skip(lua_State *L) 
{
    int amount = luaL_checkint(L, 1);
    int ret = lua_gettop(L) - amount - 1;

    return ( ret >= 0 ) ? ( ret ) : ( 0 );
}

static int global_unload(lua_State * /* L */) 
{    
    return 0;
}

static int base_open(lua_State *L) 
{
	luaL_openlib(L, moduleName, globalApi, 0);

#ifdef _DEBUG
	lua_pushstring(L, "_DEBUG");
	lua_pushboolean(L, 1);
    lua_rawset(L, -3);
#endif

	lua_pushstring(L, "_VERSION");
	lua_pushstring(L, version);
	lua_rawset(L, -3);

	return 1;
} 

int luaopen_data_core(lua_State *L) 
{
	for ( unsigned int i = 0; moduleApis[i].name; i++ ) 
		moduleApis[i].func(L);

	return 1;
} 
