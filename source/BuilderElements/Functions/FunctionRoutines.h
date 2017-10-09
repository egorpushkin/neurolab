#pragma once

#include "CmnFunction.h"

float nfSingleChange(sFunction* pFunction, float input);
float nfHysteresis(sFunction* pFunction, float input);
float nfHyperbolicTangent(sFunction* pFunction, float input);
float nfSigmoid(sFunction* pFunction, float input);
float nfSin(sFunction* pFunction, float input);
float nfExponent(sFunction* pFunction, float input);
float nfLinear(sFunction* pFunction, float input);

float nfSingleChangeDerivative(sFunction* pFunction, float input);
float nfHysteresisDerivative(sFunction* pFunction, float input);
float nfHyperbolicTangentDerivative(sFunction* pFunction, float input);
float nfSigmoidDerivative(sFunction* pFunction, float input);
float nfSinDerivative(sFunction* pFunction, float input);
float nfExponentDerivative(sFunction* pFunction, float input);
float nfLinearDerivative(sFunction* pFunction, float input);