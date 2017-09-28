// ScriptEnvMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScriptEnv.h"
#include "ScriptEnvMainDlg.h"
#include ".\scriptenvmaindlg.h"

#include "System\Directory.h"
#include "CmnDataFile.h"
#include "CmnPGMBitmap.h"
#include "CmnFactory.h"

// Resource Tools
#include "Configs\ResourceMng.h"

// Solution Operations
#include "SolutionOperations\NewSolution.h"
#include "SolutionOperations\NewScript.h"
#include "SolutionOperations\CloseSolution.h"
#include "SolutionOperations\OpenSolution.h"
#include "SolutionOperations\NewDataFile.h"
#include "SolutionOperations\ExecuteScript.h"
#include "SolutionOperations\RemoveItem.h"
#include "SolutionOperations\NewBitmap.h"
#include "SolutionOperations\NewProject.h"

// Solution UI
#include "SolutionUI\AboutDlg.h"

// CScriptEnvMainDlg dialog

IMPLEMENT_DYNAMIC(CScriptEnvMainDlg, CDialog)
CScriptEnvMainDlg::CScriptEnvMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEnvMainDlg::IDD, pParent)
{
	htiSolutionItem = NULL;
	htiScriptsRoot = NULL;
	htiDataRoot = NULL;
	htiBitmapsRoot = NULL;
	htiProjectsRoot = NULL;

	pCurrentSolutionItem = NULL;

	bIsChanged = false;

	mAcceleratorsTable = ::LoadAccelerators(
		AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR));
	ASSERT(mAcceleratorsTable);

	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);
}

CScriptEnvMainDlg::~CScriptEnvMainDlg()
{
	if (mSolutionObj.IsCreated())
		mSolutionObj.DestroySolution();
}

void CScriptEnvMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOLUTION_TREE, mSolutionTree);
	//DDX_Control(pDX, IDC_COMPILE_LOG_LIST, mCompileLogList);
	//DDX_Control(pDX, IDC_WORKSPACE_EDIT, mWorkspaceEdit);
}

void CScriptEnvMainDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	bool bRet = CSolutionOperation_CloseSolution::CloseSolution(this);

	if (bRet)
	{
		mImportManager.UnloadComponent();

		CDialog::OnCancel();
	}
}

void CScriptEnvMainDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

BEGIN_MESSAGE_MAP(CScriptEnvMainDlg, CDialog)
	ON_COMMAND(ID_CLOSE_ENVIRONMENT, OnCloseEnvironment)
	ON_COMMAND(ID_NEW_SOLUTION, OnNewSolution)
	ON_COMMAND(ID_NEW_SCRIPT, OnNewScript)
	ON_COMMAND(ID_CLOSE_SOLUTION, OnCloseSolution)
	ON_COMMAND(ID_OPEN_SOLUTION, OnOpenSolution)
	ON_COMMAND(ID_SAVE_SOLUTION, OnSaveSolution)
	ON_COMMAND(ID_ADD_EXISTING_SCRIPT, OnAddExistingScript)
	ON_COMMAND(IDC_CLOSE_CURRENT_SCRIPT, OnCloseCurrentScript)
	ON_NOTIFY(NM_DBLCLK, IDC_SOLUTION_TREE, OnNMDblclkSolutionTree)
	ON_COMMAND(ID_ADD_EXISTING_DATA_FILE, OnAddExistingDataFile)
	ON_COMMAND(ID_EXECUTE_SCRIPT, OnExecuteScript)
	ON_COMMAND(ID_ABOUT_SCRIPTING_ENVIRONMENT, OnAboutScriptingEnvironment)
	ON_COMMAND(ID_REMOVE_CURRENT_ITEM, OnRemoveCurrentItem)
	ON_COMMAND(ID_DEVELOPER_GUIDE, OnShowDeveloperGuide)
	ON_COMMAND(ID_ADD_EXISTING_BITMAP, OnAddExistingBitmap)
	ON_COMMAND(ID_ADD_EXISTING_NETWORK_PROJECT, OnAddExistingNetworkProject)	

	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)

