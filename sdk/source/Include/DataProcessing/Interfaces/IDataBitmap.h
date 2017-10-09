//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IDataBitmap.h
//	Description: The IDataBitmap declaration file.

#ifndef IDATABITMAP_H__DATAPROCESSING__INCLUDED_
#define IDATABITMAP_H__DATAPROCESSING__INCLUDED_

// IDataBitmap declaration
interface IDataBitmap : public ICommon
{
	virtual void			AllocateData(uint Width, uint Height, uint ColorDepth) = 0;
	virtual void			ReleaseBitmap() = 0;
	
	virtual result			ConstructFromDataFactory(IDataFactory* pDataFactory, uint Width = 0, uint Height = 0) = 0;
	virtual result			GetDataFactory(uint XOffset, uint YOffset, uint Width, uint Height, IDataFactory* pDataFactory) = 0;

	virtual void*			GetData() = 0;

	virtual bool			IsLoaded() = 0;

	virtual uint			GetColorDepth() = 0;
	virtual uint			GetWidth() = 0;
	virtual uint			GetHeight() = 0;
};

typedef ComPtr< IDataBitmap > IDataBitmapPtr;

#endif // !IDATABITMAP_H__DATAPROCESSING__INCLUDED_
