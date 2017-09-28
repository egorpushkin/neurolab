#include "stdafx.h"

#include "../../Common/Includes.h"

#include "FuzzyCMeans.h"

#include "Tools.h"

namespace LTILib
{
	
	int fuzzyCMeans_setClustersCount(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::fuzzyCMeans* pClustering = LuaKit::PopApiData<FuzzyCMApiSngl>(L, 1);
		int clusters = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::fuzzyCMeans, pClustering, nbOfClusters , clusters);

		return 0;
	}

	int fuzzyCMeans_setFuzzifier(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::fuzzyCMeans* pClustering = LuaKit::PopApiData<FuzzyCMApiSngl>(L, 1);
		double fuzzifier = lua_tonumber(L, 2);

		SETUP_PARAM(lti::fuzzyCMeans, pClustering, fuzzifier, fuzzifier);

		return 0;
	}

	int fuzzyCMeans_setNorm(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::fuzzyCMeans* pClustering = LuaKit::PopApiData<FuzzyCMApiSngl>(L, 1);
		int norm = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::fuzzyCMeans, pClustering, norm, fuzzycm_tools_IntToeDistanceMeasure(norm));

		return 0;
	}

	int fuzzyCMeans_setElipson(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::fuzzyCMeans* pClustering = LuaKit::PopApiData<FuzzyCMApiSngl>(L, 1);
		double epsilon = lua_tonumber(L, 2);

		SETUP_PARAM(lti::fuzzyCMeans, pClustering, epsilon, epsilon);

		return 0;
	}

	int fuzzyCMeans_setMaxIterations(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::fuzzyCMeans* pClustering = LuaKit::PopApiData<FuzzyCMApiSngl>(L, 1);
		int maxIterations = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::fuzzyCMeans, pClustering, maxIterations, maxIterations);

		return 0;
	}


	class FuzzyCMParams
	{
	public:
		FuzzyCMParams()
		{
			FuzzyCMApiSngl::Instance().AddConst("EDISTANCEMEASURE_L1", lti::classifier::parameters::L1);
			FuzzyCMApiSngl::Instance().AddConst("EDISTANCEMEASURE_L2", lti::classifier::parameters::L2);

			FuzzyCMApiSngl::Instance().AddMethod("setClustersCount", fuzzyCMeans_setClustersCount);
			FuzzyCMApiSngl::Instance().AddMethod("setFuzzifier", fuzzyCMeans_setFuzzifier);
			FuzzyCMApiSngl::Instance().AddMethod("setNorm", fuzzyCMeans_setNorm);
			FuzzyCMApiSngl::Instance().AddMethod("setElipson", fuzzyCMeans_setElipson);
			FuzzyCMApiSngl::Instance().AddMethod("setMaxIterations", fuzzyCMeans_setMaxIterations);
		}
	};

	FuzzyCMParams fuzzyCMParams;

} // namespace LTILib
