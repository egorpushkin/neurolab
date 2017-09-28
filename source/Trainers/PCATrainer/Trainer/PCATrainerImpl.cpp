#include "StdAfx.h"
#include ".\pcatrainerimpl.h"

#include "interface_idds.h"

#include "../UITools/SelectLayerDlg.h"
#include "../UITools/TrainerPropertiesDlg.h"

#include "PCALogic/VerifyerTool.h"

CPCATrainerImpl::CPCATrainerImpl(void)
{
}

CPCATrainerImpl::~CPCATrainerImpl(void)
{
}

// Custom functions
bool CPCATrainerImpl::VerifyWhetherTrainingAvaliable()
{
	bool bRet = true;

	return bRet;
}

// ITrainer implementations section
void CPCATrainerImpl::GetTrainerInfo(TRAINER_INFO* pTrainerInfo)
{
	pTrainerInfo->csTrainerName = _T("PCA Features Generation");
	pTrainerInfo->csTrainerVersion = _T("1.0.0.1");
}

bool CPCATrainerImpl::IsSupportDataType(int DataType)
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

void CPCATrainerImpl::SetDataTypeForTraining(int DataType)
{
	iTrainingDataType = DataType;
}

void CPCATrainerImpl::SetLogProvider(ILogProvider* pLog)
{
	pLogProvider = pLog;
}

void CPCATrainerImpl::SetElementsFactory(IElementsCollection* pCollection)
{
	pElementsCollection = pCollection;
}

void CPCATrainerImpl::SetDataFile(IDataFile* pData)
{
	pDataFile = pData;
}

void CPCATrainerImpl::StartTraining()
{
	if (!CVerifyerTool::VerifyWhetherDataIsCorrect(pDataFile, pLogProvider))
		return;

	ILayerControl* pLayerControl = NULL;

	CSelectLayerDlg mDlg;
	mDlg.pElementsCollection = pElementsCollection;		 
	mDlg.pLogProvider = pLogProvider;
	INT_PTR res = mDlg.DoModal();
	if (res == IDOK)
	{
		pLayerControl = mDlg.pLayerControl;

		if (!CVerifyerTool::VerifySelectedLayer(&mSettings, pLayerControl, pDataFile, pLogProvider))
			return;

		mTrainingTool.ProcessMethod(pDataFile, pLayerControl, pLogProvider, &mSettings);
	}
}

void CPCATrainerImpl::Configure()
{
	CTrainerPropertiesDlg mDlg;
	mDlg.pSettings = &mSettings;
	mDlg.DoModal();
}

int CPCATrainerImpl::GetTotalProcessed()
{
	return mTrainingTool.GetPercentage();
}

void CPCATrainerImpl::PauseTrainng()
{
}

void CPCATrainerImpl::ResumeTrainng()
{
}

void CPCATrainerImpl::StopTrainng()
{
}

// IObject implementations section
CString CPCATrainerImpl::GetClassString()		
{
	return _T("CPCATrainerImpl");
}

void CPCATrainerImpl::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ITrainer:
		*ppvObject = (ITrainer*)this;
		break;
	}
}