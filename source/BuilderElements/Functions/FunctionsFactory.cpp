#include "StdAfx.h"
#include ".\FunctionsFactory.h"

#include "FunctionRoutines.h"

#include "interface_idds.h"

CFunctionsFactory::CFunctionsFactory(void)
{
}

CFunctionsFactory::~CFunctionsFactory(void)
{
	ReleaseFunctionsList();
}

// Creation/Destruction functions
void CFunctionsFactory::CreateFunctionsList()
{
	sFunction* pFunction = new sFunction;
	pFunction->csName = _T("SingleChange");
	pFunction->csTitle = _T("Single Change");
	pFunction->csExpression = _T("Y={0, x<T; 1, x>=T}");
	pFunction->pfnProcessFunction = nfSingleChange;	
	pFunction->pfnProcessDerivative = nfSingleChangeDerivative;	
	
	pFunction->AddParameter(CString("T"), 0.0f);
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("Hysteresis");
	pFunction->csTitle = _T("Hysteresis");
	pFunction->csExpression = _T("Y={0, x<=0; x/T, 0<x<T; 1, x>=T}");
	pFunction->pfnProcessFunction = nfHysteresis;
	pFunction->pfnProcessDerivative = nfHysteresisDerivative;	
	
	pFunction->AddParameter(CString("T"), 0.5f);
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("HyperbolicTangent");
	pFunction->csTitle = _T("Hyperbolic Tangent");
	pFunction->csExpression = _T("Y={-1, atan(x)<-1; atan(x), -1<=atan(x)<=1; 1, atan(x)>1}");
	pFunction->pfnProcessFunction = nfHyperbolicTangent;
	pFunction->pfnProcessDerivative = nfHyperbolicTangentDerivative;	
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("Sigmoid");
	pFunction->csTitle = _T("Sigmoid");
	pFunction->csExpression = _T("Y=1/(1+exp(-alpha*x))");
	pFunction->pfnProcessFunction = nfSigmoid;
	pFunction->pfnProcessDerivative = nfSigmoidDerivative;	
	
	pFunction->AddParameter(CString("alpha"), 1.0f);
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("Sin");
	pFunction->csTitle = _T("Sin");
	pFunction->csExpression = _T("Y=sin(x)");
	pFunction->pfnProcessFunction = nfSin;
	pFunction->pfnProcessDerivative = nfSinDerivative;	
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("Exponent");
	pFunction->csTitle = _T("Exponent");
	pFunction->csExpression = _T("Y=exp(x)");
	pFunction->pfnProcessFunction = nfExponent;
	pFunction->pfnProcessDerivative = nfExponentDerivative;	
	mFunctionsList.AddTail(pFunction);

	pFunction = new sFunction;
	pFunction->csName = _T("Linear");
	pFunction->csTitle = _T("Linear");
	pFunction->csExpression = _T("Y=x");
	pFunction->pfnProcessFunction = nfLinear;
	pFunction->pfnProcessDerivative = nfLinearDerivative;	
	mFunctionsList.AddTail(pFunction);
}

void CFunctionsFactory::ReleaseFunctionsList()
{
	
}

// IFunctionsFactory implementations section
sFunction* CFunctionsFactory::GetHeadFunction()
{
	return mFunctionsList.GetHead();
}

sFunction* CFunctionsFactory::GetFunctionByName(CString& FunctionName)
{
	for(POSITION pos = mFunctionsList.GetHeadPosition();pos;)
	{
		sFunction* pFunction = mFunctionsList.GetNext(pos);
		if (pFunction->csName == FunctionName)
			return pFunction;	
	}

	if (FunctionName == _T("Single—hange"))
		return mFunctionsList.GetHead();

	return NULL;
}

// IObject implementations section
CString CFunctionsFactory::GetClassString()
{
	return _T("CFunctionsFactory");
}

void CFunctionsFactory::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IFunctionsFactory:
		*ppvObject = (IFunctionsFactory*)this;
		break;
	}
}