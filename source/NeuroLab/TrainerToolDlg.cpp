// TrainerToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "TrainerToolDlg.h"
#include ".\trainertooldlg.h"

#include "interface_idds.h"
#include "CmnDecl.h"

#include "TrainingPropertiesDlg.h"

#include "StandartControls\EditListCtrl.h"

#define WM_UPDATE_STATE_TIMER			WM_USER + 1

DWORD ProcessTrainingThread(DWORD dwParam)
{
	DWORD dwRet = 0;
	
	CTrainerToolDlg* pToolDlg = (CTrainerToolDlg*)dwParam;

	ITrainer* pTrainer = pToolDlg->GetTrainer();
	pTrainer->StartTraining();

	pToolDlg->OnFinishTraining();

    return dwRet;
}

// CTrainerToolDlg dialog

IMPLEMENT_DYNAMIC(CTrainerToolDlg, CDialog)
CTrainerToolDlg::CTrainerToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainerToolDlg::IDD, pParent)
	, mTrainerName(_T(""))
	, mTrainerVersion(_T(""))
	, mCurrentPercent(0)
{
	pTrainer = NULL;
	bIsPaused = false;

	iTrainerDataType = TDT_LOGIC;

	hProcessingThread = NULL;
}

CTrainerToolDlg::~CTrainerToolDlg()
{
}

void CTrainerToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PAUSE_TRAINING, mPauseTrainingCtrl);
	DDX_Control(pDX, IDC_STOP_TRAINING, mStopTrainingCtrl);
	DDX_Control(pDX, IDC_TRAINING_EVENTS_LOG, mEventsLog);
	DDX_Text(pDX, IDC_TRAINER_NAME, mTrainerName);
	DDX_Text(pDX, IDC_TRAINER_VERSION, mTrainerVersion);
	DDX_Control(pDX, IDC_PROCESS_TRAINING, mProcessTrainingCtrl);
	DDX_Control(pDX, IDC_TRAINING_PROGRESS, mTrainingProgress);
	DDX_Text(pDX, IDC_CURRENT_PERCENT, mCurrentPercent);
	DDX_Control(pDX, IDC_CURRENT_PERCENT, mCurrentPercentCtrl);
	DDX_Control(pDX, IDC_CONFIGURE_TRAINER, mConfigureTrainerCtrl);
}


BEGIN_MESSAGE_MAP(CTrainerToolDlg, CDialog)
	ON_BN_CLICKED(IDC_TRAINING_PROPERTIES, OnBnClickedTrainingProperties)
	ON_BN_CLICKED(IDC_CONFIGURE_TRAINER, OnBnClickedConfigureTrainer)
	ON_BN_CLICKED(IDC_PROCESS_TRAINING, OnBnClickedProcessTraining)
	ON_BN_CLICKED(IDC_PAUSE_TRAINING, OnBnClickedPauseTraining)
	ON_BN_CLICKED(IDC_STOP_TRAINING, OnBnClickedStopTraining)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CTrainerToolDlg::InitializeButtonIcons()
{
}

void CTrainerToolDlg::SetTrainer(ITrainer* pTrainerObj)
{
	pTrainer = pTrainerObj;
}

ITrainer* CTrainerToolDlg::GetTrainer()
{
	return pTrainer;
}

void CTrainerToolDlg::EnableControlButtons(BOOL bEnable)
{
	mTrainingProgress.SetPos(0);
    
	mProcessTrainingCtrl.EnableWindow(!bEnable);
	mPauseTrainingCtrl.EnableWindow(bEnable);
	mStopTrainingCtrl.EnableWindow(bEnable);

	mTrainingProgress.EnableWindow(bEnable);

	mCurrentPercentCtrl.SetWindowText(_T("0"));

	mConfigureTrainerCtrl.EnableWindow(!bEnable);
}

// CTrainerToolDlg message handlers

void CTrainerToolDlg::OnBnClickedTrainingProperties()
{
	// TODO: Add your control notification handler code here
	CTrainingPropertiesDlg mDlg;
	if (iTrainerDataType == TDT_LOGIC)
		mDlg.mUseNetworkMap = FALSE;
	else
		mDlg.mUseNetworkMap = TRUE;

	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		if (!mDlg.mUseNetworkMap)
			iTrainerDataType = TDT_LOGIC;
		else
			iTrainerDataType = TDT_MAPPED;
	}
}

BOOL CTrainerToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitializeButtonIcons();

	CString csWindowText;
	GetWindowText(csWindowText);

	CRect	rect;
	mEventsLog.GetClientRect(&rect);
	mEventsLog.InsertColumn(0, _T("T"), LVCFMT_LEFT,  rect.Width()*1/20); 
	mEventsLog.InsertColumn(1, _T("Time"), LVCFMT_LEFT,  rect.Width()*3/20); 
	mEventsLog.InsertColumn(2, _T("Description"), LVCFMT_LEFT,  rect.Width()*23/40); 
	mEventsLog.InsertColumn(3, _T("Section"), LVCFMT_LEFT,  rect.Width()*7/40); 

	mEventsLog.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (pTrainer)
	{
		ILogProvider* pLog = NULL;
		QueryInterface(IDD_ILogProvider, (void**)&pLog);
		pTrainer->SetLogProvider(pLog);

		TRAINER_INFO tmInfo;
		pTrainer->GetTrainerInfo(&tmInfo);

		mTrainerName = tmInfo.csTrainerName;
		mTrainerVersion = tmInfo.csTrainerVersion;

		CString csWindowText;
		GetWindowText(csWindowText);
		SetWindowText(csWindowText + CString(" : ") + mTrainerName);
	} else
	{
		EndDialog(IDOK);
		AfxMessageBox("Trainer Tool. Wrong initialization.");
	}

	UpdateData(FALSE);

	mTrainingProgress.SetRange(0, 100);
	EnableControlButtons(FALSE);

