#pragma once

#include "CmnApp.h"
#include "afxcmn.h"

// CLayersExporterDlg dialog
class CLayersExporterDlg : public CDialog
{
	DECLARE_DYNAMIC(CLayersExporterDlg)

public:
	CLayersExporterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLayersExporterDlg();

// Dialog Data
	enum { IDD = IDD_LAYERS_EXPORTER_DLG };

// UI Control Variables
	CListCtrl				mLayersList;

public:
// Global Environment
	IAppController*			pAppController;



protected:
	virtual void			DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL			OnInitDialog();

// UI Operations
	afx_msg void			OnBnClickedExportLayerData();
	afx_msg void			OnBnClickedImportLayerData();
	afx_msg void			OnBnClickedAbout();
	afx_msg void			OnLvnItemchangedLayersList(NMHDR *pNMHDR, LRESULT *pResult);

	void					EnableLayerOperations(BOOL bEnable);
};
