// NeuroLabView.h : interface of the CNeuroLabView class
//

#pragma once

#include "afxcmn.h"

#include "Builder\Builder.h"
#include "StandartControls\ATreeCtrl.h"
#include "UIControls\InfoBar.h"

#include "Components\ComponentsContainer.h"

#include "NoBarToShowDlg.h"
#include "NeuronPropDlg.h"
#include "NeuronFuncDlg.h"
#include "TrainingNetworkDlg.h"
#include "NetworkVerificationDlg.h"

void	onDragItemToNeuroBuilder(void * Param);

#include "CmnApp.h"
#include "CmnTrainers.h"

class CNeuroLabView : public CFormView, 
	public IAppController
{
protected: // create from serialization only
	CNeuroLabView();
	DECLARE_DYNCREATE(CNeuroLabView)

public:

	CInfoBar			mToolsInfo;
	CInfoBar			mBuilderTitle;

	CBuilder			mBuilder;

	CString				csOpenedFile;

	CNoBarToShowDlg			mNoBarDlg;
	CNeuronPropDlg			mNeuronPropDlg;
	CNeuronFuncDlg			mNeuronFuncDlg;
	CTrainingNetworkDlg		mTrainingNetworkDlg;
	CNetworkVerificationDlg	mNetworkVerificationDlg;

	CDialog*			mOnTop;
	CDialog*			mTopPluginBar;

	bool				bIsInited;

	IPluginsPanelControl*	pPluginsPanelControl;
	IGroupsContainer*		pGroupsContainer;
	ITrainersContainer*		pTrainersContainer;

	void				QueryComponents();
	void				CreateEnvironemtControls();
	void				FillElementsPanel();

	void				AddElement(sElement* ObjData);

	void				SizePropDialog(CDialog* pDialog);

	virtual void			ShowElementProperties(IElement* pElement);

	enum{ IDD = IDD_NEUROLAB_FORM };

// Attributes
public:
	CNeuroLabDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CNeuroLabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	CATreeCtrl mElements;
	void OnAppAbout(void);
	void OnCustFileOpen(void);
	void OnCustFileSave(void);
	void OnCustFileSaveAs(void);
	void OnCustFileNew(void);
	void UpdateAppTitle(void);
	CTabCtrl mPropTab;
	afx_msg void OnTcnSelchangePropTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

// IAppEnvironmentController declarations section
public:
	virtual void			ExecuteCallback(PCALLBACK_ROUTIME pfnRoutine, DWORD dwData);

	virtual void			CreatePluginBar(CDialog* pPluginBar, int iIDD);
	virtual void			ShowPluginBar(CDialog* pPluginBar, CString& csBarTitle);

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnToolsDatacreator();
	afx_msg void OnShowUserGuide();
	afx_msg void OnExportNetwork();
};

#ifndef _DEBUG  // debug version in NeuroLabView.cpp
inline CNeuroLabDoc* CNeuroLabView::GetDocument() const
   { return reinterpret_cast<CNeuroLabDoc*>(m_pDocument); }
#endif

