#include "Common/Includes.h"

namespace NISDK
{

	extern const char* df_factory;

	int df_loadFactoryFromPGM(lua_State *L)
	{
		(void) L;
		return 0;
	}

	int df_saveToPGM(lua_State *L)
	{
		CHECK_PARAMETERS(4);

		luaL_checktype(L, 2, LUA_TSTRING);
		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		const char* filename = lua_tostring(L, 2);
		uint width = (uint)lua_tonumber(L, 3);
		uint height = (uint)lua_tonumber(L, 4);

		DpKit::CPGMBitmap pgmBitmap; 
		pgmBitmap.ConstructFromDataFactory(piDataFactory, width, height);
		result res = pgmBitmap.SavePGMBitmap(filename);

		lua_pushboolean(L, SUCCEEDED(res) ? ( true ) : ( false ) );

		return 1;
	}

}
