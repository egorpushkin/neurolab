// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AreasBuilder.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

//IMPLEMENT_DYNCREATE(CMainFrame, CGuiFrameWnd)
IMPLEMENT_DYNCREATE(CMainFrame, CGuiMDIFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiMDIFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_THEME_XP, OnViewThemeXP)
	ON_COMMAND(ID_VIEW_THEME_2003, OnViewTheme2003)
	ON_COMMAND(ID_VIEW_PROJECT_EXPLORER, OnViewProjectExplorer)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_COMMAND(ID_VIEW_STEP_BY_STEP_GUIDE, OnViewStepByStepGuide)
	
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiMDIFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitMenu(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	

	EnableDocking(CBRS_ALIGN_ANY);

	if (!projectWorkspacePane_.Create(_T("Project Explorer"), WS_CHILD | WS_VISIBLE, this, IDC_PROJECT_EXPLORER))
	{
		TRACE0("Failed to create projectWorkspacePane_\n");
		return -1;      
	}
	projectWorkspacePane_.SetBarStyle(projectWorkspacePane_.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	projectWorkspacePane_.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&projectWorkspacePane_, AFX_IDW_DOCKBAR_LEFT);

    if (!outputWindowPane_.Create(_T("Output"), WS_CHILD | WS_VISIBLE, this, 0x995))
    {
        TRACE0("Failed to create outputWindowPane_\n");
        return -1;      
    }
    outputWindowPane_.SetBarStyle(outputWindowPane_.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    outputWindowPane_.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&outputWindowPane_, AFX_IDW_DOCKBAR_BOTTOM);

	if (!stepsWindow_.Create(_T("Step-by-Step Guide"), WS_CHILD | WS_VISIBLE, this, IDC_STEPS_WINDOW))
	{
		TRACE0("Failed to create outputWindowPane_\n");
		return -1;      
	}
	stepsWindow_.SetBarStyle(stepsWindow_.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	stepsWindow_.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&stepsWindow_, AFX_IDW_DOCKBAR_RIGHT);
//	stepsWindow_.OnNcLButtonDblClk(0, CPoint(0, 0));

	DockControlBar(&m_wndMenuBar, m_dockTop);
	
	StyleDispl(GUISTYLE_2003);

	InitMDITabbed();

	// Initialize project manager
	//////////////////////////////////////////////////////////////////////////	
	projectManager_.SetProjectTree(&projectWorkspacePane_.mTreeProjectExplorer);

	ProjectUI::ILogOutputManager* piManager = NULL;
	outputWindowPane_.QueryInterface(ProjectUI::IID_ILogOutputManager, (void**)&piManager);
   	projectManager_.SetLogOutputManager(piManager);	
	piManager->Release();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CGuiMDIFrame::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CGuiMDIFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CGuiMDIFrame::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnViewThemeXP()
{
	StyleDispl(GUISTYLE_XP);
}

void CMainFrame::OnViewTheme2003()
{
	StyleDispl(GUISTYLE_2003);
}

void CMainFrame::StyleDispl(DWORD style)
{
	GuiDrawLayer::m_Style = style;

	CGuiMDIFrame::StyleDispl(GuiDrawLayer::m_Style);

	projectWorkspacePane_.StyleDispl(GuiDrawLayer::m_Style);
	outputWindowPane_.StyleDispl(GuiDrawLayer::m_Style);
	stepsWindow_.StyleDispl(GuiDrawLayer::m_Style);
}

void CMainFrame::OnViewProjectExplorer()
{
	ShowHideBar(&projectWorkspacePane_);
}

void CMainFrame::OnViewOutput()
{
	ShowHideBar(&outputWindowPane_);
}

void CMainFrame::OnViewStepByStepGuide()
{
	ShowHideBar(&stepsWindow_);
}

void CMainFrame::OnFileClose()
{
	AfxMessageBox(_T("123"));
}
