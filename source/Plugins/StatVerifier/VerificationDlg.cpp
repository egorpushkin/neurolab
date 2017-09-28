// VerificationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatVerifier.h"
#include "VerificationDlg.h"
#include ".\verificationdlg.h"

#include "VerificationSettingsDlg.h"

#include "interface_idds.h"

#include "Operation_Verify.h"

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

// CVerificationDlg dialog

IMPLEMENT_DYNAMIC(CVerificationDlg, CDialog)
CVerificationDlg::CVerificationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVerificationDlg::IDD, pParent)
	, mConverterFileName(_T(""))
{
}

CVerificationDlg::~CVerificationDlg()
{
	mDataFile.FreeLoadedData();
}

void CVerificationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONVERTER_FILE_NAME, mConverterFileName);
	DDX_Control(pDX, IDC_RESULTS_LIST, mResultsList);
}


BEGIN_MESSAGE_MAP(CVerificationDlg, CDialog)
	ON_BN_CLICKED(IDC_LOAD_CONVERTER_PROJECT, OnBnClickedLoadConverterProject)
	ON_BN_CLICKED(IDC_VERIFICATION_SETTINGS, OnBnClickedVerificationSettings)
	ON_BN_CLICKED(IDC_TEST_RESULTS, OnBnClickedTestResults)
END_MESSAGE_MAP()


// CVerificationDlg message handlers

void CVerificationDlg::OnBnClickedLoadConverterProject()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		if (mDataFile.LoadFile(mFileDlg.GetPathName()))
		{	
			IElementsCollection* pElementsCollection = NULL;
			pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);
				
			if (pElementsCollection->GetInputsCount() != mDataFile.GetInputSymbolLength() || 
				pElementsCollection->GetOutputsCount() != mDataFile.GetOutputSymbolLength() || 
				mDataFile.GetInputSymbolsCount() != mDataFile.GetOutputSymbolsCount() ||
				mDataFile.GetInputSymbolsCount() == 0)
			{
				mDataFile.FreeLoadedData();

				AfxMessageBox(_T("Attemption to load data file failed.\nWrong data file content."));

				EnableInterface(FALSE);
			}

			csFileName = mFileDlg.GetPathName();

			UpdateConverterInformation();

			EnableInterface(TRUE);
		} else
			EnableInterface(FALSE);
	}
}

void CVerificationDlg::UpdateConverterInformation()
{
	UpdateData(TRUE);
	mConverterFileName = csFileName;
	UpdateData(FALSE);
}

void CVerificationDlg::EnableInterface(BOOL bEnable)
{
	GetDlgItem(IDC_RESULTS_LIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_TEST_RESULTS)->EnableWindow(bEnable);
}

BOOL CVerificationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect	rect;
	mResultsList.GetClientRect(&rect);
	mResultsList.InsertColumn(0, _T("Processed"), LVCFMT_LEFT,  rect.Width()*4.5/10); 
	mResultsList.InsertColumn(2, _T("Succeed"), LVCFMT_LEFT,  rect.Width()*4.5/10); 
	mResultsList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVerificationDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

void CVerificationDlg::OnBnClickedVerificationSettings()
{
	// TODO: Add your control notification handler code here
	CVerificationSettingsDlg mDlg;
	mDlg.pSettings = &mSettings;
	mDlg.DoModal();
}

void CVerificationDlg::OnBnClickedTestResults()
{
	// TODO: Add your control notification handler code here
	ILogProvider* pLog = NULL;
	QueryInterface(IDD_ILogProvider, (void**)&pLog);

	COperation_Verify::Verify(&mDataFile, &mSettings, pAppController, pLog);
}

// ILogProvider implementations section
void CVerificationDlg::ClearLog()
{
	mResultsList.DeleteAllItems();
}

void CVerificationDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
{
	AddListItem(&mResultsList, -1, NULL, 2, MessageType, Message);
}

// IObject implementations section
CString CVerificationDlg::GetClassString()
{
	return _T("CVerificationDlg");
}

void CVerificationDlg::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch (iIDD)
	{
	case IDD_ILogProvider:
		*ppvObject = (ILogProvider*)this;
		break;	
	}
}

