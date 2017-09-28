//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CopyPolicy.h
//	Description: Copy policies implementation.  

#ifndef COPYPOLICY_H__COMMON__INCLUDED_
#define COPYPOLICY_H__COMMON__INCLUDED_

#include "../Enumerator.h"

template 
<
	class T,
	class StorageType
>
class Copy
{
	const Copy& operator =(const Copy&);

public:
	explicit Copy(StorageType& container)
		: container_(container)
	{
	}

	IEnumerator<T>* CloneEnumerator()
	{
		CEnumerator<T, StorageType>* pEmumerator = 
			new CEnumerator<T, StorageType>(&container_);

		IEnumerator<T>* piEmumerator = NULL;
		pEmumerator->QueryInterface(IID_IEnumerator, (void**)&piEmumerator);

		assert(piEmumerator != NULL);

		return piEmumerator;
	}

private:
	StorageType&		   		container_;
};

template 
<
	class T,
	class StorageType
>
class NoCopy
{
	const NoCopy& operator =(const NoCopy&);

public:
	NoCopy(StorageType& container)
		: piEnumerator_(NULL)
	{
		CEnumerator<T, StorageType>* pEnumerator = 
			new CEnumerator<T, StorageType>(&container);
		
		pEnumerator->QueryInterface(IID_IEnumerator, (void**)&piEnumerator_);

		assert(piEnumerator_ != NULL);
	}

	~NoCopy()
	{
		piEnumerator_->Release();
	}

	IEnumerator<T>* CloneEnumerator()
	{	
		piEnumerator_->AddRef();

		return piEnumerator_;
	}

private:	
	IEnumerator<T>*				piEnumerator_;
};

#endif // !COPYPOLICY_H__COMMON__INCLUDED_
