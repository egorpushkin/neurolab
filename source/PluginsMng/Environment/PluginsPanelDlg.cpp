// PluginsPanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\PluginsMng.h"
#include "PluginsPanelDlg.h"

#include "..\..\Common\interface_idds.h"
#include ".\pluginspaneldlg.h"

#include "PluginPropertiesDlg.h"

// CPluginsPanelDlg dialog

IMPLEMENT_DYNAMIC(CPluginsPanelDlg, CDialog)
CPluginsPanelDlg::CPluginsPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginsPanelDlg::IDD, pParent)
	, mPluginsCount(0)
{
	iPropWndsCount = 0;

	pAppController = NULL;
}

CPluginsPanelDlg::~CPluginsPanelDlg()
{
}

void CPluginsPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLUGINS_TREE, mPluginsTree);
	DDX_Text(pDX, IDC_NUMBER_LOADED_PLUGINS, mPluginsCount);
}


BEGIN_MESSAGE_MAP(CPluginsPanelDlg, CDialog)
	ON_BN_CLICKED(IDC_START_PLUGIN, OnBnClickedStartPlugin)
	ON_BN_CLICKED(IDC_PLUGIN_PROPERTIES, OnBnClickedPluginProperties)
	ON_BN_CLICKED(IDC_REFRESH_PLUGINS_TREE, OnBnClickedRefreshPluginsTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PLUGINS_TREE, OnTvnSelchangedPluginsTree)
	ON_NOTIFY(NM_DBLCLK, IDC_PLUGINS_TREE, OnNMDblclkPluginsTree)
END_MESSAGE_MAP()


// CPluginsPanelDlg message handlers

// IPluginsPanel implementations section
BOOL CPluginsPanelDlg::CreatePanelDlg(CWnd* pWnd)
{
	BOOL bCreate = Create(IDD, pWnd);
	return bCreate;
}

BOOL CPluginsPanelDlg::ShowPanel(int iCmdShow)
{
	return ShowWindow(iCmdShow);
}

void CPluginsPanelDlg::MovePanel(int iX, int iY, int iWidth, int iHeight)
{
	MoveWindow(iX, iY, iWidth, iHeight);
}

void CPluginsPanelDlg::GetPanelRect(CRect* pRect)
{
	GetClientRect(pRect);
}

void CPluginsPanelDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// IObject implementations section
CString CPluginsPanelDlg::GetClassString()
{
	return CString("CPluginsPanelDlg");
}

void CPluginsPanelDlg::QueryInterface(int iIDD, void ** ppvObject)
{
	switch (iIDD)
	{
	case IDD_IPluginsPanelControl:
		*ppvObject = (IPluginsPanelControl*)this;
		break;		
	default:
		*ppvObject = NULL;
	}
}
BOOL CPluginsPanelDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rClRect;
	GetClientRect(&rClRect);

	mPanelInfoBar.SetMediaDirectory(CString("Media\\UI\\Images"));
	mPanelInfoBar.Create(NULL, "Plug-ins Panel", WS_VISIBLE, 
		CRect(rClRect.left, rClRect.top, rClRect.right, rClRect.top + 24), 
		this, IDC_PANEL_INFO);

	mPanelInfoBar.SetToolTipText(
		CString("Toolbax panel gives you an ..."),
		CString("ToolBox Navigator Quick Help"));
	mPanelInfoBar.SetRightPanelTips(CString("Use the menu to get access to most common toolbox functions."));

	htiRoot = mPluginsTree.InsertItem("Plug-ins v1.0");

	ShowPluginsTree();

	EnablePluginControls(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPluginsPanelDlg::SetAppFolder(CString& csFolder)
{
	csAppFolder = csFolder;
}

void CPluginsPanelDlg::SetPluginsContainer(IPluginsContainer* pContainer)
{
	pPluginsContainer = pContainer;
}

void CPluginsPanelDlg::CreatePluginsTreeHeader()
{
	htiPluginsRoot = mPluginsTree.InsertItem("Loaded Instances", htiRoot);
	htiWrongsRoot = mPluginsTree.InsertItem("Wrong Libraries", htiRoot);
}

void CPluginsPanelDlg::ShowPluginsTree()
{
	CreatePluginsTreeHeader();

	// Shows loaded plugins
	int iPluginsCount = 0;
	pPluginsContainer->CreateEnumerator();
	while (CPluginInstance* pPluginInstance = pPluginsContainer->GetNextPlugin())
	{		
		HTREEITEM htiPluginItem = mPluginsTree.InsertItem(
			pPluginInstance->mPluginInfo.csName, htiPluginsRoot);	
		mPluginsTree.SetItemData(htiPluginItem, (DWORD_PTR)pPluginInstance);
		
		iPluginsCount++;
	}

	// Shows wrong files
	CList<CString, CString> mWrongFiles;
	pPluginsContainer->GetWrongFilesList(&mWrongFiles);
	
	for(POSITION pos = mWrongFiles.GetHeadPosition();pos;)
	{
		CString csWrongFileName = mWrongFiles.GetNext(pos);
		mPluginsTree.InsertItem(csWrongFileName, htiWrongsRoot);
	}

	mPluginsTree.Expand(htiRoot, TVE_EXPAND);
	mPluginsTree.Expand(htiWrongsRoot, TVE_EXPAND);
	mPluginsTree.Expand(htiPluginsRoot, TVE_EXPAND);

	UpdateData(TRUE);
	mPluginsCount = iPluginsCount;
	UpdateData(FALSE);
}

void CPluginsPanelDlg::CleanPluginsTree()
{
	mPluginsTree.DeleteItem(htiWrongsRoot);
	mPluginsTree.DeleteItem(htiPluginsRoot);
}

void CPluginsPanelDlg::EnablePluginControls(BOOL bEnable)
{
	GetDlgItem(IDC_START_PLUGIN)->EnableWindow(bEnable);
    GetDlgItem(IDC_PLUGIN_PROPERTIES)->EnableWindow(bEnable);
}

void CPluginsPanelDlg::OnBnClickedStartPlugin()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mPluginsTree.GetSelectedItem();
	if (htiItem)
	{
		CPluginInstance* pPluginInstance = (CPluginInstance*)mPluginsTree.GetItemData(htiItem);
		if (pPluginInstance)
		{
			pPluginInstance->pPluginControl->StartPlugin();
		}
	}
}

