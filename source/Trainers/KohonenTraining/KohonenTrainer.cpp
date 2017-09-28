#include "StdAfx.h"
#include ".\kohonentrainer.h"

#include "interface_idds.h"

#include "SelectLayerDlg.h"
#include "KohonenVerify.h"
#include "KohonenPropDlg.h"

CKohonenTrainer::CKohonenTrainer(void)
{
}

CKohonenTrainer::~CKohonenTrainer(void)
{
}

// ITrainer implementations section
void CKohonenTrainer::GetTrainerInfo(TRAINER_INFO* pTrainerInfo)
{
	pTrainerInfo->csTrainerName = _T("Kohonen Trainer");
	pTrainerInfo->csTrainerVersion = _T("1.0.0.0b");
}

bool CKohonenTrainer::IsSupportDataType(int DataType)
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

void CKohonenTrainer::SetDataTypeForTraining(int DataType)
{
	iTrainingDataType = DataType;
}

void CKohonenTrainer::SetLogProvider(ILogProvider* pLog)
{
	pLogProvider = pLog;
}

void CKohonenTrainer::SetElementsFactory(IElementsCollection* pCollection)
{
	pElementsCollection = pCollection;
}

void CKohonenTrainer::SetDataFile(IDataFile* pData)
{
	pDataFile = pData;
}

void CKohonenTrainer::StartTraining()
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

		mKohonenTrainingAlg.SetAlgData(pLogProvider, pLayerControl, pDataFile, &mSettings);
		mKohonenTrainingAlg.ProcessTraining();	
	}
}

void CKohonenTrainer::Configure()
{
	CKohonenPropDlg mDlg;
	mDlg.pSettings = &mSettings;
	mDlg.DoModal();
}

int CKohonenTrainer::GetTotalProcessed()
{
	int iProcessed = mKohonenTrainingAlg.GetLoopsCount();
	int iTotalMaxLoops = mSettings.iLoopsCount;
	return iProcessed*100/iTotalMaxLoops;
}

void CKohonenTrainer::PauseTrainng()
{
}

void CKohonenTrainer::ResumeTrainng()
{
}

void CKohonenTrainer::StopTrainng()
{
	mKohonenTrainingAlg.SetLoopsCount(0);
}

// IObject implementations section
CString CKohonenTrainer::GetClassString()		
{
	return _T("CKohonenTrainer");
}

void CKohonenTrainer::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ITrainer:
		*ppvObject = (ITrainer*)this;
		break;
	}
}