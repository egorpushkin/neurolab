//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IDataFlow.h
//	Description: The IDataFlow declaration.

#ifndef IDATAFLOW_H__NETWORKIMPORTING__INCLUDED_
#define IDATAFLOW_H__NETWORKIMPORTING__INCLUDED_

// IDataFlow declaration
interface IDataFlow : public ICommon
{
	// Activation function manipulation
	virtual const TransferFunction*		GetElementFunction() const = 0;
	virtual void			SetElementFunction(TransferFunction* pFunction) = 0;
	virtual const StringA&	GetFunctionName() const = 0;

	// Data flow operations
	virtual bool			RequireData() const = 0;
	virtual void			SetWaitDataState() = 0;

	// Network processing operations
	virtual bool			IsReadyForProcessing() = 0;
	virtual void			FlowData() = 0;
	virtual void			ProcessElement() = 0;

	// Network training operations
	virtual bool			IsReadyForTraining() = 0;
	virtual void			BackFlow() = 0;
	
	// Element data operations
	virtual void			GetElementData(IDataFactory* piData) const = 0;
	virtual void			SetElementData(const IDataFactory* piData) = 0;
	virtual IDataFactory*	GetDataFactory() const = 0;			

	virtual void			MergeConnectionsData(IDataFactory* piData, uint factoryType) = 0;
};

#endif // !IDATAFLOW_H__NETWORKIMPORTING__INCLUDED_
