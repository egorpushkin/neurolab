#pragma once

class CVerifyerTool
{
public:
	static bool VerifyWhetherDataIsCorrect(
		IDataFile*			pDataFile,
		ILogProvider*		pLogProvider)
	{
		bool bRet = true;

		if (!pDataFile->IsLoaded())
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("Data for training was not loaded."), 
				CString("Verification"));
			bRet = false;
		}

		if (pDataFile->GetInputSymbolsCount() == 0)
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("Loaded data file is empty."), 
				CString("Verification"));
			bRet = false;
		}

		if (pDataFile->GetInputSymbolsCount() < 2)
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("It is not enough input fragments in the input data."), 
				CString("Verification"));
			bRet = false;
		}

		if (pDataFile->GetInputSymbolLength() < 2)
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("It is now enough dimensions in the input data."), 
				CString("Verification"));
			bRet = false;
		}

		return bRet;
	}

	static bool VerifySelectedLayer(
		sPCASettings*		pSettings,
		ILayerControl*		pLayerControl,
		IDataFile*			pDataFile,
		ILogProvider*		pLogProvider)
	{
		bool bRet = true;

		if (pLayerControl->GetInputsCount() != pDataFile->GetInputSymbolLength())
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("Selected layer has wrong inputs count. It must equals with the length of data symbols loaded for training."), 
				CString("Verification"));
			bRet = false;
		}

		if (pLayerControl->GetDimension() != pSettings->iFeaturesCount)
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("Selected layer has wrong dimension. It must equals with specified number of fetures."), 
				CString("Verification"));
			bRet = false;
		}

		return bRet;
	}

};