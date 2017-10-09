//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Element.h
//	Description: Network element additional system data structures declaration.  

#ifndef ELEMENT_H__BUILDERELEMENTS__INCLUDED_
#define ELEMENT_H__BUILDERELEMENTS__INCLUDED_

#define WRONG_ELEMENT_ID				0
#define WRONG_ELEMENT_RESOURCE_ID		-1

#define ELEMENT_DEFAULT_NEURONS_COUNT	64
#define ELEMENT_DEFAULT_INPUTS_COUNT	64

#define DEFAULT_CONNECTIONS_COUNT		1

#define DEFAULT_ADD_CONNECTION_STATE	0

#define DEFAULT_ELEMENT_DATA_LENGTH		1

#define DEFAULT_CONSTANT_INPUT_VALUE	1.0f

struct SysElement
{
	SysElement(const StringA& name, const StringA& title, const StringA& shortName)
		: name_(name)
		, title_(title)
		, shortName_(shortName)
	{
	}

	StringA					name_;
	StringA					title_;
	StringA					shortName_;
}; 

//
// Declaring aditional user types
//

typedef IEnumerator<SysElement*>		ISysElementsEnumerator;

#endif // !ELEMENT_H__BUILDERELEMENTS__INCLUDED_
