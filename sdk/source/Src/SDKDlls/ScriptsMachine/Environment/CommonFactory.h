#ifndef COMMONFACTORY_H__INCLUDED_
#define COMMONFACTORY_H__INCLUDED_

namespace ScriptsMachine
{

class CommonFactory 
	: public MinCOM::CommonImpl< MinCOM::ICommonFactory >
{
public:
	CommonFactory();
	virtual ~CommonFactory();

	// ICommonFactory declarations section	
	virtual result			LockServer(bool lock);
	virtual result			CreateInstance(ICommon* piObjOuter, REFIID iid, void** ppObject);

	// ICommon declarations section	
	virtual result			QueryInterface(REFIID iid, void** ppObject);
};

}

#endif // !COMMONFACTORY_H__INCLUDED_
