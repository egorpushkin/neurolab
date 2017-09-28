#pragma once
#include "afxcmn.h"

#include "CmnConverter.h"
// CConvertingProjectDlg dialog

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

class CConvertingProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CConvertingProjectDlg)

public:
	CConvertingProjectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConvertingProjectDlg();

// Dialog Data
	enum { IDD = IDD_DC_TO_DF_DLG };

	void			EnableInterface(BOOL bEnable);
	void			UpdateCollectionInformation();
	void			UpdateDataFileInformation();	
	void			UpdateProjectInformation();	
	void			ShowConverterProjectItems();

	void			ProcessCloseProject();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mProjectContent;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
	virtual void OnOK();

private:
	CCollectionConverter mDataConverter;

	bool bModified;

public:
	afx_msg void OnBnClickedNewProject();
	afx_msg void OnBnClickedCloseProject();
	afx_msg void OnBnClickedLoadProject();
	afx_msg void OnBnClickedSaveProject();
	CString mDCName;
	CString mDFOutputsCount;
	CString mProjectName;
	afx_msg void OnBnClickedAddEntry();
	afx_msg void OnBnClickedEditEntry();
	afx_msg void OnBnClickedRemoveEntry();
	afx_msg void OnBnClickedDataCollectionDetails();
	afx_msg void OnBnClickedDataFileDetails();
	afx_msg void OnBnClickedExportProject();
};
