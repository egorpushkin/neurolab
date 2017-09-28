//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeLayer.h
//	Description: The CSerializeLayer declaration.  

#ifndef SERIALIZELAYER_H__STORAGEPROCESSOR__INCLUDED_
#define SERIALIZELAYER_H__STORAGEPROCESSOR__INCLUDED_

#include "../../StorageProcessor.h"

class CSerializeLayer
{
public:
	static result				SerializeWeights(const StringA& fileName, NetworkImportingKit::ILayerControl* piLayerControl, bool loading);
	static result				SerializeDeltas(const StringA& fileName, NetworkImportingKit::ILayerControl* piLayerControl, bool loading);

private:
	// Internal serialization helpers
	static result				StoreWeights(FILEDev& fileDev, NetworkImportingKit::ILayerControl* piLayerControl);
	static result				StoreDeltas(FILEDev& fileDev, NetworkImportingKit::ILayerControl* piLayerControl);

	static result				LoadWeights(FILEDev& fileDev, NetworkImportingKit::ILayerControl* piLayerControl);
	static result				LoadDeltas(FILEDev& fileDev, NetworkImportingKit::ILayerControl* piLayerControl);
};

#endif // !SERIALIZELAYER_H__STORAGEPROCESSOR__INCLUDED_

