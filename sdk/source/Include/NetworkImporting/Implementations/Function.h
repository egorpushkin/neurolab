//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Function.h
//	Description: Activaion function core.

#ifndef FUNCTION_H__NETWORKIMPORTING__INCLUDED_
#define FUNCTION_H__NETWORKIMPORTING__INCLUDED_

struct TransferFunction;
typedef float (*PPROCESS_FUNCTION_ROUTINE)(const TransferFunction* pFunction, float input);

struct	FunctionParameter
{
	String					paramName_;
	float					value_;
};

struct TransferFunction
{
	TransferFunction();
	~TransferFunction();

	StringA					name_;    
	String					title_;    
	String					expression_;    

	PPROCESS_FUNCTION_ROUTINE pProcesTransferFunction_;
	PPROCESS_FUNCTION_ROUTINE pProcessDerivative_;

	vector<FunctionParameter*>		parameters_;

	void					AddParameter(const String& rParamName, float value);
	FunctionParameter*		GetParamByName(const String& rParamName) const;

private:
	void					ReleaseParameters();
};

//
// Declaring aditional user types
//

typedef IEnumerator<TransferFunction*>		IFunctionsEnumerator;

#endif // !FUNCTION_H__NETWORKIMPORTING__INCLUDED_
