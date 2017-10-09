//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: IExternalSerializer.h
//	Description: The IExternalSerializer declaration.  

#ifndef IEXTERNALSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_
#define IEXTERNALSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_

// IExternalSerializer declaration
interface IExternalSerializer : public ICommon
{
	virtual result			SerializeNLProject(const StringA& fileName, 
		NetworkImportingKit::INetworkProcessor* piNetProc, bool loading) = 0;

	virtual void			SetFlags(dword flags) = 0;
};

#endif // !IEXTERNALSERIALIZER_H__STORAGEPROCESSOR__INCLUDED_
