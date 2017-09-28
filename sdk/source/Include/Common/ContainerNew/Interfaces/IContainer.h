#ifndef ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_
#define ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_

template 
<
    class T
>
interface IContainer : public MinCOM::ICommon
{
    virtual result           Add(const T& newElement) = 0;
    virtual result           Delete(const T& value) = 0;
    virtual result           Delete(const uint index) = 0;

    virtual size_t	         Size() const = 0;

    virtual result           Clear() = 0;

    virtual IEnumerator<T>*  Clone() = 0;
};

#endif // !ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_
