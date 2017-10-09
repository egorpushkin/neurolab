#ifndef COMMONFACTORY_H__TRAINERSMANAGER__INCLUDED_
#define COMMONFACTORY_H__TRAINERSMANAGER__INCLUDED_

#include "../TrainersManager.h"

class CCommonFactory 
	: public CCommonFactoryImpl
{
public:
	CCommonFactory();
	virtual ~CCommonFactory();

	// ICommonFactory declarations section	
	virtual result			LockServer(bool lock);
	virtual result			CreateInstance(ICommon* pObjOuter, REFIID iid, void** ppObject);

	// ICommon declarations section	
	virtual String			GetClassString() const;	
	virtual result			QueryInterface(REFIID iid, void** ppObject);
};

#endif // !COMMONFACTORY_H__TRAINERSMANAGER__INCLUDED_
