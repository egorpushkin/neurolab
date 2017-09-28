#include "StdAfx.h"
#include ".\backprop.h"

#include "interface_idds.h"

#include "BPConfigureDlg.h"

CBackProp::CBackProp(void)
{
}

CBackProp::~CBackProp(void)
{
}

// Custom functions
bool CBackProp::VerifyWhetherTrainingAvaliable()
{
	bool bRet = true;

	bool bDataLoaded = pDataFile->IsLoaded();
	if (!bDataLoaded)
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Data for training was not loaded."), 
			CString("Verification"));
		bRet = false;
	}

	if (pDataFile->GetInputSymbolsCount() != pDataFile->GetOutputSymbolsCount())
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Amount of input and output symbols are not equal."), 
			CString("Verification"));
		bRet = false;		
	}

	int iInputsCount = pElementsCollection->GetInputsCount();
	int iOutputsCount = pElementsCollection->GetOutputsCount();

	if (iInputsCount != pDataFile->GetInputSymbolLength())
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Network input length not equals to the length of loaded data."), 
			CString("Verification"));
		bRet = false;	
	}

	if (iOutputsCount != pDataFile->GetOutputSymbolLength())
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Network output length not equals to the length of loaded data."), 
			CString("Verification"));
		bRet = false;	
	}

	if (!IsSupportDataType(iTrainingDataType))
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Trainer does not support data type set for training."), 
			CString("Verification"));
		bRet = false;		
	}


	return bRet;
}

// ITrainer implementations section
void CBackProp::GetTrainerInfo(TRAINER_INFO* pTrainerInfo)
{
	pTrainerInfo->csTrainerName = _T("Back Propagation");
	pTrainerInfo->csTrainerVersion = _T("1.0.0.0b");
}

bool CBackProp::IsSupportDataType(int DataType)
{
	bool bSupport = false;

	switch (DataType)
	{
	case TDT_LOGIC:
		bSupport = true;
		break;
	case TDT_MAPPED:
		bSupport = false;
		break;
	}

	return bSupport;
}

void CBackProp::SetDataTypeForTraining(int DataType)
{
	iTrainingDataType = DataType;
}

void CBackProp::SetLogProvider(ILogProvider* pLog)
{
	pLogProvider = pLog;
}

void CBackProp::SetElementsFactory(IElementsCollection* pCollection)
{
	pElementsCollection = pCollection;
}

void CBackProp::SetDataFile(IDataFile* pData)
{
	pDataFile = pData;
}

void CBackProp::StartTraining()
{
	if (VerifyWhetherTrainingAvaliable())
	{
		mAlgRealization.SetAlgData(pLogProvider, pElementsCollection, pDataFile, &mSettings);
		mAlgRealization.ProcessTraining();	
	}
}

void CBackProp::Configure()
{
	CBPConfigureDlg mDlg;
	mDlg.pSettings = &mSettings;
	mDlg.DoModal();
}

int CBackProp::GetTotalProcessed()
{
	int iLoopsProcessed = mAlgRealization.GetLoopsProcessed();
	int iTotalMaxLoops = mSettings.iMaxLoopsCount;
	if (iTotalMaxLoops == 0)
		return 0;
	return iLoopsProcessed*100/iTotalMaxLoops;
}

void CBackProp::PauseTrainng()
{
}

void CBackProp::ResumeTrainng()
{
}

void CBackProp::StopTrainng()
{
}

// IObject implementations section
CString CBackProp::GetClassString()		
{
	return _T("CBackProp");
}

void CBackProp::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ITrainer:
		*ppvObject = (ITrainer*)this;
		break;
	}
}