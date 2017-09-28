#pragma once

#include "CmnLog.h"

#include  <math.h>

#define TOP_ENUM					6
#define TRAINER_THREAD_SLEEP		10

class CBackPropAlg
{
public:
	CBackPropAlg()
	{
	}

	void SetAlgData(ILogProvider*	pProvider, 
		IElementsCollection*		pCollection, 
		IDataFile*					pData,
		sBPSettings*				pSettingsObj)
	{
		pLogProvider = pProvider;
		pElementsCollection = pCollection;
		pDataFile = pData;
		pSettings = pSettingsObj;
	}

// Alghoritm realization
	void ProcessTraining()
	{		
		pLogProvider->AddLogMessage(CString("AM"), CString("Starting processing alghorithm"), 
			CString("Training Alg"));
		pLogProvider->AddLogMessage(CString("AM"), CString("---------------------"),
			CString("Training Alg"));

		mNets.RemoveAll();

		pElementsCollection->CreateElementsEnumerator(TOP_ENUM);
		while(IElement* pElement = pElementsCollection->GetNextElement(TOP_ENUM))
		{
			IDataConnector* pDataConnector = NULL;
			pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
			IConnectionsFactory* pInputFactory = pDataConnector->GetConnectionsFactory(
				DC_INPUTS_FACTORY);
			IConnectionsFactory* pOutputFactory = pDataConnector->GetConnectionsFactory(
				DC_OUTPUTS_FACTORY);

			if ((pElement->GetSysName() == _T("NeuronsLayer") ||
				pElement->GetSysName() == _T("Neuron")) && 
				pInputFactory->GetConnectionsCount() != 0 &&
				pOutputFactory->GetConnectionsCount() != 0)
				mNets.AddTail(pElement);
		}

		if (pSettings->bInitializeWeights)
		{
			pLogProvider->AddLogMessage(CString("AM"), CString("Configuring weights"), 
				CString("Training Alg"));

			srand( (unsigned)time( NULL ) );
			for (POSITION pos = mNets.GetHeadPosition();pos;)
			{
				IElement* pElement = mNets.GetNext(pos);

				ILayerControl* pLayerControl = NULL;
				pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

				float fRandMultiplier = (pSettings->fEndRange - pSettings->fStartRange)/(RAND_MAX * 1.0f);
				float fCenterOffset = pSettings->fStartRange;

				if (pLayerControl)
				{
					for(int i = 0;i < pLayerControl->GetInputsCount();i++)
						for(int j = 0;j < pLayerControl->GetDimension();j++)
							if (pSettings->iWeightsInitializationType == WIT_RANDOM)
								pLayerControl->SetWeight(i, j, (rand()*fRandMultiplier) + fCenterOffset);
							else if (pSettings->iWeightsInitializationType == WIT_CONSTANT)
								pLayerControl->SetWeight(i, j, pSettings->fConstant);
				} else
				{
					IDataConnector* pDataConnector = NULL;
					pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
					IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
						DC_INPUTS_FACTORY);

					pConnectionsFactory->CreateEnumerator(TOP_ENUM);
					while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
						for (int i = 0;i < pConnection->mWeights.GetDataLength();i++)
							if (pSettings->iWeightsInitializationType == WIT_RANDOM)
								pConnection->mWeights.SetItemData(i, (rand()*fRandMultiplier) + fCenterOffset);			
							else if (pSettings->iWeightsInitializationType == WIT_CONSTANT)
								pConnection->mWeights.SetItemData(i, pSettings->fConstant);			
				}
			}
		}

		INetworkProcessor* pNetworkProcessor = NULL;
		pElementsCollection->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

		// Main training loop
		iLoopsCount = 0;

		fOutputTrainSpeed = pSettings->fOutputTrainSpeed;
		fHiddenTrainSpeed = pSettings->fHiddenTrainSpeed;

		pLogProvider->AddLogMessage(CString("AM"), CString("Processing main training loop"), 
			CString("Training Alg"));

		srand( (unsigned)time( NULL ) );

