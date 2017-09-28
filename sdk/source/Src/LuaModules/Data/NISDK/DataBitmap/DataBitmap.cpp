#include "Common/Includes.h"

namespace NISDK
{

	int db_createBitmap(lua_State *L);
	int db_loadBitmapFromPGM(lua_State *L);
	
	int db_release(lua_State *L);
	int db_getWidth(lua_State *L);
	int db_getHeight(lua_State *L);
	int db_getFactory(lua_State *L);
	int db_fromFactory(lua_State *L);

	const char* db_bitmap = "dbmp{bitmap}";
	const char* db_any = "dbmp{any}";

	static luaL_reg databitmapGlobalApi[] = {		
		{"createBitmap",				db_createBitmap},
		{"loadBitmapFromPGM",			db_loadBitmapFromPGM},
		{NULL, NULL}
	};

	static luaL_reg databitmapObjectApi[] = {
		{"__gc",						db_release}, 
		{"getWidth",					db_getWidth}, 
		{"getHeight",					db_getHeight}, 
		{"getFactory",					db_getFactory}, 
		{"fromFactory",					db_fromFactory}, 
		{NULL, NULL}
	};

	int databitmap_open(lua_State * L)
	{
		auxiliar_newclass(L, db_bitmap, databitmapObjectApi);
		auxiliar_add2group(L, db_bitmap, db_any);

		luaL_openlib(L, NULL, databitmapGlobalApi, 0);  

		return 0;
	}

}
