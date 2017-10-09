#include "Common/Includes.h"

namespace NISDK
{

	extern const char* db_bitmap;

	int db_loadBitmapFromPGM(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		luaL_checktype(L, 1, LUA_TSTRING);

		const char* filename = lua_tostring(L, 1);

		DpKit::CPGMBitmap* pPGMBitmap = new DpKit::CPGMBitmap;
		result res = pPGMBitmap->LoadPGMBitmap(filename);
		if ( FAILED(res) )
		{
			delete pPGMBitmap;
			return 0;
		}

		DpKit::IDataBitmap* piDataBitmap = NULL;
		pPGMBitmap->QueryInterface(DpKit::IID_IDataBitmap, (void**)&piDataBitmap);

		PUSH_AUXILIAR(DpKit::IDataBitmap*, piDataBitmap, db_bitmap, -1);

		return 1;
	}

}
