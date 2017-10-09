// AreasBuilderView.cpp : implementation of the CAreasBuilderView class
//

#include "stdafx.h"
#include "AreasBuilder.h"

#include "AreasBuilderDoc.h"
#include "AreasBuilderView.h"
#include ".\areasbuilderview.h"

#include "MainFrm.h"

#include "UI/Common/Providers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAreasBuilderView

IMPLEMENT_DYNCREATE(CAreasBuilderView, CFormView)

BEGIN_MESSAGE_MAP(CAreasBuilderView, CFormView)	
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE_PROJECT, OnFileCloseProject)
	ON_COMMAND(ID_PROJECT_BUILD, OnProjectBuild)
END_MESSAGE_MAP()

// CAreasBuilderView construction/destruction

CAreasBuilderView::CAreasBuilderView()
	: CFormView(CAreasBuilderView::IDD)
{
	// TODO: add construction code here

}

CAreasBuilderView::~CAreasBuilderView()
{
}

BOOL CAreasBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

// CAreasBuilderView drawing

void CAreasBuilderView::OnDraw(CDC* /*pDC*/)
{
	CAreasBuilderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAreasBuilderView diagnostics

#ifdef _DEBUG
void CAreasBuilderView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAreasBuilderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAreasBuilderDoc* CAreasBuilderView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAreasBuilderDoc)));
	return (CAreasBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CAreasBuilderView message handlers

void CAreasBuilderView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// TODO: Add your specialized code here and/or call the base class
	GetModuleFileName(GetModuleHandle(NULL), appFolder_.GetBuffer(MAX_PATH), MAX_PATH);
	appFolder_.ReleaseBuffer();
	int tmPos = appFolder_.ReverseFind('\\');
	appFolder_	= appFolder_.Left(tmPos);	

	CString helpPage = 
		appFolder_ + 
		CString(_T("/UserGuide/index.htm"));

	browserControl_.Navigate(helpPage, NULL, NULL, NULL, NULL);

	((CMainFrame*)AfxGetMainWnd())->projectManager_.DislpayEmptyProject();
}

void CAreasBuilderView::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class
	DDX_Control(pDX, IDC_IWB_HELP_CTRL, browserControl_);

	CFormView::DoDataExchange(pDX);
}

void CAreasBuilderView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (browserControl_.GetSafeHwnd())
	{
		browserControl_.MoveWindow(0, 0, cx, cy);
	}
}

void CAreasBuilderView::OnFileOpen()
{
	if (GetDocument()->IsOpened())
	{
		int res = AfxMessageBox("Are you sure that you want to open project and close currently opened one?", MB_YESNO);
		if (res == IDYES)
		{
			OnFileCloseProject();
		} else
		{
			AddProjectLogMessage(_T("Attempt to open new project disclaimed."));
			return;
		}
	}

	CFileDialog	fileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Areas Builder Project v1.0|*.xml||");
	INT_PTR res = fileDlg.DoModal();
	if (res == IDOK)
	{
		AddProjectLogMessage(_T("Attempting to load project..."));		
		((CMainFrame*)AfxGetMainWnd())->Invalidate();

		if (SUCCEEDED(GetDocument()->DoOpenProject(fileDlg.GetPathName().GetBuffer())))
		{			
			DoDisplayProject();
			AddProjectLogMessage(
				String(_T("Project ")) + 
				String(fileDlg.GetPathName().GetBuffer()) +
				String(_T(" was loaded.")));
		} else
		{
			AddProjectLogMessage(
				String(_T("Error loading project ")) + 
				String(fileDlg.GetPathName().GetBuffer()) +
				String(_T(".")));
		}
	}	
}

void CAreasBuilderView::OnFileCloseProject()
{		
	// Step 1. Destroy project UI tools
	DoCloseProject();

	// Step 2. Release project content
	GetDocument()->DoCloseProject();	
}

void CAreasBuilderView::DoDisplayProject()
{
	((CMainFrame*)AfxGetMainWnd())->projectManager_.DislpayProject(GetDocument()->piAreasProject_);	
}

void CAreasBuilderView::DoCloseProject()
{
	((CMainFrame*)AfxGetMainWnd())->projectManager_.DislpayEmptyProject();
}

void CAreasBuilderView::AddProjectLogMessage(const String& message)
{
	((CMainFrame*)AfxGetMainWnd())->projectManager_.DisplayLogMessage(ProjectUI::PROJECT_LOG, message);
}

void CAreasBuilderView::OnProjectBuild()
{
	((CMainFrame*)AfxGetMainWnd())->projectManager_.BuildDisplayedProject();
}

