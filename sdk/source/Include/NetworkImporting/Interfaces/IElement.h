//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IElement.h
//	Description: Network element core.

#ifndef IELEMENT_H__NETWORKIMPORTING__INCLUDED_
#define IELEMENT_H__NETWORKIMPORTING__INCLUDED_

// IElement declaration
interface IElement : public ICommon
{
	// Element identificator manipulation routines
	virtual void			SetElementID(uint eleemntId) = 0;
	virtual uint			GetElementID() const = 0;

	// Element type receiving routine
	virtual	uint			GetElementType() const = 0;

	// Element system name and title manipulation routines
	virtual void			SetSysName(const StringA& name) = 0;
	virtual const StringA&	GetSysName() const = 0;
	
	virtual void			SetSysTitle(const StringA& title) = 0;
	virtual const StringA&	GetSysTitle() const = 0;	

	virtual void			SetShortName(const StringA& name) = 0;
	virtual const StringA&	GetShortName() const = 0;

	// Element events notification routine
	virtual void			CommandNotify(wparam wParam, lparam lParam) = 0;
};

//
// Declaring aditional user types
//

typedef ComPtr<	IElement > IElementPtr;
typedef const IElementPtr& IElementRef;

typedef IEnumerator<IElement*> IElementsEnumerator;

typedef IElementsEnumerator IElementsEnum;

typedef ComPtr<	IElementsEnum > IElementsEnumPtr;
typedef const IElementsEnumPtr& IElementsEnumRef;

#endif // !IELEMENT_H__NETWORKIMPORTING__INCLUDED_
