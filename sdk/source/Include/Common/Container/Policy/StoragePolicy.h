//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: StoragePolicy.h
//	Description: Storage policies implementation.  

#ifndef STORAGEPOLICY_H__COMMON__INCLUDED_
#define STORAGEPOLICY_H__COMMON__INCLUDED_

template 
<
	class T
>
class VectorStorage
{
public:
	typedef vector<T>		StorageType;

public:
	StorageType				container_;	
};

template 
<
	class T
>
class ListStorage
{
public:
	typedef list<T>			StorageType;

public:
	StorageType				container_;	
};

#endif // !STORAGEPOLICY_H__COMMON__INCLUDED_
