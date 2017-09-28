//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IStorageController.h
//	Description: The IStorageController declaration file.

#ifndef ISTORAGECONTROLLER_H__DATAPROCESSING__INCLUDED_
#define ISTORAGECONTROLLER_H__DATAPROCESSING__INCLUDED_

// IStorageController declaration
interface IStorageController : public ICommon
{
	virtual result			Serialize(FILEDev& fileDev, bool loading) = 0;
};

#endif // !ISTORAGECONTROLLER_H__DATAPROCESSING__INCLUDED_
