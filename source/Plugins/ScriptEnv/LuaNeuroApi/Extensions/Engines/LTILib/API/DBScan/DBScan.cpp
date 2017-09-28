#include "stdafx.h"

#include "../../Common/Includes.h"

#include "DBScan.h"

#include "../dmatrix/dmatrix.h"
#include "../ivector/ivector.h"

namespace LTILib
{

	//////////////////////////////////////////////////////////////////////////
	IMPLEMENT_API(DBScanL1Distantor, "lti{DBScanL1Distantor}");

	IMPLEMENT_FACTORY_API2(
		DBScanL1Distantor, 
		"createDBScanL1");

	IMPLEMENT_TRAIN_API2(
		DBScanL1Distantor);

	//////////////////////////////////////////////////////////////////////////
	IMPLEMENT_API(DBScanL2Distantor, "lti{DBScanL2Distantor}");

	IMPLEMENT_FACTORY_API2(
		DBScanL2Distantor,
		"createDBScanL2");

	IMPLEMENT_TRAIN_API2(
		DBScanL2Distantor);

	//////////////////////////////////////////////////////////////////////////
	IMPLEMENT_API(DBScanL2SquareDistantor, "lti{DBScanL2SquareDistantor}");

	IMPLEMENT_FACTORY_API2(
		DBScanL2SquareDistantor,
		"createDBScanL2Square");

	IMPLEMENT_TRAIN_API2(
		DBScanL2SquareDistantor);

}
