#ifndef CONTAINER_IMPL_H__CONTAINER__COMMONKIT__INCLUDED_
#define CONTAINER_IMPL_H__CONTAINER__COMMONKIT__INCLUDED_

// Container implementation
template 
<
    class T,
    template <class, template <class> class > class StoragePolicy = VectorStorage,
    template <class, class> class CopyPolicy = Copy,
    template <class> class ReferencesPolicy = WithRefs
>
class Container
    : public MinCOM::CommonImpl< IContainer<T> >
    , private StoragePolicy<T, ReferencesPolicy>
    , private CopyPolicy<T, typename StoragePolicy<T, ReferencesPolicy>::StorageType>
{    
    Container(const Container&);
    Container& operator =(const Container&);

    typedef StoragePolicy<T, ReferencesPolicy>						StoragePolicyInst;
	typedef CopyPolicy<T, typename StoragePolicyInst::StorageType>	CopyPolicyInst;

public:    
    Container()
		: StoragePolicyInst()
		, CopyPolicyInst(StoragePolicyInst::container_)
    {
    }

    virtual ~Container() 
    {
        Clear();
    }

    // IContainer implementations section
    virtual IEnumerator<T>* Clone()
    {
        return CopyPolicyInst::CloneEnumerator();
    }

    virtual result Add(const T& newElement)
    {
        return StoragePolicyInst::Add(newElement);
    }

    virtual result Delete(const T& value)
    {
		return StoragePolicyInst::Delete(value);
    }

    virtual result Delete(const uint index)
    {
		return StoragePolicyInst::Delete(index);
    }

    virtual size_t Size() const
    {
        return StoragePolicyInst::container_.size();
    }

    virtual result Clear()
    {
        return StoragePolicyInst::Clear();
    }

    // ICommon implementations section
    virtual result QueryInterface(REFIID iid, void** ppObject)
    {
        if (iid == MinCOM::IID_ICommon)
            *ppObject = static_cast<MinCOM::ICommon*>(this);

        else if (iid == IID_IContainer)
            *ppObject = static_cast<IContainer<T>*>(this);

        else
        {
            *ppObject = NULL;
            return E_NOINTERFACE;
        }

        static_cast<MinCOM::ICommon*>(this)->AddRef();
        return S_OK;
    }
};

#endif // !CONTAINER_IMPL_H__CONTAINER__COMMONKIT__INCLUDED_
