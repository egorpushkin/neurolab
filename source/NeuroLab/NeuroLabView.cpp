// NeuroLabView.cpp : implementation of the CNeuroLabView class
//

#include "stdafx.h"
#include "NeuroLab.h"

#include "NeuroLabDoc.h"
#include "NeuroLabView.h"
#include ".\neurolabview.h"

#include "NeuronPropDlg.h"
#include "NeuronFuncDlg.h"

#include "interface_idds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PLUGIN_BAR_TAB_INDEX		4


// CNeuroLabView

CNeuroLabView* mGlobView;

void onDragItemToNeuroBuilder(void * Param)
{
	IParDef(ObjItem, ObjData, Param, sElement);

	mGlobView->AddElement(ObjData);
}


IMPLEMENT_DYNCREATE(CNeuroLabView, CFormView)

BEGIN_MESSAGE_MAP(CNeuroLabView, CFormView)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_CUST_FILE_NEW, OnCustFileNew)
	ON_COMMAND(ID_CUST_FILE_OPEN, OnCustFileOpen)
	ON_COMMAND(ID_CUST_FILE_SAVE, OnCustFileSave)
	ON_COMMAND(ID_CUST_FILE_SAVE_AS, OnCustFileSaveAs)
	ON_NOTIFY(TCN_SELCHANGE, IDC_PROPTAB, OnTcnSelchangePropTab)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOLS_DATACREATOR, OnToolsDatacreator)
	ON_COMMAND(ID_TOOLS_NETWORKEXPORRTER, OnExportNetwork)
	ON_COMMAND(ID_USER_GUIDE, OnShowUserGuide)
END_MESSAGE_MAP()

// CNeuroLabView construction/destruction

CNeuroLabView::CNeuroLabView()
	: CFormView(CNeuroLabView::IDD)
{
	// TODO: add construction code here
	mOnTop = NULL;

	mGlobView = this;

	bIsInited = false;

	pPluginsPanelControl = NULL;
	pGroupsContainer = NULL;
	pTrainersContainer = NULL;
}

CNeuroLabView::~CNeuroLabView()
{
}

void CNeuroLabView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ELEMENTSTREE, mElements);
	DDX_Control(pDX, IDC_PROPTAB, mPropTab);
}

BOOL CNeuroLabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CNeuroLabView::QueryComponents()
{
	IAppController* pAppController = NULL;
	QueryInterface(IDD_IAppController, (void**)&pAppController);

	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();

	pAppMain->mComponents.SetAppController(pAppController);
	pAppMain->mComponents.FillComponentsTable();
	pAppMain->mAppLoader.SetComponentsContainer(&pAppMain->mComponents);
	pAppMain->mAppLoader.ProcessLoadingComponents();

	IComponent* pComponent = pAppMain->mComponents.GetComponentByName(CString("PluginsManager"));
	if (pComponent)
		pComponent->QueryInterface(IDD_IPluginsPanelControl, (void**)&pPluginsPanelControl);

	pComponent = pAppMain->mComponents.GetComponentByName(CString("BuilderElements"));
	if (pComponent)
		pComponent->QueryInterface(IDD_IGroupsContainer, (void**)&pGroupsContainer);	

	pComponent = pAppMain->mComponents.GetComponentByName(CString("NetworkTrainers"));
	if (pComponent)
		pComponent->QueryInterface(IDD_ITrainersContainer, (void**)&pTrainersContainer);	
}

