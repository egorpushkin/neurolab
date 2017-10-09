#pragma once
#include "afxwin.h"


// CAdvOperationsDlg dialog

class CAdvOperationsDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdvOperationsDlg)

public:
	CAdvOperationsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdvOperationsDlg();

// Dialog Data
	enum { IDD = IDD_ADVENCED_OPERATIONS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mOperationType;
	virtual BOOL OnInitDialog();
	CString mKeyContainerName;
	afx_msg void OnBnClickedPerformOperation();
};
