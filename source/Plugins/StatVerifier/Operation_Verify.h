#pragma once

#include "CmnFactory.h"
#include "CollectionConverter/Operation_LoadImage.h"

#include "VerificationDlg.h"

#include <Math.h>

class COperation_Verify
{
public:
	static bool Verify(
		CDataFile*					mDataFile,
		sVerificationSettings*		pSettings, 
		IAppController*				pAppController,
		ILogProvider*				pLog)
	{
		pLog->ClearLog();

		INetworkProcessor* pNetworkProcessor = NULL;
		pAppController->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);		

		IElementsCollection* pElementsCollection = NULL;
		pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

		int count = mDataFile->GetInputSymbolsCount();

		int iTotalSymbols = count;
		int iTotalSucceed = 0;

		CDataFactory dataFactory(pElementsCollection->GetOutputsCount());

		for (int i = 0;i < count;i++)
		{
			IDataFactory* pInputDataFactory = mDataFile->GetInputSymbol(i);
			IDataFactory* pOutputDataFactory = mDataFile->GetOutputSymbol(i);

			pNetworkProcessor->SetInputData(pInputDataFactory);
			pNetworkProcessor->ProcessNetwork();
			pNetworkProcessor->GetOutputData(&dataFactory);

			if (CompareFactories(pOutputDataFactory, &dataFactory, pSettings))
				iTotalSucceed++;

			if (i != 0 && i % 100 == 0)
			{
				Report(pLog, i + 1, iTotalSucceed, iTotalSymbols);
			}
		}

		Report(pLog, iTotalSymbols, iTotalSucceed, iTotalSymbols);

		return true;   
	}

	static void Report(ILogProvider* pLog, int iProcessed, int iTotalSucceed, int iTotalSymbols)
	{
		CString tmProcessed;
		tmProcessed.Format("%d of %d", iProcessed, iTotalSymbols);
		CString tmSucceed;
		tmSucceed.Format("%d%%", (iTotalSucceed*100)/(iProcessed));

		pLog->AddLogMessage(tmProcessed, tmSucceed, CString(_T("")));
	}

	static bool CompareFactories(
		IDataFactory*				pOutput,
		IDataFactory*				pCorrectResult,
		sVerificationSettings*		pSettings) 
	{
		if (pSettings->iCondition == VS_CONDITION_EQUAL)
		{			
			for (int i = 0;i < pOutput->GetDataLength();i++)
				if (pOutput->GetItemData(i) != pCorrectResult->GetItemData(i))
					return false;
			return true;

		} else if (pSettings->iCondition == VS_CONDITION_COINSIDE)
		{
			int iOutputWinner = 0;
			float fOWValue = pOutput->GetItemData(0);

			int iCorrectWinner = 0;
			float fCWValue = pCorrectResult->GetItemData(0);

			for (int i = 1;i < pOutput->GetDataLength();i++)
			{
				if (pOutput->GetItemData(i) > fOWValue)
				{
					iOutputWinner = i;
					fOWValue = pOutput->GetItemData(i);
				}

				if (pCorrectResult->GetItemData(i) > fCWValue)
				{
					iCorrectWinner = i;
					fCWValue = pCorrectResult->GetItemData(i);
				}
			}

			if (iOutputWinner == iCorrectWinner)
				return true;

			return false;

		} else if (pSettings->iCondition == VS_CONDITION_ERROR)
		{
			for (int i = 0;i < pOutput->GetDataLength();i++)
				if (fabs(pOutput->GetItemData(i) - pCorrectResult->GetItemData(i)) > pSettings->fMaxError)
					return false;
			return true;
		}			

		return false;
	}

};