void CNeuroLabView::CreateEnvironemtControls()
{
	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();
	CNeuroLabDoc* pDoc = GetDocument();

	IElementsCollection* pCollection = NULL;
	pDoc->mFactory.QueryInterface(IDD_IElementsCollection, (void**)&pCollection);

	IAppController* pAppController = NULL;
	QueryInterface(IDD_IAppController, (void**)&pAppController);
	
	CRect tmBuilderRect(10, 30, 700, 500);
	mBuilder.SetAppFolder(pAppMain->GetAppFolder());
	mBuilder.CreateBuilder(tmBuilderRect, this, IDR_BUILDERCTRL);	
	mBuilder.SetAppController(pAppController);

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("Element Properties");
	mPropTab.InsertItem(0, &tcItem);

	tcItem.pszText = _T("Neuron Functions");
	mPropTab.InsertItem(1, &tcItem);

	tcItem.pszText = _T("Training Network");
	mPropTab.InsertItem(2, &tcItem);

	tcItem.pszText = _T("Network Verification");
	mPropTab.InsertItem(3, &tcItem);

	tcItem.pszText = _T("Plugin Bar");
	mPropTab.InsertItem(PLUGIN_BAR_TAB_INDEX, &tcItem);

	CRect rect;
	IBuilderControl* pBuilderControl = NULL;
	mBuilder.QueryInterface(IDD_IBuilderControl, (void**)&pBuilderControl);

	mNeuronPropDlg.SetBuilderControl(pBuilderControl);
	mNeuronPropDlg.Create(CNeuronPropDlg::IDD, &mPropTab);
	mNeuronPropDlg.GetWindowRect(&rect);
	mNeuronPropDlg.MoveWindow(3, 23, rect.Width(), rect.Height());
	mNeuronPropDlg.ShowWindow(SW_SHOW);

	mOnTop = (CDialog*)&mNeuronPropDlg;

	mNeuronFuncDlg.Create(CNeuronFuncDlg::IDD, &mPropTab);
	mNeuronFuncDlg.GetWindowRect(&rect);
	mNeuronFuncDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mTrainingNetworkDlg.SetAppController(pAppController);
	mTrainingNetworkDlg.SetTrainersContainer(pTrainersContainer);
	mTrainingNetworkDlg.Create(CTrainingNetworkDlg::IDD, &mPropTab);
	mTrainingNetworkDlg.GetWindowRect(&rect);
	mTrainingNetworkDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mNetworkVerificationDlg.SetAppController(pAppController);
	mNetworkVerificationDlg.Create(CNetworkVerificationDlg::IDD, &mPropTab);
	mNetworkVerificationDlg.GetWindowRect(&rect);
	mNetworkVerificationDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mNoBarDlg.Create(CNoBarToShowDlg::IDD, &mPropTab);
	mNoBarDlg.GetWindowRect(&rect);
	mNoBarDlg.MoveWindow(3, 23, rect.Width(), rect.Height());

	mTopPluginBar = (CDialog*)&mNoBarDlg;

	rect = CRect(3, 3, 100, 27);
	mBuilderTitle.SetMediaDirectory(CString("Media\\UI\\Images"));
	mBuilderTitle.Create(NULL, _T("Builder Workspace    "), WS_VISIBLE, rect, this, IDC_BUILDER_INFO);
	mBuilderTitle.SetBarPopupMenu(IDR_BUILDERPOPUP, 0);

	mBuilderTitle.SetToolTipText(
		CString("You can use this zone for:\n   - Placing neurons, layers and data flow elements.\n   - Establishing requierd connections.\n   - Configuring elements' properties."), 
		ID_TOOLTIP_NBINFO,
		CString("Builder Workshop Usage."));
	mBuilderTitle.SetRightPanelTips(CString("Use the menu to get access to most common Builder functions."), ID_TOOLTIP_NBINFO_RIGHT);

	mBuilderTitle.AddIcon(IDI_TB_MAIN_NEWFILE, ID_CUST_FILE_NEW);
	mBuilderTitle.AddIcon(IDI_TB_MAIN_OPENFILE, ID_CUST_FILE_OPEN);
	mBuilderTitle.AddIcon(IDI_TB_MAIN_SAVEFILE, ID_CUST_FILE_SAVE);
	mBuilderTitle.AddButton(CString(_T("")), -1, BT_SEPARATOR);
	mBuilderTitle.AddIcon(IDI_TB_MAIN_ABOUT, ID_APP_ABOUT);

	rect = CRect(3, 3, 250, 27);
	mToolsInfo.SetMediaDirectory(CString("Media\\UI\\Images"));
	mToolsInfo.Create(NULL, "Network Elements Toolbox", WS_VISIBLE, rect, this, IDC_TOOLS_INFO);

	mToolsInfo.SetToolTipText(
		CString("Toolbox contains all necessary elements for building \nnetwork. Simply drag elements from this area to Builder \nWorkshop zone to add required element."),
		ID_TOOLTIP_TBINFO,
		CString("Network Elements Toolbox Usage."));
	mToolsInfo.SetRightPanelTips(CString("Use the menu to get access to most common Toolbox functions."), ID_TOOLTIP_TBINFO_RIGHT);

	if (pPluginsPanelControl)
	{
		pPluginsPanelControl->CreatePanelDlg(this);
		pPluginsPanelControl->ShowPanel(SW_SHOW);	
	}
}

