//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMFactory.cpp
//	Description: The CPGMFactory implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CPGMFactory::CPGMFactory()
	: numRef_(0)
{
}

CPGMFactory::~CPGMFactory()
{
}

// IPGMFactory implementations section
result CPGMFactory::LoadPGMFile(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeReadBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeLoad);
	return rSerialize;
}

result CPGMFactory::SavePGMFile(LPCSTR FileName)
{	
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeWriteBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeStore);
	return rSerialize;
}

// IStorageController implementations section
result CPGMFactory::Serialize(FILEDev& FileDev, bool Loading)
{
	if (Loading)
	{
		int				xsize;
		int				ysize;
		unsigned char	maxg;

		result fHeaderReading = PGMBReadHeader(FileDev, &xsize, &ysize, &maxg);
		if (FAILED(fHeaderReading))
			return fHeaderReading;

		CreateFactory(xsize * ysize);

		result rContentReading = PGMReadData<float>(FileDev, xsize, ysize, GetData());
		if (FAILED(rContentReading))
		{
			ReleaseFactory();
			return rContentReading;
		}
	} else
	{

	}

	return S_OK;
}

// ICommon implementations section
ulong CPGMFactory::AddRef()
{
	return ++numRef_;						
}

ulong CPGMFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CPGMFactory::GetClassString() const
{
	return _T("CPGMFactory");	
}

result CPGMFactory::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IPGMFactory*)this;
	}
	else if (refIID == IID_IDataFactory)
	{
		*ppvObject = (IDataFactory*)this;
	}
	else if (refIID == IID_IPGMFactory)
	{
		*ppvObject = (IPGMFactory*)this;
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

	((ICommon*)(IPGMFactory*)this)->AddRef();
	return S_OK;
}
