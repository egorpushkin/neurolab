//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IContainer.h
//	Description: IContainer declaration.  

#ifndef ICONTAINER_H__COMMON__INCLUDED_
#define ICONTAINER_H__COMMON__INCLUDED_

// IContainer declaration
template 
<
	class T
>
interface IContainer : ICommon
{
	virtual	result			Add(const T& newElement) = 0;
	virtual	result			Delete(const T& value) = 0;
	virtual	result			Delete(const uint index) = 0;

	virtual uint			Size() = 0;

	virtual	result			Clear() = 0;

	virtual IEnumerator<T>*	Clone() = 0;
};

#endif // !ICONTAINER_H__COMMON__INCLUDED_