void CNeuroLabView::FillElementsPanel()
{
	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();

	HTREEITEM htiElRoot = mElements.InsertItem(_T("Network elements"), TVI_ROOT);
	mElements.SetDragAcceptWnd(&mBuilder);

	if (pGroupsContainer)
	{
		// Initializing elements container
		IBuilderControl* pBuilderControl = NULL;
		mBuilder.QueryInterface(IDD_IBuilderControl, (void**)&pBuilderControl);

		pGroupsContainer->SetBuilderControl(pBuilderControl);
		pGroupsContainer->SetMediaDirectory(CString("Media\\BuilderCommon"));

		pGroupsContainer->ProcessLoadMediaData();

		// Enumerating groups of elements and preparing toolbox tree
		pGroupsContainer->CreateEnumerator();
		while (IElementsContainer* pElContainer = pGroupsContainer->GetNextContainer())
		{
			HTREEITEM htiGroupRoot = mElements.InsertItem(pElContainer->GetTitle(), htiElRoot);

			pElContainer->CreateEnumerator();
			while (sElement* pElement = pElContainer->GetNextElement())
			{
				ItemDataStruct*	idsItem = new ItemDataStruct;
				idsItem->ItemData = pElement;
				idsItem->IsDraggingEnabled = true;
				idsItem->Dragged = onDragItemToNeuroBuilder;
				
				mElements.InsertActiveItem(pElement->csTitle, idsItem, htiGroupRoot);
			}	

			//mElements.Expand(htiGroupRoot, TVE_EXPAND);
		}	
		mElements.Expand(htiElRoot, TVE_EXPAND);
	}
}

#pragma code_seg(push,  r1, ".secure")
void CNeuroLabView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	QueryComponents();

	CreateEnvironemtControls();

	FillElementsPanel();

	bIsInited = true;
}
#pragma code_seg(pop, r1)

void CNeuroLabView::AddElement(sElement* ObjData)
{
	CNeuroLabDoc* pDoc = GetDocument();

	CPoint tmPoint;
	GetCursorPos(&tmPoint);
	mBuilder.ScreenToClient(&tmPoint);

	IElement* pElement = pGroupsContainer->CreateElement(ObjData);
	if (!pElement)
		return;

	tmPoint = mBuilder.AttachElementToGrid(tmPoint, true);
	
	IBuilderElement* pBuilderElement = NULL;
	pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
	pBuilderElement->SetElementPosition(tmPoint);
	
	pDoc->mFactory.AddElement(pElement);
	
	mBuilder.SelectElement(pElement);
	mBuilder.Invalidate();
}

// CNeuroLabView diagnostics

#ifdef _DEBUG
void CNeuroLabView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNeuroLabView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNeuroLabDoc* CNeuroLabView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNeuroLabDoc)));
	return (CNeuroLabDoc*)m_pDocument;
}
#endif //_DEBUG


// CNeuroLabView message handlers

BOOL CNeuroLabView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL	bRet = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	return bRet;
}

