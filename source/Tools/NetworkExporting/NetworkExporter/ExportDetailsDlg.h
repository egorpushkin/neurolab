#pragma once

#include "ExportSolution\ExportSolution.h"
#include "afxcmn.h"
// CExportDetailsDlg dialog

class CExportDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CExportDetailsDlg)

public:
	CExportDetailsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExportDetailsDlg();

// Dialog Data
	enum { IDD = IDD_EXPORT_DETAILS };

	void ShowSolution();
	void ShowSolutionItem(IObject* pItemObject);

	CExportSolution*		pExportSolution;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl mSolutionTree;
	CString mVersion;
	CString mType;
	CString mDescription;
	CImageList	mImageList;
	afx_msg void OnTvnSelchangedSolutionTree(NMHDR *pNMHDR, LRESULT *pResult);
};
