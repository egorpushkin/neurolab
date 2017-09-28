//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IPGMFactory.h
//	Description: The IPGMFactory declaration file.

#ifndef IPGMFACTORY_H__DATAPROCESSING__INCLUDED_
#define IPGMFACTORY_H__DATAPROCESSING__INCLUDED_

// IPGMFactory declaration
interface IPGMFactory : public ICommon
{
	virtual result			LoadPGMFile(LPCSTR FileName) = 0;
	virtual result			SavePGMFile(LPCSTR FileName) = 0;
};

typedef ComPtr< IPGMFactory > IPGMFactoryPtr;

#endif // !IPGMFACTORY_H__DATAPROCESSING__INCLUDED_
