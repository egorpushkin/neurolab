//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ICommonFactory.h
//	Description: ICommonFactory declaration.  

#ifndef ICOMMONFACTORY_H__COMMON__INCLUDED_
#define ICOMMONFACTORY_H__COMMON__INCLUDED_

// IObject declaration
interface ICommonFactory : public ICommon
{
	virtual result			LockServer(bool lock) = 0;
	virtual result			CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject) = 0;
};

#endif // !ICOMMONFACTORY_H__COMMON__INCLUDED_
