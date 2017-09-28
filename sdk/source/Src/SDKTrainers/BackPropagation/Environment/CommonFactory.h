#ifndef COMMONFACTORY_H__TRAINER__INCLUDED_
#define COMMONFACTORY_H__TRAINER__INCLUDED_

namespace Trainer
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
	virtual result			QueryInterface(REFIID rIID, void** ppObject);
};

} // namespace Trainer

#endif // !COMMONFACTORY_H__TRAINER__INCLUDED_
