//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IPGMBitmap.h
//	Description: The IDataBitmap declaration file.

#ifndef IPGMBITMAP_H__DATAPROCESSING__INCLUDED_
#define IPGMBITMAP_H__DATAPROCESSING__INCLUDED_

// IPGMBitmap declaration
interface IPGMBitmap : public ICommon
{
	virtual result			LoadPGMBitmap(LPCSTR FileName) = 0;
	virtual result			SavePGMBitmap(LPCSTR FileName) = 0;
};

typedef ComPtr< IPGMBitmap > IPGMBitmapPtr;

#endif // !IPGMBITMAP_H__DATAPROCESSING__INCLUDED_
