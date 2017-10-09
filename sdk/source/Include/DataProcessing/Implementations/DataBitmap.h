//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataBitmap.h
//	Description: The CDataBitmap declaration file.

#ifndef DATABITMAP_H__DATAPROCESSING__INCLUDED_
#define DATABITMAP_H__DATAPROCESSING__INCLUDED_

// CDataBitmap declaration
class CDataBitmap
	: public IDataBitmap
	, public IStorageController
{
public:
	CDataBitmap();
	virtual ~CDataBitmap();

	// IDataBitmap declarations section
	virtual void			AllocateData(uint Width, uint Height, uint ColorDepth);
	virtual void			ReleaseBitmap();

	virtual result			ConstructFromDataFactory(IDataFactory* pDataFactory, uint Width = 0, uint Height = 0);
	virtual result			GetDataFactory(uint XOffset, uint YOffset, uint Width, uint Height, IDataFactory* pDataFactory);

	virtual void*			GetData();

	virtual bool			IsLoaded();

	virtual uint			GetColorDepth();
	virtual uint			GetWidth();
	virtual uint			GetHeight();

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& FileDev, bool Loading);

	// IObject declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID refIID, void** ppvObject);

private:
	unsigned char*			pBitmapData;

	uint					iColorDepth;
	uint					iWidth;
	uint					iHeight;

private:
	ulong					numRef_;
};

#endif // !DATABITMAP_H__DATAPROCESSING__INCLUDED_
