// ProcessExportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetworkExporter.h"
#include "ProcessExportDlg.h"
#include ".\processexportdlg.h"

#include "CmnDecl.h"

#include "ExportSolution\ProcessExport.h"

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

DWORD ExportSolutionThread(DWORD dwParam)
{
	DWORD dwRet = 0;

	CProcessExportDlg* pDialog = (CProcessExportDlg*)dwParam;

	ILogProvider* pLogProvider = NULL;
	pDialog->QueryInterface(IDD_ILogProvider, (void**)&pLogProvider);

	CProcessExport::ExportSolution(pDialog->pExportSolution, 
		pDialog->csDestinationFolder, pLogProvider);

	pDialog->OnFinishExporting();

	return dwRet;
}

// CProcessExportDlg dialog

IMPLEMENT_DYNAMIC(CProcessExportDlg, CDialog)
CProcessExportDlg::CProcessExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessExportDlg::IDD, pParent)
	, hThread(NULL)
	, pExportSolution(NULL)
{
}

CProcessExportDlg::~CProcessExportDlg()
{
}

void CProcessExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPERATIONS_LOG_LIST, mOperationsLogList);
}


BEGIN_MESSAGE_MAP(CProcessExportDlg, CDialog)
	ON_BN_CLICKED(ID_PROCESS_EXPORT, OnBnClickedProcessExport)
END_MESSAGE_MAP()


// CProcessExportDlg message handlers

BOOL CProcessExportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pExportSolution != NULL);
	ASSERT(csDestinationFolder != _T(""));

	CRect	rect;
	mOperationsLogList.GetClientRect(&rect);
	mOperationsLogList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mOperationsLogList.InsertColumn(0, _T("Message"), LVCFMT_LEFT,  rect.Width()*19/20); 

	if (CheckDestinationDirectory())
		AddListItem(&mOperationsLogList, -1, NULL, 1, _T("Ready to export solution now."));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CProcessExportDlg::OnBnClickedProcessExport()
{
	// TODO: Add your control notification handler code here
	EnableInterface(FALSE);

	ClearLog();

	unsigned dwThreadID;
	hThread = __beginthreadex(NULL, 0, ExportSolutionThread, this, 
		0, &dwThreadID);
}

void CProcessExportDlg::EnableInterface(BOOL bEnable)
{
	GetDlgItem(IDOK)->EnableWindow(bEnable);
	GetDlgItem(ID_PROCESS_EXPORT)->EnableWindow(bEnable);
}	

void CProcessExportDlg::OnFinishExporting()
{
	EnableInterface(TRUE);
	GetDlgItem(ID_PROCESS_EXPORT)->EnableWindow(FALSE);

	hThread = NULL;
}

// Support services
bool CProcessExportDlg::CheckDestinationDirectory()
{
	WIN32_FIND_DATA fdFileData; 
	HANDLE hSearch; 

	hSearch = FindFirstFile(csDestinationFolder, &fdFileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{
		AddListItem(&mOperationsLogList, -1, NULL, 1, _T("Wrong source directory path specified."));
		GetDlgItem(ID_PROCESS_EXPORT)->EnableWindow(FALSE);

		return false;
	}

	FindClose(hSearch);

	return true;
}

// ILogProvider implementations section
void CProcessExportDlg::ClearLog()
{
	mOperationsLogList.DeleteAllItems();
}

void CProcessExportDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
{
	AddListItem(&mOperationsLogList, -1, NULL, 1, Message);
}

// IObject implementations section
CString CProcessExportDlg::GetClassString()
{
	return _T("CProcessExportDlg");
}

void CProcessExportDlg::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch(iIDD)
	{
	case IDD_ILogProvider:
		*ppvObject = (ILogProvider*)this;
		break;
	}
}

void CProcessExportDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (hThread)
	{
		AfxMessageBox("Solution is exporting now.");
		return;
	}

	__super::OnOK();
}

void CProcessExportDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (hThread)
	{
		AfxMessageBox("Solution is exporting now.");
		return;
	}

	__super::OnCancel();
}
