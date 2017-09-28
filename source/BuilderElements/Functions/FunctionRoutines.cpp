#include "StdAfx.h"
#include "FunctionRoutines.h"

#include "Math.h"

float nfSingleChange(sFunction* pFunction, float input)
{
	sParameter* pParTValue = pFunction->GetParamByName(CString("T"));
	if (pParTValue)
	{
		if (input > pParTValue->fValue)
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

float nfHysteresis(sFunction* pFunction, float input)
{
	sParameter* pParTValue = pFunction->GetParamByName(CString("T"));
	if (pParTValue)
	{
		if (input <= 0)
			return 0;
		else if (input >= pParTValue->fValue)
			return 1;
		else
			return 1*input/pParTValue->fValue;	
	} else
	{
		if (input >= 0)
			return 1;
		else
			return 0;		
	}
}

float nfHyperbolicTangent(sFunction* pFunction, float input)
{
	double dRet = atan(input);
	if (dRet < -1)
		dRet = -1;
	else if (dRet > 1)
		dRet = 1;
	return dRet;
}

float nfSigmoid(sFunction* pFunction, float input)
{
	sParameter* pParTValue = pFunction->GetParamByName(CString("alpha"));
	if (pParTValue)
	{
		return 1/(1 + exp(-pParTValue->fValue*input));		
	} else
	{
		return 1/(1 + exp(-1*input));
	}	
}

float nfSin(sFunction* pFunction, float input)
{
	return sin(input);
}

float nfExponent(sFunction* pFunction, float input)
{
	return exp(input);
}

float nfLinear(sFunction* pFunction, float input)
{
	return input;
}

float nfSingleChangeDerivative(sFunction* pFunction, float input)
{
	return 0;
}

float nfHysteresisDerivative(sFunction* pFunction, float input)
{
	sParameter* pParTValue = pFunction->GetParamByName(CString("T"));
	if (pParTValue)
	{
		if (input <= 0)
			return 0;
		else if (input >= pParTValue->fValue)
			return 0;
		else
			return 1/pParTValue->fValue;	
	} else
	{
		return 0;		
	}
}

float nfHyperbolicTangentDerivative(sFunction* pFunction, float input)
{
	double dRet = tan(input);
	if (dRet < -1)
		dRet = 0;
	else if (dRet > 1)
		dRet = 0;
	return dRet;
}

float nfSigmoidDerivative(sFunction* pFunction, float input)
{
	sParameter* pParTValue = pFunction->GetParamByName(CString("alpha"));
	if (pParTValue)
	{
		return pParTValue->fValue*input*(1 - input);		
	} else
	{
		return input*(1 - input);
	}	
}

float nfSinDerivative(sFunction* pFunction, float input)
{
	return -input;
}

float nfExponentDerivative(sFunction* pFunction, float input)
{
	return exp(input);
}

float nfLinearDerivative(sFunction* pFunction, float input)
{
	return 1;
}