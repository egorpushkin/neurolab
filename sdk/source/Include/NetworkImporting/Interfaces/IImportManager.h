//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IImportManager.h
//	Description: The IImportManager declaration.

#ifndef IIMPORTMANAGER_H__NETWORKIMPORTING__INCLUDED_
#define IIMPORTMANAGER_H__NETWORKIMPORTING__INCLUDED_

// IImportManager declaration
interface IImportManager : public ICommon
{
	virtual result			InitializeManager() = 0;

	virtual result			LoadNLProject(const StringA& fileName, INetworkProcessor** ppiNetProc) = 0;
	virtual result			StoreNLProject(const StringA& fileName, INetworkProcessor* piNetProc) = 0;

	virtual result			CreateEmptyNetwork(INetworkProcessor** ppiNetProc) = 0;
};

#endif // !IIMPORTMANAGER_H__NETWORKIMPORTING__INCLUDED_
