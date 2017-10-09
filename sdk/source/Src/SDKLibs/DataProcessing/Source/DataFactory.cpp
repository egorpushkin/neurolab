//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataFactory.cpp
//	Description: The CDataFactory implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CDataFactory::CDataFactory()
	: iDataLength(0)
	, pfFactoryData(NULL)
	, bFactoryCreated(false)
	, numRef_(0)
{
}

CDataFactory::CDataFactory(uint DataLength)
	: iDataLength(0)
	, pfFactoryData(NULL)
	, bFactoryCreated(false)
{
	CreateFactory(DataLength);
}

CDataFactory::CDataFactory(uint DataLength, float InitialData)
	: iDataLength(0)
	, pfFactoryData(NULL)
	, bFactoryCreated(false)
{
	CreateFactory(DataLength, InitialData);
}

CDataFactory::~CDataFactory()
{
	if (bFactoryCreated)
		ReleaseFactory();
}

// IDataFactory implementations section
// Creation/Destruction entries
void CDataFactory::CreateFactory(uint DataLength, float InitialData)
{
	if (DataLength <= 0)
		return;

	if (bFactoryCreated)
		ReleaseFactory();
	
	pfFactoryData = new float[DataLength];
	iDataLength = DataLength;

	bFactoryCreated = true;

	FillFactory(InitialData);
}

void CDataFactory::ReleaseFactory()
{
	if (pfFactoryData)
		delete []pfFactoryData;

	pfFactoryData = NULL;
	iDataLength = 0;

	bFactoryCreated = false;	
}

// Data processing routines
void CDataFactory::SetData(const IDataFactory* piData)
{
	SetData(piData->GetData(), piData->GetDataLength());
}

void CDataFactory::SetData(const float* pfData, uint DataLength)
{
	if (!bFactoryCreated || DataLength != iDataLength)
		CreateFactory(DataLength);

	memcpy(pfFactoryData, pfData, sizeof(float)*DataLength);
}

void CDataFactory::SetItemData(uint ItemIndex, float Data)
{
	if (!bFactoryCreated || ItemIndex >= iDataLength)
		return;

    pfFactoryData[ItemIndex] = Data;
}

void CDataFactory::FillFactory(float Data)
{
	if (!bFactoryCreated)
		return;

	for(uint i = 0;i < iDataLength;i++)
		pfFactoryData[i] = Data;
}

void CDataFactory::IncreaseValue(uint ItemIndex, float Data)
{
	if (!bFactoryCreated || ItemIndex >= iDataLength)
		return;

    pfFactoryData[ItemIndex] += Data;
}

float* CDataFactory::GetData() const
{
	if (!bFactoryCreated)
		return NULL;

	return pfFactoryData;
}

float* CDataFactory::GetData(uint& DataLength) const
{
	if (!bFactoryCreated)
		return NULL;

	DataLength = iDataLength;
	return pfFactoryData;
}

float CDataFactory::GetItemData(uint ItemIndex) const
{
	if (!bFactoryCreated || ItemIndex >= iDataLength)
		return 0;

	return pfFactoryData[ItemIndex];	
}

uint CDataFactory::GetDataLength() const
{
	return iDataLength;	
}

// IStorageController implementations section
result CDataFactory::Serialize(FILEDev& FileDev, bool Loading)
{
	if (Loading)
	{
		FileDev.Read(&bFactoryCreated, sizeof(bool));

		if (!bFactoryCreated)
			ReleaseFactory();
		else
		{
			uint iLength;
			FileDev.Read(&iLength, sizeof(int));

			CreateFactory(iLength);
			FileDev.Read(pfFactoryData, sizeof(float)*iDataLength);	
		}		

	} else
	{
		FileDev.Write(&bFactoryCreated, sizeof(bool));

		if (bFactoryCreated)
		{
			FileDev.Write(&iDataLength, sizeof(int));
			FileDev.Write(pfFactoryData, sizeof(float)*iDataLength);			
		}
	}

	return S_OK;
}

// ICommon implementations section
ulong CDataFactory::AddRef()
{
	return ++numRef_;						
}

ulong CDataFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CDataFactory::GetClassString() const
{
    return _T("CDataFactory");	
}

result CDataFactory::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IDataFactory*)this;
	}
	else if (refIID == IID_IDataFactory)
	{
		*ppvObject = (IDataFactory*)this;
	}
	else if (refIID == IID_IStorageController)
	{
		*ppvObject = (IStorageController*)this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IDataFactory*)this)->AddRef();
	return S_OK;
}
