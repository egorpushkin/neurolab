#ifndef SUBJECTIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
#define SUBJECTIMPL_H__OBSERVER__COMMONKIT__INCLUDED_

class SubjectImpl 
	: public MinCOM::CommonImpl< ISubject > 
{
public:
	SubjectImpl()
		: observers_()
	{}

	virtual ~SubjectImpl() {}

	// ISubject implementations section
	virtual result Attach(const IObserverPtr& observer)
	{
		IDuplexObserverPtr duplexObserver(observer, IID_IDuplexObserver);
		if (duplexObserver)
			duplexObserver->SetSubject(this);

		observers_.push_back(observer);
		return S_OK;
	}

	virtual result Detach(const IObserverPtr& observer)
	{
		ObserversContainer::iterator position = 
			std::find(observers_.begin(), observers_.end(),	observer);
		if (observers_.end() == position)
            return S_FALSE;

		observers_.erase(position);
		return S_OK;
	}

	virtual result Notify(const IObserverPtr& observer = NULL) const
	{
		for (ObserversContainer::const_iterator iter = observers_.begin();iter != observers_.end();iter++)
		{
			if ((*iter) != observer)
			{
				result r = (*iter)->Update();
				if (FAILED(r))
					return r;
			}
		}
		return S_OK;
	}

	// ICommon implementations section
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< ISubject >::GetCommon(); 

		else if (iid == IID_ISubject)
			*ppObject = static_cast< ISubject* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< ISubject >::GetCommon()->AddRef();
		return S_OK;
	}

private:
	typedef std::vector< IObserverPtr > ObserversContainer;
	ObserversContainer observers_;

};

#endif // !SUBJECTIMPL_H__OBSERVER__COMMONKIT__INCLUDED_
 