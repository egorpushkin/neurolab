//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDataFactory.h
//	Description: The CSerializeDataFactory declaration.  

#ifndef SERIALIZEDATAFACTORY_H__PROCESSTOOL__INCLUDED_
#define SERIALIZEDATAFACTORY_H__PROCESSTOOL__INCLUDED_

class SerializeDataFactory
{
public:
	static result Serialize(const StringA& fileName, IDataFactory* piDataFactory, bool loading)
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

private:
	// Internal serialization helpers
	static result Store(FILEDev& fileDev, IDataFactory* piDataFactory)
	{
		fprintf(fileDev, "%d\n", piDataFactory->GetDataLength());

		for (uint i = 0;i < piDataFactory->GetDataLength();i++)
			fprintf(fileDev, "%f ", piDataFactory->GetItemData(i));

		return S_OK;
	}

	static result Load(FILEDev& fileDev, IDataFactory* piDataFactory)
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
};

#endif // !SERIALIZEDATAFACTORY_H__PROCESSTOOL__INCLUDED_
