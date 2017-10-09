#pragma once

#include "CmnElement.h"

#include "ConnectionsFactory.h"

#define DF_TOP_ENUM		2

class CCmnDataFlow : public IDataFlow
{
public:
	CCmnDataFlow()
	{
		pActivateFunction = NULL;
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			bool bHasFunction;
			ar.Read(&bHasFunction, sizeof(bool));
			if (bHasFunction)
				ar.ReadString(csFunctionName);

			mElementData.Serialize(ar);
		} else
		{			
			bool bHasFunction = true;
			if (pActivateFunction)
			{
				ar.Write(&bHasFunction, sizeof(bool));
				ar.WriteString(pActivateFunction->csName); ar.Write("\n",1);
			} else
			{
				bHasFunction = false;
				ar.Write(&bHasFunction, sizeof(bool));
			}
			
			mElementData.Serialize(ar);
		}

		return true;
	}

	// Custom operations 
	bool GetFactoryReadyState(int iFactoryType)
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			iFactoryType);

		bool bIsReady = true;

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			if (!pConnection->bHasData)
			{
				bIsReady = false;
				break;
			}

        return bIsReady;
	}

	// IDataFlow implementations section
	virtual sFunction* GetElementFunction()
	{
		return pActivateFunction;
	}

	virtual void SetElementFunction(sFunction* pFunction)
	{
		pActivateFunction = pFunction;
	}

	virtual CString GetFunctionName()
	{
		return csFunctionName;
	}

	// Data flow operations
	virtual bool RequireData()
	{
		return true;
	}

	virtual void SetWaitDataState()
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_INPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			pConnection->bHasData = false;

		pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_OUTPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			pConnection->bHasData = false;
	}

	virtual void FlowData()
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_OUTPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			if (pConnection->pOpposite)
			{
				pConnection->pOpposite->bHasData = true;

				for (int i = 0;i < pConnection->pOpposite->mData.GetDataLength();i++)
					pConnection->pOpposite->mData.SetItemData(i, 
						mElementData.GetItemData(0));
			}	
	}

	virtual void BackFlow()
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_INPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			if (pConnection->pOpposite)
				pConnection->pOpposite->bHasData = true;
	}

	virtual bool IsReadyForProcessing()
	{
		return GetFactoryReadyState(DC_INPUTS_FACTORY);
	}

	virtual bool IsReadyForTraining()
	{
		return GetFactoryReadyState(DC_OUTPUTS_FACTORY);
	}

	virtual void ProcessElement()
	{		
	}

	virtual void SplitConnectionsData(IDataFactory* pData, int FactoryType)
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			FactoryType);

		int iDataLength = 0;

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
			iDataLength += pConnection->mData.GetDataLength();

		float* pfData = new float[iDataLength];

		int iDataOffset = 0;

		pConnectionsFactory->CreateEnumerator(DF_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(DF_TOP_ENUM))
		{
			memcpy(pfData + iDataOffset, 
				pConnection->mData.GetData(), 
				pConnection->mData.GetDataLength()*sizeof(float));
		
			iDataOffset += pConnection->mData.GetDataLength();
		}
		
		pData->SetData(pfData, iDataLength);
		
		delete []pfData;	
	}

	// Element data operations
	virtual void GetElementData(IDataFactory* pData)
	{
		pData->SetData(mElementData.GetData(), mElementData.GetDataLength());
	}

	virtual void SetElementData(IDataFactory* pData)
	{
		mElementData.SetData(pData->GetData(), pData->GetDataLength());	
	}

	virtual IDataFactory* GetDataFactory()
	{
		return &mElementData;
	}

protected:
    sFunction*				pActivateFunction;	
	CString					csFunctionName;

	CDataFactory			mElementData;
};