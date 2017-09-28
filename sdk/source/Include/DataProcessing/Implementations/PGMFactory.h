//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMFactory.h
//	Description: The CPGMFactory declaration file.

#ifndef PGMFACTORY_H__DATAPROCESSING__INCLUDED_
#define PGMFACTORY_H__DATAPROCESSING__INCLUDED_

// CPGMFactory declaration
class CPGMFactory
	: public CDataFactory
	, public IPGMFactory
{
public:
	CPGMFactory();
	virtual ~CPGMFactory();

	// IPGMFactory implementations section
	virtual result			LoadPGMFile(LPCSTR FileName);
	virtual result			SavePGMFile(LPCSTR FileName);

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

#endif // !CMNPGMFACTORY_H__DATAPROCESSING__INCLUDED_
