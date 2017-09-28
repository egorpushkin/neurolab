//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Connection.cpp
//	Description: The CConnection implementation file.

#include "../Headers/CmnNetworkImportingLib.h"

using namespace NetworkImportingKit;

CConnection::CConnection()
	: piElement_(NULL)
	, pOpposite_(NULL)
	, hasData_(false)
	, numRef_(1)
{
}

CConnection::CConnection(uint Count)
	: piElement_(NULL)
	, pOpposite_(NULL)
	, hasData_(false)
	, numRef_(1)
{
	SizeConnection(Count);
}

CConnection::~CConnection()
{
}

void CConnection::SizeConnection(uint Count)
{
	weights_.CreateFactory(Count);
	data_.CreateFactory(Count);
	deltas_.CreateFactory(Count);

	if (pOpposite_)
	{
		pOpposite_->weights_.CreateFactory(Count);
		pOpposite_->data_.CreateFactory(Count);
		pOpposite_->deltas_.CreateFactory(Count);
	}
}

// IStorageController implementations section
result CConnection::Serialize(FILEDev& FileDev, bool Loading)
{
	if (Loading)
	{		
		FileDev.Read(&prevPtr_, sizeof(int));
		FileDev.Read(&prevOpositePtr_, sizeof(int));
		FileDev.Read(&hasData_, sizeof(bool));
	} else
	{		
		CConnection* pThis = this;

		FileDev.Write(&pThis, sizeof(int));
		FileDev.Write(&pOpposite_, sizeof(int));
		FileDev.Write(&hasData_, sizeof(bool));
	}

	weights_.Serialize(FileDev, Loading);
	data_.Serialize(FileDev, Loading);

	if (Loading)
		deltas_.CreateFactory(data_.GetDataLength());

	return S_OK;
}

// ICommon implementations section
ulong CConnection::AddRef()
{
	return ++numRef_;						
}

ulong CConnection::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CConnection::GetClassString() const
{
	return _T("CConnection");	
}

result CConnection::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)this;
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

	((ICommon*)this)->AddRef();
	return S_OK;
}
