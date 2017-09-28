//	This code is a part of Data Processing SDK.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IBMPFactory.h
//	Description: The IBMPFactory declaration file.

#ifndef IBMPFACTORY_H__DATAPROCESSING__INCLUDED_
#define IBMPFACTORY_H__DATAPROCESSING__INCLUDED_

// IBMPFactory declaration
interface IBMPFactory : public ICommon
{
	virtual result			LoadBMPFile(LPCSTR FileName) = 0;
};

#endif // !IBMPFACTORY_H__DATAPROCESSING__INCLUDED_
