//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonFactoryImpl.h
//	Description: The CCommonFactoryImpl declaration.  

#ifndef COMMONFACTORYIMPL_H__COMPONENTS__INCLUDED_
#define COMMONFACTORYIMPL_H__COMPONENTS__INCLUDED_

class CCommonFactoryImpl : public ICommonFactory
{
public:
	CCommonFactoryImpl();
	virtual ~CCommonFactoryImpl();

	// ICommon declarations section	
	virtual	ulong			AddRef();
	virtual	ulong			Release();

private:
	ulong					numRef_;
};

#endif // !COMMONFACTORYIMPL_H__COMPONENTS__INCLUDED_
