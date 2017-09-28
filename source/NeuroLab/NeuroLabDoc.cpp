// NeuroLabDoc.cpp : implementation of the CNeuroLabDoc class
//

#include "stdafx.h"
#include "NeuroLab.h"

#include "NeuroLabDoc.h"
#include "NeuroLabView.h"
#include ".\neurolabdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNeuroLabDoc

IMPLEMENT_DYNCREATE(CNeuroLabDoc, CDocument)

BEGIN_MESSAGE_MAP(CNeuroLabDoc, CDocument)
END_MESSAGE_MAP()


// CNeuroLabDoc construction/destruction

CNeuroLabDoc::CNeuroLabDoc()
{
	// TODO: add one-time construction code here

}

CNeuroLabDoc::~CNeuroLabDoc()
{
}

BOOL CNeuroLabDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CNeuroLabDoc serialization

void CNeuroLabDoc::Serialize(CArchive& ar)
{
	/*if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}*/
/*	bool bIsSucceeded = mFactory.Serialize(ar);
	if (!bIsSucceeded && ar.IsLoading())
		AfxMessageBox("Error Loading file.");
	if (!bIsSucceeded && ar.IsStoring())
		AfxMessageBox("Error saving file.");*/
}


// CNeuroLabDoc diagnostics

#ifdef _DEBUG
void CNeuroLabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNeuroLabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNeuroLabDoc commands

void CNeuroLabDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(lpszTitle);
}

void CNeuroLabDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetPathName(lpszPathName, bAddToMRU);
}
