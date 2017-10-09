#pragma once

class CVerifyData
{
public:
	CVerifyData(IDataFile* pData, ILogProvider* pLog) :
		pDataFile(pData),
		pLogProvider(pLog)
	{	
	}

	bool VerifyWhetherDataIsCorrect()
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
				CString("There is no any input symbols for training network."), 
				CString("Verification"));
			bRet = false;
		}

		return bRet;
	}

private:
	IDataFile*			pDataFile; 
	ILogProvider*		pLogProvider;
};

class CVerifyLayer
{
public:
	CVerifyLayer(ILayerControl* pLayer, IDataFile* pData, ILogProvider* pLog) :
		pLayerControl(pLayer),
		pDataFile(pData),
		pLogProvider(pLog)
	{
	}

	bool VerifyWhetherLayerCorrect()
	{
		bool bRet = true;

        if (pLayerControl->GetDimension() != pDataFile->GetInputSymbolsCount())
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("A number of input symbols not equals to the dimension of selected layer."), 
				CString("Verification"));
			bRet = false;
		}

        if (pLayerControl->GetInputsCount() != pDataFile->GetInputSymbolLength())
		{
			pLogProvider->AddLogMessage(CString("TE"), 
				CString("Input symbol length not equals to a number of layer inputs."), 
				CString("Verification"));
			bRet = false;
		}

        return bRet;	
	}

private:
	ILayerControl*		pLayerControl;
	IDataFile*			pDataFile; 
	ILogProvider*		pLogProvider;
};