//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Enumerator.h
//	Description: The CEnumerator declaration and implementation.  

#ifndef ENUMERATOR_H__COMMON__INCLUDED_
#define ENUMERATOR_H__COMMON__INCLUDED_

// CEnumerator declaration and implementation
template 
<
	class T,
	class StorageType
>
class CEnumerator
	: public IEnumerator<T>
{
	CEnumerator(CEnumerator& /* enumerator */);
	const CEnumerator& operator =(const CEnumerator& /* enumerator */);

public:
	CEnumerator(StorageType* pContainer = NULL)
		: pContainer_(pContainer)
		, numRef_(0)
	{		
	}

	virtual ~CEnumerator() {}

	// Initialization tools
	virtual void SetContainer(StorageType* pContainer = NULL)
	{
		pContainer_ = pContainer;
	}

	// IEnumerator implementations section
	virtual bool SelectFirst()
	{
		if (!pContainer_)
			return false;

		if (pContainer_->size() == 0)
			return false;

		containerConstIterator_ = pContainer_->begin();

        return true;
	}

	virtual bool SelectNext()
	{
		if (!pContainer_)
			return false;

		if (pContainer_->size() == 0)
			return false;

		if (containerConstIterator_ == pContainer_->end())
			return false;
		
		if (++containerConstIterator_ == pContainer_->end())
			return false;

		return true;
	}

	virtual bool SelectLast()
	{
		if (!pContainer_)
			return false;

		if (pContainer_->size() == 0)
			return false;

		containerConstIterator_ = pContainer_->end();
		containerConstIterator_--;

		return true;
	}

	virtual bool SelectPrev()
	{
		if (!pContainer_)
			return false;

		if (containerConstIterator_ == pContainer_->begin())
			return false;

		containerConstIterator_--;

		return true;
	}

	virtual T& GetSelected() 
	{
		assert(pContainer_ != NULL);		

		return (T&)*containerConstIterator_;
	}

	virtual T& GetFirst() 
	{
		assert(pContainer_ != NULL);	

		typename StorageType::const_iterator containerIterator = pContainer_->begin();

		return (T&)*containerIterator;
	}

	virtual T& GetLast() 
	{
		assert(pContainer_ != NULL);	

		typename StorageType::const_iterator containerIterator = pContainer_->end(); 
		containerIterator--;

		return (T&)*containerIterator;
	}

	virtual const T& GetSelected() const
	{
		assert(pContainer_ != NULL);		

        return *containerConstIterator_;
	}

	virtual const T& GetFirst() const
	{
		assert(pContainer_ != NULL);	

		typename StorageType::const_iterator constIterator;
		constIterator = pContainer_->begin();
        
		return *constIterator;
	}

	virtual const T& GetLast() const
	{
		assert(pContainer_ != NULL);	

		typename StorageType::const_iterator constIterator;
		constIterator = pContainer_->end();
		constIterator--;

		return *constIterator;
	}

	virtual size_t GetTotal() const
	{
		if (!pContainer_)
			return 0;

		return pContainer_->size();
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
		return _T("CEnumerator");
	}

	virtual result QueryInterface(REFIID rIID, void** ppObject)
	{
		if (rIID == IID_ICommon)
		{		
			*ppObject = (ICommon*)this;
		}
		else if (rIID == IID_IEnumerator)
		{
			*ppObject = (IEnumerator<T>*)this;			
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
	StorageType*								pContainer_;
	typename StorageType::const_iterator		containerConstIterator_;

	ulong					numRef_;
};

#endif // !ENUMERATOR_H__COMMON__INCLUDED_
