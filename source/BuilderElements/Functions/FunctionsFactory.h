#pragma once

#include "CmnFunction.h"

class CFunctionsFactory : IFunctionsFactory
{
public:
	CFunctionsFactory(void);
	~CFunctionsFactory(void);

// Creation/Destruction functions
    void				CreateFunctionsList();
    void				ReleaseFunctionsList();

// IFunctionsFactory declarations section
	virtual	sFunction*			GetHeadFunction();
	virtual sFunction*			GetFunctionByName(CString& FunctionName);

	ENUMERATOR(mFunctionsList, sFunction*, CreateEnumerator, GetNextFunction, posFunctionsEnum)

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CList<sFunction*, sFunction*> mFunctionsList;
};
