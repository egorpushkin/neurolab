#include "Common/Includes.h"

namespace NISDK
{

	extern const char* db_bitmap;

	int db_getWidth(lua_State *L)
	{	
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, 1);

		lua_pushnumber(L, piDataBitmap->GetWidth());

		return 1;
	}

	int db_getHeight(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, 1);

		lua_pushnumber(L, piDataBitmap->GetHeight());

		return 1;
	}

}