void CNeuroLabView::OnCustFileOpen(void)
{
	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Project File v1.0|*.nlproj||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		CFile cfLoadFile;
		if (cfLoadFile.Open(mFileDlg.GetPathName(), CFile::modeRead, NULL))
		{
			CArchive ar(&cfLoadFile, CArchive::load);
			if (GetDocument()->mFactory.Serialize(ar))
			{			
				mNeuronPropDlg.ShowElement(NULL);
				mBuilder.SelectElement(NULL);

				csOpenedFile = mFileDlg.GetPathName();
				UpdateAppTitle();			
			} else
				AfxMessageBox("Loading terminated. Wrong project file.");
		
			ar.Close();
			cfLoadFile.Close();
		}		

		Invalidate();
	}
}

void CNeuroLabView::OnCustFileSave(void)
{
	if (csOpenedFile.GetLength() > 0)
	{
		CFile cfSaveFile;
		if (cfSaveFile.Open(csOpenedFile, CFile::modeCreate|CFile::modeWrite, NULL))
		{
			CArchive ar(&cfSaveFile, CArchive::store);
			GetDocument()->mFactory.Serialize(ar);
			ar.Close();
			cfSaveFile.Close();
		}			
	} else
	{
		OnCustFileSaveAs();
	}
}

void CNeuroLabView::OnCustFileSaveAs(void)
{
	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Project File v1.0|*.nlproj||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		CFile cfSaveFile;
		if (cfSaveFile.Open(mFileDlg.GetPathName(), CFile::modeCreate|CFile::modeWrite, NULL))
		{
			csOpenedFile = mFileDlg.GetPathName();

			CArchive ar(&cfSaveFile, CArchive::store);
			GetDocument()->mFactory.Serialize(ar);
			ar.Close();
			cfSaveFile.Close();

			UpdateAppTitle();
		}		
	}
}

void CNeuroLabView::OnAppAbout(void)
{
    ((CNeuroLabApp*)AfxGetApp())->OnAppAbout();
}

void CNeuroLabView::OnCustFileNew(void)
{	
	GetDocument()->mFactory.ReleaseElementsList();

	csOpenedFile = "";
	UpdateAppTitle();

	mNeuronPropDlg.ShowElement(NULL);
	mBuilder.SelectElement(NULL);

	Invalidate();
}

void CNeuroLabView::UpdateAppTitle(void)
{
	CString	csTitle = "Neuro Laboratory";
	if (csOpenedFile.GetLength() > 0)
		csTitle += CString(" - ") + csOpenedFile;
	
	AfxGetMainWnd()->SetWindowText(csTitle);
}

void CNeuroLabView::OnTcnSelchangePropTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (mOnTop)
		mOnTop->ShowWindow(SW_HIDE); 
	switch(mPropTab.GetCurSel())	
	{
	case 0:
		mOnTop = (CDialog*)&mNeuronPropDlg;
		break;
	case 1:
		mOnTop = (CDialog*)&mNeuronFuncDlg;
		break;
	case 2:
		mOnTop = (CDialog*)&mTrainingNetworkDlg;
		break;
	case 3:
		mOnTop = (CDialog*)&mNetworkVerificationDlg;
		break;
	case PLUGIN_BAR_TAB_INDEX:
		mOnTop = (CDialog*)mTopPluginBar;
		break;
	default:
		mOnTop = NULL;
	}
	if (mOnTop && mOnTop->m_hWnd)
		mOnTop->ShowWindow(SW_SHOW);		

	*pResult = 0;
}

BOOL CNeuroLabView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CFormView::OnEraseBkgnd(pDC);
}

void CNeuroLabView::SizePropDialog(CDialog* pDialog)
{
	CRect rProps;
	mPropTab.GetClientRect(&rProps);

	CRect	rPrepared(rProps.left + 3, rProps.top + 23, rProps.right - 5, rProps.bottom - 5);
	pDialog->MoveWindow(&rPrepared);
}

