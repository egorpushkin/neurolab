#pragma once

#include "Math.h"

#define TRAINER_THREAD_SLEEP		10

class CKohonenTrainingAlg
{
public:
	CKohonenTrainingAlg()
	{
		iLoopsCount = 0;

		pLogProvider = NULL;
		pLayerControl = NULL;
		pDataFile = NULL;
		pSettings = NULL;
	}

	void SetAlgData(ILogProvider*	pProvider, 
		ILayerControl*				pLayer, 
		IDataFile*					pData,
		sSettings*					pSettingsObj)
	{
		pLogProvider = pProvider;
		pLayerControl = pLayer;
		pDataFile = pData;
		pSettings = pSettingsObj;
	}
	
	void ProcessTraining()
	{
		pLogProvider->AddLogMessage(CString("AM"), CString("Starting processing alghorithm"), 
			CString("Training Alg"));
		pLogProvider->AddLogMessage(CString("AM"), CString("---------------------"),
			CString("Training Alg"));

		iLoopsCount = 0;

		if (pSettings->bInitializeWeights)
		{
			srand( (unsigned)time( NULL ) );

			float fRandMultiplier = (pSettings->fToValue - pSettings->fFromValue)/(RAND_MAX * 1.0f);
			float fCenterOffset = pSettings->fFromValue;

			for(int i = 0;i < pLayerControl->GetInputsCount();i++)
				for(int j = 0;j < pLayerControl->GetDimension();j++)
					pLayerControl->SetWeight(i, j, (rand()*fRandMultiplier) + fCenterOffset);
		}

		if (pSettings->bNormilizeWeights)
		{
			for(int j = 0;j < pLayerControl->GetDimension();j++)
				NormilizeNeuronWeights(j);
		}

		if (pSettings->bNormilizeInputs)
		{
			for (int i = 0;i < pDataFile->GetInputSymbolsCount();i++)
			{
				IDataFactory* pSymbol = pDataFile->GetInputSymbol(i);

				float fSymbolLength = 0.0f;
				for (int j = 0;j < pSymbol->GetDataLength();j++)
					fSymbolLength += (pSymbol->GetItemData(j)*pSymbol->GetItemData(j));

				fSymbolLength = sqrt(fSymbolLength);

				if (fSymbolLength != 0)
					for (int j = 0;j < pSymbol->GetDataLength();j++)
						pSymbol->SetItemData(j, pSymbol->GetItemData(j)/fSymbolLength);
			}		
		}

		fSpeed = pSettings->fStartSpeed;
		mWins.CreateFactory(pLayerControl->GetDimension(), 1.0f);

		bool bContinue = true;
		while (bContinue)
		{
			if (iLoopsCount >= pSettings->iLoopsCount)
				break;
			iLoopsCount++;	

			for (int i = 0;i < pDataFile->GetInputSymbolsCount();i++)
				UpdateWeights(pDataFile->GetInputSymbol(i));

			bContinue = CheckWhetherToContinue();

			fSpeed *= pSettings->fMultiplier;

			Sleep(TRAINER_THREAD_SLEEP);
		}

		pLogProvider->AddLogMessage(CString("AM"), CString("Alghorithm done."), 
			CString("Training Alg"));
		pLogProvider->AddLogMessage(CString("AM"), CString("---------------------"),
			CString("Training Alg"));

		CString tmLoopsString;
		tmLoopsString.Format("%d loop(s) required.", iLoopsCount);
		pLogProvider->AddLogMessage(CString("AM"), tmLoopsString, 
			CString("Training Alg"));

		iLoopsCount = 0;
	}

	void NormilizeNeuronWeights(int iNeuronInd)
	{
		float fLength = 0.0f;
		for(int i = 0;i < pLayerControl->GetInputsCount();i++)
			fLength += (pLayerControl->GetWeight(i, iNeuronInd)*
				pLayerControl->GetWeight(i, iNeuronInd));

		fLength = sqrt(fLength);

		if (fLength != 0)
			for(int i = 0;i < pLayerControl->GetInputsCount();i++)
			{
				float fCurrent = pLayerControl->GetWeight(i, iNeuronInd);
				pLayerControl->SetWeight(i, iNeuronInd, fCurrent/fLength);
			}
	}

	bool CheckWhetherToContinue()
	{
		bool bContinue = false;

		for (int j = 0;j < pDataFile->GetInputSymbolsCount();j++)		
		{
			IDataFactory* pInputSymbol = pDataFile->GetInputSymbol(j);

			int iNeuronInd = -1;
			float fMinimumDistance = 10000.0f;

			for (int i = 0;i < pLayerControl->GetDimension();i++)
			{
				float fDistance = CalculateEuclideanDistance(pInputSymbol, i);

				if (fDistance < fMinimumDistance)
				{
					fMinimumDistance = fDistance;
					iNeuronInd = i;
				}		
			}

			if (fMinimumDistance > pSettings->fMaxDistance)
			{
				bContinue = true;
				break;
			}
		}
	
		return bContinue;
	}

	float CalculateEuclideanDistance(IDataFactory* pFirstFactory, int iNeuronInd)
	{
		float fDistance = 0;

		for (int i = 0;i < pFirstFactory->GetDataLength();i++)
		{
			float fFirst = pFirstFactory->GetItemData(i);
			float fSecond = pLayerControl->GetWeight(i, iNeuronInd);

			fDistance += (fFirst - fSecond)*(fFirst - fSecond);
		}

		fDistance = sqrt(fDistance);

		return fDistance;	
	}

	void UpdateWeights(IDataFactory* pInputSymbol)
	{
		int iNeuronInd = -1;
		float fMinimumDistance = 10000.0f;

		for (int i = 0;i < pLayerControl->GetDimension();i++)
		{
			float fDistance = CalculateEuclideanDistance(pInputSymbol, i);
			fDistance *= mWins.GetItemData(i);

			if (fDistance < fMinimumDistance)
			{
				fMinimumDistance = fDistance;
				iNeuronInd = i;
			}		
		}

		mWins.IncreaseValue(iNeuronInd, 1.0f);

		for (int j = 0;j < pLayerControl->GetInputsCount();j++)
		{
			float fCurrent = pLayerControl->GetWeight(j, iNeuronInd);
			float fDifference = pInputSymbol->GetItemData(j) - fCurrent;

			fDifference *= fSpeed;

			pLayerControl->SetWeight(j, iNeuronInd, fCurrent + fDifference);		
		}

		NormilizeNeuronWeights(iNeuronInd);
	}

	int GetLoopsCount()
	{
		return iLoopsCount;
	}

	void SetLoopsCount(int iCount)
	{
		iLoopsCount = iCount;
	}

private:
	ILogProvider*			pLogProvider;
	ILayerControl*			pLayerControl; 
	IDataFile*				pDataFile;
	sSettings*				pSettings;

	// Loops periodic information
	int						iLoopsCount;
	
	CDataFactory			mWins;
	float					fSpeed;	
};
