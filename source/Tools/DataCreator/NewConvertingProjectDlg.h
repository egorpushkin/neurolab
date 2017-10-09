#pragma once

#include "CmnDataFile.h"
#include "DataCollection//DataCollection.h"

// CNewConvertingProjectDlg dialog

class CNewConvertingProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewConvertingProjectDlg)

public:
	CNewConvertingProjectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewConvertingProjectDlg();

// Dialog Data
	enum { IDD = IDD_NEW_CONVERTER_DLG };

	CDataFile		mDataFile;
	CDataCollection	mDataCollection;

	CString			csDataFileName;
	CString			csDataCollectionFileName;

	void			UpdateCollectionInformation();
	void			UpdateDataFileInformation();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mProjectName;
	CString mDCFileName;
	CString mDCName;
	CString mDFFileName;
	int mDFOutputsCount;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedDataCollectionLoad();
	afx_msg void OnBnClickedDataFileLoad();
	afx_msg void OnBnClickedDetailsDataCollection();
	afx_msg void OnBnClickedDeteilsDataFile();
};