#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	ON_REGISTERED_MESSAGE(BCGM_ON_EDITCHANGE, OnEnChangeWorkspaceEdit)
#else
	ON_EN_CHANGE(IDC_WORKSPACE_EDIT, OnEnChangeWorkspaceEdit)
#endif
	ON_COMMAND(ID_LUA_MANUAL, OnShowLuaManual)
END_MESSAGE_MAP()

// CScriptEnvMainDlg message handlers

BOOL CScriptEnvMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here	
	ASSERT(pAppController != NULL);

	CreateEnvironmentControls();
	LocateControls();
	//ConfigureLogControl();

	// Initializing Network Import Manager Tool
	bool bRet = mImportManager.LoadComponent();
	if (!bRet)
	{
		AfxMessageBox("Network Importing component was not loaded.\nCorresponding API would not be available during this session.\nReinstall your application or contact technical support to resolve this problem.");
	}
	// CenterWindow());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// Dialog UI Operations 
void CScriptEnvMainDlg::CreateEnvironmentControls()
{
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	// Creating WorkspaceEditControl
	mWorkspaceEdit.Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, IDC_WORKSPACE_EDIT);
	mWorkspaceEdit.m_nLeftMarginWidth = 0;
	
	// Initializing WorkspaceEditControl
	mWorkspaceEdit.EnableToolTips();

	// Enable outlining
	mWorkspaceEdit.EnableOutlining();
	mWorkspaceEdit.EnableAutoOutlining();
	mWorkspaceEdit.SetOutlineMargin();
	mWorkspaceEdit.SetLineNumbersMargin(TRUE, 30);
	mWorkspaceEdit.EnableOutlineParser(FALSE);

	// Load XML settings for syntax highlighting
	CString csXMLConfig = CResourceManager::GetResourceString(IDR_EDITOR_CONFIG);
	mWorkspaceEdit.LoadXMLSettingsFromBuffer(csXMLConfig);
	mWorkspaceEdit.SetHyperlinkColor(TRUE, RGB(80, 105, 255));
	
	mWorkspaceEdit.m_bCopyRTFToClipboard = TRUE;

	mWorkspaceEdit.EnableOutlineParser(TRUE);
	mWorkspaceEdit.UpdateAutoOutlining();
#else
	// Creating WorkspaceEditControl
	mWorkspaceEdit.Create(
		WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_VSCROLL |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN, 
		CRect(0, 0, 0, 0), 
		this, 
		IDC_WORKSPACE_EDIT);
#endif

	// Initializing WorkspaceEditControl Font
	BOOL bRet = mWorkspaceFont.CreateFont(
		14,							// nHeight
		0,							// nWidth
		0,							// nEscapement
		0,							// nOrientation
		FW_NORMAL,					// nWeight
		FALSE,						// bItalic
		FALSE,						// bUnderline
		0,							// cStrikeOut
		ANSI_CHARSET,				// nCharSet
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
		_T("Courier New")); 
	mWorkspaceEdit.SetFont(&mWorkspaceFont);

	// Initializing other environment controls
	CRect rect(10, 10, 100, 100);
	mSolutionBar.Create(NULL, "Solution", WS_VISIBLE, rect, this, IDC_SOLUTION_BAR);
	mWorkspaceBar.Create(NULL, PrepareWorkspaceBarTitle(), WS_VISIBLE, rect, this, IDC_WORKSPACE_BAR);
	//mCompileLogBar.Create(NULL, "Operations Log", WS_VISIBLE, rect, this, IDC_COMPILELOG_BAR);

	mSolutionBar.AddButton(CString(_T("Operations")), IDR_SOLUTION_OPERATIONS, BT_DROPDOWN_MENU_BUTTON);
	mSolutionBar.AddButton(CString(_T("Help")), IDR_HELP, BT_DROPDOWN_MENU_BUTTON);

	CString tmWorkspaceTips = 
		CString(_T("This zone provides an opportunity of writing user scripts\n")) + 
		CString(_T("and is used for presenting Data File content information."));
	CString tmWorkspaceTipsTitle(_T("Workspace Zone"));
	mWorkspaceBar.SetMediaDirectory(CString(_T("Media\\UI\\Images")));
	mWorkspaceBar.SetToolTipText(tmWorkspaceTips, IDC_TOOLTIP_WORKSPACE, tmWorkspaceTipsTitle);
	mWorkspaceBar.AddButton(CString(_T("Close Script")), IDC_CLOSE_CURRENT_SCRIPT);
	
	/*CString tmOperationsTips = 
		CString(_T("A list of all environment operations is being displayed here."));
	CString tmOperationsTipsTitle(_T("Operations Log"));
	mCompileLogBar.SetMediaDirectory(CString(_T("Media\\UI\\Images")));
	mCompileLogBar.SetToolTipText(tmOperationsTips, IDC_TOOLTIP_OPERATIONS, tmOperationsTipsTitle);*/

	// Initializing images list
	mSolutionImageList.Create(16, 16, TRUE, 1, 1);
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_SOLUTION_EMPTY));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_SOLUTION_OPENED));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_SOLUTION_SCRIPTS));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_SCRIPT_ITEM));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_DATA_FILES));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_DATA_ITEM));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_BITMAP_FILES));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_BITMAP_ITEM));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_PROJECT_FILES));
	mSolutionImageList.Add(AfxGetApp()->LoadIcon(IDI_PROJECT_ITEM));

	mSolutionTree.SetImageList(&mSolutionImageList, LVSIL_SMALL);
	mSolutionTree.SetImageList(&mSolutionImageList, TVSIL_NORMAL);

	ShowEmptySolution();
	EnableSolutionControls(FALSE);
}

