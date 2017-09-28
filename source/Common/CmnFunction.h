#pragma once

#include "Templates\Enumerator.h"

#include "CmnObjects.h"

struct sFunction;
typedef float (*PPROCESS_FUNCTION_ROUTINE)(sFunction* pFunction, float input);

struct	sParameter
{
	CString				csParamName;
	float				fValue;
};

struct sFunction
{
	CString				csName;    
	CString				csTitle;    
	CString				csExpression;    

	PPROCESS_FUNCTION_ROUTINE pfnProcessFunction;
	PPROCESS_FUNCTION_ROUTINE pfnProcessDerivative;
	CList<sParameter*,sParameter*>	mParameters;

	void AddParameter(CString& ParamName, float Value)
	{
		sParameter* pParam = new sParameter;
		pParam->csParamName = ParamName;
		pParam->fValue = Value;
		mParameters.AddTail(pParam);
	}

	sParameter* GetParamByName(CString& ParamName)
	{	
		for (POSITION pos = mParameters.GetHeadPosition();pos;)
		{
			sParameter* tmParam = mParameters.GetNext(pos);
			if (tmParam->csParamName == ParamName)
				return tmParam;	
		}
		return NULL;
	}
};

interface IFunctionsFactory : public IObject
{
	virtual	sFunction*			GetHeadFunction() = 0;
	virtual sFunction*			GetFunctionByName(CString& FunctionName) = 0;

	INTERFACE_ENUMERATOR_DECLARATION(sFunction*, CreateEnumerator, GetNextFunction)
};

