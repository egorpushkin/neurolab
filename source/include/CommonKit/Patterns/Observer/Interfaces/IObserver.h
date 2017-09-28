#ifndef IOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_
#define IOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_

interface IObserver : public MinCOM::ICommon
{
	virtual result			Update() = 0;
};

typedef MinCOM::ComPtr< IObserver > IObserverPtr;

#endif // !IOBSERVER_H__OBSERVER__COMMONKIT__INCLUDED_
