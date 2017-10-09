#include "StdAfx.h"
#include ".\rbftrainer.h"

#include "interface_idds.h"

#include "SelectLayerDlg.h"

#include "RBFVerify.h"

CRBFTrainer::CRBFTrainer(void)
{
}

CRBFTrainer::~CRBFTrainer(void)
{
}

// ITrainer implementations section
void CRBFTrainer::GetTrainerInfo(TRAINER_INFO* pTrainerInfo)
{
	pTrainerInfo->csTrainerName = _T("RBF Trainer");
	pTrainerInfo->csTrainerVersion = _T("1.0.0.0b");
}

bool CRBFTrainer::IsSupportDataType(int DataType)
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

void CRBFTrainer::SetDataTypeForTraining(int DataType)
{
	iTrainingDataType = DataType;
}

void CRBFTrainer::SetLogProvider(ILogProvider* pLog)
{
	pLogProvider = pLog;
}

void CRBFTrainer::SetElementsFactory(IElementsCollection* pCollection)
{
	pElementsCollection = pCollection;
}

void CRBFTrainer::SetDataFile(IDataFile* pData)
{
	pDataFile = pData;
}

void CRBFTrainer::StartTraining()
{
	CVerifyData mDataVerifier(pDataFile, pLogProvider);
	if (!mDataVerifier.VerifyWhetherDataIsCorrect())
		return;

	ILayerControl* pLayerControl = NULL;

	CSelectLayerDlg mDlg;
	mDlg.pElementsCollection = pElementsCollection;		 
	mDlg.pLogProvider = pLogProvider;
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		pLayerControl = mDlg.pLayerControl;

		CVerifyLayer mLayerVerifier(pLayerControl, pDataFile, pLogProvider);
		if (!mLayerVerifier.VerifyWhetherLayerCorrect())
			return;

		mRBFTrainingAlg.SetAlgData(pLogProvider, pLayerControl, pDataFile);
		mRBFTrainingAlg.ProcessTraining();	
	}
}

void CRBFTrainer::Configure()
{
	/*CBPConfigureDlg mDlg;
	mDlg.pSettings = &mSettings;
	mDlg.DoModal();*/
}

int CRBFTrainer::GetTotalProcessed()
{
	return mRBFTrainingAlg.GetLoopsCount();
}

void CRBFTrainer::PauseTrainng()
{
}

void CRBFTrainer::ResumeTrainng()
{
}

void CRBFTrainer::StopTrainng()
{
}

// IObject implementations section
CString CRBFTrainer::GetClassString()		
{
	return _T("CRBFTrainer");
}

void CRBFTrainer::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ITrainer:
		*ppvObject = (ITrainer*)this;
		break;
	}
}