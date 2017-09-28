#include "stdafx.h"

#include "../../Common/Includes.h"

#include "DBScan.h"

namespace LTILib
{

	IMPLEMENT_SETPARAM_FUNC(
		dbscanl2sd_setEps, DBScanL2SquareDistantorApiSngl, 
		double, eps);

	IMPLEMENT_SETPARAM_FUNC(
		dbscanl2sd_setMinPts, DBScanL2SquareDistantorApiSngl, 
		int, minPts);

	IMPLEMENT_SETPARAM_FUNC(
		dbscanl2sd_setBuckedSize, DBScanL2SquareDistantorApiSngl, 
		int, buckedSize);

	template
	<
		class T
	>
	typename lti::DBScan<T>::parameters::eDistanceType dbscan_tools_IntToeDistanceType(int metric)
	{
		lti::DBScan<T>::parameters::eDistanceType eMetric = lti::DBScan<T>::parameters::L1Distance;

		switch ( metric )
		{
		case lti::DBScan<T>::parameters::L1Distance:
			eMetric = lti::DBScan<T>::parameters::L1Distance;
			break;
		case lti::DBScan<T>::parameters::L2Distance:
			eMetric = lti::DBScan<T>::parameters::L2Distance;
			break;
		case lti::DBScan<T>::parameters::L2SquareDistance:
			eMetric = lti::DBScan<T>::parameters::L2SquareDistance;
			break;
		}

		return eMetric;
	}

	int dbscanl2sd_setDistanceMeasure(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::DBScan< lti::l2SquareDistantor< lti::dvector > >* pClustering = 
			LuaKit::PopApiData<DBScanL2SquareDistantorApiSngl>(L, 1);
		int measure = (int)lua_tonumber(L, 2);

		SETUP_PARAM(
			lti::DBScan< lti::l2SquareDistantor< lti::dvector > >, 
			pClustering, 
			distanceMeasure, 
			dbscan_tools_IntToeDistanceType< lti::l2SquareDistantor< lti::dvector > >(measure));

		return 0;
	}

	class DBScanL2SquareDistantorParams
	{
	public:
		DBScanL2SquareDistantorParams()
		{
			DBScanL2SquareDistantorApiSngl::Instance().AddConst("EDISTANCETYPE_L1DISTANCE", lti::DBScan< lti::l2SquareDistantor< lti::dvector > >::parameters::L1Distance);
			DBScanL2SquareDistantorApiSngl::Instance().AddConst("EDISTANCETYPE_L2DISTANCE", lti::DBScan< lti::l2SquareDistantor< lti::dvector > >::parameters::L2Distance);
			DBScanL2SquareDistantorApiSngl::Instance().AddConst("EDISTANCETYPE_L2SQUAREDISTANCE", lti::DBScan< lti::l2SquareDistantor< lti::dvector > >::parameters::L2SquareDistance);

			DBScanL2SquareDistantorApiSngl::Instance().AddMethod("setEps", dbscanl2sd_setEps);
			DBScanL2SquareDistantorApiSngl::Instance().AddMethod("setMinPts", dbscanl2sd_setMinPts);
			DBScanL2SquareDistantorApiSngl::Instance().AddMethod("setBuckedSize", dbscanl2sd_setBuckedSize);
			DBScanL2SquareDistantorApiSngl::Instance().AddMethod("setDistanceMeasure", dbscanl2sd_setDistanceMeasure);
		}
	};

	DBScanL2SquareDistantorParams dbScanL2SquareDistantorParams;

} // namespace LTILib