		bool bContinue = true;
		while (bContinue)
		{
			if (iLoopsCount >= pSettings->iMaxLoopsCount)
				break;
			iLoopsCount++;	

			pLogProvider->AddLogMessage(CString("AM"), CString("Enumerating data symbols for training"), 
				CString("Training Alg"));

			for (iCurSymbol = 0;iCurSymbol < pDataFile->GetInputSymbolsCount(); iCurSymbol++)
			{
				/*CString csSymbolInfo;
				csSymbolInfo.Format("Processing symbol %d ...", iCurSymbol);
				pLogProvider->AddLogMessage(CString("AM"), csSymbolInfo, CString("Training Alg"));*/

				int iSymbol = iCurSymbol;
				if (pSettings->bSelectRandomSymbolForTraining)
					iSymbol = (rand()*(pDataFile->GetInputSymbolsCount()-1)*1.0f)/(RAND_MAX*1.0f);

				pNetworkProcessor->SetInputData(pDataFile->GetInputSymbol(iSymbol));
				pNetworkProcessor->ProcessNetwork();

				// Training network weights on currrent symbol
				CList<IElement*, IElement*> mNetsCur;
				mNetsCur.AddTail(&mNets);

				pElementsCollection->CreateElementsEnumerator(TOP_ENUM);
				while(IElement* pElement = pElementsCollection->GetNextElement(TOP_ENUM))
				{
					if (!mNetsCur.Find(pElement))
					{
						IDataFlow* pDataFlow = NULL;
						pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

						pDataFlow->BackFlow();					
					}
				}

				while (mNetsCur.GetCount() > 0)
				{
					for(POSITION pos = mNetsCur.GetHeadPosition();pos;)
					{
						POSITION posPrev = pos;
						IElement* pElement = mNetsCur.GetNext(pos);

						IDataFlow* pDataFlow = NULL;
						pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);	

						if (pDataFlow->IsReadyForTraining())
						{
							// training network weights
							TrainElement(pElement);

							pDataFlow->BackFlow();

							mNetsCur.RemoveAt(posPrev);						
						}					
					}
				}

				Sleep(TRAINER_THREAD_SLEEP);
			}

			pLogProvider->AddLogMessage(CString("AM"), CString("Verifying whether additional training required"), 
				CString("Training Alg"));

			// Verifying whether additional training required
			float fE = 0;
			
			bContinue = false;
			for (iCurSymbol = 0;iCurSymbol < pDataFile->GetInputSymbolsCount(); iCurSymbol++)
			{
				pNetworkProcessor->SetInputData(pDataFile->GetInputSymbol(iCurSymbol));
				pNetworkProcessor->ProcessNetwork();

				CDataFactory tmOutputData;
				pNetworkProcessor->GetOutputData(&tmOutputData);

				for (int i = 0;i < tmOutputData.GetDataLength();i++)
				{
					float fOutput = tmOutputData.GetItemData(i);
					float fTarget = pDataFile->GetOutputSymbol(iCurSymbol)->GetItemData(i);

					float fAbsDiff = fabs(fTarget - fOutput);

					if (fAbsDiff > pSettings->fMaxError)
					{
						bContinue = true;
						//break;
					}

					fE += (fAbsDiff*fAbsDiff);
				}
			}

			fE /= 2;

			CString csCriterion;
			csCriterion.Format("Criterion function value: %f", fE);
			pLogProvider->AddLogMessage(CString("AM"), csCriterion, CString("Training Alg"));

			if (pSettings->iOutputSpeedChange == VCT_INCREMENT)
				fOutputTrainSpeed += pSettings->fOutputChange;
			else if (pSettings->iOutputSpeedChange == VCT_MULTIPLY)
				fOutputTrainSpeed *= pSettings->fOutputChange;

			if (pSettings->iHiddenSpeedChange == VCT_INCREMENT)
				fHiddenTrainSpeed += pSettings->fHiddenChange;
			else if (pSettings->iHiddenSpeedChange == VCT_MULTIPLY)
				fHiddenTrainSpeed *= pSettings->fHiddenChange;

