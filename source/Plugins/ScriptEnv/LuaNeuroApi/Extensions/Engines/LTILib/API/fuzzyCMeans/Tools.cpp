#include "stdafx.h"

#include "../../Common/Includes.h"

namespace LTILib
{

	lti::classifier::parameters::eDistanceMeasure fuzzycm_tools_IntToeDistanceMeasure(int metric)
	{
		lti::classifier::parameters::eDistanceMeasure eMetric = lti::classifier::parameters::L1;

		switch ( metric )
		{
		case lti::classifier::parameters::L1:
			eMetric = lti::classifier::parameters::L1;
			break;
		case lti::classifier::parameters::L2:
			eMetric = lti::classifier::parameters::L2;
			break;
		}

		return eMetric;
	}

} // namespace LTILib
