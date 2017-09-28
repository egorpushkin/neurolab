#pragma once

class CNormalizeData
{
public:
	static void NormalizeData(
		IDataFile*		pInputData,
		IDataFile*		pOutputData)
	{
		for (int i = 0;i < pInputData->GetInputSymbolLength();i++)
		{
			// Calculating average value for every  dimension
			double lfAverage = 0.0f;

			for (int j = 0;j < pInputData->GetInputSymbolsCount();j++)
				lfAverage += pInputData->GetInputSymbol(j)->GetItemData(i);

			lfAverage /= (pInputData->GetInputSymbolsCount() * 1.0f);

			float fAverage = (float)lfAverage; 

			// Fill output object with updated m\nomilized data 
			for (int j = 0;j < pInputData->GetInputSymbolsCount();j++)
			{
				float fData = pInputData->GetInputSymbol(j)->GetItemData(i);

				pOutputData->GetInputSymbol(j)->SetItemData(i, fData - fAverage);
			}
		}
	}
};
