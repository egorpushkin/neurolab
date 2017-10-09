#pragma once


// CScriptingElementCodeDlg dialog

class CScriptingElementCodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CScriptingElementCodeDlg)

public:
	CScriptingElementCodeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptingElementCodeDlg();

// Dialog Data
	enum { IDD = IDD_SCREL_PROCESS_SCRIPT_DLG };

	CFont			mWorkspaceFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mScriptCode;
	virtual BOOL OnInitDialog();
};
