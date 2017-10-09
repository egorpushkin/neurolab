#include "stdafx.h"

#include "../../Common/Includes.h"

#include "competitiveAgglomeration.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(CompAgglom, "lti{competitiveAgglomeration}");

	IMPLEMENT_FACTORY_API2(
		CompAgglom, 
		"createCompAgglom");

	IMPLEMENT_TRAIN_API2(
		CompAgglom);

}
