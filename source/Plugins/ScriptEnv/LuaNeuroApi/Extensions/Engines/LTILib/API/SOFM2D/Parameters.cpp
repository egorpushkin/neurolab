#include "stdafx.h"

#include "../../Common/Includes.h"

#include "SOFM2D.h"

#include "Tools.h"

namespace LTILib
{

	int sofm2d_setCalculateSize(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TBOOLEAN);

		lti::SOFM2D* pSofm2d = LuaKit::PopApiData<SOFM2DApiSngl>(L, 1);
		bool calculate = ( lua_toboolean(L, 2) != 0 );

		SETUP_PARAM(lti::SOFM2D, pSofm2d, calculateSize, calculate);

		return 0;
	}

	int sofm2d_setSize(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);

		lti::SOFM2D* pSofm2d = LuaKit::PopApiData<SOFM2DApiSngl>(L, 1);
		int sizeX = (int)lua_tonumber(L, 2);
		int sizeY = (int)lua_tonumber(L, 3);

		SETUP_PARAM(lti::SOFM2D, pSofm2d, sizeX, sizeX);
		SETUP_PARAM(lti::SOFM2D, pSofm2d, sizeY, sizeY);

		return 0;
	}

	int sofm2d_setArea(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::SOFM2D* pSofm2d = LuaKit::PopApiData<SOFM2DApiSngl>(L, 1);
		int area = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::SOFM2D, pSofm2d, area, area);

		return 0;
	}

	int sofm2d_setInitType(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);	

		lti::SOFM2D* pSofm2d = LuaKit::PopApiData<SOFM2DApiSngl>(L, 1);
		int initType = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::SOFM2D, pSofm2d, initType, sofm2d_tools_IntToeInit(initType));

		return 0;
	}

	int sofm2d_setMetricType(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);			

		lti::SOFM2D* pSofm2d = LuaKit::PopApiData<SOFM2DApiSngl>(L, 1);
		int metricType = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::SOFM2D, pSofm2d, metricType, sofm2d_tools_IntToeMetric(metricType));

		return 0;
	}

	class SOFM2DParams
	{
	public:
		SOFM2DParams()
		{
			SOFM2DApiSngl::Instance().AddConst("EINIT_RANDOM", lti::SOFM::parameters::Random);
			SOFM2DApiSngl::Instance().AddConst("EINIT_LINEAR", lti::SOFM::parameters::Linear);
			SOFM2DApiSngl::Instance().AddConst("EMETRIC_L1", lti::SOFM::parameters::L1);
			SOFM2DApiSngl::Instance().AddConst("EMETRIC_L2", lti::SOFM::parameters::L2);
			SOFM2DApiSngl::Instance().AddConst("EMETRIC_DOT", lti::SOFM::parameters::Dot);

			SOFM2DApiSngl::Instance().AddMethod("setCalculateSize", sofm2d_setCalculateSize);
			SOFM2DApiSngl::Instance().AddMethod("setSize", sofm2d_setSize);
			SOFM2DApiSngl::Instance().AddMethod("setArea", sofm2d_setArea);
			SOFM2DApiSngl::Instance().AddMethod("setInitType", sofm2d_setInitType);
			SOFM2DApiSngl::Instance().AddMethod("setMetricType", sofm2d_setMetricType);
		}
	};

	SOFM2DParams sofm2dParams;

} // namespace LTILib
