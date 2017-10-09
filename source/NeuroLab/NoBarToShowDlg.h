#pragma once


// CNoBarToShowDlg dialog

class CNoBarToShowDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoBarToShowDlg)

public:
	CNoBarToShowDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNoBarToShowDlg();

// Dialog Data
	enum { IDD = IDD_NO_PLUGIN_BAR_TO_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
