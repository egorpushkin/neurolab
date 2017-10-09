#include "stdafx.h"
#include "BackProp.h"

#include "interface_idds.h"

#include "../UI/ParamsDlg.h"

#include "GenericNetwork.h"
#include "ConstructNetwork.h"
#include "Trainer.h"

CBackProp::CBackProp(void)
{
}

CBackProp::~CBackProp(void)
{
}

// Custom functions
bool CBackProp::VerifyDataFile()
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

	return bRet;
}

// ITrainer implementations section
void CBackProp::GetTrainerInfo(TRAINER_INFO* pTrainerInfo)
{
	pTrainerInfo->csTrainerName = _T("Back Propagation FANN");
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

void CBackProp::SetDataTypeForTraining(int /* DataType */)
{
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
	if ( !VerifyDataFile() )
		return;

	network_.SetElementsFactory(pElementsCollection);
	network_.SetDataFile(pDataFile);
	network_.SetLogProvider(pLogProvider);
	
	ConstructNetwork netConstructer(&mSettings, pElementsCollection, pDataFile, pLogProvider, &network_);
	if ( !netConstructer.DoConstructNetwork() )				
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Network has not been constructed."), 
			CString("Constructor"));
		return;
	}

	FannTrainer trainer(&mSettings, pDataFile, pLogProvider, &network_);
	if ( !trainer.DoTrainNetwork() )
	{
		return;
	}

	pLogProvider->AddLogMessage(CString("TE"), 
		CString("Network has been successfully trained."), 
		CString("Constructor"));
	return;
}

void CBackProp::Configure()
{
	CParamsDlg paramsDlg;
	paramsDlg.pSettings_ = &mSettings;
	paramsDlg.DoModal();
}

int CBackProp::GetTotalProcessed()
{
	return 0;
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
