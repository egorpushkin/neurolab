//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IElementsContainer.h
//	Description: The IElementsContainer declaration.  

#ifndef IELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
#define IELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_

// IElementsContainer declaration
interface IElementsContainer : public ICommon
{
	virtual const String&	GetTitle() = 0;
	
	virtual ISysElementsEnumerator*				GetElementsEnumerator() = 0;
};

//
// Declaring aditional user types
//

typedef IEnumerator<IElementsContainer*>		IElementContainersEnumerator;

#endif // !IELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
