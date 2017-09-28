#ifndef DUPLEXOBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
#define DUPLEXOBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_

class DuplexObserverImpl 
	: public MinCOM::CommonImpl< IDuplexObserver > 
{
public:
	DuplexObserverImpl()
		: piSubject_(NULL)
	{}

	virtual ~DuplexObserverImpl() {}

	// IDuplexObserver implementations section
	virtual void SetSubject(ISubject* piSubject)
	{
		piSubject_ = piSubject;
	}

	virtual result NotifySubject()
	{
		if (!piSubject_)
			return S_FALSE;

		piSubject_->Notify(this);

		return S_OK;
	}

	// IObserver implementations section
	virtual result Update()
	{
		// Do nothing on update by default.
        return E_NOTIMPL;
	}

	// ICommon implementations section
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IDuplexObserver >::GetCommon(); 

		else if (iid == IID_IObserver)
			*ppObject = static_cast< IObserver* >(this);

		else if (iid == IID_IDuplexObserver)
			*ppObject = static_cast< IDuplexObserver* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IDuplexObserver >::GetCommon()->AddRef();
		return S_OK;
	}

protected:
	ISubject* piSubject_;

};

#endif // !DUPLEXOBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
 