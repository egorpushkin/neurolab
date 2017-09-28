// AreasBuilderDoc.cpp : implementation of the CAreasBuilderDoc class
//

#include "stdafx.h"
#include "AreasBuilder.h"
#include "AreasBuilderDoc.h"

#include "MainFrm.h"

#include "UI/Common/Providers.h"
#include ".\areasbuilderdoc.h"

using namespace Workspace;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAreasBuilderDoc

IMPLEMENT_DYNCREATE(CAreasBuilderDoc, CDocument)

BEGIN_MESSAGE_MAP(CAreasBuilderDoc, CDocument)
END_MESSAGE_MAP()


// CAreasBuilderDoc construction/destruction

CAreasBuilderDoc::CAreasBuilderDoc()
	: piAreasProject_(NULL)
{
	// TODO: add one-time construction code here
}

CAreasBuilderDoc::~CAreasBuilderDoc()
{
	DoCloseProject();
}

BOOL CAreasBuilderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CAreasBuilderDoc serialization
void CAreasBuilderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CAreasBuilderDoc diagnostics

#ifdef _DEBUG
void CAreasBuilderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAreasBuilderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAreasBuilderDoc commands
result CAreasBuilderDoc::DoOpenProject(const StringA& fileName)
{
	AreasProject* pProject = new AreasProject;
	piAreasProject_ = QueryTool<AreasProject, IAreasProject>::QueryInterface(pProject, IID_IAreasProject);

	result resultCode = projectParser_.LoadProject(fileName, piAreasProject_);
	if (FAILED(resultCode))
		DoCloseProject();

	return resultCode;
}

void CAreasBuilderDoc::DoCloseProject()
{
	if (piAreasProject_)
	{
		piAreasProject_->Release();

		((CMainFrame*)AfxGetMainWnd())->projectManager_.DisplayLogMessage(ProjectUI::PROJECT_LOG, _T("Project was released."));
	}

	piAreasProject_ = NULL;
}

bool CAreasBuilderDoc::IsOpened()
{
	return (piAreasProject_ != NULL);
}

void CAreasBuilderDoc::SetTitle(LPCTSTR /* lpszTitle */)
{
	CDocument::SetTitle(_T("Demonstration"));	
}