void CScriptEnvMainDlg::LocateControls()
{
	CRect ClRect;
	GetClientRect(&ClRect);

	int iSolutionWidth = 200;
	int iLogHeight = 90;
	//int iSolutionHeight = ClRect.Height() - 3 - 24 - 3 - 3 - 24 - 3 - iLogHeight - 3;
	int iSolutionHeight = ClRect.Height() - 3 - 24 - 3 - 3;

	mSolutionBar.MoveWindow(3, 3, iSolutionWidth, 24);
	mWorkspaceBar.MoveWindow(3 + iSolutionWidth + 3, 3, 
		ClRect.Width() - 3 - iSolutionWidth - 3 - 3, 24);
	//mCompileLogBar.MoveWindow(3, 3 + 24 + 3 + iSolutionHeight + 3, 
	//	ClRect.Width() - 3 - 3, 24);

	mSolutionTree.MoveWindow(3, 3 + 24 + 3, iSolutionWidth, iSolutionHeight + 1);
	//mCompileLogList.MoveWindow(3, 3 + 24 + 3 + iSolutionHeight + 3 + 24 + 3,		
	//	ClRect.Width() - 3 - 3, iLogHeight);
	mWorkspaceEdit.MoveWindow(3 + iSolutionWidth + 3, 3 + 24 + 3,
		ClRect.Width() - 3 - iSolutionWidth - 3 - 3, iSolutionHeight);
}

void CScriptEnvMainDlg::ConfigureLogControl()
{
	CRect rect;
	mCompileLogList.GetClientRect(&rect);
	mCompileLogList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mCompileLogList.InsertColumn(0, _T("Description"), LVCFMT_LEFT,  rect.Width()*13/20); 
	mCompileLogList.InsertColumn(1, _T("Section"), LVCFMT_LEFT,  rect.Width()*6/20); 
}

void CScriptEnvMainDlg::UpdateMainWndTitle()
{
	SetWindowText(PrepareMainWndTitle());
}

void CScriptEnvMainDlg::UpdateWorkspaceBarTitle()
{
	mWorkspaceBar.SetWindowText(PrepareWorkspaceBarTitle());
	mWorkspaceBar.Invalidate();
}

CString CScriptEnvMainDlg::PrepareMainWndTitle()
{
	if (mSolutionObj.IsCreated())	
		return CString(_T("Scripting Environment - [ ")) + 
		mSolutionObj.GetSolutionName() + 
		CString(" ] Solution");
	else 
		return CString(_T("Scripting Environment"));
}

CString	CScriptEnvMainDlg::PrepareWorkspaceBarTitle()
{
	if (pCurrentSolutionItem)
		return CString(_T("Workspace [design] - ")) + 
			CPath::GetFileName(pCurrentSolutionItem->GetFileName());
	else 
		return CString(_T("Workspace [design]"));
}

