//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Function.cpp
//	Description: The TransferFunction implementation file.

#include "../Headers/CmnNetworkImportingLib.h"

using namespace NetworkImportingKit;

TransferFunction::TransferFunction()
{
}

TransferFunction::~TransferFunction()
{
	ReleaseParameters();
}

void TransferFunction::AddParameter(const String& ParamName, float Value)
{
	FunctionParameter* pParam = new FunctionParameter;
	pParam->paramName_ = ParamName;
	pParam->value_ = Value;
	parameters_.push_back(pParam);    
}

FunctionParameter* TransferFunction::GetParamByName(const String& rParamName) const
{
	for (vector<FunctionParameter*>::const_iterator paramIter = parameters_.begin() ; paramIter != parameters_.end() ; paramIter++)
	{
		FunctionParameter* pParam = *paramIter;

		if (pParam->paramName_ == rParamName)
			return pParam;		
	}
	
	return NULL;
}

void TransferFunction::ReleaseParameters()
{
	for (vector<FunctionParameter*>::const_iterator paramIter = parameters_.begin() ; paramIter != parameters_.end() ; paramIter++)
	{
		FunctionParameter* pParam = *paramIter;
		delete pParam;        
	}

	parameters_.clear();
}
