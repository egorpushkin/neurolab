#include "Common/Includes.h"

namespace NISDK
{

	extern const char* db_bitmap;

	int db_createBitmap(lua_State *L)
	{
		DpKit::IDataBitmap* piDataBitmap = 
			MinCOM::ConstructTool<DpKit::CDataBitmap, DpKit::IDataBitmap>::
			ConstructObject(DpKit::IID_IDataBitmap);

		uint params = LuaKit::GetParamsCount(L);
		if ( params == 2 )
		{
			luaL_checktype(L, 1, LUA_TNUMBER);
			luaL_checktype(L, 2, LUA_TNUMBER);

			uint width = (uint)lua_tonumber(L, 1);
			uint height = (uint)lua_tonumber(L, 2);

			piDataBitmap->AllocateData(width, height, 1);
		} 

		PUSH_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, -1);

		return 1;
	}

	int db_release(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, 1);

		COM_RELEASE_WRAPPER(piDataBitmap);

		return 0;
	}

}
