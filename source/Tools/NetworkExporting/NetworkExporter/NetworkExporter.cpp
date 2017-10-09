// NetworkExporter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NetworkExporter.h"
#include "NetworkExporterDlg.h"

#include "..\..\..\NeuroLab\LicenseKeeper\ssdhelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetworkExporterApp

BEGIN_MESSAGE_MAP(CNetworkExporterApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNetworkExporterApp construction

CNetworkExporterApp::CNetworkExporterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);	
}


// The one and only CNetworkExporterApp object

CNetworkExporterApp theApp;


// CNetworkExporterApp initialization

BOOL CNetworkExporterApp::InitInstance()
{
	SetCurrentDirectory(csAppFolder);

#ifdef CHECK_LICENSE_INFORMATION_AT_STARTUP
	// Check License Information
	if (!SSDHelper::Initialize(csAppFolder, _T("Neuro Laboratory Environment"), _T("license.key")))
	{
		AfxMessageBox("Package content error.\nNetwork Exporter Tool was not properly installed.");
		return FALSE;
	}

	SSDHelper::ExportKey("public_user_license.key");
	
	if(!SSDHelper::IsUnlocked())
	{
		AfxMessageBox("Error during verifying user license data.\nYou must register your application!\nSee Neuro Laboratory - User Guide documentation for more information.");
		return FALSE;
	}
#endif

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InitializeGDIP();

	CNetworkExporterDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	ReleaseGDIP();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