			CString csSpeeds;
			csSpeeds.Format("Hidden speed: %f. Output speed: %f", fHiddenTrainSpeed, fOutputTrainSpeed);
			pLogProvider->AddLogMessage(CString("AM"), csSpeeds, CString("Training Alg"));


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
	}

	void TrainElement(IElement* pElement)
	{
		ILayerControl* pLayerContol = NULL;
		pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerContol);
		
		if (pLayerContol)
			TrainLayer(pElement);
		else
			TrainSingleNeuron(pElement);
	}

	void TrainLayer(IElement* pElement)
	{
		ILayerControl* pLayerControl = NULL;
		pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		for (int i = 0;i < pLayerControl->GetDimension();i++)
		{
			int iConnectionIndex = -1;
			CConnection* pOutputConnection = FindLayerConnection(pElement, 
				DC_OUTPUTS_FACTORY, i, iConnectionIndex);

			float fNeuronOut = pDataFlow->GetDataFactory()->GetItemData(i);

			if (pOutputConnection->pElement->GetElementType() == ET_OUTPUT)
			{
				int iDataIndex = FindConnectionStartDataIndex(pOutputConnection);
				int iOutputIndex = iDataIndex + iConnectionIndex;

				float fDelta = 1;
				sFunction* pFunction = pDataFlow->GetElementFunction();
				if (pFunction)
					fDelta = (*pFunction->pfnProcessDerivative)(pFunction, fNeuronOut);

				float fTargetNeuronOutput = 
					pDataFile->GetOutputSymbol(iCurSymbol)->GetItemData(iOutputIndex);

				fDelta *= (fTargetNeuronOutput - fNeuronOut);
				pLayerControl->SetDelta(i, fDelta);

				CDataFactory tmData;
				pDataFlow->SplitConnectionsData(&tmData, DC_INPUTS_FACTORY);

				for (int j = 0;j < tmData.GetDataLength();j++)
				{
					float fWeightDelta = fDelta;
					
					fWeightDelta *= tmData.GetItemData(j);
					fWeightDelta *= fOutputTrainSpeed;

                    float fCurWeight = pLayerControl->GetWeight(j, i);
					pLayerControl->SetWeight(j, i, fCurWeight + fWeightDelta);
				}

			} else
			{
				float fHiddenError = CalculateLayerHiddenError(pElement, i);

				float fDelta = 1;
				sFunction* pFunction = pDataFlow->GetElementFunction();
				if (pFunction)
					fDelta = (*pFunction->pfnProcessDerivative)(pFunction, fNeuronOut);

				fDelta *= fHiddenError;
				pLayerControl->SetDelta(i, fDelta);

				CDataFactory tmData;
				pDataFlow->SplitConnectionsData(&tmData, DC_INPUTS_FACTORY);

				for (int j = 0;j < tmData.GetDataLength();j++)
				{
					float fWeightDelta = fDelta;
					
					fWeightDelta *= tmData.GetItemData(j);
					fWeightDelta *= fHiddenTrainSpeed;

                    float fCurWeight = pLayerControl->GetWeight(j, i);
					pLayerControl->SetWeight(j, i, fCurWeight + fWeightDelta);
				}
			}		
		}        
	}

	CConnection* FindLayerConnection(IElement* pElement, int FactoryType, int Index, int& ConnectionIndex)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory =
			pDataConnector->GetConnectionsFactory(FactoryType);

		int iCurrentIndex = 0;

		pConnectionsFactory->CreateEnumerator(TOP_ENUM);
		while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
		{
			int iDataLength = tmConnection->mData.GetDataLength();
			if (iCurrentIndex + iDataLength > Index)
			{
				ConnectionIndex	= Index - iCurrentIndex;
				return tmConnection;
			}
			
			iCurrentIndex += iDataLength;
		}
        
		ConnectionIndex = -1;
		return NULL;
	}

	float CalculateLayerHiddenError(IElement* pElement, int Index)
	{
		int iConnectionIndex = -1;
		CConnection* pConnection = FindLayerConnection(pElement, DC_OUTPUTS_FACTORY, Index, iConnectionIndex);

		float fError = 0;

		ILayerControl* pLayerControl = NULL;
		pConnection->pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
		if (pLayerControl)
		{
			int iLayerInputIndex = FindLayerInputIndex(
				pConnection->pElement, pConnection->pOpposite);
		
			for (int j = 0;j < pLayerControl->GetDimension();j++)
				fError += pLayerControl->GetDelta(j) * 
					pLayerControl->GetWeight(iLayerInputIndex + iConnectionIndex, j);	
		} else
		{
			if (pSettings->bSaveNeuronWeights)
				fError += pConnection->pOpposite->mDeltas.GetItemData(iConnectionIndex) * 
					pConnection->pOpposite->mOldWeights.GetItemData(iConnectionIndex);
			else
				fError += pConnection->pOpposite->mDeltas.GetItemData(iConnectionIndex) * 
					pConnection->pOpposite->mWeights.GetItemData(iConnectionIndex);
		}

		return fError;
	}

	void TrainSingleNeuron(IElement* pElement)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory =
			pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		float fElementOut = pDataFlow->GetDataFactory()->GetItemData(0);

		CConnection* pConnection = FindToOutputConnection(pElement);
		if (pConnection)
		{
			int iDataIndex = FindConnectionStartDataIndex(pConnection);
			float fTargetElementOutput = pDataFile->GetOutputSymbol(iCurSymbol)->GetItemData(iDataIndex);

			pConnectionsFactory->CreateEnumerator(TOP_ENUM);
			while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
			{
				tmConnection->mOldWeights.SetData(tmConnection->mWeights.GetData(), 
					tmConnection->mWeights.GetDataLength());

				for (int i = 0;i < tmConnection->mData.GetDataLength();i++)
				{
					float fDelta = 1;
					sFunction* pFunction = pDataFlow->GetElementFunction();
					if (pFunction)
						fDelta = (*pFunction->pfnProcessDerivative)(pFunction, fElementOut);
					
					fDelta *= (fTargetElementOutput - fElementOut);
					tmConnection->mDeltas.SetItemData(i, fDelta);

					fDelta *= tmConnection->mData.GetItemData(i);
					fDelta *= fOutputTrainSpeed;
					tmConnection->mWeights.IncreaseValue(i, fDelta);
				}
			}		
		} else
		{
			float fHiddenError = CalculateHiddenError(pElement);

			pConnectionsFactory->CreateEnumerator(TOP_ENUM);
			while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
			{
				tmConnection->mOldWeights.SetData(tmConnection->mWeights.GetData(), 
					tmConnection->mWeights.GetDataLength());

				for (int i = 0;i < tmConnection->mData.GetDataLength();i++)
				{
					float fDelta = 1;
					sFunction* pFunction = pDataFlow->GetElementFunction();
					if (pFunction)
						fDelta = (*pFunction->pfnProcessDerivative)(pFunction, fElementOut);

					fDelta *= fHiddenError;
					tmConnection->mDeltas.SetItemData(i, fDelta);					

					fDelta *= tmConnection->mData.GetItemData(i);
					fDelta *= fHiddenTrainSpeed;
					tmConnection->mWeights.IncreaseValue(i, fDelta);
				}
			}
		}
	}

	CConnection* FindToOutputConnection(IElement* pElement)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = 
			pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(TOP_ENUM);
		while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
		{
			if (pConnection->pElement->GetElementType() == ET_OUTPUT)
				return pConnection;	
		}

		return NULL;
	}

	int FindConnectionStartDataIndex(CConnection* pConnection)
	{
		int iDataIndex = 0;

		pElementsCollection->CreateElementsEnumerator(TOP_ENUM);
		while (IElement* pElement = pElementsCollection->GetNextElement(TOP_ENUM))
		{
			if (pConnection->pElement == pElement)
				break;
			if (pElement->GetElementType() == ET_OUTPUT)
			{
				IDataFlow* pDataFlow = NULL;
				pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

				iDataIndex += pDataFlow->GetDataFactory()->GetDataLength();
			}		
		}

		IDataConnector* pDataConnector = NULL;
		pConnection->pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = 
			pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

		pConnectionsFactory->CreateEnumerator(TOP_ENUM);
		while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
		{
			if (tmConnection->pOpposite == pConnection)
				break;			
			iDataIndex += tmConnection->mData.GetDataLength();
		}
		
		return iDataIndex;
	}

	float CalculateHiddenError(IElement* pElement)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = 
			pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);

		float fError = 0;
		
		pConnectionsFactory->CreateEnumerator(TOP_ENUM);
		while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
			if (mNets.Find(tmConnection->pElement))
				for (int i = 0;i < tmConnection->pOpposite->mData.GetDataLength();i++)
				{
					ILayerControl* pLayerControl = NULL;
					tmConnection->pElement->QueryInterface(IDD_ILayerControl, 
						(void**)&pLayerControl);
                    
					if (pLayerControl)
					{
						int iLayerInputIndex = FindLayerInputIndex(
							tmConnection->pElement, tmConnection->pOpposite);
					
						for (int j = 0;j < pLayerControl->GetDimension();j++)
							fError += pLayerControl->GetDelta(j) * 
								pLayerControl->GetWeight(iLayerInputIndex + i, j);					
					} else
					{
						if (pSettings->bSaveNeuronWeights)
							fError += tmConnection->pOpposite->mDeltas.GetItemData(i) * 
								tmConnection->pOpposite->mOldWeights.GetItemData(i);
						else
							fError += tmConnection->pOpposite->mDeltas.GetItemData(i) * 
								tmConnection->pOpposite->mWeights.GetItemData(i);
					}
				}
	
		return fError;
	}

	int FindLayerInputIndex(IElement* pElement, CConnection* pConnection)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = 
			pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);		

		int iIndex = 0;
	
		pConnectionsFactory->CreateEnumerator(TOP_ENUM);
		while (CConnection* tmConnection = pConnectionsFactory->GetNextConnection(TOP_ENUM))
		{
			if (tmConnection == pConnection)
                break;		
		
			iIndex += tmConnection->mData.GetDataLength();
		}

		return iIndex;
	}

// Properties functions
	int					GetLoopsProcessed()
	{
		return iLoopsCount;
	}

private:
	ILogProvider*			pLogProvider;
	IElementsCollection*	pElementsCollection; 
	IDataFile*				pDataFile;
	sBPSettings*			pSettings;

	// Training data
	CList<IElement*, IElement*>	mNets;

	// Loops periodic information
	int						iLoopsCount;
	int						iCurSymbol;

	float					fOutputTrainSpeed;
	float					fHiddenTrainSpeed;
};