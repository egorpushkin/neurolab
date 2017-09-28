//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IDataConnector.h
//	Description: Then IDataConnector declaration.

#ifndef IDATACONNECTOR_H__NETWORKIMPORTING__INCLUDED_
#define IDATACONNECTOR_H__NETWORKIMPORTING__INCLUDED_

// IDataConnector declaration
interface IDataConnector : public ICommon
{
	virtual result			AddConnectionTo(IElement* piElement, uint factoryType) = 0;
	virtual void			RemoveConnection(CConnection* pConnection) = 0;

	virtual	void			SetAddConnectionState(uint state, uint count) = 0;
	virtual result			ProcessAddConnection(IElement* piElement) = 0;

	virtual	bool			MoveConnection(const CConnection* pConnection, bool moveUp = false) = 0;

	virtual IConnectionsFactory* GetConnectionsFactory(uint factoryType) const = 0;

	virtual	CConnection*	FindConnectionByPrevPtr(dword_ptr connection) = 0;
};

typedef ComPtr<	IDataConnector > IDataConnectorPtr;
typedef const IDataConnectorPtr& IDataConnectorRef;

#endif // !IDATACONNECTOR_H__NETWORKIMPORTING__INCLUDED_
