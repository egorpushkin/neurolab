// CommonPluginPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\PluginsMng.h"
#include "CommonPluginPropDlg.h"
#include ".\commonpluginpropdlg.h"

#include "..\StandartControls\BDS.h"

#include "interface_idds.h"
#include "CmnPlugin.h"

// CCommonPluginPropDlg dialog

IMPLEMENT_DYNAMIC(CCommonPluginPropDlg, CDialog)
CCommonPluginPropDlg::CCommonPluginPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommonPluginPropDlg::IDD, pParent)
	, mPluginName(_T(""))
	, mPluginVersion(_T(""))
	, mPluginFileName(_T(""))
	, mLibraryType(_T(""))
	, mLibraryVersion(_T(""))
	, mLastModified(_T(""))
	, mFileSize(_T(""))
	, mInstanceAddress(_T(""))
{
}

CCommonPluginPropDlg::~CCommonPluginPropDlg()
{
}

void CCommonPluginPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PLUGIN_NAME, mPluginName);
	DDX_Text(pDX, IDC_PLUGIN_VERSION, mPluginVersion);
	DDX_Text(pDX, IDC_BAR_PRESENCE_STRING, mBarPresenceString);
	DDX_Text(pDX, IDC_PLUGIN_FILE_NAME, mPluginFileName);
	DDX_Text(pDX, IDC_LIBRARY_TYPE, mLibraryType);
	DDX_Text(pDX, IDC_LIBRARY_VERSION, mLibraryVersion);
	DDX_Text(pDX, IDC_LAST_MODIFIED, mLastModified);
	DDX_Text(pDX, IDC_LIBRARY_SIZE, mFileSize);
	DDX_Control(pDX, IDC_SYMBOLS_LIST, mSymbolsList);
	DDX_Control(pDX, IDC_INTERFACES_LIST, mInterfacesTable);
	DDX_Text(pDX, IDC_INSTANCE_ADDRESS, mInstanceAddress);
}


BEGIN_MESSAGE_MAP(CCommonPluginPropDlg, CDialog)
END_MESSAGE_MAP()


// CCommonPluginPropDlg message handlers

void CCommonPluginPropDlg::UpdatePropertyPage(CPluginInstance* pInstance)
{
	UpdateData(TRUE);

	mSymbolsList.DeleteAllItems();
	AddListItem(&mSymbolsList, -1, NULL, 2, _T("CreatePluginInstance"), _T("IPluginControl*"));
	AddListItem(&mSymbolsList, -1, NULL, 2, _T("ReleasePluginInstance"), _T("void"));
	AddListItem(&mSymbolsList, -1, NULL, 2, _T("GetPluginInfo"), _T("void"));

	mInterfacesTable.DeleteAllItems();
	AddListItem(&mInterfacesTable, -1, NULL, 2, _T("IPluginControl"), pInstance->pPluginControl->GetClassString());

	if (pInstance->mPluginInfo.bHasBar)
	{
		IPluginBarControl*	pBarControl = NULL;	
		pInstance->pPluginControl->QueryInterface(IDD_IPluginBarControl, (void**)&pBarControl);
		if (pBarControl)
			AddListItem(&mInterfacesTable, -1, NULL, 2, _T("IPluginBarControl"), pBarControl->GetClassString());
	}
	
	if (pInstance->mPluginInfo.bHasPropertiesPage)
	{
		IPluginPropertiesControl* pPropertiesControl = NULL;
		pInstance->pPluginControl->QueryInterface(IDD_IPluginPropertiesControl, (void**)&pPropertiesControl);
		if (pPropertiesControl)
			AddListItem(&mInterfacesTable, -1, NULL, 2, _T("IPluginPropertiesControl"), pPropertiesControl->GetClassString());
	}

	mPluginName = pInstance->mPluginInfo.csName;
	mPluginVersion = pInstance->mPluginInfo.csVersion;
	if (pInstance->mPluginInfo.bHasBar)
		mBarPresenceString = _T("Presents");
	else
		mBarPresenceString = _T("Absents");
	mPluginFileName = pInstance->csPluginFileName;
	mLibraryType = pInstance->mPluginInfo.csLibraryType;
	mLibraryVersion = pInstance->mPluginInfo.csLibraryVersion;

	WIN32_FIND_DATA fdFileData;
	HANDLE hSearch = FindFirstFile(pInstance->csPluginFileName, &fdFileData);
	if (hSearch != INVALID_HANDLE_VALUE) 
	{
		mFileSize.Format("%d", fdFileData.nFileSizeLow);

		SYSTEMTIME stSystemTime, stLocalTime;
		FileTimeToSystemTime(&fdFileData.ftLastWriteTime, &stSystemTime);
        SystemTimeToTzSpecificLocalTime(NULL, &stSystemTime, &stLocalTime);

		mLastModified.Format("%d.%d.%d at %d:%d:%d", stLocalTime.wDay, stLocalTime.wMonth, stLocalTime.wYear,
			stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);

		FindClose(hSearch);
	}

	mInstanceAddress.Format("0x%x", (int)pInstance);

    UpdateData(FALSE);
}
BOOL CCommonPluginPropDlg::Create(int iIDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(iIDD, pParentWnd);

	if (bRet)
	{
		CRect rect;
		mSymbolsList.GetClientRect(&rect);
		mSymbolsList.InsertColumn(0, _T("Symbol name"), LVCFMT_LEFT,  rect.Width()*9/14); 
		mSymbolsList.InsertColumn(1, _T("Return type"), LVCFMT_LEFT,  rect.Width()*5/14); 
		mSymbolsList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

		mInterfacesTable.GetClientRect(&rect);
		mInterfacesTable.InsertColumn(0, _T("Interface"), LVCFMT_LEFT,  rect.Width()*6/14); 
		mInterfacesTable.InsertColumn(1, _T("Class name"), LVCFMT_LEFT,  rect.Width()*8/14); 
		mInterfacesTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	}

	return bRet;
}

void CCommonPluginPropDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnOK();
}

void CCommonPluginPropDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnCancel();
}
