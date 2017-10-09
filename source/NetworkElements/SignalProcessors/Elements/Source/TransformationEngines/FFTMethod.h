#pragma once

#include "fft.h"

class CFFTMethod
{
public:
	bool IsReadyForTransform(
		ILayerControl*				pLayerControl,
		IFFTProcessorControl*		pFFTProcessorControl,
		IDataFactory*				pInputData,
		IDataFactory*				pOutputData)
	{
		if (!pLayerControl || 
			!pFFTProcessorControl ||
			!pInputData ||
			!pOutputData)
			return false;

		int iInputDataLength = pInputData->GetDataLength();
		int iOutputDataLength = pOutputData->GetDataLength();

		if (iInputDataLength < 2 ||
			iInputDataLength != pLayerControl->GetInputsCount() ||
			iInputDataLength != pLayerControl->GetDimension())
			return false;

		bool bIsPower2 = true;
		while (iInputDataLength >= 2)
		{
			int iRemainder = iInputDataLength % 2;
			if (iRemainder != 0)
			{
				bIsPower2 = false;
				break;			
			}
			iInputDataLength /= 2;
		}
		if (!bIsPower2)
			return false;
	
		return true;
	}

	void ProcessTransform(
		ILayerControl*				pLayerControl,
		IFFTProcessorControl*		pFFTProcessorControl,
		IDataFactory*				pInputData,
		IDataFactory*				pOutputData)
	{
		if (!IsReadyForTransform(
			pLayerControl, 
			pFFTProcessorControl,
			pInputData, 
			pOutputData))
			return;

		// Preparing data
		pOutputData->SetData(pInputData->GetData(), pInputData->GetDataLength());

		if (pFFTProcessorControl->GetFFTDataModel() == FFTPC_COMPLEX_DATA)
		{
			// Complex transform
			Complex* pComplexData = (Complex*)pOutputData->GetData();

			// Preparing input data for corrcet algorithm input data format
			FFTReOrder(pComplexData, pOutputData->GetDataLength() / 2);

			// Processing transform
			FFT_T(
				pComplexData, 
				pOutputData->GetDataLength() / 2, 
				pFFTProcessorControl->GetTransformDirection());		
		}
		else
		{
			// Real transform
			// Processing transform
			RealFFT(
				pOutputData->GetData(),
				pOutputData->GetDataLength(),
				pFFTProcessorControl->GetTransformDirection());
		}

		// Normalizing result
		if (pFFTProcessorControl->GetNormalizationMethod())
		{
			for (int i = 0;i < pOutputData->GetDataLength();i++)
			{
				float fValue = pOutputData->GetItemData(i);

				fValue /= (pOutputData->GetDataLength() / 2);

				pOutputData->SetItemData(i, fValue);
			}
		}
	}
};