void CNeuroLabView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (bIsInited)
	{
		CRect	rToolsTitle;
		CRect	rBuilderTitle;
		mBuilderTitle.GetClientRect(&rBuilderTitle);
		mBuilderTitle.ClientToScreen(&rBuilderTitle);
		ScreenToClient(&rBuilderTitle);
		mToolsInfo.GetClientRect(&rToolsTitle);
		mToolsInfo.ClientToScreen(&rToolsTitle);
		ScreenToClient(&rToolsTitle);
        
		CRect	rProps;
		mPropTab.GetClientRect(&rProps);
		mPropTab.ClientToScreen(&rProps);
		ScreenToClient(&rProps);

		CRect	rElements;
		mElements.GetWindowRect(&rElements);
		ScreenToClient(&rElements);
        
		mPropTab.MoveWindow(3, cy - 3 - rProps.Height(), 
			cx - 6 - rToolsTitle.Width(), rProps.Height());

		SizePropDialog(&mNeuronPropDlg);
		SizePropDialog(&mNeuronFuncDlg);
		SizePropDialog(&mTrainingNetworkDlg);
		SizePropDialog(&mNetworkVerificationDlg);
		SizePropDialog(&mNoBarDlg);


		if (mTopPluginBar != &mNoBarDlg)
			SizePropDialog(mTopPluginBar);		

	    mToolsInfo.MoveWindow(cx - 3 - rToolsTitle.Width(), rToolsTitle.top, 
			rToolsTitle.Width(), rToolsTitle.Height());

		mElements.MoveWindow(cx - 3 - rToolsTitle.Width(), rToolsTitle.bottom + 3, 
			rToolsTitle.Width(), rElements.Height());

	    mBuilderTitle.MoveWindow(3, rBuilderTitle.top, 
			cx - 9 - rToolsTitle.Width(), rBuilderTitle.Height());

		mBuilder.MoveWindow(3, rBuilderTitle.bottom + 3, 
			cx - 9 - rToolsTitle.Width(), cy - 12 - rProps.Height() - rBuilderTitle.Height());

		if (pPluginsPanelControl)
		{
			CRect rPanelRect;
			pPluginsPanelControl->GetPanelRect(&rPanelRect);
			pPluginsPanelControl->MovePanel(cx - 3 - rToolsTitle.Width(), rToolsTitle.bottom + 3 + rElements.Height() + 10,
				rToolsTitle.Width(), rPanelRect.Height());
		}
	}

	// TODO: Add your message handler code here
}

// IAppEnvironmentController declarations section
void CNeuroLabView::ExecuteCallback(PCALLBACK_ROUTIME pfnRoutine, DWORD dwData)
{
	(*pfnRoutine)(dwData);
}

void CNeuroLabView::ShowElementProperties(IElement* pElement)
{
	mNeuronPropDlg.ShowElement(pElement);
}

void CNeuroLabView::CreatePluginBar(CDialog* pPluginBar, int iIDD)
{
	CRect rBarRect;
	pPluginBar->Create(iIDD, (CWnd*)&mPropTab);
	pPluginBar->GetClientRect(&rBarRect);
	pPluginBar->MoveWindow(3, 23, rBarRect.Width(), rBarRect.Height());
}

void CNeuroLabView::ShowPluginBar(CDialog* pPluginBar, CString& csBarTitle)
{
	if (mTopPluginBar && bIsInited && pPluginBar)
		mTopPluginBar->ShowWindow(SW_HIDE);
	mTopPluginBar = pPluginBar;

	CString csBarItemTitle;

	if (!mTopPluginBar)
	{
		mTopPluginBar = (CDialog*)&mNoBarDlg;
		csBarItemTitle = _T("Plugin Bar");
	}
	else
	{
		csBarItemTitle = csBarTitle;		
		if (bIsInited)
			SizePropDialog(pPluginBar);
	}

	if (bIsInited)
	{
		if (pPluginBar)
		{
			TCITEM tcItem;
			tcItem.mask = TCIF_TEXT;
			tcItem.pszText = csBarItemTitle.GetBuffer();
			mPropTab.SetItem(PLUGIN_BAR_TAB_INDEX, &tcItem);
		}

		if (mPropTab.GetCurSel() == PLUGIN_BAR_TAB_INDEX)
		{
			mTopPluginBar->ShowWindow(SW_SHOW);
			mOnTop = mTopPluginBar;
		}
	}
}

