// DataCreator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DataCreator.h"
#include "DataCreatorDlg.h"

#include "..\..\NeuroLab\LicenseKeeper\ssdhelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataCreatorApp

BEGIN_MESSAGE_MAP(CDataCreatorApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDataCreatorApp construction

CDataCreatorApp::CDataCreatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);	
}


// The one and only CDataCreatorApp object

CDataCreatorApp theApp;

/*const GUID CDECL BASED_CODE _tlid =
		{ 0x626DFA4E, 0xE5B7, 0x4C9B, { 0xBA, 0xAE, 0x7F, 0xCC, 0x36, 0x6C, 0x64, 0x32 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;*/

// CDataCreatorApp initialization

BOOL CDataCreatorApp::InitInstance()
{
	SetCurrentDirectory(csAppFolder);

#ifdef CHECK_LICENSE_INFORMATION_AT_STARTUP
	// Check License Information
	if (!SSDHelper::Initialize(csAppFolder, _T("Neuro Laboratory Environment"), _T("license.key")))
	{
		AfxMessageBox("Package content error.\nData Creator Tool was not properly installed.");
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

	if (!AfxOleInit())
	{
		AfxMessageBox("Failed to initialize OLE!");
		return FALSE;
	}

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

	// Parse command line for automation or reg/unreg switches.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

/*	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register class factories via CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
	}
	// App was launched with /Unregserver or /Unregister switch.  Remove
	// entries from the registry.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}*/

	InitializeGDIP();

	CDataCreatorDlg dlg;
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
