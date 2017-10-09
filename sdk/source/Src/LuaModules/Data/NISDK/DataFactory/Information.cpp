#include "Common/Includes.h"

namespace NISDK
{

	extern const char* df_factory;

	int df_getItemData(lua_State *L)
	{
		CHECK_PARAMETERS(2)

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		uint index = (uint )lua_tonumber(L, 2);

		float value = piDataFactory->GetItemData(index);
		
		lua_pushnumber(L, (lua_Number)value);

		return 1;
	}

	int df_getDataLength(lua_State *L)
	{
		CHECK_PARAMETERS(1)

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);

		uint length = piDataFactory->GetDataLength();

		lua_pushnumber(L, (lua_Number)length);

		return 1;
	}

}
