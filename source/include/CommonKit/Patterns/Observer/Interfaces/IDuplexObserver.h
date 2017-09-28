#ifndef IDUPLEXOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_
#define IDUPLEXOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_

interface IDuplexObserver : public IObserver
{
	virtual void			SetSubject(ISubject* piSubject) = 0;
	virtual result			NotifySubject() = 0;
};

typedef MinCOM::ComPtr< IDuplexObserver > IDuplexObserverPtr;

#endif // !IDUPLEXOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_
