#pragma once

class CDataFileDuplicator : public CDataFile
{
public:
	void Duplicate(IDataFile* pInputData)
	{
		CreateNewFile(pInputData->GetInputSymbolLength(), pInputData->GetOutputSymbolLength());

		for (int i = 0;i < pInputData->GetInputSymbolsCount();i++)
			AddInputSymbol(pInputData->GetInputSymbol(i));

		for (int i = 0;i < pInputData->GetOutputSymbolsCount();i++)
			AddOutputSymbol(pInputData->GetOutputSymbol(i));
	}
};

