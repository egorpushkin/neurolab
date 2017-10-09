#include "Common/Includes.h"

namespace NISDK
{

	extern const char* db_bitmap;
	extern const char* df_factory;

	int db_getFactory(lua_State *L)
	{
		CHECK_PARAMETERS(6);

		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);
		luaL_checktype(L, 5, LUA_TNUMBER);

		POP_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, 1);
		uint xOffset = (uint)lua_tonumber(L, 2);
		uint yOffset = (uint)lua_tonumber(L, 3);
		uint width = (uint)lua_tonumber(L, 4);
		uint height = (uint)lua_tonumber(L, 5);
		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 6);

		result res = piDataBitmap->GetDataFactory(xOffset, yOffset, width, height, piDataFactory);

		lua_pushboolean(L, SUCCEEDED(res) ? ( true ) : ( false ) );

		return 1;
	}	

	int db_fromFactory(lua_State *L)
	{
		CHECK_PARAMETERS(4);

		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);

		POP_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, 1);
		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 2);
		uint width = (uint)lua_tonumber(L, 3);
		uint height = (uint)lua_tonumber(L, 4);

		result res = piDataBitmap->ConstructFromDataFactory(piDataFactory, width, height);
        
		lua_pushboolean(L, SUCCEEDED(res) ? ( true ) : ( false ) );

		return 1;
	}

}
