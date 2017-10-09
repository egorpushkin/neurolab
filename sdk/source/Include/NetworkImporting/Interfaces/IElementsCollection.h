//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IElementsCollection.h
//	Description: The IElementsCollection declaration.

#ifndef IELEMENTSCOLLECTION_H__NETWORKIMPORTING__INCLUDED_
#define IELEMENTSCOLLECTION_H__NETWORKIMPORTING__INCLUDED_

// IElementsCollection declaration
interface IElementsCollection : public ICommon
{
	virtual result			SelectElement(IElement* piElement, bool shift, bool ctrl) = 0;

	virtual uint			GetInputsCount() = 0;
	virtual uint			GetOutputsCount() = 0;

	virtual IElementsEnumerator*	GetElementsEnumerator() = 0;
};

typedef ComPtr<	IElementsCollection > IElementsCollectionPtr;
typedef const IElementsCollectionPtr& IElementsCollectionRef;

#endif // !IELEMENTSCOLLECTION_H__NETWORKIMPORTING__INCLUDED_