// IObject declarations section
CString	CNeuroLabView::GetClassString()
{
	return _T("CNeuroLabView");
}

void CNeuroLabView::QueryInterface(int iIDD, void** ppvObject)
{
	CNeuroLabDoc* pDoc = GetDocument();

	*ppvObject = NULL;

	mBuilder.QueryInterface(iIDD, ppvObject);
	if (*ppvObject)
		return;
	pDoc->mFactory.QueryInterface(iIDD, ppvObject);
	if (*ppvObject)
		return;

	switch(iIDD)
	{
	case IDD_IAppController:
		*ppvObject = (IAppController*)this;
		break;
	}
}

BOOL CNeuroLabView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	mBuilder.SendMessage(WM_COMMAND, wParam, lParam);

	return __super::OnCommand(wParam, lParam);
}

void CNeuroLabView::OnToolsDatacreator()
{
	// TODO: Add your command handler code here

	CString csToolAppPath = ((CNeuroLabApp*)AfxGetApp())->GetAppFolder()+CString("\\DataCreator.exe");

	STARTUPINFO tmStartupInfo = {sizeof(tmStartupInfo)};
	PROCESS_INFORMATION tmProcessInformation;

	BOOL bRet = CreateProcess(csToolAppPath, NULL, 
		NULL, NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL, 
		&tmStartupInfo, 
		&tmProcessInformation);

	if (!bRet)
		AfxMessageBox("Data Creator tool was not properly installed.");

	CloseHandle(tmProcessInformation.hThread);
	CloseHandle(tmProcessInformation.hProcess);
}

void CNeuroLabView::OnExportNetwork()
{
	CString csToolAppPath = ((CNeuroLabApp*)AfxGetApp())->GetAppFolder()+CString("\\NetworkExporter.exe");

	// Saving temporary project file
    char lpPathBuffer[4096];
    DWORD  dwBufSize = 4096;

	GetTempPath(dwBufSize,   // length of the buffer
         lpPathBuffer);      // buffer for path

	COleDateTime tmTime = COleDateTime::GetCurrentTime();	
	CString csTime = tmTime.Format("%H.%M.%S_%d.%m.%Y");

	CString csTempProjectFileName = 
		CString(_T(lpPathBuffer)) + 
		CString(_T("\\")) + 
		CString(_T("NeuroLab_Project_")) + 
		csTime + 
		CString(_T(".nlproj"));
	
	CFile cfSaveFile;
	if (cfSaveFile.Open(csTempProjectFileName, 
		CFile::modeCreate|CFile::modeWrite, NULL))
	{
		CArchive ar(&cfSaveFile, CArchive::store);
		GetDocument()->mFactory.Serialize(ar);
		ar.Close();
		cfSaveFile.Close();
	} else
	{
		AfxMessageBox("Error saving temporary project file.");
		return;
	}

	CString csAppCmdLine = 
		csToolAppPath + 
		CString(_T(" ")) + 
		csTempProjectFileName;

	STARTUPINFO tmStartupInfo = {sizeof(tmStartupInfo)};
	PROCESS_INFORMATION tmProcessInformation;

	BOOL bRet = CreateProcess(csToolAppPath, (LPSTR)csAppCmdLine.GetBuffer(), 
		NULL, NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL, 
		&tmStartupInfo, 
		&tmProcessInformation);

	if (!bRet)
		AfxMessageBox("Network Creator tool was not properly installed.");

	CloseHandle(tmProcessInformation.hThread);
	CloseHandle(tmProcessInformation.hProcess);	
}

void CNeuroLabView::OnShowUserGuide()
{
	// TODO: Add your command handler code here
	CString csUserGuidePath = ((CNeuroLabApp*)AfxGetApp())->GetAppFolder()+CString("\\Documentation\\Neuro Laboratory - User Guide.chm");

	ShellExecute(NULL, "open", csUserGuidePath, NULL, "", SW_MAXIMIZE);
}