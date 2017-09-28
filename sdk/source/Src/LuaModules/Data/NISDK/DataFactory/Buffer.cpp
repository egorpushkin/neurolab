#include "Common/Includes.h"

namespace NISDK
{

	extern const char* df_factory;

	int df_toString(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);

		lua_pushlstring(L, (const char*)piDataFactory->GetData(), piDataFactory->GetDataLength() * sizeof(float));

		return 1;
	}

	int df_fromString(lua_State *L)
	{
		CHECK_PARAMETERS(3);

		luaL_checktype(L, 2, LUA_TSTRING);
		luaL_checktype(L, 3, LUA_TNUMBER);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		const char* buffer = lua_tostring(L, 2);
		uint length = (uint)lua_tonumber(L, 3);

		float* dataBuffer = (float*)buffer;

		piDataFactory->SetData(dataBuffer, length);

		return 0;
	}

}
