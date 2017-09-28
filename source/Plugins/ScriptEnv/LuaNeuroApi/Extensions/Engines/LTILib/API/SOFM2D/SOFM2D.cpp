#include "stdafx.h"

#include "../../Common/Includes.h"

#include "SOFM2D.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(SOFM2D, "lti{sofm2d}");

	IMPLEMENT_FACTORY_API2(
		SOFM2D, 
		"createSOFM2D");

	IMPLEMENT_TRAIN_API2(
		SOFM2D);

}
