// DataCreatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "DataCreatorDlg.h"
#include ".\datacreatordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "UIControls/InfoHeader.h"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CInfoHeader mInformationHeader;

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	mInformationHeader.SubclassDlgItem(IDC_INFOHEADERCONTROL, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// CDataCreatorDlg dialog

CDataCreatorDlg::CDataCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataCreatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	pOnTop = NULL;
}

void CDataCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, mMainTab);
}

BEGIN_MESSAGE_MAP(CDataCreatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, OnTcnSelchangeMainTab)
END_MESSAGE_MAP()


// CDataCreatorDlg message handlers

#pragma code_seg(push,  r1, ".secure")
BOOL CDataCreatorDlg::OnInitDialog()
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

	CRect rect(3, 3, 100, 27);
	mTitleBar.SetMediaDirectory(CString("Media\\UI\\Images"));
	mTitleBar.SubclassDlgItem(IDC_PANEL_BAR, this);

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("Data Collections");
	mMainTab.InsertItem(0, &tcItem);

	tcItem.pszText = _T("Data Files");
	mMainTab.InsertItem(1, &tcItem);

	tcItem.pszText = _T("Converting DC to DF");
	mMainTab.InsertItem(2, &tcItem);

	mDataCollectionsDlg.Create(CDataCollectionsDlg::IDD, &mMainTab);
	mDataCollectionsDlg.GetWindowRect(&rect);
	mDataCollectionsDlg.MoveWindow(3, 23, rect.Width(), rect.Height());
	mDataCollectionsDlg.ShowWindow(SW_SHOW);

	mDataFilesDlg.Create(CDataFilesDlg::IDD, &mMainTab);
	mDataFilesDlg.GetWindowRect(&rect);
	mDataFilesDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mConvertingProjectDlg.Create(CConvertingProjectDlg::IDD, &mMainTab);
	mConvertingProjectDlg.GetWindowRect(&rect);
	mConvertingProjectDlg.MoveWindow(3, 23, rect.Width(), rect.Height());


	pOnTop = &mDataCollectionsDlg;
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}
#pragma code_seg(pop)

void CDataCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDataCreatorDlg::OnPaint() 
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
HCURSOR CDataCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDataCreatorDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (pOnTop)
		pOnTop->ShowWindow(SW_HIDE);

	switch(mMainTab.GetCurSel())	
	{
	case 0:
		pOnTop = (CDialog*)&mDataCollectionsDlg;
		break;
	case 1:
		pOnTop = (CDialog*)&mDataFilesDlg;
		break;
	case 2:
		pOnTop = (CDialog*)&mConvertingProjectDlg;
		break;
	default:
		pOnTop = NULL;
	}

	if (pOnTop)
		pOnTop->ShowWindow(SW_SHOW);
}

void CDataCreatorDlg::ShowUserGuide()
{
	CString csUserGuidePath = ((CDataCreatorApp*)AfxGetApp())->GetAppFolder()+CString("\\Documentation\\Data Creator - User Guide.chm");

	ShellExecute(NULL, "open", csUserGuidePath, NULL, "", SW_MAXIMIZE);
}

void CDataCreatorDlg::ShowSDKDocumentation()
{
	CString csSDKDocPath = ((CDataCreatorApp*)AfxGetApp())->GetAppFolder()+CString("\\Documentation\\NISDK 1.0\\Data Processing SDK Documentation.chm");

	ShellExecute(NULL, "open", csSDKDocPath, NULL, "", SW_MAXIMIZE);
}