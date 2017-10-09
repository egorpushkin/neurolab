#include "stdafx.h"

#include "../../Common/Includes.h"

#include "MSTClustering.h"

namespace LTILib
{

	IMPLEMENT_SETPARAM_FUNC(
		mstclustering2sd_setDevFac, MSTClusteringL2SquareDistantorApiSngl, 
		float, devFac);

	IMPLEMENT_SETPARAM_FUNC(
		mstclustering2sd_setNbMaxSteps, MSTClusteringL2SquareDistantorApiSngl, 
		int, nbMaxSteps);

	IMPLEMENT_SETPARAM_FUNC(
		mstclustering2sd_setVariance, MSTClusteringL2SquareDistantorApiSngl, 
		double, variance);

	class MSTClusteringL2SquareDistantorParams
	{
	public:
		MSTClusteringL2SquareDistantorParams()
		{
			MSTClusteringL2SquareDistantorApiSngl::Instance().AddMethod("setDevFac", mstclustering2sd_setDevFac);
			MSTClusteringL2SquareDistantorApiSngl::Instance().AddMethod("setNbMaxSteps", mstclustering2sd_setNbMaxSteps);
			MSTClusteringL2SquareDistantorApiSngl::Instance().AddMethod("setVariance", mstclustering2sd_setVariance);
		}
	};

	MSTClusteringL2SquareDistantorParams mstClusteringL2SquareDistantorParams;

} // namespace LTILib