// Solution Environment Operations 
void CScriptEnvMainDlg::EnableSolutionControls(BOOL bEnable)
{
//	mCompileLogList.EnableWindow(bEnable);
	mWorkspaceEdit.EnableWindow(bEnable);
}

// Solution Tree Operations
void CScriptEnvMainDlg::ShowEmptySolution()
{
	CString tmEmptySolutionName(_T("Empty Solution"));
	if (mSolutionObj.IsCreated())
		tmEmptySolutionName = PrepareSolutionName(mSolutionObj.GetSolutionName());

	if (!htiSolutionItem)
	{
		htiSolutionItem = mSolutionTree.InsertItem(tmEmptySolutionName);
	} else
	{
		mSolutionTree.SetItemText(htiSolutionItem, tmEmptySolutionName);
	}

	if (!htiScriptsRoot && mSolutionObj.IsCreated())
		htiScriptsRoot = mSolutionTree.InsertItem(_T("Solution Scripts"), 2, 2, htiSolutionItem);

	if (!htiDataRoot && mSolutionObj.IsCreated())
		htiDataRoot = mSolutionTree.InsertItem(_T("Solution Binded Data"), 4, 4, htiSolutionItem);

	if (!htiBitmapsRoot && mSolutionObj.IsCreated())
		htiBitmapsRoot = mSolutionTree.InsertItem(_T("Solution Binded Bitmaps"), 6, 6, htiSolutionItem);

	if (!htiProjectsRoot && mSolutionObj.IsCreated())
		htiProjectsRoot = mSolutionTree.InsertItem(_T("Network Projects"), 8, 8, htiSolutionItem);

	UpdateMainWndTitle();

	UINT uItemStyle = 0;
	int iImageIndex = 0;
	if (mSolutionObj.IsCreated())
	{
		uItemStyle = TVIS_BOLD;
		iImageIndex = 1;
	}

	mSolutionTree.SetItemState(htiSolutionItem, uItemStyle, TVIS_BOLD);
	mSolutionTree.SetItemImage(htiSolutionItem, iImageIndex, iImageIndex);

	mSolutionTree.Expand(htiSolutionItem, TVE_EXPAND);
}

void CScriptEnvMainDlg::CloseSolution()
{
	// Remove solution script items
	HTREEITEM hCurrent = mSolutionTree.GetNextItem(htiScriptsRoot, TVGN_CHILD);
	while (hCurrent != NULL)
	{	
		HTREEITEM htiItem = hCurrent;
		
		hCurrent = mSolutionTree.GetNextItem(hCurrent, TVGN_NEXT);

		mSolutionTree.DeleteItem(htiItem);
	}

	if (htiScriptsRoot)
	{
		mSolutionTree.DeleteItem(htiScriptsRoot);
		htiScriptsRoot = NULL;
	}

	if (htiDataRoot)
	{
		mSolutionTree.DeleteItem(htiDataRoot);
		htiDataRoot = NULL;	
	}

	if (htiBitmapsRoot)
	{
		mSolutionTree.DeleteItem(htiBitmapsRoot);
		htiBitmapsRoot = NULL;				
	}

	if (htiProjectsRoot)
	{
		mSolutionTree.DeleteItem(htiProjectsRoot);
		htiProjectsRoot = NULL;	
	}

	pCurrentSolutionItem = NULL;
	
	ShowEmptySolution();
	ShowScriptFileInEditor();
}

CString CScriptEnvMainDlg::PrepareSolutionName(CString& Name)
{
	return CString(_T("[")) + Name + CString(_T("] Solution"));
}

// Building Solution Functions
void CScriptEnvMainDlg::AddItem(CSolutionItem* pItem)
{
	CString tmFileName = CPath::GetFileName(pItem->GetFileName());

	HTREEITEM htiItem = mSolutionTree.InsertItem(tmFileName, 3, 3, htiScriptsRoot);
	mSolutionTree.SetItemData(htiItem, (DWORD_PTR)pItem);

	mSolutionTree.Expand(htiSolutionItem, TVE_EXPAND);
	mSolutionTree.Expand(htiScriptsRoot, TVE_EXPAND);
}

