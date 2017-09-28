#ifndef ENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
#define ENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_

template 
<
    class T,
    class StorageType
>
class Enumerator 
	: public MinCOM::CommonImpl< IEnumerator<T> >
{
    Enumerator(const Enumerator&);
    Enumerator& operator =(const Enumerator&);

public:
    Enumerator(const StorageType* pContainer = NULL)
        : pContainer_(pContainer)
    {        
    }

    virtual ~Enumerator() {}

    // Initialization tools
    virtual void SetContainer(const StorageType* pContainer = NULL)
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

    virtual T GetSelected() 
    {
        assert(pContainer_ != NULL);        

        return const_cast<T&>(
			static_cast<const T&>(*containerConstIterator_)
		);
    }
    
    virtual const T GetSelected() const
    {
        assert(pContainer_ != NULL);        

        return (*containerConstIterator_);
    }

    virtual T GetFirst()
    {
        assert(pContainer_ != NULL);    

        typename StorageType::const_iterator containerIterator = pContainer_->begin();

        return const_cast<T&>(
			static_cast<const T&>(*containerIterator)
		);
    }

    virtual const T GetFirst() const
    {
        assert(pContainer_ != NULL);    

        typename StorageType::const_iterator containerIterator = pContainer_->begin();

        return (*containerIterator);
    }

    virtual T GetLast()
    {
        assert(pContainer_ != NULL);    

        typename StorageType::const_iterator containerIterator = pContainer_->end(); 
        containerIterator--;

        return const_cast<T&>(
			static_cast<const T&>(*containerIterator)
		);
    }

    virtual const T GetLast() const
    {
        assert(pContainer_ != NULL);    

        typename StorageType::const_iterator containerIterator = pContainer_->end();
        containerIterator--;

        return (*containerIterator);
    }

    virtual size_t GetTotal() const
    {
        if (!pContainer_)
            return 0;

        return pContainer_->size();
    }

    // ICommon implementations section
    virtual result QueryInterface(REFIID iid, void** ppObject)
    {
        if (iid == MinCOM::IID_ICommon)
            *ppObject = static_cast<MinCOM::ICommon*>(this);

        else if (iid == IID_IEnumerator)
            *ppObject = static_cast<IEnumerator<T>*>(this);

        else
        {
            *ppObject = NULL;
            return E_NOINTERFACE;
        }

        static_cast<MinCOM::ICommon*>(this)->AddRef();
        return S_OK;
    }

private:
    const StorageType*                      pContainer_;
    typename StorageType::const_iterator    containerConstIterator_;
};

#endif // !ENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
