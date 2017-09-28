#ifndef OBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
#define OBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_

class ObserverImpl 
	: public MinCOM::CommonImpl< IObserver > 
{
public:
	ObserverImpl() {}

	virtual ~ObserverImpl() {}

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
			*ppObject = MinCOM::CommonImpl< IObserver >::GetCommon(); 

		else if (iid == IID_IObserver)
			*ppObject = static_cast< IObserver* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IObserver >::GetCommon()->AddRef();
		return S_OK;
	}

};

#endif // !OBSERVERIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
 