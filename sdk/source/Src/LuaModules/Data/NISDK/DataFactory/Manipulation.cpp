#include "Common/Includes.h"

namespace NISDK
{

	extern const char* df_factory;

	int df_setItemData(lua_State *L)
	{
		CHECK_PARAMETERS(3);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		uint index = (uint)lua_tonumber(L, 2);
		float value = (float)lua_tonumber(L, 3);

		piDataFactory->SetItemData(index, value);

		return 0;
	}

	int df_fillFactory(lua_State *L)
	{
		CHECK_PARAMETERS(2);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		float value = (float)lua_tonumber(L, 2);

		piDataFactory->FillFactory(value);

		return 0;
	}

	int df_increaseValue(lua_State *L)
	{
		CHECK_PARAMETERS(3);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		uint index = (uint)lua_tonumber(L, 2);
		float value = (float)lua_tonumber(L, 3);

		piDataFactory->IncreaseValue(index, value);

		return 0; 
	}

	int df_moveFactoryData(lua_State *L)
	{
		CHECK_PARAMETERS(5);

		POP_AUXILIAR(DpKit::IDataFactory*, piSourceDataFactory, df_factory, 1);
		uint sourceOffset = (uint)lua_tonumber(L, 2);
		uint length = (uint)lua_tonumber(L, 3);
		POP_AUXILIAR(DpKit::IDataFactory*, piDestinationDataFactory, df_factory, 4);
		uint destinationOffset = (uint)lua_tonumber(L, 5);

		if (length == 0 || 
			!piSourceDataFactory->GetData() || 
			!piDestinationDataFactory->GetData())
		{
			return luaL_error(L, "Wrong parameters specified");
		}

		if (sourceOffset + length > piSourceDataFactory->GetDataLength())
		{
			return luaL_error(L, "Wrong parameters specified");
		}

		if (destinationOffset + length > piDestinationDataFactory->GetDataLength())
		{
			return luaL_error(L, "Wrong parameters specified");
		}

		memcpy(piDestinationDataFactory->GetData() + destinationOffset, 
			piSourceDataFactory->GetData() + sourceOffset, 
			sizeof(float)*length);

		return 0;
	}

}