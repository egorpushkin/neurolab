#pragma once

class CCovarianceTool
{
public:
	static void CaclulateCovariance(
		IDataFile*		pInputData,
		IDataFile*		pOutputData)
	{
		for (int i = 0;i < pInputData->GetInputSymbolLength();i++)
			for (int j = 0;j < pInputData->GetInputSymbolLength();j++)
			{
				double lfCovarValue = 0.0f;

				for (int k = 0;k < pInputData->GetInputSymbolsCount();k++)
					lfCovarValue += 
						pInputData->GetInputSymbol(k)->GetItemData(i) * 
						pInputData->GetInputSymbol(k)->GetItemData(j);

				lfCovarValue /= (pInputData->GetInputSymbolsCount() - 1);
                
				pOutputData->GetInputSymbol(i)->SetItemData(j, (float)lfCovarValue);
			}
	}
};