void CPluginsPanelDlg::OnBnClickedPluginProperties()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mPluginsTree.GetSelectedItem();
	if (htiItem)
	{
		CPluginInstance* pPluginInstance = (CPluginInstance*)mPluginsTree.GetItemData(htiItem);
		if (pPluginInstance)
		{
			if (pPluginInstance->IsPropertiesDlgActivated)
				return;

			pPluginInstance->IsPropertiesDlgActivated = true;
            			
			iPropWndsCount++;			

			CPluginPropertiesDlg mDlg;
			mDlg.SetPluginInstance(pPluginInstance);
			mDlg.DoModal();

			iPropWndsCount--;

			pPluginInstance->IsPropertiesDlgActivated = false;
		}
	}
}

void CPluginsPanelDlg::OnBnClickedRefreshPluginsTree()
{
	// TODO: Add your control notification handler code here
	if (iPropWndsCount > 0)
	{	
		MessageBox("Please close all property windows to process this operation.", "Neuro Laboratory");	
		return;
	}

	pAppController->ShowPluginBar(NULL, CString(""));

	pPluginsContainer->RefreshPluginsList(csAppFolder);

	CleanPluginsTree();
	ShowPluginsTree();
}

void CPluginsPanelDlg::OnTvnSelchangedPluginsTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM htiItem = mPluginsTree.GetSelectedItem();
	if (htiItem)
	{
		DWORD_PTR dwpItemData = mPluginsTree.GetItemData(htiItem);
		EnablePluginControls(!(dwpItemData == NULL));

		if (dwpItemData)
		{
			CPluginInstance* pPluginInstance = (CPluginInstance*)dwpItemData;
			ShowPluginBar(pPluginInstance);

			return;
		}
	}

	pAppController->ShowPluginBar(NULL, CString(""));
}

void CPluginsPanelDlg::OnNMDblclkPluginsTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	OnBnClickedStartPlugin();
}

void CPluginsPanelDlg::ShowPluginBar(CPluginInstance* pInstance)
{
	if (pInstance->mPluginInfo.bHasBar)
	{
		IPluginBarControl* pPluginBarControl = NULL;
		pInstance->pPluginControl->QueryInterface(IDD_IPluginBarControl, (void**)&pPluginBarControl); 

		if (pPluginBarControl)
		{
			if (!pPluginBarControl->IsBarCreated())
			{
				pAppController->CreatePluginBar(
					pPluginBarControl->GetBarDialog(),
					pPluginBarControl->GetBarIDD());
				pPluginBarControl->SetBarState(true);
			}				

			pAppController->ShowPluginBar(pPluginBarControl->GetBarDialog(), 
				pPluginBarControl->GetBarTitle());

			return;
		}
	}

	pAppController->ShowPluginBar(NULL, CString(""));
}