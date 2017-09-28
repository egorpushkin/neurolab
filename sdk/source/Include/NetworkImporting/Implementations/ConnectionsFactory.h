//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ConnectionsFactory.h
//	Description: The CConnectionsFactory declaration file.

#ifndef CONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_
#define CONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_

// CConnectionsFactory declaration
class CConnectionsFactory : 
	public IConnectionsFactory,
	public IStorageController
{
public:
	CConnectionsFactory(void);
	virtual ~CConnectionsFactory(void);

	//////////////////////////////////////////////////////////////////////////
	// Internal destruction tools
	//////////////////////////////////////////////////////////////////////////
	void					ProcessRemoveConnections();

	//////////////////////////////////////////////////////////////////////////
	// IConnectionsFactory declarations section
	//////////////////////////////////////////////////////////////////////////
	CConnection*			FindConnectionByPrevPtr(dword_ptr connection);

	virtual void			AddConnection(CConnection* piConnection, bool addDisconnected = false);
	virtual void			RemoveConnection(CConnection* pConnection);

	virtual	bool			MoveConnection(const CConnection* piConnection, bool moveUp = false);

	virtual void			RemoveConnections();

	virtual uint			GetConnectionsCount();
	virtual IConnectionsEnumerator*		GetConnectionsEnumerator();

	//////////////////////////////////////////////////////////////////////////
	// IStorageController declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	//////////////////////////////////////////////////////////////////////////
	// ICommon declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual	String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	//////////////////////////////////////////////////////////////////////////
	// IConnectionsFactory members
	//////////////////////////////////////////////////////////////////////////
	IContainer<CConnection*>*	piConnectionsList_;

	//////////////////////////////////////////////////////////////////////////
	// ICommon members
	//////////////////////////////////////////////////////////////////////////
	ulong					numRef_;
};

#endif // !CONNECTIONSFACTORY_H__NETWORKIMPORTING__INCLUDED_
