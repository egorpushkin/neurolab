// NetworkExporterDlg.h : header file
//

#pragma once

#include "ExportSolution\ExportSolution.h"

// CNetworkExporterDlg dialog
class CNetworkExporterDlg : public CDialog
{
// Construction
public:
	CNetworkExporterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NETWORKEXPORTER_DIALOG };

	CString				csNeuroLabProjectFile;
	CExportSolution		mExportSolution;

	void				ShowUserGuide();
	void				ShowSDKDocumentation();

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
public:
	afx_msg void OnBnClickedBrowseProjectFileName();
	afx_msg void OnBnClickedBrowseDestinationFolder();
	CString mCustomProjectFileName;
	CString mDestinationFolder;
	afx_msg void OnBnClickedExportDetails();
	afx_msg void OnBnClickedProcessExport();
};