void CScriptEnvMainDlg::AddDataItem(CDataFileItem* pItem)
{
	CString tmFileName = CPath::GetFileName(pItem->GetFileName());

	HTREEITEM htiItem = mSolutionTree.InsertItem(tmFileName, 5, 5, htiDataRoot);
	mSolutionTree.SetItemData(htiItem, (DWORD_PTR)pItem);

	mSolutionTree.Expand(htiSolutionItem, TVE_EXPAND);
	mSolutionTree.Expand(htiDataRoot, TVE_EXPAND);	
}

void CScriptEnvMainDlg::AddBitmapItem(CBitmapItem* pItem)
{
	CString tmFileName = CPath::GetFileName(pItem->GetFileName());

	HTREEITEM htiItem = mSolutionTree.InsertItem(tmFileName, 7, 7, htiBitmapsRoot);
	mSolutionTree.SetItemData(htiItem, (DWORD_PTR)pItem);

	mSolutionTree.Expand(htiSolutionItem, TVE_EXPAND);
	mSolutionTree.Expand(htiBitmapsRoot, TVE_EXPAND);	
}

void CScriptEnvMainDlg::AddProjectItem(CProjectItem* pItem)
{
	CString tmFileName = CPath::GetFileName(pItem->GetFileName());

	HTREEITEM htiItem = mSolutionTree.InsertItem(tmFileName, 9, 9, htiProjectsRoot);
	mSolutionTree.SetItemData(htiItem, (DWORD_PTR)pItem);

	mSolutionTree.Expand(htiSolutionItem, TVE_EXPAND);
	mSolutionTree.Expand(htiProjectsRoot, TVE_EXPAND);	
}

void CScriptEnvMainDlg::ShowScriptFileInEditor(CSolutionItem* pItem)
{
	if (pCurrentSolutionItem)
	{
		CString tmCurrentContent;
		mWorkspaceEdit.GetWindowText(tmCurrentContent);

		pCurrentSolutionItem->UpdateScriptFileContent(tmCurrentContent);
		pCurrentSolutionItem = NULL;
	}

	if (!pItem)
	{		
		mWorkspaceEdit.EnableWindow(FALSE);		
		
		mWorkspaceEdit.SetWindowText(_T(""));

		UpdateWorkspaceBarTitle();
	} else
	{
		mWorkspaceEdit.EnableWindow(TRUE);

		CString tmCurrentContent = pItem->GetScriptFileContent();		
		
#ifndef USE_SCISOFT_ADVANCED_EDIT_CONTROL
		tmCurrentContent.Replace(_T("\n"), _T("\r\n"));
		tmCurrentContent.Replace(_T("\r\r\n"), _T("\r\n"));
		tmCurrentContent.Replace(_T("\t"), _T("    "));
#endif		

		mWorkspaceEdit.SetWindowText(tmCurrentContent);
		mWorkspaceEdit.SetReadOnly(FALSE);

		pCurrentSolutionItem = pItem;

		UpdateWorkspaceBarTitle();
	}
}

void CScriptEnvMainDlg::ShowDataFileInEditor(CDataFileItem* pItem)
{
	if (!pItem)
		return;

    CString csPreparedContent(_T(""));

	CDataFile tmDataFile(pItem->GetFileName());
	if (!tmDataFile.IsLoaded())
	{
		csPreparedContent += CString(_T(" Data File Overview\r\n"));
		csPreparedContent += CString(_T("\tFile name: ")) + pItem->GetFileName() + CString(_T(" \r\n"));
		csPreparedContent += CString(_T("\r\n"));		
		csPreparedContent += CString(_T("\tWrong Data File Content!\r\n"));
	} else
	{
		CString tmInputsCount, tmInputLength, tmOutputsCount, tmOutputLength;
		tmInputsCount.Format("%d", tmDataFile.GetInputSymbolsCount());
		tmInputLength.Format("%d", tmDataFile.GetInputSymbolLength());
		tmOutputsCount.Format("%d", tmDataFile.GetOutputSymbolsCount());
		tmOutputLength.Format("%d", tmDataFile.GetOutputSymbolLength());

		csPreparedContent += CString(_T(" Data File Overview\r\n"));
		csPreparedContent += CString(_T("\tFile name: ")) + pItem->GetFileName() + CString(_T(" \r\n"));
		csPreparedContent += CString(_T("\r\n"));
		csPreparedContent += CString(_T(" Data File Content\r\n"));
		csPreparedContent += CString(_T("\tInput symbols count: ")) + tmInputsCount + CString(_T(".\r\n"));;
		csPreparedContent += CString(_T("\tInput symbol length: ")) + tmInputLength + CString(_T(".\r\n"));;
		csPreparedContent += CString(_T("\tOutput symbols count: ")) + tmOutputsCount + CString(_T(".\r\n"));;
		csPreparedContent += CString(_T("\tOutput symbol length: ")) + tmOutputLength + CString(_T(".\r\n"));;
	}
	
	mWorkspaceEdit.EnableWindow(TRUE);
	mWorkspaceEdit.SetWindowText(csPreparedContent);
	mWorkspaceEdit.SetReadOnly(TRUE);
}

