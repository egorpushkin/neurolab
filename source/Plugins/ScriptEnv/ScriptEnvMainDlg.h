#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// Object Model tools
#include "CmnApp.h"
#include "Common\ScriptSolution.h"

// Network Importing component
#include "NetworkImporter\ImportManagerComponent.h"

// User interface tools
#include "UIControls/InfoBar.h"

#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	// Using advanced edit control
	#include "..\..\ControlsLib\AdvancedEditControl\BCGCBProInc.h"
#endif

// CScriptEnvMainDlg dialog

class CScriptEnvMainDlg
	: public CDialog
{
	DECLARE_DYNAMIC(CScriptEnvMainDlg)

public:
	CScriptEnvMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptEnvMainDlg();

// Dialog Data
	enum { IDD = IDD_SCRIPT_ENV_MAIN_DLG };

// Global Environment
	IAppController*		pAppController;
	CString				csAppFolder;

// Environment Controls
	CInfoBar			mSolutionBar;
	CInfoBar			mWorkspaceBar;
	CInfoBar			mCompileLogBar;

	CTreeCtrl			mSolutionTree;
	CListCtrl			mCompileLogList;
	
	// Solution Workspace		
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	CBCGPEditCtrl		mWorkspaceEdit;
#else
	CEdit				mWorkspaceEdit;
#endif

	CFont				mWorkspaceFont;
	CImageList			mSolutionImageList;
	HACCEL				mAcceleratorsTable;

// Dialog UI Operations 
	void				CreateEnvironmentControls();
	void				LocateControls();
	void				ConfigureLogControl();

	void				UpdateMainWndTitle();
	void				UpdateWorkspaceBarTitle();
	CString				PrepareMainWndTitle();
	CString				PrepareWorkspaceBarTitle();

// Solution Environment Operations 
	void				EnableSolutionControls(BOOL bEnable);

// Solution Tree Configuration & Properties
	void				ShowEmptySolution();
	void				CloseSolution();

	CString				PrepareSolutionName(CString& Name);

	HTREEITEM			htiSolutionItem;
	HTREEITEM			htiScriptsRoot;
	HTREEITEM			htiDataRoot;
	HTREEITEM			htiBitmapsRoot;
	HTREEITEM			htiProjectsRoot;

	CSolutionItem*		pCurrentSolutionItem;

// Building Solution Functions
	void				AddItem(CSolutionItem* pItem);
	void				AddDataItem(CDataFileItem* pItem);
	void				AddBitmapItem(CBitmapItem* pItem);
	void				AddProjectItem(CProjectItem* pItem);

	void				ShowScriptFileInEditor(CSolutionItem* pItem = NULL);
	void				ShowDataFileInEditor(CDataFileItem* pItem);
	void				ShowBitmapInEditor(CBitmapItem* pItem);
	void				ShowProjectInEditor(CProjectItem* pItem);

	void				RemoveScriptFile(HTREEITEM htiItem, CSolutionItem* pItem);
	void				RemoveDataFile(HTREEITEM htiItem, CDataFileItem* pItem);
	void				RemoveBitmap(HTREEITEM htiItem, CBitmapItem* pItem);
	void				RemoveProject(HTREEITEM htiItem, CProjectItem* pItem);

// Solution Operations
	afx_msg void		OnCloseEnvironment();
	afx_msg void		OnNewSolution();
	afx_msg void		OnNewScript();
	afx_msg void		OnCloseSolution();
	afx_msg void		OnCloseCurrentScript();
	afx_msg void		OnOpenSolution();
	afx_msg void		OnSaveSolution();
	afx_msg void		OnAddExistingScript();
	afx_msg void		OnAddExistingDataFile();
	afx_msg void		OnExecuteScript();
	afx_msg void		OnAboutScriptingEnvironment();
	afx_msg void		OnRemoveCurrentItem();
	afx_msg void		OnShowDeveloperGuide();
	afx_msg void		OnShowLuaManual();
	afx_msg void		OnAddExistingBitmap();
	afx_msg void		OnAddExistingNetworkProject();

// Workspace Edit Handlers
	afx_msg void		OnEditCopy();
	afx_msg void		OnEditCut();
	afx_msg void		OnEditPaste();
	afx_msg void		OnEditSelectAll();
	afx_msg void		OnEditUndo();
	afx_msg void		OnEditRedo();

// Solution Tree Handlers
	afx_msg void		OnNMDblclkSolutionTree(NMHDR *pNMHDR, LRESULT *pResult);

// Solution Workspace Handlers
#ifdef USE_SCISOFT_ADVANCED_EDIT_CONTROL
	afx_msg LONG		OnEnChangeWorkspaceEdit(WPARAM wParam, LPARAM lParam);
#else
	afx_msg void		OnEnChangeWorkspaceEdit();
#endif

// Solution Object & Properties
    CScriptSolution		mSolutionObj;
	bool				bIsChanged;

// Network Projects Importing Tool
	CImportManagerComponent		mImportManager;

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void		OnCancel();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL		OnInitDialog();
	virtual BOOL		PreTranslateMessage(MSG* pMsg);
};
