// NeuroLab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "MainFrm.h"

#include "NeuroLabDoc.h"
#include "NeuroLabView.h"
#include ".\neurolab.h"
#include "afxwin.h"

#include "interface_idds.h"
#include "CmnApp.h"

#include "LicenseKeeper\ssdhelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNeuroLabApp

BEGIN_MESSAGE_MAP(CNeuroLabApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
END_MESSAGE_MAP()


// CNeuroLabApp construction

CNeuroLabApp::CNeuroLabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);	
}


// The one and only CNeuroLabApp object

CNeuroLabApp theApp;

// CNeuroLabApp initialization

BOOL CNeuroLabApp::InitInstance()
{
	SetCurrentDirectory(csAppFolder);

#ifdef CHECK_LICENSE_INFORMATION_AT_STARTUP
	// Check License Information
	if (!SSDHelper::Initialize(csAppFolder, _T("Neuro Laboratory Environment"), _T("license.key")))
	{
		AfxMessageBox("Package content error.\nNeuro Laboratory Environment was not properly installed.");
		return FALSE;
	}

	SSDHelper::ExportKey("public_user_license.key");
	
	if(!SSDHelper::IsUnlocked())
	{
		AfxMessageBox("Error during verifying user license data.\nYou must register your application!\nSee User Guide documentation for more information.");
		return FALSE;
	}
#endif
    
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();
	
#ifdef SOURCE_NEUROLAB_INTERNAL
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
#endif

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNeuroLabDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CNeuroLabView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->SetWindowText("Neuro Laboratory Environment");
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand

	return TRUE;
}

CString	CNeuroLabApp::GetAppFolder()
{
	return csAppFolder;
}

// CAboutDlg dialog used for App About

#include "UIControls\InfoHeader.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CInfoHeader mInformationHeader;
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

// App command to run the dialog
void CNeuroLabApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CNeuroLabApp message handlers


void CNeuroLabApp::OnFinalRelease()
{
	// TODO: Add your specialized code here and/or call the base class

#ifdef SOURCE_NEUROLAB_INTERNAL
	GdiplusShutdown(gdiplusToken);
#endif

	mAppLoader.UnloadComponents();
	mComponents.ReleaseComponetsTable();

	SSDHelper::Release();

	CWinApp::OnFinalRelease();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	mInformationHeader.SubclassDlgItem(IDC_INFOHEADERCONTROL, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//BOOL CNeuroLabApp::InitApplication()
//{
//	// TODO: Add your specialized code here and/or call the base class
//	AfxMessageBox("123");
//
//	return CWinApp::InitApplication();
//}
