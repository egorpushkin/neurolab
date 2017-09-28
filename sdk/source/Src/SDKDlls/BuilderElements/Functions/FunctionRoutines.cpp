//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: FunctionRoutines.h
//	Description: Declaration of all used transfer functions.  

#include "FunctionRoutines.h"

using namespace NetworkImportingKit;

float nfSingleChange(const TransferFunction* pFunction, float input)
{
	FunctionParameter* pParTValue = pFunction->GetParamByName(String(_T("T")));
	if (pParTValue)
	{
		if (input > pParTValue->value_)
			return 1;
		else
			return -1;		
	} else
	{
		if (input > 0)
			return 1;
		else
			return -1;
	}
}

float nfHysteresis(const TransferFunction* pFunction, float input)
{
	FunctionParameter* pParTValue = pFunction->GetParamByName(String(_T("T")));
	if (pParTValue)
	{
		if (input <= 0)
			return 0;
		else if (input >= pParTValue->value_)
			return 1;
		else
			return 1*input/pParTValue->value_;	
	} else
	{
		if (input >= 0)
			return 1;
		else
			return 0;		
	}
}

float nfHyperbolicTangent(const TransferFunction* /* pFunction */, float input)
{
	float dRet = atan(input);
	if (dRet < -1)
		dRet = -1;
	else if (dRet > 1)
		dRet = 1;
	return dRet;
}

float nfSigmoid(const TransferFunction* /* pFunction */, float input)
{
	// float paramValue = 1.0f;
	return 1/(1 + exp(-input));		
}

float nfSin(const TransferFunction* /* pFunction */, float input)
{
	return sin(input);
}

float nfExponent(const TransferFunction* /* pFunction */, float input)
{
	return exp(input);
}

float nfLinear(const TransferFunction* /* pFunction */, float input)
{
	return input;
}

float nfSingleChangeDerivative(const TransferFunction* /* pFunction */, float /* input */)
{
	return 0;
}

float nfHysteresisDerivative(const TransferFunction* pFunction, float input)
{
	FunctionParameter* pParTValue = pFunction->GetParamByName(String(_T("T")));
	if (pParTValue)
	{
		if (input <= 0)
			return 0;
		else if (input >= pParTValue->value_)
			return 0;
		else
			return 1/pParTValue->value_;	
	} else
	{
		return 0;		
	}
}

float nfHyperbolicTangentDerivative(const TransferFunction* /* pFunction */, float input)
{
	float dRet = tan(input);
	if (dRet < -1)
		dRet = 0;
	else if (dRet > 1)
		dRet = 0;
	return dRet;
}

float nfSigmoidDerivative(const TransferFunction* /* pFunction */, float input)
{
	// float paramValue = 1.0f;
	return input * (1 - input);		
}

float nfSinDerivative(const TransferFunction* /* pFunction */, float input)
{
	return -input;
}

float nfExponentDerivative(const TransferFunction* /* pFunction */, float input)
{
	return exp(input);
}

float nfLinearDerivative(const TransferFunction* /* pFunction */, float /* input */)
{
	return 1;
}
