#include "stdafx.h"

#include "../../Common/Includes.h"

#include "kMeansClustering.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(KMClustering, "lti{kmeansclustering}");

	IMPLEMENT_FACTORY_API2(
		KMClustering, 
		"createKMClustering");

	IMPLEMENT_TRAIN_API2(
		KMClustering);

}
