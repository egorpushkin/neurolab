// AreasBuilderView.h : interface of the CAreasBuilderView class
//
#pragma once

#include "UI/Controls/BrowserControl.h"

class CAreasBuilderView : public CFormView
{
protected: // create from serialization only
	CAreasBuilderView();
	DECLARE_DYNCREATE(CAreasBuilderView)

// Attributes
public:
	CAreasBuilderDoc* GetDocument() const;

public:
	enum{ IDD = IDD_MAIN_APP_VIEW };

	BrowserControl		browserControl_;

	CString				appFolder_;

	void				DoDisplayProject();
	void				DoCloseProject();

	void				AddProjectLogMessage(const String& message);

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CAreasBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
	afx_msg void OnFileCloseProject();
	afx_msg void OnProjectBuild();
};

#ifndef _DEBUG  // debug version in AreasBuilderView.cpp
inline CAreasBuilderDoc* CAreasBuilderView::GetDocument() const
   { return reinterpret_cast<CAreasBuilderDoc*>(m_pDocument); }
#endif

