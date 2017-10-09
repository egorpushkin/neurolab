//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: RefeerncesPolicy.h
//	Description: References policies implementation.  

#ifndef REFERENCESPOLICY_H__COMMON__INCLUDED_
#define REFERENCESPOLICY_H__COMMON__INCLUDED_

template 
<
	class T
>
class WithRefs
{
public:
	ulong AddRef(const T& element)
	{
		return element->AddRef();
	}

	ulong Release(const T& element)
	{
		return element->Release();
	}
};

template 
<
	class T
>
class NoRefs
{
public:
	ulong AddRef(const T& /* element */)
	{
		return 0;
	}

	ulong Release(const T& /* element */)
	{
		return 0;
	}
};

#endif // !REFERENCESPOLICY_H__COMMON__INCLUDED_
