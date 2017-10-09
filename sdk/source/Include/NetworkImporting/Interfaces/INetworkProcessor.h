//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: INetworkProcessor.h
//	Description: The INetworkProcessor declaration.

#ifndef INETWORKPROCESSOR_H__NETWORKIMPORTING__INCLUDED_
#define INETWORKPROCESSOR_H__NETWORKIMPORTING__INCLUDED_

// INetworkProcessor declaration
interface INetworkProcessor : public ICommon
{
	virtual result			ProcessNetwork() = 0;

	virtual void			SetInputData(const IDataFactory* piData) = 0;
	virtual void			SetOutputData(const IDataFactory* piData) = 0;

	virtual void			GetInputData(IDataFactory* piData) = 0;
	virtual void			GetOutputData(IDataFactory* piData) = 0;
};

typedef ComPtr<	INetworkProcessor > INetworkProcessorPtr;
typedef const INetworkProcessorPtr& INetworkProcessorRef;

#endif // !INETWORKPROCESSOR_H__NETWORKIMPORTING__INCLUDED_
