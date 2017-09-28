#pragma once

#include "Math.h"

class CRBFTrainingAlg
{
public:
	CRBFTrainingAlg()
	{
		iLoopsCount = 0;

		pLogProvider = NULL;
		pLayerControl = NULL;
		pDataFile = NULL;
	}

	void SetAlgData(ILogProvider*	pProvider, 
		ILayerControl*				pLayer, 
		IDataFile*					pData)
	{
		pLogProvider = pProvider;
		pLayerControl = pLayer;
		pDataFile = pData;
	}

	void ProcessTraining()
	{
		iLoopsCount = 0;

		for (int i = 0;i < pDataFile->GetInputSymbolsCount();i++)
		{
			IDataFactory* pCurImage = pDataFile->GetInputSymbol(i);
			for (int j = 0;j < pDataFile->GetInputSymbolLength();j++)
				pLayerControl->SetWeight(j, i, pCurImage->GetItemData(j));

			float fHalfDistance = FindNearestClassCenterDistance(i) / 2.0f;
			pLayerControl->SetDelta(i, fHalfDistance);
		
			iLoopsCount++;
		}
	}

	float FindNearestClassCenterDistance(int Index)
	{
		float fDistance = 10000.0f;
		IDataFactory* pImage = pDataFile->GetInputSymbol(Index);

		for (int i = 0;i < pDataFile->GetInputSymbolsCount();i++)
		{
			if (i == Index)
				continue;

			IDataFactory* pCurImage = pDataFile->GetInputSymbol(i);

			float fCurDistance = 0;

			for (int j = 0;j < pCurImage->GetDataLength();j++)
				fCurDistance += ((pImage->GetItemData(j) - pCurImage->GetItemData(j))*
					(pImage->GetItemData(j) - pCurImage->GetItemData(j)));

			fCurDistance = sqrt(fCurDistance)/2;
			
			if (fCurDistance < fDistance)
				fDistance = fCurDistance;		
		}
	
		return fDistance;
	}

	int GetLoopsCount()
	{
		if (pDataFile)
			return iLoopsCount*100/pDataFile->GetInputSymbolsCount();
		
		return 0;
	}

private:
	ILogProvider*			pLogProvider;
	ILayerControl*			pLayerControl; 
	IDataFile*				pDataFile;

	// Loops periodic information
	int						iLoopsCount;
};