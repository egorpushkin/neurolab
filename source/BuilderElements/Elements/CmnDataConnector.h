#pragma once

#include "interface_idds.h"

#include "CmnElement.h"
#include "ConnectionsFactory.h"

class CCmnDataConnector : public IDataConnector
{
public:
	CCmnDataConnector()
	{
		iAddConnectionState = 0;
		iConnectionsCount = -1;
	}

	virtual bool Serialize(CArchive& ar)
	{
		mInputsFactory.Serialize(ar);
		mOutputsFactory.Serialize(ar);

		return true;
	}

// IDataConnector implementations section
	virtual IConnectionsFactory* GetConnectionsFactory(int FactoryType)
	{
		IConnectionsFactory* pFactory = NULL;
		switch (FactoryType)
		{
		case DC_INPUTS_FACTORY:
			mInputsFactory.QueryInterface(IDD_IConnectionsFactory, (void**)&pFactory);
			break;
		case DC_OUTPUTS_FACTORY:
			mOutputsFactory.QueryInterface(IDD_IConnectionsFactory, (void**)&pFactory);
			break;
		}	
		return pFactory;
	}

	virtual void AddConnectionTo(IElement* pElement, int FactoryType)
	{
		// Adding direct connection
		CConnection* pConnection = new CConnection(iConnectionsCount);
		pConnection->pElement = pElement;

		IElement* pThisElement = NULL;
		QueryInterface(IDD_IElement, (void**)&pThisElement);

		pConnection->pOpposite = (CConnection*)pThisElement;
		pConnection->pPrevPtr = NULL;
		pConnection->pPrevOpositePtr = (CConnection*)FactoryType;

		IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(FactoryType);
		pConnectionsFactory->AddConnection(pConnection);
    }

	virtual void RemoveConnection(CConnection* pConnection)
	{
		IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);
		pConnectionsFactory->RemoveConnection(pConnection);

		pConnectionsFactory = GetConnectionsFactory(DC_OUTPUTS_FACTORY);
		pConnectionsFactory->RemoveConnection(pConnection);
	}

	virtual	void SetAddConnectionState(int iState, int Count)
	{
		iAddConnectionState = iState;
		iConnectionsCount = Count;
	}

	virtual void ProcessAddConnection(IElement* pElement)
	{
		// checking whether connection can be established
		IElement* pFromElement = NULL;
		QueryInterface(IDD_IElement, (void**)&pFromElement);

		IElement* pToElement = pElement;

		if (pFromElement == pToElement)
		{
			AfxMessageBox("Cannot establish connection to itself.");
			return;	
		}

		if (pFromElement->GetElementType() == ET_INPUT &&
			iAddConnectionState == DC_INPUTS_FACTORY)
			{
				AfxMessageBox("Cannot add dendrite for Input element.");
				return;
			}		

		if (pFromElement->GetElementType() == ET_OUTPUT &&
			iAddConnectionState == DC_OUTPUTS_FACTORY)
			{
				AfxMessageBox("Cannot add axon for Output element.");
				return;
			}		

		if (pToElement->GetElementType() == ET_INPUT &&
			iAddConnectionState == DC_OUTPUTS_FACTORY)
			{
				AfxMessageBox("Cannot add axon to Input element.");
				return;
			}		

		if (pToElement->GetElementType() == ET_OUTPUT &&
			iAddConnectionState == DC_INPUTS_FACTORY)
			{
				AfxMessageBox("Cannot add dendrite to Output element.");
				return;
			}		

		AddConnectionTo(pElement, iAddConnectionState);

		iAddConnectionState = 0;
	}

	virtual	bool MoveConnection(CConnection* pConnection, bool bIsMoveUp)
	{		
		IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);
		bool bRet = pConnectionsFactory->MoveConnection(pConnection, bIsMoveUp);

		pConnectionsFactory = GetConnectionsFactory(DC_OUTPUTS_FACTORY);
		bRet |= pConnectionsFactory->MoveConnection(pConnection, bIsMoveUp);

		return bRet;
	}

	virtual	CConnection* FindConnectionByPrevPtr(CConnection* pConnection)
	{
		CConnection* pFoundConnection = mInputsFactory.FindConnectionByPrevPtr(pConnection);
		if (pFoundConnection)
			return pFoundConnection;

		pFoundConnection = mOutputsFactory.FindConnectionByPrevPtr(pConnection);
		if (pFoundConnection)
			return pFoundConnection;

        return NULL;
	}

// Data section
protected:       
	CConnectionsFactory		mInputsFactory;
	CConnectionsFactory		mOutputsFactory;

	int						iAddConnectionState;
	int						iConnectionsCount;
};