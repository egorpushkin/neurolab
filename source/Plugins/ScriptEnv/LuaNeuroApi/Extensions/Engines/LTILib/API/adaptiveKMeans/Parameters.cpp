#include "stdafx.h"

#include "../../Common/Includes.h"

#include "AdaptiveKMeans.h"

namespace LTILib
{
	
	int adaptiveKMeans_setClustersCount(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);
		int clusters = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::adaptiveKMeans, pClustering, nbClusters, clusters);

		return 0;
	}

	int adaptiveKMeans_getClustersCount(lua_State *L)
	{
		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);

		lti::adaptiveKMeans::parameters akmp = pClustering->getParameters();
		int clusters = akmp.nbClusters;

		lua_pushnumber(L, clusters);

		return 1;
	}

	int adaptiveKMeans_setMaxIterations(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);
		int maxIterations = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::adaptiveKMeans, pClustering, maxIterations, maxIterations);

		return 0;
	}

	int adaptiveKMeans_setNeighborhoods(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);
		int neighborhoods = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::adaptiveKMeans, pClustering, nbNeighborhoods, neighborhoods);

		return 0;
	}

	int adaptiveKMeans_setMaxDistance(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);
		double maxDistance = lua_tonumber(L, 2);

		SETUP_PARAM(lti::adaptiveKMeans, pClustering, maxDistance, maxDistance);

		return 0;
	}

	int adaptiveKMeans_setMinNumberOfPoints(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::adaptiveKMeans* pClustering = LuaKit::PopApiData<AdaptiveKMApiSngl>(L, 1);
		double minNumberOfPoints = lua_tonumber(L, 2);

		SETUP_PARAM(lti::adaptiveKMeans, pClustering, minNumberOfPoints, minNumberOfPoints);

		return 0;
	} 

	class AdaptiveKMParams
	{
	public:
		AdaptiveKMParams()
		{
			AdaptiveKMApiSngl::Instance().AddMethod("setClustersCount", adaptiveKMeans_setClustersCount);
			AdaptiveKMApiSngl::Instance().AddMethod("getClustersCount", adaptiveKMeans_getClustersCount);
			AdaptiveKMApiSngl::Instance().AddMethod("setMaxIterations", adaptiveKMeans_setMaxIterations);
			AdaptiveKMApiSngl::Instance().AddMethod("setNeighborhoods", adaptiveKMeans_setNeighborhoods);
			AdaptiveKMApiSngl::Instance().AddMethod("setMaxDistance", adaptiveKMeans_setMaxDistance);
			AdaptiveKMApiSngl::Instance().AddMethod("setMinNumberOfPoints", adaptiveKMeans_setMinNumberOfPoints);
		}
	};

	AdaptiveKMParams adaptiveKMParams;

} // namespace LTILib
