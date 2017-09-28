// NetworkExporterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetworkExporter.h"
#include "NetworkExporterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "UIControls\InfoHeader.h"
#include "afxwin.h"
#include ".\networkexporterdlg.h"

#include "ExportDetailsDlg.h"
#include "ProcessExportDlg.h"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	CInfoHeader mInfoHeader;
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CNetworkExporterDlg dialog



CNetworkExporterDlg::CNetworkExporterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkExporterDlg::IDD, pParent)
	, csNeuroLabProjectFile(_T(""))
	, mCustomProjectFileName(_T(""))
	, mDestinationFolder(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkExporterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROJECT_FILE_NAME, mCustomProjectFileName);
	DDX_Text(pDX, IDC_DESTINATION_FOLDER, mDestinationFolder);
}

BEGIN_MESSAGE_MAP(CNetworkExporterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSE_PROJECT_FILE_NAME, OnBnClickedBrowseProjectFileName)
	ON_BN_CLICKED(IDC_BROWSE_DESTINATION_FOLDER, OnBnClickedBrowseDestinationFolder)
	ON_BN_CLICKED(IDC_EXPORT_DETAILS, OnBnClickedExportDetails)
	ON_BN_CLICKED(IDC_PROCESS_EXPORT, OnBnClickedProcessExport)
END_MESSAGE_MAP()


// CNetworkExporterDlg message handlers

#pragma code_seg(push,  r1, ".secure")
BOOL CNetworkExporterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		CString strSDKDocMenu;
		strSDKDocMenu.LoadString(IDS_SDKDOK);
		CString strUserGuideMenu;
		strUserGuideMenu.LoadString(IDS_USERGUIDE);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_USERGUIDE, strUserGuideMenu);
			pSysMenu->AppendMenu(MF_STRING, IDM_SDKDOC, strSDKDocMenu);
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if (!mExportSolution.LoadSolution())
	{
		AfxMessageBox("Error loading exports main table.\nPosibly Network Exporter tool was not corectly installed.");

        EndDialog(IDOK);
		return TRUE;
	}

	if (!mExportSolution.VerifySolution())
	{
		AfxMessageBox("Error verifying export symbols.\nPosibly Network Exporter tool was not corectly installed.");

        EndDialog(IDOK);
		return TRUE;
	}

	int iNumArgs;
	PWSTR* ppArgv = CommandLineToArgvW(GetCommandLineW(), &iNumArgs);

	USES_CONVERSION;

	if (iNumArgs == 2)
		csNeuroLabProjectFile = W2T(ppArgv[1]);

	HeapFree(GetProcessHeap(), 0, ppArgv);

	if (csNeuroLabProjectFile == _T(""))
	{
		GetDlgItem(IDC_PROJECT_TYPE_NEUROLAB)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_PROJECT_TYPE_CUSTOM))->SetCheck(BST_CHECKED);
	} else
		((CButton*)GetDlgItem(IDC_PROJECT_TYPE_NEUROLAB))->SetCheck(BST_CHECKED);	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
#pragma code_seg(pop)

void CNetworkExporterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else 
	if ((nID & 0xFFF0) == IDM_USERGUIDE)
	{
		ShowUserGuide();
	} else
	if ((nID & 0xFFF0) == IDM_SDKDOC)
	{
		ShowSDKDocumentation();
	} else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetworkExporterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetworkExporterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	mInfoHeader.SubclassDlgItem(IDC_INFOHEADERCONTROL, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNetworkExporterDlg::OnBnClickedBrowseProjectFileName()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Project File v1.0|*.nlproj||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);
		mCustomProjectFileName = mFileDlg.GetPathName();
		UpdateData(FALSE);	
	}
}

void CNetworkExporterDlg::OnBnClickedBrowseDestinationFolder()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO              bi;
	LPITEMIDLIST            pidl; 
	LPMALLOC				pMalloc = NULL;
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = NULL; 
	bi.lpszTitle = TEXT("Select Directory To Export Neural Network:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_NEWDIALOGSTYLE;  
	pidl = SHBrowseForFolder(&bi); 
	if  (pidl)
	{
		UpdateData(TRUE);
		SHGetPathFromIDList(pidl, mDestinationFolder.GetBuffer(MAX_PATH));
		mDestinationFolder.ReleaseBuffer(MAX_PATH);
		UpdateData(FALSE);	
	}
}

void CNetworkExporterDlg::OnBnClickedExportDetails()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (((CButton*)GetDlgItem(IDC_PROJECT_TYPE_NEUROLAB))->GetCheck() == BST_CHECKED)
		mExportSolution.SetProjectFileName(csNeuroLabProjectFile);
	else if (((CButton*)GetDlgItem(IDC_PROJECT_TYPE_CUSTOM))->GetCheck() == BST_CHECKED)
		mExportSolution.SetProjectFileName(mCustomProjectFileName);

	CExportDetailsDlg mDlg;
	mDlg.pExportSolution = &mExportSolution;
	mDlg.DoModal();
}

void CNetworkExporterDlg::OnBnClickedProcessExport()
{	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (((CButton*)GetDlgItem(IDC_PROJECT_TYPE_NEUROLAB))->GetCheck() == BST_CHECKED)
		mExportSolution.SetProjectFileName(csNeuroLabProjectFile);
	else if (((CButton*)GetDlgItem(IDC_PROJECT_TYPE_CUSTOM))->GetCheck() == BST_CHECKED)
	{
		if (mCustomProjectFileName != _T(""))
			mExportSolution.SetProjectFileName(mCustomProjectFileName);
		else
		{
			AfxMessageBox("You must select project file.");
			return;
		}
	}

	if (mDestinationFolder == _T(""))
	{
		AfxMessageBox("You must select destination folder.");
		return;
	}

	CProcessExportDlg mDlg;
	mDlg.pExportSolution = &mExportSolution;
    mDlg.csDestinationFolder = mDestinationFolder;
	mDlg.DoModal();
}

void CNetworkExporterDlg::ShowUserGuide()
{
	CString csUserGuidePath = ((CNetworkExporterApp*)AfxGetApp())->GetAppFolder()+CString("\\Documentation\\Network Exporter - User Guide.chm");

	ShellExecute(NULL, "open", csUserGuidePath, NULL, "", SW_MAXIMIZE);
}

void CNetworkExporterDlg::ShowSDKDocumentation()
{
	CString csSDKDocPath = ((CNetworkExporterApp*)AfxGetApp())->GetAppFolder()+CString("\\Documentation\\NISDK 1.0\\Network Importing SDK Documentation.chm");

	ShellExecute(NULL, "open", csSDKDocPath, NULL, "", SW_MAXIMIZE);
}