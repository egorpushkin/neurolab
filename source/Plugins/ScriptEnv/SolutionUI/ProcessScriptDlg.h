#pragma once


// CProcessScriptDlg dialog

#include "../Common/ScriptSolution.h"
#include "afxcmn.h"

#include "..\Resource.h"

#include "CmnLog.h"
#include "CmnApp.h"
#include "afxwin.h"

#include "..\NetworkImporter\ImportManagerComponent.h"

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

class CProcessScriptDlg 
	: public CDialog
	, public ILogProvider
{
	DECLARE_DYNAMIC(CProcessScriptDlg)

public:
	CProcessScriptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessScriptDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_SCRIPT_DLG };

// Global Environment
	IAppController*		pAppController;
	CString				csAppFolder;

	CScriptSolution*	pSolutionObj;
	CSolutionItem*		pCurrentSolutionItem;
	CImportManagerComponent*	pImportManagerComponent;

	DWORD_PTR			GetSelectedPriorityLevel();

// Script Execution
	void				EnableControls(BOOL bEnable);
	void				OnFinishScript();

	bool				TryCloseEnvironment();

	// ILogProvider implementations section
	virtual void		ClearLog();
	virtual void		AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CProcessScriptDlg");
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_ILogProvider:
			*ppvObject = (ILogProvider*)this;
			break;
		}
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedStartScript();
	afx_msg void OnBnClickedStopScript();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedSaveLog();

protected:
	virtual void OnCancel();
	virtual void OnOK();

	CString				mFileName;
	CListCtrl			mEventsLog;
	int					mCurrentPercentage;
	CProgressCtrl		mExecutionProgress;
	CStatic				mCtrlCurrentPercentage;
	CComboBox			mScriptPriority;
	CButton				mLogButton;

};
