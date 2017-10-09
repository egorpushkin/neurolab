//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ObjectFactoryImpl.cpp
//	Description: The CCommonFactoryImpl implementation.  

#include "../Headers/CmnComponentsLib.h"

using namespace ComponentsKit;

CCommonFactoryImpl::CCommonFactoryImpl()
	: numRef_(0)
{
}

CCommonFactoryImpl::~CCommonFactoryImpl()
{
}

// ICommon implementations section
ulong CCommonFactoryImpl::AddRef()
{
	return ++numRef_;						
}

ulong CCommonFactoryImpl::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}
