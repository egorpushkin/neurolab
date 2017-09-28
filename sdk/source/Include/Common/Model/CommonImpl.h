#ifndef COMMONIMPL_H__COMMON__INCLUDED_
#define COMMONIMPL_H__COMMON__INCLUDED_

namespace Private
{

	class ReferenceDecl
	{
		ReferenceDecl(const ReferenceDecl&);
		ReferenceDecl& operator =(const ReferenceDecl&);

	protected:
		ReferenceDecl()
			: numRef_(0)
		{
		}

		ulong numRef_;
	};

} // namespace Private

template
<
    class T
>
class CommonImpl
    : virtual public Private::ReferenceDecl
    , public T
{
	CommonImpl(const CommonImpl&);
    CommonImpl& operator =(const CommonImpl&); 

protected:
    CommonImpl()
        : ReferenceDecl()
    {
    }

    virtual ~CommonImpl() {}

public:
    // Cast tools
    T* CastType()
    {
        return static_cast<T*>(this);
    }

    ICommon* GetCommon()
    {
        return static_cast<ICommon*>(this);
    }

    // ICommon implementations section
    virtual ulong AddRef()
    {
        return ++ReferenceDecl::numRef_;                        
    }

    virtual ulong Release()
    {
        --ReferenceDecl::numRef_;

        if (ReferenceDecl::numRef_ == 0)
        {
            delete this;
            return 0;
        }

        return ReferenceDecl::numRef_;
    }

	// Required to establish compatibility with old ICommon definition widely used in NISDK 1.1 and lower
	virtual	String GetClassString() const
	{
		return _T("CommonImpl");
	}

	result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == IID_ICommon)
			*ppObject = static_cast< ICommon* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		static_cast< ICommon* >(this)->AddRef();
		return S_OK;
	}

};

#endif // !COMMONIMPL_H__COMMON__INCLUDED_
