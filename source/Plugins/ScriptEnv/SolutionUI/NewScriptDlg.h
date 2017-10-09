#pragma once


// CNewScriptDlg dialog

class CNewScriptDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewScriptDlg)

public:
	CNewScriptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewScriptDlg();

// Dialog Data
	enum { IDD = IDD_NEW_SCRIPT_DLG };

	bool bNewScript;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowse();
	CString mFileName;
protected:
	virtual void OnOK();
};
