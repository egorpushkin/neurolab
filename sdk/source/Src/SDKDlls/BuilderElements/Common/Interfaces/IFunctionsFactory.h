//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IFunctionsFactory.h
//	Description: The IFunctionsFactory declaration.  

#ifndef IFUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_
#define IFUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_

// IFunctionsFactory declaration
interface IFunctionsFactory : public ICommon
{
	virtual	NetworkImportingKit::TransferFunction*				GetHeadFunction() = 0;
	virtual NetworkImportingKit::TransferFunction*				GetFunctionByName(const StringA& rFunctionName) = 0;

	virtual NetworkImportingKit::IFunctionsEnumerator*			GetFunctionsEnumerator() = 0;
};

#endif // !IFUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_
