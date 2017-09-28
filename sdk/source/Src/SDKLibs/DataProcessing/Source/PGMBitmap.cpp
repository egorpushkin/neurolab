//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMBitmap.cpp
//	Description: The CPGMBitmap implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CPGMBitmap::CPGMBitmap()
	: numRef_(0)
{
}

CPGMBitmap::~CPGMBitmap()
{
}

// IPGMBitmap implementations section
result CPGMBitmap::LoadPGMBitmap(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeReadBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeLoad);
	return rSerialize;
}

result CPGMBitmap::SavePGMBitmap(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeWriteBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeStore);
	return rSerialize;
}

// IStorageController implementations section
result CPGMBitmap::Serialize(FILEDev& FileDev, bool Loading)
{
	if (Loading)
	{
		int				xsize;
		int				ysize;
		unsigned char	maxg;

		result fHeaderReading = PGMBReadHeader(FileDev, &xsize, &ysize, &maxg);
		if (FAILED(fHeaderReading))
			return fHeaderReading;

		AllocateData(xsize, ysize, 1);

		result rContentReading = PGMReadData<unsigned char>(FileDev, xsize, ysize, (unsigned char*)GetData());
		if (FAILED(rContentReading))
		{
			ReleaseBitmap();
			return rContentReading;
		}
	} else
	{
		char pszHeader[255];
		sprintf(pszHeader, "P5 %d %d 255", GetWidth(), GetHeight());
		FileDev.WriteStringA(pszHeader);

		FileDev.Write(GetData(), GetWidth()*GetHeight()*sizeof(unsigned char));
	}

	return S_OK;
}

// ICommon implementations section
ulong CPGMBitmap::AddRef()
{
	return ++numRef_;						
}

ulong CPGMBitmap::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CPGMBitmap::GetClassString() const
{
	return _T("CPGMBitmap");	
}

result CPGMBitmap::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IDataFile*)this;
	}
	else if (refIID == IID_IDataBitmap)
	{
		*ppvObject = (IDataBitmap*)this;
	}
	else if (refIID == IID_IPGMBitmap)
	{
		*ppvObject = (IPGMBitmap*)this;
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

	((ICommon*)(IDataFile*)this)->AddRef();
	return S_OK;
}
