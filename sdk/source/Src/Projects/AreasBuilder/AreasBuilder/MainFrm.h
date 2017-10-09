// MainFrm.h : interface of the CMainFrame class
//
#pragma once

#include "UI/Panes/ProjectWorkspace.h"
#include "UI/Panes/OutputWindow.h"
#include "UI/Panes/Steps.h"

#include "UI/ProjectManager/ProjectManager.h"

class CMainFrame 
	: public CGuiMDIFrame
{
	friend class CAreasBuilderDoc;
	friend class CAreasBuilderView;
	
public: 
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CProjectWorkspace			projectWorkspacePane_;
   	COutputWindow               outputWindowPane_;
	CSteps						stepsWindow_;

	ProjectUI::ProjectManager	projectManager_;

	void						StyleDispl(DWORD style);

public:
	afx_msg void OnViewThemeXP();
	afx_msg void OnViewTheme2003();
	afx_msg void OnViewProjectExplorer();
	afx_msg void OnViewOutput();
	afx_msg void OnViewStepByStepGuide();

	afx_msg void OnFileClose();
};


