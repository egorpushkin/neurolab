// LicenseMngDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LicenseMng.h"
#include "LicenseMngDlg.h"

#include "AdvOperationsDlg.h"
#include ".\licensemngdlg.h"

#include "..\..\NeuroLab\LicenseKeeper\ssdhelper.h"

#include "UIControls/InfoHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	CInfoHeader mInformationHeader;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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

// CLicenseMngDlg dialog



CLicenseMngDlg::CLicenseMngDlg(CString& AppFolder, CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseMngDlg::IDD, pParent)
	, csAppFolder(AppFolder)
	, mProductsSolution(AppFolder)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLicenseMngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRODUCTS_COMBO, mProductsList);
}

BEGIN_MESSAGE_MAP(CLicenseMngDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADVANCED_OPERATIONS, OnBnClickedAdvancedOperations)
	ON_BN_CLICKED(IDC_EXPORT_PUBLIC_KEY, OnBnClickedExportPublicKey)
END_MESSAGE_MAP()


// CLicenseMngDlg message handlers

BOOL CLicenseMngDlg::OnInitDialog()
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
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if (!mProductsSolution.LoadSolution())
	{
		AfxMessageBox("Package content error.\nLicense Manager was not properly installed.");

		CDialog::OnCancel();
		return FALSE;	
	}

	mProductsSolution.CreateEnumerator();
	while (CProduct* pProduct = mProductsSolution.GetNextProduct())
	{	
		int iIndex = mProductsList.AddString(pProduct->csTitle);
		mProductsList.SetItemData(iIndex, (DWORD_PTR)pProduct);
	}

	mProductsList.SetCurSel(0);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLicenseMngDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLicenseMngDlg::OnPaint() 
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
HCURSOR CLicenseMngDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLicenseMngDlg::OnBnClickedAdvancedOperations()
{
	// TODO: Add your control notification handler code here
	CAdvOperationsDlg mDlg;
	mDlg.DoModal();
}

void CLicenseMngDlg::OnBnClickedExportPublicKey()
{
	// TODO: Add your control notification handler code here
	int iIndex = mProductsList.GetCurSel();
	if (iIndex == -1)
		return;

	CProduct* pProduct = (CProduct*)mProductsList.GetItemData(iIndex);
	if (!pProduct)
		return;

	BROWSEINFO			bi;
	LPITEMIDLIST		pidl; 
	LPMALLOC			pMalloc = NULL;
	ZeroMemory(&bi, sizeof(bi));      
	bi.hwndOwner = NULL; 
	bi.lpszTitle = TEXT("Select Directory To Export Public Key:"); 
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_NEWDIALOGSTYLE;  
	pidl = SHBrowseForFolder(&bi); 
	if  (pidl)
	{
		char pszBuffer[MAX_PATH];
		SHGetPathFromIDList(pidl, pszBuffer);

		CString tmDestinationFolder(pszBuffer);
		
		CString tmResultFile = 
			tmDestinationFolder + 
			CString("\\") + 
			pProduct->csPublicKey;

		if (!SSDHelper::Initialize(
			csAppFolder, 
			pProduct->csName, 
			pProduct->csPrivateKey))
		{
			AfxMessageBox("Package content error.\nLicense Manager was not properly installed.");
			return;
		}

		SSDHelper::ExportKey(tmResultFile);

		CString tmMessage = 
			CString("Key file exporting details:\n") + 
			CString("    File name: ") + 
			pProduct->csPublicKey + 
			CString("\n") + 
			CString("    Product name: ") + 
			pProduct->csTitle + 
			CString("\n") + 
			CString("    Destination: ") +
			tmDestinationFolder + 
			CString("\n") + 
			CString("    Status: Succeded");
		AfxMessageBox(tmMessage, MB_OK | MB_ICONINFORMATION);
	}
}
