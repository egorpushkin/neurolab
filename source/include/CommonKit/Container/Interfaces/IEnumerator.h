#ifndef IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
#define IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_

template 
<
    class T
>
interface IEnumerator : public MinCOM::ICommon
{
    virtual size_t          GetTotal() const = 0;

    virtual bool            SelectFirst() = 0;
    virtual bool            SelectLast() = 0;
    virtual bool            SelectNext() = 0;
    virtual bool            SelectPrev() = 0;

    virtual T               GetSelected() = 0;
    virtual T               GetFirst() = 0;
    virtual T               GetLast() = 0;
    
    virtual const T         GetSelected() const = 0;
    virtual const T         GetFirst() const = 0;
    virtual const T         GetLast() const = 0; 
};

#endif // !IENUMERATOR_H__CONTAINER__COMMONKIT__INCLUDED_
