//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDataFactory.cpp
//	Description: The CSerializeDataFactory implementation.  

#include "SerializeDataFactory.h"

result CSerializeDataFactory::Serialize(const StringA& fileName, IDataFactory* piDataFactory, bool loading)
{
	result resultCode = S_OK;

	if (loading)
	{
		FILEDev fileDev;
		result resultCode = fileDev.Open(fileName.c_str(), ModeRead);
		if (FAILED(resultCode))
			return resultCode;

		resultCode = Load(fileDev, piDataFactory);

		fileDev.Close();		
	} else
	{
		FILEDev fileDev;
		result resultCode = fileDev.Open(fileName.c_str(), ModeWrite);
		if (FAILED(resultCode))
			return resultCode;

		resultCode = Store(fileDev, piDataFactory);

		fileDev.Close();
	}

	return resultCode;
}

IDataFactory* CSerializeDataFactory::LoadDataFactoryFromFile(const StringA& fileName)
{
	CDataFactory* pDataFactory = new CDataFactory;
	IDataFactory* piDataFactory = QueryTool<CDataFactory, IDataFactory>::QueryInterface(pDataFactory, IID_IDataFactory);

	result resultCode = Serialize(fileName, piDataFactory, ModeLoad);
	if (FAILED(resultCode))
	{
		piDataFactory->Release();
		return NULL;
	}

    return piDataFactory;
}

result CSerializeDataFactory::Store(FILEDev& fileDev, IDataFactory* piDataFactory)
{
    fprintf(fileDev, "%d\n", piDataFactory->GetDataLength());

    for (uint i = 0;i < piDataFactory->GetDataLength();i++)
		fprintf(fileDev, "%f ", piDataFactory->GetItemData(i));

	return S_OK;
}

result CSerializeDataFactory::Load(FILEDev& fileDev, IDataFactory* piDataFactory)
{
    uint dataLength = 0;
	fscanf(fileDev, "%d", &dataLength);

	piDataFactory->CreateFactory(dataLength);

	for (uint i = 0;i < piDataFactory->GetDataLength();i++)
	{
		float dataItem = 0.0f;
		fscanf(fileDev, "%f", &dataItem);
		piDataFactory->SetItemData(i, dataItem);
	}

	return S_OK;
}
