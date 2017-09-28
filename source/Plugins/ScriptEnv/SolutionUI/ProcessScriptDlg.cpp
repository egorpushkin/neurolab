// ProcessScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\ScriptEnv.h"
#include "ProcessScriptDlg.h"
#include ".\processscriptdlg.h"

#include "System/Directory.h"
#include "CmnDataFile.h"

#define WM_UPDATE_STATE_TIMER			WM_USER + 1

// Operations
#include "../ScriptOperations/ExecuteScript.h"

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
{
	LV_ITEM item;
    item.iItem = m_List->GetItemCount();
    item.iImage = icon;
	item.lParam = data;
   
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

	va_list params;
	va_start(params, num);
	char * temp = va_arg(params,char *);

	item.iSubItem = 0;
    item.pszText = temp;
    m_List->InsertItem(&item);

	for(int i = 1;i<num;i++)
	{
		temp = va_arg(params,char *);
		item.mask = LVIF_TEXT;
		item.iSubItem = i;
		item.pszText = temp;
		m_List->SetItem(&item);
	}
} 

// CProcessScriptDlg dialog

IMPLEMENT_DYNAMIC(CProcessScriptDlg, CDialog)
CProcessScriptDlg::CProcessScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessScriptDlg::IDD, pParent)
	, pSolutionObj(NULL)
	, mFileName(_T(""))
	, mCurrentPercentage(0)
	, pImportManagerComponent(NULL)
{	
}

CProcessScriptDlg::~CProcessScriptDlg()
{
}

void CProcessScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCRIPT_FILE_NAME, mFileName);
	DDX_Control(pDX, IDC_EVENTS_LOG, mEventsLog);
	DDX_Text(pDX, IDC_CURRENT_PERCENTAGE, mCurrentPercentage);
	DDX_Control(pDX, IDC_EXECUTION_PROGRESS, mExecutionProgress);
	DDX_Control(pDX, IDC_CURRENT_PERCENTAGE, mCtrlCurrentPercentage);
	DDX_Control(pDX, IDC_SCRIPT_PRIORITY, mScriptPriority);
	DDX_Control(pDX, IDC_SAVE_LOG, mLogButton);
}


BEGIN_MESSAGE_MAP(CProcessScriptDlg, CDialog)
	ON_BN_CLICKED(IDC_START_SCRIPT, OnBnClickedStartScript)
	ON_BN_CLICKED(IDC_STOP_SCRIPT, OnBnClickedStopScript)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SAVE_LOG, OnBnClickedSaveLog)
END_MESSAGE_MAP()


// CProcessScriptDlg message handlers

BOOL CProcessScriptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pSolutionObj != NULL);
	ASSERT(pCurrentSolutionItem != NULL);
	ASSERT(pAppController != NULL);
	ASSERT(pImportManagerComponent != NULL);

	CRect rect;
	mEventsLog.GetClientRect(&rect);
	mEventsLog.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mEventsLog.InsertColumn(0, _T("T"), LVCFMT_LEFT,  rect.Width()*1/20); 
	mEventsLog.InsertColumn(1, _T("Time"), LVCFMT_LEFT,  rect.Width()*3/20); 
	mEventsLog.InsertColumn(2, _T("Description"), LVCFMT_LEFT,  rect.Width()*10/20); 
	mEventsLog.InsertColumn(3, _T("Section"), LVCFMT_LEFT,  rect.Width()*5/20); 

	mFileName = pCurrentSolutionItem->GetFileName();
	UpdateData(FALSE);

	mExecutionProgress.SetRange(0, 100);
	mExecutionProgress.SetStep(1);
	mExecutionProgress.SetPos(0);

	// Initializing script priority control
	mScriptPriority.AddString(_T("Real-time"));
	mScriptPriority.AddString(_T("High"));
	mScriptPriority.AddString(_T("Above-normal"));
	mScriptPriority.AddString(_T("Normal"));
	mScriptPriority.AddString(_T("Below-normal"));
	mScriptPriority.AddString(_T("Idle"));

	mScriptPriority.SetItemData(0, THREAD_PRIORITY_TIME_CRITICAL);
	mScriptPriority.SetItemData(1, THREAD_PRIORITY_HIGHEST);
	mScriptPriority.SetItemData(2, THREAD_PRIORITY_ABOVE_NORMAL);
	mScriptPriority.SetItemData(3, THREAD_PRIORITY_NORMAL);
	mScriptPriority.SetItemData(4, THREAD_PRIORITY_BELOW_NORMAL);
	mScriptPriority.SetItemData(5, THREAD_PRIORITY_IDLE);

	mScriptPriority.SetCurSel(3);

	mLogButton.SetIcon(AfxGetApp()->LoadIcon(IDI_LOG));

	EnableControls(TRUE);

	OnBnClickedStartScript();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// Global Environment
