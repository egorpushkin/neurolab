#include "stdafx.h"

#include "../../Common/Includes.h"

#include "adaptiveKMeans.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(AdaptiveKM, "lti{adaptiveKMeans}");

	IMPLEMENT_FACTORY_API2(
		AdaptiveKM, 
		"createAdaptiveKM");

	IMPLEMENT_TRAIN_API2(
		AdaptiveKM);

}
