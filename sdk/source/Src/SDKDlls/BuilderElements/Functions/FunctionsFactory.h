//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: FunctionsFactory.h
//	Description: The CFunctionsFactory declaration.  

#ifndef FUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_
#define FUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

// CFunctionsFactory declaration
class CFunctionsFactory 
	: BuilderElementsCommonKit::IFunctionsFactory
{
public:
	CFunctionsFactory(void);
	virtual ~CFunctionsFactory(void);

	//////////////////////////////////////////////////////////////////////////
	// Creation/Destruction functions
	//////////////////////////////////////////////////////////////////////////
    void					CreateFunctionsList();
    void					ReleaseFunctionsList();
	NetworkImportingKit::TransferFunction*	AddFunction(						
		const StringA& rName,
		const String& rTitle,
		const String& rExpression,
		NetworkImportingKit::PPROCESS_FUNCTION_ROUTINE pFunctionRoutine,
		NetworkImportingKit::PPROCESS_FUNCTION_ROUTINE pDerivativeRoutine);

	//////////////////////////////////////////////////////////////////////////
	// IFunctionsFactory declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual	NetworkImportingKit::TransferFunction*				GetHeadFunction();
	virtual NetworkImportingKit::TransferFunction*				GetFunctionByName(const StringA& rFunctionName);

	virtual NetworkImportingKit::IFunctionsEnumerator*			GetFunctionsEnumerator();

	//////////////////////////////////////////////////////////////////////////
	// ICommon declarations section	
	//////////////////////////////////////////////////////////////////////////
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	//////////////////////////////////////////////////////////////////////////
	// BuilderElementsCommonKit::IFunctionsFactory members
	//////////////////////////////////////////////////////////////////////////
	IContainer<NetworkImportingKit::TransferFunction*>*		piFunctionsList_;

	//////////////////////////////////////////////////////////////////////////
	// ICommon members
	//////////////////////////////////////////////////////////////////////////
	ulong					numRef_;
};

#endif // !FUNCTIONSFACTORY_H__BUILDERELEMENTS__INCLUDED_
