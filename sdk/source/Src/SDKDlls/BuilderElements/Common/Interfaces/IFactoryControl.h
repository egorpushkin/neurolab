//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IFactoryControl.h
//	Description: The IFactoryControl declaration.  

#ifndef IFACTPRYCONTROL_H__BUILDERELEMENTS__INCLUDED_
#define IFACTPRYCONTROL_H__BUILDERELEMENTS__INCLUDED_

// IFactoryControl declaration
interface IFactoryControl : public ICommon
{
	virtual void			SetBuilderElementsControls(
		IGroupsContainer* piGroupsContainer,
		IFunctionsFactory* piFunctionsFactory) = 0;
};

#endif // !IFACTPRYCONTROL_H__BUILDERELEMENTS__INCLUDED_
