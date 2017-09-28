//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: BMPFactory.cpp
//	Description: The CBMPFactory implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CBMPFactory::CBMPFactory()
	: numRef_(0)
{
}

// IBMPFactory implementations section
result CBMPFactory::LoadBMPFile(LPCSTR FileName)
{
	FILEDev fdFileDev;
	result rFileOpen = fdFileDev.Open(FileName, ModeReadBinary);
	if (FAILED(rFileOpen))
		return rFileOpen;

	result rSerialize = Serialize(fdFileDev, ModeLoad);
	return rSerialize;
}

// IStorageController implementations section
result CBMPFactory::Serialize(FILEDev& FileDev, bool Loading)
{
	if (Loading)
	{
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;

		FileDev.Read(&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
		if (bitmapFileHeader.bfType != 0x4D42)
			return STG_E_INVALIDHEADER;

		FileDev.Read(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
		if (bitmapInfoHeader.biBitCount > 8)
			return STG_E_INVALIDHEADER;

		unsigned char* pImageData = new unsigned char[bitmapInfoHeader.biSizeImage];

		fseek(FileDev, bitmapFileHeader.bfOffBits, SEEK_SET);
		FileDev.Read(pImageData, bitmapInfoHeader.biSizeImage);

		int iImageLength = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight;
		CreateFactory(iImageLength);

		// Parsing BMP data format
/*
		for (int i = 0;i < iImageLength;i++)
		{
			float fValue = GetFloatOfBitData(pszImageData, i, &bitmapInfoHeader);				
			SetItemData(i, fValue);
		}
*/		

		delete []pImageData;  
	} else
	{
		return E_NOTIMPL;
	}

	return S_OK;
}

// ICommon implementations section
ulong CBMPFactory::AddRef()
{
	return ++numRef_;						
}

ulong CBMPFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CBMPFactory::GetClassString() const
{
	return _T("CPGMBitmap");	
}

result CBMPFactory::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IDataFile*)this;
	}
	else if (refIID == IID_IDataFactory)
	{
		*ppvObject = (IDataFactory*)this;
	}
	else if (refIID == IID_IBMPFactory)
	{
		*ppvObject = (IBMPFactory*)this;
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
/*
private:
float GetFloatOfBitData(unsigned char* pszData, int iIndex, BITMAPINFOHEADER* pHeader)
{
	int iYOffset = pHeader->biHeight - (iIndex / pHeader->biWidth) - 1;
	int iXOffset = iIndex % pHeader->biWidth;

	int iLineDWORDs = ((pHeader->biWidth * pHeader->biBitCount - 1) / 64) + 1;
	int iBitLineWidth = iLineDWORDs * 64;

	int iBitOffset = iYOffset * iBitLineWidth + iXOffset * pHeader->biBitCount;
              	
	int iByteIndex = iBitOffset / (8 / pHeader->biBitCount);
	unsigned char cData = pszData[iByteIndex];

	int iByteOffset = 7 - (iBitOffset % (8 / pHeader->biBitCount));

	unsigned char cShiftedData = cData >> iByteOffset;
	cShiftedData = cShiftedData << (8 - pHeader->biBitCount);
	cShiftedData = cShiftedData >> (8 - pHeader->biBitCount);
	
	return cShiftedData*1.0f;
}
*/