/*	mConfigureTrainerCtrl.EnableWindow(TRUE);*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// ILogProvider implementations section
void CTrainerToolDlg::ClearLog()
{
	mEventsLog.DeleteAllItems();
}

void CTrainerToolDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
{
	COleDateTime tmTime = COleDateTime::GetCurrentTime();
	
	CString csTime = tmTime.Format("%H:%M:%S");

	AddListItem(&mEventsLog, -1, NULL, 4, MessageType, csTime, Message, MessageSection);

	int iItemsCount = mEventsLog.GetItemCount();
	int iSelectedItem = mEventsLog.GetNextItem(-1, LVNI_SELECTED);
	if (iItemsCount == 1)
		mEventsLog.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	else
		if (iSelectedItem == iItemsCount - 2)
		{
			mEventsLog.Scroll(CSize(0, 50));		
			mEventsLog.SetItemState(iItemsCount - 1, LVIS_SELECTED, LVIS_SELECTED);
		} 
}

// IObject implementations section
CString CTrainerToolDlg::GetClassString()
{
	return _T("CTrainerToolDlg");
}

void CTrainerToolDlg::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ILogProvider:
		*ppvObject = (ILogProvider*)this;
		break;
	}
}
void CTrainerToolDlg::OnBnClickedConfigureTrainer()
{
	// TODO: Add your control notification handler code here
	if (pTrainer)
		pTrainer->Configure();
}

void CTrainerToolDlg::OnBnClickedProcessTraining()
{
	// TODO: Add your control notification handler code here
	EnableControlButtons(TRUE);

	ClearLog();
	AddLogMessage(CString("M"), CString("-- Training started."), CString("Trainer Tool"));

	pTrainer->SetDataTypeForTraining(iTrainerDataType);

	unsigned dwThreadID;
	hProcessingThread = __beginthreadex(NULL, 0, ProcessTrainingThread, this, 0, &dwThreadID);

	SetTimer(WM_UPDATE_STATE_TIMER, 50, NULL);	
}

void CTrainerToolDlg::OnBnClickedPauseTraining()
{
	// TODO: Add your control notification handler code here
	if (bIsPaused)
	{
		AddLogMessage(CString("M"), CString("-- Training resumed."), CString("Trainer Tool"));

		ResumeThread(hProcessingThread);
		pTrainer->ResumeTrainng();

		mPauseTrainingCtrl.SetWindowText(_T("Pause"));

		bIsPaused = false;
	} else
	{
		pTrainer->PauseTrainng();
		SuspendThread(hProcessingThread);		

		AddLogMessage(CString("M"), CString("-- Training paused."), CString("Trainer Tool"));

		mPauseTrainingCtrl.SetWindowText(_T("Resume"));

		bIsPaused = true;
	}
}

void CTrainerToolDlg::OnBnClickedStopTraining()
{
	// TODO: Add your control notification handler code here
	pTrainer->StopTrainng();
	TerminateThread(hProcessingThread, 0);

	AddLogMessage(CString("M"), CString("-- Training stopped."), CString("Trainer Tool"));

	OnFinishTraining();
}

void CTrainerToolDlg::OnFinishTraining()
{
	KillTimer(WM_UPDATE_STATE_TIMER);

	bIsPaused = false;
	mPauseTrainingCtrl.SetWindowText(_T("Pause"));

	EnableControlButtons(FALSE);

	CloseHandle(hProcessingThread);
	hProcessingThread = NULL;

	AddLogMessage(CString("M"), CString("-- Training Finished."), CString("Trainer Tool"));
}

void CTrainerToolDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == WM_UPDATE_STATE_TIMER)
	{
		int iPercentsDone = pTrainer->GetTotalProcessed();
		
		mTrainingProgress.SetPos(iPercentsDone);	

		UpdateData(TRUE);
		mCurrentPercent = iPercentsDone;
		UpdateData(FALSE);
	}

	__super::OnTimer(nIDEvent);
}

bool CTrainerToolDlg::OnTryingToExit()
{
	bool bRet = true;

	if (hProcessingThread)
	{
		SuspendThread(hProcessingThread);

		int iRet = AfxMessageBox("Training is in process. Are you sure that you want to exit?", MB_YESNO);
		if (iRet == IDYES)
		{
			OnBnClickedStopTraining();
		} else
		{
			ResumeThread(hProcessingThread);
			bRet = false;
		}
	}

    return bRet;
}

void CTrainerToolDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (!OnTryingToExit())
		return;

	__super::OnOK();
}

void CTrainerToolDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (!OnTryingToExit())
		return;

	__super::OnCancel();
}
