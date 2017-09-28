#pragma once

#include "CmnElement.h"

class CConnectionsFactory : 
	public IConnectionsFactory,
	public IStorageController
{
public:
	CConnectionsFactory(void);
	~CConnectionsFactory(void);

	CConnection*			FindConnectionByPrevPtr(CConnection* pConnection);

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IConnectionsFactory declarations section
	virtual void			RemoveConnections();
	
	virtual void			AddConnection(CConnection* pConnection);	
	virtual void			RemoveConnection(CConnection* pConnection);

	virtual	bool			MoveConnection(CConnection* pConnection, bool bIsMoveUp = false);

	virtual int				GetConnectionsCount();
	ENUMERATOR(mConnections, CConnection*, CreateEnumerator, GetNextConnection, posConnectionsEnum)	

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CList<CConnection*, CConnection*>	mConnections;
};
