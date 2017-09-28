#include "Common/Includes.h"

namespace NISDK
{

	extern const char* df_factory;

	int df_createFactoryObject(lua_State *L)
	{
		DpKit::IDataFactory* piDataFactory = 
			MinCOM::ConstructTool<DpKit::CDataFactory, DpKit::IDataFactory>::
				ConstructObject(DpKit::IID_IDataFactory);

		uint params = LuaKit::GetParamsCount(L);
		if ( params == 1 )
		{
			uint length = (uint)lua_tonumber(L, 1);

			piDataFactory->CreateFactory(length);
		} 
		else if ( params == 2 )
		{
			uint length = (uint)lua_tonumber(L, 1);
			float value = (float)lua_tonumber(L, 2);

			piDataFactory->CreateFactory(length, value);	
		}

		PUSH_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, -1);

		return 1;
	}

	int df_release(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);

		COM_RELEASE_WRAPPER(piDataFactory);

		return 0;
	}

	int df_createFactory(lua_State *L)
	{
		CHECK_PARAMETERS(2);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);
		uint length = (uint)lua_tonumber(L, 2);
		float value = 0.0f;

		if ( LuaKit::GetParamsCount(L) == 3 )
			value = (float)lua_tonumber(L, 3);

		piDataFactory->CreateFactory(length, value);

		return 0;
	}

	int df_releaseFactory(lua_State *L)
	{
		CHECK_PARAMETERS(1);

		POP_AUXILIAR(DpKit::IDataFactory*, piDataFactory, df_factory, 1);

		piDataFactory->ReleaseFactory();

		return 0;
	}

}