DWORD_PTR CProcessScriptDlg::GetSelectedPriorityLevel()
{
	int iPriorityItemIndex = mScriptPriority.GetCurSel();
	DWORD_PTR dwThreadPriority = mScriptPriority.GetItemData(iPriorityItemIndex);

    return dwThreadPriority;
}

// Script Execution
void CProcessScriptDlg::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_START_SCRIPT)->EnableWindow(bEnable);
	GetDlgItem(IDC_STOP_SCRIPT)->EnableWindow(!bEnable);

	mScriptPriority.EnableWindow(bEnable);
}

void CProcessScriptDlg::OnFinishScript()
{
	KillTimer(WM_UPDATE_STATE_TIMER);

	CString tmCurrentPercentage;
	tmCurrentPercentage.Format("%d", 0);
	mCtrlCurrentPercentage.SetWindowText(tmCurrentPercentage);

	mExecutionProgress.SetPos(0);	

	EnableControls(TRUE);
}

bool CProcessScriptDlg::TryCloseEnvironment()
{
	if (!CSolutionOperation_ExecuteScript::hThread)
		return true;

	SuspendThread(CSolutionOperation_ExecuteScript::hThread);

	int res = AfxMessageBox("The script is running.\nAre you sure that you want to terminate it and exit?", MB_YESNO);
	if (res == IDYES)
	{
		OnBnClickedStopScript();
			
		return true;
	}

	ResumeThread(CSolutionOperation_ExecuteScript::hThread);

	return false;
}

void CProcessScriptDlg::OnBnClickedStartScript()
{
	// TODO: Add your control notification handler code here
	bool bRet = CSolutionOperation_ExecuteScript::ExecuteScript(this);
	if (bRet)
	{
		EnableControls(FALSE);
		
		SetTimer(WM_UPDATE_STATE_TIMER, 50, NULL);
	}
}

void CProcessScriptDlg::OnBnClickedStopScript()
{
	// TODO: Add your control notification handler code here
	CSolutionOperation_ExecuteScript::TerminateScript(this);
	OnFinishScript();
}

void CProcessScriptDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == WM_UPDATE_STATE_TIMER)
	{
		UpdateData(TRUE);
		mCurrentPercentage = CLuaStorage_LogProvider::iCurPercentage;
		UpdateData(FALSE);

		mExecutionProgress.SetPos(mCurrentPercentage);	
	}

	__super::OnTimer(nIDEvent);
}

void CProcessScriptDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (TryCloseEnvironment())
		__super::OnCancel();
}

void CProcessScriptDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (TryCloseEnvironment())
		__super::OnOK();
}

// ILogProvider implementations section
void CProcessScriptDlg::ClearLog()
{
	mEventsLog.DeleteAllItems();
}

void CProcessScriptDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
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
void CProcessScriptDlg::OnBnClickedSaveLog()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Text file (log)|*.txt||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		std::ofstream logFile(mFileDlg.GetPathName());
	
		int iItemsCount = mEventsLog.GetItemCount();
		for ( int i = 0 ; i < iItemsCount ; ++i )
		{
			logFile 
				<< mEventsLog.GetItemText(i, 0) << "\t"
				<< mEventsLog.GetItemText(i, 1) << "\t"
				<< mEventsLog.GetItemText(i, 2) << "\t"
				<< mEventsLog.GetItemText(i, 3) << "\t"
				<< std::endl;
		}
	}
}
