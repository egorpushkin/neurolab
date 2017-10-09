// LicenseMngDlg.h : header file
//

#pragma once

#include "ProductsSolution\ProductsSolution.h"
#include "afxwin.h"

// CLicenseMngDlg dialog
class CLicenseMngDlg : public CDialog
{
// Construction
public:
	CLicenseMngDlg(CString& AppFolder, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LICENSEMNG_DIALOG };

	CProductsSolution			mProductsSolution;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CString						csAppFolder;
public:
	CComboBox					mProductsList;
	afx_msg void OnBnClickedAdvancedOperations();
	afx_msg void OnBnClickedExportPublicKey();
};
