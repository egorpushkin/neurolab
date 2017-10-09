//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Container.h
//	Description: The CContainer declaration and implementation.  

#ifndef CONTAINER_H__COMMON__INCLUDED_
#define CONTAINER_H__COMMON__INCLUDED_

// CContainer implementation
template 
<
	class T,
	template <class> class StoragePolicy = VectorStorage,
	template <class, class> class CopyPolicy = Copy,
	template <class> class ReferencesPolicy = WithRefs
>
class CContainer
	: public IContainer<T>
	, public StoragePolicy<T>
	, public CopyPolicy<T, typename StoragePolicy<T>::StorageType>
	, public ReferencesPolicy<T>
{	
	CContainer(CContainer& /* container */);
	const CContainer& operator =(const CContainer& /* container */);

	typedef CopyPolicy<T, typename StoragePolicy<T>::StorageType>	CopyPolicyInst;
	typedef ReferencesPolicy<T>										ReferencesPolicyInst;
	typedef StoragePolicy<T>										StoragePolicyInst;

public:	
	CContainer()
		: CopyPolicyInst(StoragePolicyInst::container_)
		, numRef_(0)
	{
	}

	virtual ~CContainer() 
	{
		Clear();
	}

	// IContainer implementations section
	virtual IEnumerator<T>* Clone()
	{
		return CopyPolicyInst::CloneEnumerator();
	}

	virtual	result Add(const T& newElement)
	{
		StoragePolicyInst::container_.push_back(newElement);
		ReferencesPolicyInst::AddRef(newElement);

		return S_OK;
	}

	virtual	result Delete(const T& value)
	{
		typename StoragePolicyInst::StorageType::iterator position = 
			find(
				StoragePolicyInst::container_.begin(), 
				StoragePolicyInst::container_.end(),
				value
			);

        if (position == StoragePolicyInst::container_.end())
			return S_FALSE;

		ReferencesPolicyInst::Release(*position);

        StoragePolicyInst::container_.erase(position);
        
		return S_OK;
	}

	virtual	result Delete(const uint /* index */)
	{
/*		if (index + 1 > StoragePolicyInst::container_.size())
			return S_FALSE;

		StoragePolicyInst::StorageType::iterator position = 
			StoragePolicyInst::container_.begin() + index;
        StoragePolicyInst::container_.erase(position);*/

		return S_OK;
	}

	virtual uint Size()
	{
		return (uint)StoragePolicyInst::container_.size();
	}

    virtual	result Clear()
	{
		typename StoragePolicyInst::StorageType::const_iterator iterator;
		
		for (iterator = StoragePolicyInst::container_.begin(); 
			iterator != StoragePolicyInst::container_.end(); 
			iterator++)
			ReferencesPolicyInst::Release(*iterator);

		StoragePolicyInst::container_.clear();

		return S_OK;
	}

	// ICommon implementations section
	virtual	ulong AddRef()
	{
		return ++numRef_;						
	}

	virtual	ulong Release()
	{
		--numRef_;

		if (numRef_ == 0)
		{
			delete this;
			return 0;
		}

		return numRef_;
	}

	virtual	String GetClassString() const
	{
		return _T("CContainer");
	}

	virtual result QueryInterface(REFIID rIID, void** ppObject)
	{
		if (rIID == IID_ICommon)
		{		
			*ppObject = (ICommon*)this;
		}
		else if (rIID == IID_IContainer)
		{
			*ppObject = (IContainer<T>*)this;			
		}
		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		((ICommon*)this)->AddRef();
		return S_OK;
	}

private:
	ulong					numRef_;
};

#endif // !CONTAINER_H__COMMON__INCLUDED_
