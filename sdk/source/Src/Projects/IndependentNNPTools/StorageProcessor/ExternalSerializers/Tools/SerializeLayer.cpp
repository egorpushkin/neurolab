//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeLayer.cpp
//	Description: The CSerializeLayer implementation.  

#include "SerializeLayer.h"

using namespace NetworkImportingKit;

result CSerializeLayer::SerializeWeights(const StringA& fileName, ILayerControl* piLayerControl, bool loading)
{
	result resultCode = S_OK;

	FILEDev fileDev;
	resultCode = fileDev.Open(fileName.c_str(), (loading ? ModeRead : ModeWrite));
	if (FAILED(resultCode))
		return resultCode;

	if (loading)
		resultCode = LoadWeights(fileDev, piLayerControl);
	else
		resultCode = StoreWeights(fileDev, piLayerControl);

	fileDev.Close();

	return resultCode;
}

result CSerializeLayer::SerializeDeltas(const StringA& fileName, ILayerControl* piLayerControl, bool loading)
{
	result resultCode = S_OK;

	FILEDev fileDev;
	resultCode = fileDev.Open(fileName.c_str(), (loading ? ModeRead : ModeWrite));
	if (FAILED(resultCode))
		return resultCode;

	if (loading)
		resultCode = LoadDeltas(fileDev, piLayerControl);
	else
		resultCode = StoreDeltas(fileDev, piLayerControl);

	fileDev.Close();

	return resultCode;
}

result CSerializeLayer::StoreWeights(FILEDev& fileDev, ILayerControl* piLayerControl)
{
	fprintf(fileDev, "%d\n", piLayerControl->GetDimension() * piLayerControl->GetInputsCount());

	for (uint i = 0;i < piLayerControl->GetDimension();i++)
		for (uint j = 0;j < piLayerControl->GetInputsCount();j++)
			fprintf(fileDev, "%f ", piLayerControl->GetWeight(j, i));

	return S_OK;
}

result CSerializeLayer::StoreDeltas(FILEDev& fileDev, ILayerControl* piLayerControl)
{
	fprintf(fileDev, "%d\n", piLayerControl->GetDimension());

	for (uint i = 0;i < piLayerControl->GetDimension();i++)
		fprintf(fileDev, "%f ", piLayerControl->GetDelta(i));

	return S_OK;
}

result CSerializeLayer::LoadWeights(FILEDev& fileDev, ILayerControl* piLayerControl)
{
	uint size = 0;
	fscanf(fileDev, "%d", &size);

	if (piLayerControl->GetDimension() * piLayerControl->GetInputsCount() != size)
		return S_FALSE;

	for (uint i = 0;i < piLayerControl->GetDimension();i++)
		for (uint j = 0;j < piLayerControl->GetInputsCount();j++)
		{
			float weight = 0.0f;
			fscanf(fileDev, "%f", &weight);
			piLayerControl->SetWeight(j, i, weight);
		}

	return S_OK;
}

result CSerializeLayer::LoadDeltas(FILEDev& fileDev, ILayerControl* piLayerControl)
{
	uint dimension = 0;
	fscanf(fileDev, "%d", &dimension);
	if (dimension != piLayerControl->GetDimension())
		return S_FALSE;

	for (uint i = 0;i < piLayerControl->GetDimension();i++)
	{
		float delta = 0.0f;
		fscanf(fileDev, "%f", &delta);
		piLayerControl->SetDelta(i, delta);
	}

	return S_OK;
}

