#include "stdafx.h"

#include "../../Common/Includes.h"

#include "fuzzyCMeans.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(FuzzyCM, "lti{fuzzyCMeans}");

	IMPLEMENT_FACTORY_API2(
		FuzzyCM, 
		"createFuzzyCM");

	IMPLEMENT_TRAIN_API2(
		FuzzyCM);

}
