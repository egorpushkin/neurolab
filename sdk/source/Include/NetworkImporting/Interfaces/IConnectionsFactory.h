//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IConnectionsFactory.h
//	Description: The IConnectionsFactory declaration.

#ifndef ICONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_
#define ICONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_

// IConnectionsFactory declaration
interface IConnectionsFactory : public ICommon
{
	virtual CConnection*	FindConnectionByPrevPtr(dword_ptr pConnectionOldPtr) = 0;

	virtual void			AddConnection(CConnection* piConnection, bool addDisconnected = false) = 0;
	virtual void			RemoveConnection(CConnection* pConnection) = 0;

	virtual	bool			MoveConnection(const CConnection* piConnection, bool moveUp = false) = 0;

	virtual void			RemoveConnections() = 0;

	virtual uint			GetConnectionsCount() = 0;
	virtual IConnectionsEnumerator*		GetConnectionsEnumerator() = 0;
};

typedef ComPtr<	IConnectionsFactory > IConnectionsFactoryPtr;
typedef const IConnectionsFactoryPtr& IConnectionsFactoryRef;

#endif // !ICONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_
