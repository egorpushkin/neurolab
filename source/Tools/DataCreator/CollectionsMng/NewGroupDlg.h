#pragma once


// CNewGroupDlg dialog

class CNewGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewGroupDlg)

public:
	CNewGroupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewGroupDlg();

// Dialog Data
	enum { IDD = IDD_NEW_GROUP_DLG };

	CString			mWmdTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mGroupName;
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
