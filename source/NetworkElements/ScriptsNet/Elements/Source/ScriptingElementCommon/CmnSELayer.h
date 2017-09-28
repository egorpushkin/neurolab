#pragma once

#include "CmnScriptingElement.h"

#include "..\..\ElementsCommon.h"

class CCmnSELayer : public CCmnLayer
{
public:
	CCmnSELayer()
	{
	}

	virtual bool Serialize(CArchive& ar)
	{
		IScriptingElementControl* pScriptingElementControl = NULL;
		QueryInterface(
			IDD_IScriptingElementControl, 
			(void**)&pScriptingElementControl);

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
				pLayerWeights = new CDataFactory[pScriptingElementControl->GetInputsCountSE()];
				for (int i = 0;i < pScriptingElementControl->GetInputsCountSE();i++)
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
				for (int i = 0;i < pScriptingElementControl->GetInputsCountSE();i++)
					pLayerWeights[i].Serialize(ar);
		}

		return true;
	}

// ILayerControl implementations section
	virtual float GetWeight(int i, int j)
	{
		IScriptingElementControl* pScriptingElementControl = NULL;
		QueryInterface(
			IDD_IScriptingElementControl, 
			(void**)&pScriptingElementControl);

		if (!pLayerWeights || 
			i >= pScriptingElementControl->GetInputsCountSE() || 
			j >= pScriptingElementControl->GetDimensionSE())
			return 0;

		return pLayerWeights[i].GetItemData(j);
	}

	virtual void SetWeight(int i, int j, float fWeight)
	{
		IScriptingElementControl* pScriptingElementControl = NULL;
		QueryInterface(
			IDD_IScriptingElementControl, 
			(void**)&pScriptingElementControl);
		
		if (!pLayerWeights || 
			i >= pScriptingElementControl->GetInputsCountSE() || 
			j >= pScriptingElementControl->GetDimensionSE())
			return;

		pLayerWeights[i].SetItemData(j, fWeight);
	}

	virtual void CreateWeights(int Inputs, int Dimension)
	{
		iLayerDimension = Dimension;
		iInputsCount = Inputs;
	}

	virtual void RemoveWeights()
	{
		iLayerDimension = 0;
		iInputsCount = 0;
	}
};