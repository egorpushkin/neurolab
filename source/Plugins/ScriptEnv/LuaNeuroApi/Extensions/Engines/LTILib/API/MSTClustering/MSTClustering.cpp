#include "stdafx.h"

#include "../../Common/Includes.h"

#include "MSTClustering.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	IMPLEMENT_API(MSTClusteringL2SquareDistantor, "lti{MSTClusteringL2SquareDistantor}");

	IMPLEMENT_FACTORY_API2(
		MSTClusteringL2SquareDistantor,
		"createMSTClusteringL2Square");

	IMPLEMENT_TRAIN_API2(
		MSTClusteringL2SquareDistantor);

}
