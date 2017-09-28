#include "stdafx.h"

#include "../../Common/Includes.h"

namespace LTILib
{

	lti::SOFM::parameters::eInit sofm2d_tools_IntToeInit(int method)
	{
		lti::SOFM::parameters::eInit eMethod = lti::SOFM::parameters::Random;

		switch ( method )
		{
		case lti::SOFM::parameters::Random:
			eMethod = lti::SOFM::parameters::Random;
			break;
		case lti::SOFM::parameters::Linear:
			eMethod = lti::SOFM::parameters::Linear;
			break;
		}

		return eMethod;
	}

	lti::SOFM::parameters::eMetric sofm2d_tools_IntToeMetric(int metric)
	{
		lti::SOFM::parameters::eMetric eMetric = lti::SOFM::parameters::L1;

		switch ( metric )
		{
		case lti::SOFM::parameters::L1:
			eMetric = lti::SOFM::parameters::L1;
			break;
		case lti::SOFM::parameters::L2:
			eMetric = lti::SOFM::parameters::L2;
			break;
		case lti::SOFM::parameters::Dot:
			eMetric = lti::SOFM::parameters::Dot;
			break;
		}

		return eMetric;
	}

} // namespace LTILib
