//	This code is a part of Data Processing SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: BMPFactory.h
//	Description: The CBMPFactory declaration file.

#ifndef BMPFACTORY_H__DATAPROCESSING__INCLUDED_
#define BMPFACTORY_H__DATAPROCESSING__INCLUDED_

// CBMPFactory declaration
class CBMPFactory
	: public CDataFactory
	, public IBMPFactory
{
public:
	CBMPFactory();
	virtual ~CBMPFactory();

	// IBMPFactory declarations section
	virtual result			LoadBMPFile(LPCSTR FileName);

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

#endif // !BMPFACTORY_H__DATAPROCESSING__INCLUDED_
