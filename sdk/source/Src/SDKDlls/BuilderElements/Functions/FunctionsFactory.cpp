//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: FunctionsFactory.cpp
//	Description: The CFunctionsFactory implementation.

#include "FunctionsFactory.h"

#include "FunctionRoutines.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CFunctionsFactory::CFunctionsFactory(void)
	: piFunctionsList_(NULL)
	, numRef_(0)
{
	CContainer<TransferFunction*, VectorStorage, Copy, NoRefs>* pFunctionsContainer = 
		new CContainer<TransferFunction*, VectorStorage, Copy, NoRefs>;

	pFunctionsContainer->QueryInterface(IID_IContainer, (void**)&piFunctionsList_);

	CreateFunctionsList();
}

CFunctionsFactory::~CFunctionsFactory(void)
{
	ReleaseFunctionsList();

	piFunctionsList_->Release();
}

//////////////////////////////////////////////////////////////////////////
// Creation/Destruction functions
//////////////////////////////////////////////////////////////////////////
void CFunctionsFactory::CreateFunctionsList()
{
	TransferFunction* pFunction = AddFunction(
		"SingleChange", 
		_T("Single Change"), 
		_T("Y={0, x<T; 1, x>=T}"),
		nfSingleChange, 
		nfSingleChangeDerivative);		
	pFunction->AddParameter(_T("T"), 0.0f);
	
	pFunction = AddFunction(
		"Hysteresis",
		_T("Hysteresis"),
		_T("Y={0, x<=0; x/T, 0<x<T; 1, x>=T}"),
		nfHysteresis,
		nfHysteresisDerivative);		
	pFunction->AddParameter(_T("T"), 0.5f);

	pFunction = AddFunction(
		"HyperbolicTangent",
		_T("Hyperbolic Tangent"),
		_T("Y={-1, atan(x)<-1; atan(x), -1<=atan(x)<=1; 1, atan(x)>1}"),
		nfHyperbolicTangent,
		nfHyperbolicTangentDerivative);	
	
	pFunction = AddFunction(
		"Sigmoid",
		_T("Sigmoid"),
		_T("Y=1/(1+exp(-alpha*x))"),
		nfSigmoid,
		nfSigmoidDerivative);	
	pFunction->AddParameter(_T("alpha"), 1.0f);

	pFunction = AddFunction(
		"Sin",
		_T("Sin"),
		_T("Y=sin(x)"),
		nfSin,
		nfSinDerivative);	

	pFunction = AddFunction(
		"Exponent",
		_T("Exponent"),
		_T("Y=exp(x)"),
		nfExponent,
		nfExponentDerivative);	

	pFunction = AddFunction(
		"Linear",
		_T("Linear"),
		_T("Y=x"),
		nfLinear,
		nfLinearDerivative);	
}

void CFunctionsFactory::ReleaseFunctionsList()
{
	IFunctionsEnumerator* pFuncEnum = piFunctionsList_->Clone();
	for(bool haSysElements = pFuncEnum->SelectFirst();haSysElements;haSysElements = pFuncEnum->SelectNext())
	{
		TransferFunction* pFunction = pFuncEnum->GetSelected();

		delete pFunction;
	}
	pFuncEnum->Release();
}

TransferFunction* CFunctionsFactory::AddFunction(						
	const StringA& rName,
	const String& rTitle,
	const String& rExpression,
	PPROCESS_FUNCTION_ROUTINE pFunctionRoutine,
	PPROCESS_FUNCTION_ROUTINE pDerivativeRoutine)
{
	TransferFunction* pFunction = new TransferFunction;
	
	pFunction->name_ = rName;
	pFunction->title_ = rTitle;
	pFunction->expression_ = rExpression;
	pFunction->pProcesTransferFunction_ = pFunctionRoutine;
	pFunction->pProcessDerivative_ = pDerivativeRoutine;

	piFunctionsList_->Add(pFunction);

    return pFunction;
}

//////////////////////////////////////////////////////////////////////////
// IFunctionsFactory implementations section
//////////////////////////////////////////////////////////////////////////
TransferFunction* CFunctionsFactory::GetHeadFunction()
{
	IFunctionsEnumerator* pFuncEnum = piFunctionsList_->Clone();

	TransferFunction* pHeadFunction = pFuncEnum->GetFirst();

	pFuncEnum->Release();

	return pHeadFunction;
}

TransferFunction* CFunctionsFactory::GetFunctionByName(const StringA& rFunctionName)
{
	TransferFunction* pFoundFunc = NULL;

	IFunctionsEnumerator* pFuncEnum = piFunctionsList_->Clone();
	for(bool haSysElements = pFuncEnum->SelectFirst();haSysElements;haSysElements = pFuncEnum->SelectNext())
	{
		TransferFunction* pFunction = pFuncEnum->GetSelected();
		if (pFunction->name_ == rFunctionName)
		{
			pFoundFunc = pFunction;
			break;
		}
	}
	pFuncEnum->Release();

	if (!pFoundFunc && rFunctionName == "SingleÑhange")
		return GetFunctionByName("SingleChange");

	return pFoundFunc;
}

IFunctionsEnumerator* CFunctionsFactory::GetFunctionsEnumerator()
{
	return piFunctionsList_->Clone();
}

//////////////////////////////////////////////////////////////////////////
// ICommon implementations section
//////////////////////////////////////////////////////////////////////////
ulong CFunctionsFactory::AddRef()
{
	return ++numRef_;						
}

ulong CFunctionsFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CFunctionsFactory::GetClassString() const
{
	return _T("CFunctionsFactory");
}

result CFunctionsFactory::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IFunctionsFactory)
	{
		*ppObject = (IFunctionsFactory*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
