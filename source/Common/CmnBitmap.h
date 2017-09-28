#pragma once

#include "interface_idds.h"
#include "CmnObjects.h"

#include <Math.h>

interface IDataBitmap : public IObject
{
	virtual void			AllocateData(int Width, int Height, int ColorDepth) = 0;
	virtual void			ReleaseBitmap() = 0;
	
	virtual bool			ConstructFromDataFactory(IDataFactory* pDataFactory, int Width = -1, int Height = -1) = 0;
	virtual bool			GetDataFactory(int XOffset, int YOffset, int Width, int Height, IDataFactory* pDataFactory) = 0;

	virtual void*			GetData() = 0;

	virtual bool			IsLoaded() = 0;

	virtual int				GetColorDepth() = 0;
	virtual int				GetWidth() = 0;
	virtual int				GetHeight() = 0;
};

class CDataBitmap : 
	public IDataBitmap,
	public IStorageController
{
public:
	CDataBitmap()
		: pBitmapData(NULL)
		, iColorDepth(0)
		, iWidth(0)
		, iHeight(0)
	{
	}

	~CDataBitmap()
	{
		ReleaseBitmap();
	}

	// IDataBitmap implementations section
	virtual void AllocateData(int Width, int Height, int ColorDepth)
	{
		ReleaseBitmap();

		iColorDepth = ColorDepth;
		iWidth = Width;
		iHeight = Height;

		pBitmapData = (void*)new unsigned char[iWidth*iHeight*iColorDepth];	
	}

	virtual bool ConstructFromDataFactory(IDataFactory* pDataFactory, int Width = -1, int Height = -1)
	{
		if (!pDataFactory || !pDataFactory->GetData())
			return false;

		if (Width == -1 || Height == -1)
		{
			Width = sqrt((pDataFactory->GetDataLength() - 1)*1.0f) + 1;
			Height = (pDataFactory->GetDataLength() - 1)/Width + 1;
		}

		AllocateData(Width, Height, 1);
		
		for (int i = 0;i < pDataFactory->GetDataLength();i++)
			((unsigned char*)pBitmapData)[i] = (unsigned char)pDataFactory->GetItemData(i);

		return true;
	}

	virtual bool GetDataFactory(int XOffset, int YOffset, int Width, int Height, IDataFactory* pDataFactory)
	{
		if (XOffset + Width > GetWidth() || 
			YOffset + Height > GetHeight() || 
			XOffset < 0 || 
			YOffset < 0 ||
			Width < 0 || 
			Height < 0 ||
			!pDataFactory)
			return false;

		pDataFactory->CreateFactory(Width*Height);

		unsigned char* pRastrData = (unsigned char*)GetData();
		int iBitmapWidth = GetWidth();
		int iBitmapHeight = GetHeight();

		int tmOffset = 0;
		for (int j = 0;j < Height;j++)
			for (int i = 0;i < Width;i++)
			{
				float fData = pRastrData[(j + YOffset)*iBitmapWidth + XOffset + i];
				pDataFactory->SetItemData(tmOffset++, fData);
			}

		return true;
	}

	virtual void* GetData()
	{
		return pBitmapData;
	}

	virtual bool IsLoaded()
	{
		return (GetData() != NULL);
	}
	
	virtual int GetColorDepth()
	{
		return iColorDepth;
	}

	virtual int GetWidth()
	{
		return iWidth;
	}

	virtual int GetHeight()
	{
		return iHeight;
	}

	virtual void ReleaseBitmap()
	{
		if (pBitmapData)
		{
			delete pBitmapData;
			pBitmapData = NULL;

			iColorDepth = 0;
			iWidth = 0;
			iHeight = 0;
		}
	}

	// IStorageController implementations section
	virtual bool Serialize(CArchive& ar)
	{
		return false;
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CDataFactory");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IDataBitmap:
			*ppvObject = (IDataBitmap*)this;
			break;
		}
	}

private:
	void*			pBitmapData;

	int				iColorDepth;
	int				iWidth;
	int				iHeight;
};
