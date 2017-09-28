//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMFactory.cpp
//	Description: The CDataBitmap implementation file.

#include "../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

CDataBitmap::CDataBitmap()
	: pBitmapData(NULL)
	, iColorDepth(0)
	, iWidth(0)
	, iHeight(0)
	, numRef_(0)
{
}

CDataBitmap::~CDataBitmap()
{
	ReleaseBitmap();
}

// IDataBitmap implementations section
void CDataBitmap::AllocateData(uint Width, uint Height, uint ColorDepth)
{
	ReleaseBitmap();

	iColorDepth = ColorDepth;
	iWidth = Width;
	iHeight = Height;

	pBitmapData = new unsigned char[iWidth*iHeight*iColorDepth];	
}

result CDataBitmap::ConstructFromDataFactory(IDataFactory* pDataFactory, uint Width, uint Height)
{
	if (!pDataFactory || !pDataFactory->GetData())
		return E_INVALIDARG;

	if (Width == 0 || Height == 0)
	{
		Width = (uint)sqrt((pDataFactory->GetDataLength() - 1)*1.0f) + 1;
		Height = (uint)(pDataFactory->GetDataLength() - 1)/Width + 1;
	}

	AllocateData(Width, Height, 1);
	
	for (uint i = 0;i < pDataFactory->GetDataLength();i++)
		((unsigned char*)pBitmapData)[i] = (unsigned char)pDataFactory->GetItemData(i);

	return S_OK;
}

result CDataBitmap::GetDataFactory(uint XOffset, uint YOffset, uint Width, uint Height, IDataFactory* pDataFactory)
{
	if (XOffset + Width > GetWidth() || 
		YOffset + Height > GetHeight() || 
		!pDataFactory)
		return E_INVALIDARG;

	pDataFactory->CreateFactory(Width*Height);

	unsigned char* pRastrData = (unsigned char*)GetData();
	uint iBitmapWidth = GetWidth();

	uint tmOffset = 0;
	for (uint j = 0;j < Height;j++)
		for (uint i = 0;i < Width;i++)
		{
			float fData = pRastrData[(j + YOffset)*iBitmapWidth + XOffset + i];
			pDataFactory->SetItemData(tmOffset++, fData);
		}

	return true;
}

void* CDataBitmap::GetData()
{
	return pBitmapData;
}

bool CDataBitmap::IsLoaded()
{
	return (GetData() != NULL);
}

uint CDataBitmap::GetColorDepth()
{
	return iColorDepth;
}

uint CDataBitmap::GetWidth()
{
	return iWidth;
}

uint CDataBitmap::GetHeight()
{
	return iHeight;
}

void CDataBitmap::ReleaseBitmap()
{
	if (pBitmapData)
	{
		delete []pBitmapData;
		pBitmapData = NULL;

		iColorDepth = 0;
		iWidth = 0;
		iHeight = 0;
	}
}

// IStorageController implementations section
result CDataBitmap::Serialize(FILEDev& /* FileDev */, bool /* Loading*/)
{
	return E_NOTIMPL;
}

// ICommon implementations section
ulong CDataBitmap::AddRef()
{
	return ++numRef_;						
}

ulong CDataBitmap::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CDataBitmap::GetClassString() const
{
	return _T("CDataFactory");	
}

result CDataBitmap::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IDataFile*)this;
	}
	else if (refIID == IID_IDataBitmap)
	{
		*ppvObject = (IDataBitmap*)this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IDataFile*)this)->AddRef();
	return S_OK;
}
