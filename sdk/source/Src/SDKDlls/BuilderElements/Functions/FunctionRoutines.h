//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: FunctionRoutines.h
//	Description: Declaration of all used transfer functions.  

#ifndef FUNCTIONROUTINES_H__BUILDERELEMENTS__INCLUDED_
#define FUNCTIONROUTINES_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

float nfSingleChange(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfHysteresis(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfHyperbolicTangent(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfSigmoid(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfSin(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfExponent(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfLinear(const NetworkImportingKit::TransferFunction* pFunction, float input);

float nfSingleChangeDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfHysteresisDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfHyperbolicTangentDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfSigmoidDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfSinDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfExponentDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);
float nfLinearDerivative(const NetworkImportingKit::TransferFunction* pFunction, float input);

#endif // !FUNCTIONROUTINES_H__BUILDERELEMENTS__INCLUDED_
