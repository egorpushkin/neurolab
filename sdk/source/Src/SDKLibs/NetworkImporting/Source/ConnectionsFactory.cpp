//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ConnectionFactory.cpp
//	Description: The ConnectionFactory implementation file.

#include "../Headers/CmnNetworkImportingLib.h"

using namespace NetworkImportingKit;

#define MASK_OPPOSITE_POINTER		0x00000001

CConnectionsFactory::CConnectionsFactory(void)
	: piConnectionsList_(NULL)
	, numRef_(0)
{
	CContainer<CConnection*>* pConnectionsContainer = new CContainer<CConnection*>;

	pConnectionsContainer->QueryInterface(IID_IContainer, (void**)&piConnectionsList_);	
}

CConnectionsFactory::~CConnectionsFactory(void)
{
	ProcessRemoveConnections();

	if (piConnectionsList_)
		piConnectionsList_->Release();
}

//////////////////////////////////////////////////////////////////////////
// Internal destruction tools
//////////////////////////////////////////////////////////////////////////
void CConnectionsFactory::ProcessRemoveConnections()
{
	IConnectionsEnumerator* piEnumerator = piConnectionsList_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		CConnection* pConnection = piEnumerator->GetSelected();
		pConnection->Release();
	}
	piEnumerator->Release();      

	piConnectionsList_->Clear();
}

CConnection* CConnectionsFactory::FindConnectionByPrevPtr(dword_ptr connection)
{
	CConnection* pFoundConnection = NULL;

	IConnectionsEnumerator* piEnumerator = piConnectionsList_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		CConnection* pConnection = piEnumerator->GetSelected();

		if (pConnection->prevPtr_ == connection)
		{
			pFoundConnection = pConnection;
			break;
		}
	}
	piEnumerator->Release();

    return pFoundConnection;
}

//////////////////////////////////////////////////////////////////////////
// IConnectionsFactory implementations section
//////////////////////////////////////////////////////////////////////////
void CConnectionsFactory::AddConnection(CConnection* pConnection, bool addDisconnected)
{
	if (addDisconnected)
	{
		piConnectionsList_->Add(pConnection);
		return;
	}

	if (!pConnection->prevPtr_)	
	{
		piConnectionsList_->Add(pConnection);

		uint factoryType = (uint)pConnection->prevOpositePtr_;		
		int backFactory = DC_INPUTS_FACTORY;
		if (factoryType == DC_INPUTS_FACTORY)
			backFactory = DC_OUTPUTS_FACTORY;		

		IDataConnector* piOppositeDataConnector = QueryTool<IElement, IDataConnector>::
			QueryInterface(pConnection->piElement_, IID_IDataConnector);
 
		IConnectionsFactory* piOppositeConnectionsFactory = piOppositeDataConnector->GetConnectionsFactory(backFactory);

		pConnection->prevPtr_ = MASK_OPPOSITE_POINTER;
		piOppositeConnectionsFactory->AddConnection(pConnection);

		piOppositeConnectionsFactory->Release();

		piOppositeDataConnector->Release();

	} else if (pConnection->prevPtr_ == MASK_OPPOSITE_POINTER)
	{
		CConnection* pOppositeConnection = new CConnection(pConnection->data_.GetDataLength());
		piConnectionsList_->Add(pOppositeConnection);

		pOppositeConnection->piElement_ = (IElement*)pConnection->pOpposite_;

		// Cross connections
		pConnection->pOpposite_ = pOppositeConnection;
		pOppositeConnection->pOpposite_ = pConnection;
	
		pConnection->prevPtr_ = (dword_ptr)NULL;
	}	
}

void CConnectionsFactory::RemoveConnection(CConnection* pConnection)
{
	if (piConnectionsList_->Delete(pConnection) == S_OK)
	{
		if (pConnection->piElement_)
		{
			// Releasing opposite connection
			IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
				QueryInterface(pConnection->piElement_, IID_IDataConnector);

			piDataConnector->RemoveConnection(pConnection->pOpposite_);			

			piDataConnector->Release();
		}

		// Releasing current connection
		pConnection->Release();
	}
}

bool CConnectionsFactory::MoveConnection(const CConnection* /* pConnection */, bool /* bIsMoveUp */)
{
	// This method performs manipulation with connections' order.
	// Warning. NOT IMPLEMENTED.

	return false;
}

void CConnectionsFactory::RemoveConnections()
{
	ProcessRemoveConnections();
}

uint CConnectionsFactory::GetConnectionsCount()
{
	return piConnectionsList_->Size();
}

IConnectionsEnumerator* CConnectionsFactory::GetConnectionsEnumerator()
{
	return piConnectionsList_->Clone();
}

//////////////////////////////////////////////////////////////////////////
// IStorageController implementations section
//////////////////////////////////////////////////////////////////////////
result CConnectionsFactory::Serialize(FILEDev& fileDev, bool loading)
{
	if (loading)
	{
		uint count = 0;
		fileDev.Read(&count, sizeof(uint));

		for(uint i = 0;i < count;i++)
		{
			CConnection* pConnection = new CConnection();

			pConnection->Serialize(fileDev, loading);

			piConnectionsList_->Add(pConnection);
		}
	} else
	{
		uint count = piConnectionsList_->Size();
		fileDev.Write(&count, sizeof(uint));

		IConnectionsEnumerator* piEnumerator = piConnectionsList_->Clone();
		for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
		{
			CConnection* pConnection = piEnumerator->GetSelected();

			pConnection->Serialize(fileDev, loading);
		}
		piEnumerator->Release();
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// ICommon implementations section
//////////////////////////////////////////////////////////////////////////
ulong CConnectionsFactory::AddRef()
{
	return ++numRef_;						
}

ulong CConnectionsFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CConnectionsFactory::GetClassString() const
{
	return _T("CConnectionsFactory");	
}

result CConnectionsFactory::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IConnectionsFactory*)this;
	}
	else if (refIID == IID_IStorageController)
	{
		*ppvObject = (IStorageController*)this;
	}
	else if (refIID == IID_IConnectionsFactory)
	{
		*ppvObject = (IConnectionsFactory*)this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IConnectionsFactory*)this)->AddRef();
	return S_OK;
}

