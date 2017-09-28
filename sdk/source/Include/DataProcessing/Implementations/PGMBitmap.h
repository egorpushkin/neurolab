//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMBitmap.h
//	Description: The CPGMBitmap declaration file.

#ifndef PGMBITMAP_H__DATAPROCESSING__INCLUDED_
#define PGMBITMAP_H__DATAPROCESSING__INCLUDED_

// CPGMBitmap declaration
class CPGMBitmap
	: public CDataBitmap
	, public IPGMBitmap
{
public:
	CPGMBitmap();
	virtual ~CPGMBitmap();

	// IPGMBitmap declarations section
	virtual result			LoadPGMBitmap(LPCSTR FileName);
	virtual result			SavePGMBitmap(LPCSTR FileName);

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& FileDev, bool Loading);

	// IObject declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID refIID, void** ppvObject);

private:
	ulong					numRef_;
};

#endif // !PGMBITMAP_H__DATAPROCESSING__INCLUDED_
