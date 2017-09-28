#include "stdafx.h"

#include "../../Common/Includes.h"

#include "kMeansClustering.h"

namespace LTILib
{
	
	int kmeansclustering_setClustersCount(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::kMeansClustering* pClustering = LuaKit::PopApiData<KMClusteringApiSngl>(L, 1);
		int clusters = (int)lua_tonumber(L, 2);

		SETUP_PARAM(lti::kMeansClustering, pClustering, numberOfClusters, clusters);

		return 0;
	}

	class KMClusteringParams
	{
	public:
		KMClusteringParams()
		{
			KMClusteringApiSngl::Instance().AddMethod("setClustersCount", kmeansclustering_setClustersCount);
		}
	};

	KMClusteringParams kmClusteringParams;

} // namespace LTILib
