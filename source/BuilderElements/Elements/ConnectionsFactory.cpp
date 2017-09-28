#include "StdAfx.h"
#include ".\connectionsfactory.h"

#include "interface_idds.h"

#define MASK_OPPOSITE_POINTER		0x00000001

CConnectionsFactory::CConnectionsFactory(void)
{
}

CConnectionsFactory::~CConnectionsFactory(void)
{
}

CConnection* CConnectionsFactory::FindConnectionByPrevPtr(CConnection* pConnection)
{
	for(POSITION pos = mConnections.GetHeadPosition();pos;)
	{
		CConnection* tmConnection = mConnections.GetNext(pos);

		if (tmConnection->pPrevPtr == pConnection)
            return tmConnection;
	}

    return NULL;
}

// IStorageController implementations section
bool CConnectionsFactory::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
	{
		int iCount;
		ar.Read(&iCount, sizeof(int));

		for(int i = 0;i < iCount;i++)
		{
			CConnection* pConnection = new CConnection();

			pConnection->Serialize(ar);

			mConnections.AddTail(pConnection);
		}		
	} else
	{
		int iCount = mConnections.GetCount();
		ar.Write(&iCount, sizeof(int));

		for(POSITION pos = mConnections.GetHeadPosition();pos;)
		{
			CConnection* pConnection = mConnections.GetNext(pos);

			pConnection->Serialize(ar);			
		}	
	}

    return true;
}

// IConnectionsFactory implementations section
void CConnectionsFactory::RemoveConnections()
{
	for (;mConnections.GetCount()>0;)
	{
		CConnection* pConnection = mConnections.GetHead();
		RemoveConnection(pConnection);
	}
}

void CConnectionsFactory::AddConnection(CConnection* pConnection)
{
	if (pConnection->pPrevPtr == NULL)	
	{
		mConnections.AddTail(pConnection);

		int iFactoryType = (int)pConnection->pPrevOpositePtr;		
		int iBackFactory = DC_INPUTS_FACTORY;
		if (iFactoryType == DC_INPUTS_FACTORY)
			iBackFactory = DC_OUTPUTS_FACTORY;		

		IDataConnector* pOppositeDataConnector = NULL;
		pConnection->pElement->QueryInterface(IDD_IDataConnector, (void**)&pOppositeDataConnector);
		IConnectionsFactory* pOppositeConnectionsFactory = pOppositeDataConnector->GetConnectionsFactory(iBackFactory);

		pConnection->pPrevPtr = (CConnection*)MASK_OPPOSITE_POINTER;
		pOppositeConnectionsFactory->AddConnection(pConnection);

	} else if ((int)pConnection->pPrevPtr == MASK_OPPOSITE_POINTER)
	{
		CConnection* pOppositeConnection = new CConnection(pConnection->mWeights.GetDataLength());
		mConnections.AddTail(pOppositeConnection);

		pOppositeConnection->pElement = (IElement*)pConnection->pOpposite;

		// Cross connections
		pConnection->pOpposite = pOppositeConnection;
		pOppositeConnection->pOpposite = pConnection;
	
		pConnection->pPrevPtr = NULL;
	}	
}

void CConnectionsFactory::RemoveConnection(CConnection* pConnection)
{
	POSITION pos = mConnections.Find(pConnection);
	if (pos)
	{		
		mConnections.RemoveAt(pos);

		if (pConnection->pElement && pConnection->pOpposite)
		{
			pConnection->pOpposite->pOpposite = NULL;

			IDataConnector* pDataConnector = NULL;
			pConnection->pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

			pDataConnector->RemoveConnection(pConnection->pOpposite);			
		}		
		
		delete pConnection;
	}
}

bool CConnectionsFactory::MoveConnection(CConnection* pConnection, bool bIsMoveUp)
{
    POSITION posCur = mConnections.Find(pConnection);
	if (!posCur)
		return false;

	POSITION posMoved = posCur;

	if(bIsMoveUp)
		mConnections.GetPrev(posMoved);
	else 
		mConnections.GetNext(posMoved);

	if (posMoved != NULL)
	{
		CConnection* tmPrevConn = mConnections.GetAt(posMoved);
			
		mConnections.SetAt(posCur, tmPrevConn);
		mConnections.SetAt(posMoved, pConnection);		

		return true;
	}	
    return false;
}

int CConnectionsFactory::GetConnectionsCount()
{
	return mConnections.GetCount();
}

// IObject implementations section
CString CConnectionsFactory::GetClassString()
{
	return _T("CConnectionsFactory");
}

void CConnectionsFactory::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IConnectionsFactory:
        *ppvObject = (IConnectionsFactory*)this;
		break;
	case IDD_IStorageController:
        *ppvObject = (IStorageController*)this;
		break;
	}
}