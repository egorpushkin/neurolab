#ifndef STORAGEPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
#define STORAGEPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_

template 
<
	class T,
    class StorageType,
	template <class> class ReferencesPolicy
>
class CommonStorage
{
	typedef ReferencesPolicy<T>	ReferencesPolicyInst;

protected:
	CommonStorage();

public:
	static result Add(const T& newElement, StorageType& container)
	{
		container.push_back(newElement);
		ReferencesPolicyInst::AddRef(newElement);

		return S_OK;
	}

	static result Delete(const T& value, StorageType& container)
	{
		typename StorageType::iterator position = 
			std::find(
				container.begin(), 
				container.end(),
				value
			);

		if (position == container.end())
			return S_FALSE;

		ReferencesPolicyInst::Release(value);
		container.erase(position);
		
		return S_OK;
	}

	static result Clear(StorageType& container)
	{
		typename StorageType::const_iterator iterator;

		for (iterator = container.begin(); iterator != container.end(); iterator++)
			ReferencesPolicyInst::Release(*iterator);

		container.clear();

		return S_OK;
	}



};

template 
<
    class T,
    template <class> class ReferencesPolicy
>
class VectorStorage 
{
public:
	typedef std::vector<T>      StorageType;

private:
	typedef ReferencesPolicy<T>	ReferencesPolicyInst;
	typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

protected:
	VectorStorage() {}

	virtual result Add(const T& newElement)
	{
		return CommonStorageInst::Add(newElement, container_);
	}

	virtual result Delete(const T& value)
	{
		return CommonStorageInst::Delete(value, container_);
	}

	virtual result Delete(const uint index)
	{
		if (index + 1 > container_.size())
			return S_FALSE;

		typename StorageType::iterator position = container_.begin() + index;
		
        ReferencesPolicyInst::Release(*position);

		container_.erase(position);
				
		return S_OK;
	}

    virtual result Clear()
	{
		return CommonStorageInst::Clear(container_);
	}

	StorageType                 container_;
};

template 
<
    class T,
	template <class> class ReferencesPolicy
>
class ListStorage
{
public:
    typedef std::list<T>        StorageType;

private:
	typedef ReferencesPolicy<T>	ReferencesPolicyInst;
	typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

protected:
	ListStorage() {}

	virtual result Add(const T& newElement)
	{
		return CommonStorageInst::Add(newElement, container_);
	}

	virtual result Delete(const T& value)
	{
		return CommonStorageInst::Delete(value, container_);
	}

	virtual result Delete(const uint index)
	{
		if (index + 1 > container_.size())
			return S_FALSE;

/*		StorageType::iterator position = container_.begin() + index;
		container_.erase(position);*/

		return E_NOTIMPL;
	}

    virtual result Clear()
	{
		return CommonStorageInst::Clear(container_);
	}

    StorageType                 container_;    
};

template 
<
	class T,
	template <class> class ReferencesPolicy
>
class MapStorage
{
public:
	typedef std::map<typename T::first_type, typename T::second_type>        StorageType;

private:
	typedef ReferencesPolicy<T>	ReferencesPolicyInst;
	typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

protected:
	MapStorage() {}

	virtual result Add(const T& newElement)
	{
		std::pair<StorageType::iterator, bool> iter = container_.insert(newElement);
		if ( !iter.second )
		{
            Delete(newElement);
			return Add(newElement);
		}

		ReferencesPolicyInst::AddRef(newElement);

		return (iter.second ? S_OK : S_FALSE);
	}

	virtual result Delete(const T& value)
	{
		StorageType::iterator iter = container_.find(value.first);
		
		if ( iter == container_.end() )
			return S_FALSE;
		
		ReferencesPolicyInst::Release(*iter);
        container_.erase(iter);

		return S_OK;
	}

	virtual result Delete(const uint index)
	{
		if (index + 1 > container_.size())
			return S_FALSE;

		/*		StorageType::iterator position = container_.begin() + index;
		container_.erase(position);*/

		return E_NOTIMPL;
	}

	virtual result Clear()
	{
		typename StorageType::const_iterator iterator;

		for (iterator = container_.begin(); iterator != container_.end(); iterator++)
			ReferencesPolicyInst::Release(*iterator);

		container_.clear();

		return S_OK;
	}

	StorageType                 container_;      
};


template 
<
	class T,
	template <class> class ReferencesPolicy
>
class MultimapStorage
{
public:
	typedef std::multimap<typename T::first_type, typename T::second_type>        StorageType;

private:
	typedef ReferencesPolicy<T>	ReferencesPolicyInst;
	typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

protected:
	MultimapStorage() {}

	virtual result Add(const T& newElement)
	{
		/*std::pair<StorageType::iterator, bool> iter =*/ container_.insert(newElement);
		/* if ( !iter.second )
		{
            Delete(newElement);
			return Add(newElement);
		} */

		ReferencesPolicyInst::AddRef(newElement);

		return /*(iter.second ?*/ S_OK /*: S_FALSE)*/;
	}

	virtual result Delete(const T& value)
	{
		StorageType::iterator iter = container_.find(value.first);
		
		if ( iter == container_.end() )
			return S_FALSE;
		
		ReferencesPolicyInst::Release(*iter);
        container_.erase(iter);

		return S_OK;
	}

	virtual result Delete(const uint index)
	{
		if (index + 1 > container_.size())
			return S_FALSE;

		/*		StorageType::iterator position = container_.begin() + index;
		container_.erase(position);*/

		return E_NOTIMPL;
	}

	virtual result Clear()
	{
		typename StorageType::const_iterator iterator;

		for (iterator = container_.begin(); iterator != container_.end(); iterator++)
			ReferencesPolicyInst::Release(*iterator);

		container_.clear();

		return S_OK;
	}

	StorageType                 container_;      
};

#endif // !STORAGEPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