void CScriptEnvMainDlg::ShowBitmapInEditor(CBitmapItem* pItem)
{
	if (!pItem)
		return;

    CString csPreparedContent(_T(""));

	CPGMBitmap tmBitmapFile;
	if (!tmBitmapFile.LoadPGMBitmap(pItem->GetFileName()))
	{
		csPreparedContent += CString(_T(" Bitmap File Overview\r\n"));
		csPreparedContent += CString(_T("\tFile name: ")) + pItem->GetFileName() + CString(_T(" \r\n"));
		csPreparedContent += CString(_T("\r\n"));		
		csPreparedContent += CString(_T("\tWrong Bitmap File Content!\r\n"));
	} else
	{
		CString tmColorDepth, tmWidth, thHeight;
		tmColorDepth.Format("%d", tmBitmapFile.GetColorDepth());
		tmWidth.Format("%d", tmBitmapFile.GetWidth());
		thHeight.Format("%d", tmBitmapFile.GetHeight());

		csPreparedContent += CString(_T(" Bitmap File Overview\r\n"));
		csPreparedContent += CString(_T("\tFile name: ")) + pItem->GetFileName() + CString(_T(" \r\n"));
		csPreparedContent += CString(_T("\r\n"));
		csPreparedContent += CString(_T(" Bitmap File Content\r\n"));
		csPreparedContent += CString(_T("\tColor depth: ")) + tmColorDepth + CString(_T(" byte(s) per pixel.\r\n"));;
		csPreparedContent += CString(_T("\tImage width: ")) + tmWidth + CString(_T(".\r\n"));;
		csPreparedContent += CString(_T("\tImage height: ")) + thHeight + CString(_T(".\r\n"));;
	}
	
	mWorkspaceEdit.EnableWindow(TRUE);
	mWorkspaceEdit.SetWindowText(csPreparedContent);
	mWorkspaceEdit.SetReadOnly(TRUE);
}

void CScriptEnvMainDlg::ShowProjectInEditor(CProjectItem* pItem)
{
	if (!pItem)
		return;

    CString csPreparedContent(_T(""));

	if (!mImportManager.IsLoaded())
	{
		csPreparedContent += CString(_T(" Error loading Network Importing component.\r\n")); 
        csPreparedContent += CString(_T(" Project file cannot be processed."));
	} else
	{
		IImportManager* pImportManager = mImportManager.GetImportManager();

		csPreparedContent += CString(_T(" Project File Overview\r\n"));
		csPreparedContent += CString(_T("\tFile name: ")) + pItem->GetFileName() + CString(_T(" \r\n"));
		csPreparedContent += CString(_T("\r\n"));		
		
		if (!pImportManager->LoadNLProject(pItem->GetFileName()))
			csPreparedContent += CString(_T("\tWrong Project File Content!\r\n"));				
		else
		{
			IElementsCollection* pElementsCollection = NULL;
			pImportManager->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

			csPreparedContent += CString(_T(" Project File Content\r\n"));

            pElementsCollection->CreateElementsEnumerator(6);
			while (IElement* pElement = pElementsCollection->GetNextElement(6))
			{
				ILayerControl* pLayerControl = NULL;
				pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
				
				CString tmElementType(_T("\t[ Single Element ] "));
				if (pLayerControl)
					tmElementType = CString(_T("\t[ Layer Element ] "));

				CString tmElementID;
				tmElementID.Format(" %d", pElement->GetElementID());

				csPreparedContent += tmElementType;
				csPreparedContent += pElement->GetElementTitle();
				csPreparedContent += tmElementID;
				csPreparedContent += CString(_T("\r\n"));	
			
			}
		}

		mImportManager.ReleaseImportManager(pImportManager);	
	}
	
	mWorkspaceEdit.EnableWindow(TRUE);
	mWorkspaceEdit.SetWindowText(csPreparedContent);
	mWorkspaceEdit.SetReadOnly(TRUE);
}

