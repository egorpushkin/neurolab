#ifndef ISUBJECT_H__OBSERVER__COMMONKIT__INCLUDED_
#define ISUBJECT_H__OBSERVER__COMMONKIT__INCLUDED_

interface ISubject : public MinCOM::ICommon
{
	virtual result			Attach(const IObserverPtr& observer) = 0;
	virtual result			Detach(const IObserverPtr& observer) = 0;

	virtual result			Notify(const IObserverPtr& observer = NULL) const = 0;
};

typedef MinCOM::ComPtr< ISubject > ISubjectPtr;

#endif // !ISUBJECT_H__OBSERVER__COMMONKIT__INCLUDED_
