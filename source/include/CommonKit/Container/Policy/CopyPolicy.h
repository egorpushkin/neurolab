#ifndef COPYPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
#define COPYPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_

#include "../Source/Enumerator.h"

template 
<
    class T,
    class StorageType
>
class Copy
{
	const Copy& operator=(const Copy&);

protected:
    Copy(const StorageType& container)
        : container_(container)
    {
    }

    IEnumerator<T>* CloneEnumerator()
    {
        Enumerator<T, StorageType>* pEmumerator = 
            new Enumerator<T, StorageType>(&container_);

        IEnumerator<T>* piEmumerator = NULL;
        pEmumerator->QueryInterface(IID_IEnumerator, (void**)&piEmumerator);

		return piEmumerator;
    }

private:
    const StorageType&		container_;
};

template 
<
    class T,
    class StorageType
>
class NoCopy
{
protected:
    NoCopy(const StorageType& container)
        : piEnumerator_(NULL)
    {
        Enumerator<T, StorageType>* pEnumerator = 
            new Enumerator<T, StorageType>(&container);
        
        result r = pEnumerator->QueryInterface(IID_IEnumerator, (void**)&piEnumerator_);

        assert(r == S_OK);
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
    IEnumerator<T>*     piEnumerator_;
};

#endif // !COPYPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
