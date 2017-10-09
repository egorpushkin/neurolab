#pragma once


// CNewSolutionDlg dialog

class CNewSolutionDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewSolutionDlg)

public:
	CNewSolutionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewSolutionDlg();

// Dialog Data
	enum { IDD = IDD_NEW_SOLUTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mSolutionName;
	CString mFileName;
	afx_msg void OnBnClickedBrowse();
protected:
	virtual void OnOK();
};