void CScriptEnvMainDlg::RemoveScriptFile(HTREEITEM htiItem, CSolutionItem* pItem)
{
	mSolutionTree.DeleteItem(htiItem);

	if (pCurrentSolutionItem == pItem)
		OnCloseCurrentScript();
}

void CScriptEnvMainDlg::RemoveDataFile(HTREEITEM htiItem, CDataFileItem* pItem)
{
	mSolutionTree.DeleteItem(htiItem);

	CString tmText;
	mWorkspaceEdit.GetWindowText(tmText);
	if (tmText.Find(pItem->GetFileName()) != -1)
		OnCloseCurrentScript();
}

void CScriptEnvMainDlg::RemoveBitmap(HTREEITEM htiItem, CBitmapItem* pItem)
{
	mSolutionTree.DeleteItem(htiItem);

	CString tmText;
	mWorkspaceEdit.GetWindowText(tmText);
	if (tmText.Find(pItem->GetFileName()) != -1)
		OnCloseCurrentScript();
}

void CScriptEnvMainDlg::RemoveProject(HTREEITEM htiItem, CProjectItem* pItem)
{
	mSolutionTree.DeleteItem(htiItem);

	CString tmText;
	mWorkspaceEdit.GetWindowText(tmText);
	if (tmText.Find(pItem->GetFileName()) != -1)
		OnCloseCurrentScript();
}

// Solution Operations
void CScriptEnvMainDlg::OnCloseEnvironment()
{
	// TODO: Add your command handler code here
	OnCancel();
}

void CScriptEnvMainDlg::OnNewSolution()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewSolution::CreateNewSolution(this);
}

void CScriptEnvMainDlg::OnNewScript()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewScript::NewScript(this);
}

void CScriptEnvMainDlg::OnCloseSolution()
{
	// TODO: Add your command handler code here
	CSolutionOperation_CloseSolution::CloseSolution(this);
}

void CScriptEnvMainDlg::OnCloseCurrentScript()
{	
	ShowScriptFileInEditor();
}

void CScriptEnvMainDlg::OnOpenSolution()
{	
	// TODO: Add your command handler code here
	CSolutionOperation_OpenSolution::OpenSolution(this);
}

void CScriptEnvMainDlg::OnSaveSolution()
{
	// TODO: Add your command handler code here
	CSolutionOperation_SaveSolution::SaveSolution(this);
}

void CScriptEnvMainDlg::OnAddExistingScript()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewScript::NewScript(this, false);
}

void CScriptEnvMainDlg::OnAddExistingDataFile()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewDataFile::NewDataFile(this);
}

void CScriptEnvMainDlg::OnExecuteScript()
{
	// TODO: Add your command handler code here
	CSolutionOperation_ExecuteScript::ExecuteScript(this);
}

void CScriptEnvMainDlg::OnAboutScriptingEnvironment()
{
	// TODO: Add your command handler code here
	CAboutDlg mDlg;
	mDlg.DoModal();
}

void CScriptEnvMainDlg::OnShowDeveloperGuide()
{
	// TODO: Add your command handler code here
	CString csAppFolder;
	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);	
	CString csDeveloperGuidePath = csAppFolder +
		CString("\\Documentation\\Scripting Environment - Developer Guide.chm");

	ShellExecute(NULL, "open", csDeveloperGuidePath, NULL, "", SW_MAXIMIZE);
}

