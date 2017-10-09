#pragma once

#include "CmnElement.h"

#define LC_TOP_ENUM		2

class CCmnLayer : public ILayerControl
{
public:
	CCmnLayer()
		: pLayerWeights(NULL)
		, iLayerDimension(0)
		, iInputsCount(0)
	{
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{	
			ar.Read(&iLayerDimension, sizeof(int));				
			ar.Read(&iInputsCount, sizeof(int));	

			mInputData.Serialize(ar);
			mOutputData.Serialize(ar);

			int iPrevPtr = NULL;
			ar.Read(&iPrevPtr, sizeof(int));
			if (iPrevPtr)
			{
				pLayerWeights = new CDataFactory[iInputsCount];
				for (int i = 0;i < iInputsCount;i++)
					pLayerWeights[i].Serialize(ar);
			}
		} else
		{			
			ar.Write(&iLayerDimension, sizeof(int));
			ar.Write(&iInputsCount, sizeof(int));

			mInputData.Serialize(ar);
			mOutputData.Serialize(ar);

			ar.Write(&pLayerWeights, sizeof(int));
			if (pLayerWeights)
				for (int i = 0;i < iInputsCount;i++)
					pLayerWeights[i].Serialize(ar);
		}

		return true;
	}

	virtual void FlowLayerData()
	{
		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_OUTPUTS_FACTORY);

		IDataFlow* pDataFlow = NULL;
		QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		int iOutputIndex = 0;
		CDataFactory tmData;

		pConnectionsFactory->CreateEnumerator(LC_TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(LC_TOP_ENUM))
		{
			int iDataLength = pConnection->pOpposite->mData.GetDataLength();

			pDataFlow->GetElementData(&tmData);
			
			pConnection->pOpposite->mData.SetData(
				tmData.GetData() + iOutputIndex, iDataLength);

			iOutputIndex += iDataLength;

			pConnection->pOpposite->bHasData = true;
		}
	}

	virtual void ProcessLayer()
	{
		if (mInputData.GetDataLength() != iInputsCount || !pLayerWeights)
			return;

		IDataFlow* pDataFlow = NULL;
		QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		sFunction* pActivateFunction = pDataFlow->GetElementFunction();
		
		mOutputData.CreateFactory(iLayerDimension);

		for (int i = 0;i < iLayerDimension;i++)
		{
			for (int j = 0;j < iInputsCount;j++)
				mOutputData.IncreaseValue(i, 
					pLayerWeights[j].GetItemData(i)*mInputData.GetItemData(j));

			if (pActivateFunction)
				mOutputData.SetItemData(i, (*pActivateFunction->pfnProcessFunction)(
					pActivateFunction, mOutputData.GetItemData(i))); 
		}
	}

// ILayerControl implementations section
	virtual void SetInputData(IDataFactory* pData)
	{
		mInputData.SetData(pData->GetData(), pData->GetDataLength());
	}

	virtual void SetOutputData(IDataFactory* pData)
	{
		mOutputData.SetData(pData->GetData(), pData->GetDataLength());
	}	

	virtual float GetWeight(int i, int j)
	{
		if (i >= iInputsCount || j >= iLayerDimension || !pLayerWeights)
			return 0;
		return pLayerWeights[i].GetItemData(j);
	}

	virtual void SetWeight(int i, int j, float fWeight)
	{
		if (i >= iInputsCount || j >= iLayerDimension || !pLayerWeights)
			return;
		pLayerWeights[i].SetItemData(j, fWeight);
	}

	virtual int GetDimension()
	{
		return iLayerDimension;
	}

	virtual int GetInputsCount()
	{
		return iInputsCount;
	}

	virtual void CreateWeights(int Inputs, int Dimension)
	{
		if (pLayerWeights && iLayerDimension > 0 && iInputsCount > 0)
			RemoveWeights();

		pLayerWeights = new CDataFactory[Inputs];        	
		for (int i = 0;i < Inputs;i++)
			pLayerWeights[i].CreateFactory(Dimension);

		IDataFlow* pDataFlow = NULL;
		QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);
		
		pDataFlow->GetDataFactory()->CreateFactory(Dimension);

		mDeltas.CreateFactory(Dimension);

		iLayerDimension = Dimension;
		iInputsCount = Inputs;
	}

	virtual void RemoveWeights()
	{
        if (pLayerWeights)		
		{
			delete []pLayerWeights;			
			pLayerWeights = NULL;

			mDeltas.ReleaseFactory();
		}
	}

	virtual void ResetWeights(float Value)
	{
		if (!pLayerWeights)
			return;

		for (int i = 0;i < iInputsCount;i++)
			pLayerWeights[i].FillFactory(Value);

		return;
	}

	virtual bool ModifyWeights()
	{
		return false;
	}

	virtual void SetDelta(int i, float Value)
	{
		mDeltas.SetItemData(i, Value);
	}

	virtual float GetDelta(int i)
	{
		return mDeltas.GetItemData(i);	
	}

protected:
	CDataFactory			mInputData;
	CDataFactory			mOutputData;

	int						iLayerDimension;
	int						iInputsCount;

	CDataFactory*			pLayerWeights;
	CDataFactory			mDeltas;
};