#pragma once
#include "afxcmn.h"

#include "CmnLog.h"

#include "ExportSolution\ExportSolution.h"

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

DWORD ExportSolutionThread(DWORD dwParam);

// CProcessExportDlg dialog

class CProcessExportDlg : public CDialog,
	public ILogProvider
{
	DECLARE_DYNAMIC(CProcessExportDlg)

public:
	CProcessExportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessExportDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_EXPORT_DLG };

	// Support services
	bool					CheckDestinationDirectory();
	
	// Exporting thread data
	HANDLE					hThread;

	void					EnableInterface(BOOL bEnable);
	void					OnFinishExporting();

	// Solution data
	CExportSolution*		pExportSolution;
	CString					csDestinationFolder;

// ILogProvider declarations section
	virtual void			ClearLog();
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mOperationsLogList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedProcessExport();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