void CScriptEnvMainDlg::OnShowLuaManual()
{
	// TODO: Add your command handler code here
	CString csAppFolder;
	GetModuleFileName(GetModuleHandle(NULL), csAppFolder.GetBuffer(MAX_PATH), MAX_PATH);
	csAppFolder.ReleaseBuffer();
	int tmPos = csAppFolder.ReverseFind('\\');
	csAppFolder	= csAppFolder.Left(tmPos);	
	CString csDeveloperGuidePath = csAppFolder +
		CString("\\Documentation\\Lua 5.0.2 Manual\\contents.html");

	ShellExecute(NULL, "open", csDeveloperGuidePath, NULL, "", SW_MAXIMIZE);
}


void CScriptEnvMainDlg::OnRemoveCurrentItem()
{
	// TODO: Add your command handler code here
	CSolutionOperation_RemoveItem::RemoveItem(this);
}

void CScriptEnvMainDlg::OnAddExistingBitmap()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewBitmap::NewBitmap(this);
}

void CScriptEnvMainDlg::OnAddExistingNetworkProject()
{
	// TODO: Add your command handler code here
	CSolutionOperation_NewProject::NewProject(this);
}

// Solution Tree Handlers
void CScriptEnvMainDlg::OnNMDblclkSolutionTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM htiCurrent = mSolutionTree.GetSelectedItem();
	if (htiCurrent)
	{
		IObject* pObject = (IObject*)mSolutionTree.GetItemData(htiCurrent);
		if (!pObject)
			return;

		if (pObject->GetClassString() == CString(_T("CSolutionItem")))
		{
			CSolutionItem* pItem = (CSolutionItem*)pObject;
       		ShowScriptFileInEditor(pItem);
		} else if (pObject->GetClassString() == CString(_T("CDataFileItem")))
		{
			ShowScriptFileInEditor();

			CDataFileItem* pItem = (CDataFileItem*)pObject;
       		ShowDataFileInEditor(pItem);			
		} else if (pObject->GetClassString() == CString(_T("CBitmapItem")))
		{
			ShowScriptFileInEditor();

			CBitmapItem* pItem = (CBitmapItem*)pObject;
       		ShowBitmapInEditor(pItem);			
		} else if (pObject->GetClassString() == CString(_T("CProjectItem")))
		{
			ShowScriptFileInEditor();

			CProjectItem* pItem = (CProjectItem*)pObject;
       		ShowProjectInEditor(pItem);			
		}
	}
}

// Solution Workspace Handlers
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
LRESULT CScriptEnvMainDlg::OnEnChangeWorkspaceEdit(WPARAM wParam, LPARAM lParam)
#else
void CScriptEnvMainDlg::OnEnChangeWorkspaceEdit()
#endif
{
	// TODO:  Add your control notification handler code here
	if (pCurrentSolutionItem)
	{
		CString tmCurrentContent;
		mWorkspaceEdit.GetWindowText(tmCurrentContent);

		pCurrentSolutionItem->UpdateScriptFileContent(tmCurrentContent);
	}	

#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	return 0;
#endif
}

BOOL CScriptEnvMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) 
	{
		return ::TranslateAccelerator(m_hWnd, mAcceleratorsTable, pMsg);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CScriptEnvMainDlg::OnEditCopy() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
		mWorkspaceEdit.Copy();
	}
}

void CScriptEnvMainDlg::OnEditCut() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
		mWorkspaceEdit.Cut();
	}
}

void CScriptEnvMainDlg::OnEditPaste() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
		mWorkspaceEdit.Paste();
	}
}

void CScriptEnvMainDlg::OnEditSelectAll() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
		mWorkspaceEdit.MakeSelection(CBCGPEditCtrl::ST_ALL_TEXT);
#else
		mWorkspaceEdit.SetSel(0, -1);
#endif
	}
}

void CScriptEnvMainDlg::OnEditUndo() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
		mWorkspaceEdit.OnUndo();
#endif
	}
}

void CScriptEnvMainDlg::OnEditRedo() 
{
	if (mWorkspaceEdit.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
	{
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
		mWorkspaceEdit.OnRedo();
#endif
	}
}
