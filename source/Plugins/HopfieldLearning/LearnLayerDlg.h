#pragma once

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

// CLearnLayerDlg dialog
#include "afxwin.h"

#include "CmnApp.h"
#include "afxcmn.h"

#include "CmnDataFile.h"

class CLearnLayerDlg : public CDialog
{
	DECLARE_DYNAMIC(CLearnLayerDlg)

public:
	CLearnLayerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLearnLayerDlg();

// Dialog Data
	enum { IDD = IDD_LEARNING_LAYER_DLG };

	void				EnableDataControlSection(BOOL bEnable);

	CDataImageCtrl		mDataImageCtrl;

	CDataFile			mDataFile;
	void				ReleaseDataSymbols();

	void				EnumerateLayers();

	void				SetAppController(IAppController* pController)
	{
		pAppController = pController;	
	}

	void				AddLogMessage(CString& message);

private:
	IAppController*			pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL Create(int iIDD, CWnd* pParentWnd = NULL);
	CStatic mSymbolsCount;
	CStatic mSymbolNumber;
	CButton mUpShowSymbol;
	CButton mDownShowSymbol;
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedLoadFile();
	CEdit mFileName;
	int mSymbols;
	int mSymbol;
	afx_msg void OnBnClickedUpshow();
	afx_msg void OnBnClickedDownshow();
	CListBox mStudyLog;
	afx_msg void OnBnClickedStudyLayer();
	afx_msg void OnBnClickedResetWeights();
	CButton mResetWeights;
	CButton mStudyLayers;
	CListCtrl mLayersList;
	afx_msg void OnLvnItemchangedLayersList(NMHDR *pNMHDR, LRESULT *pResult);
	CButton mCtrlProp;
	afx_msg void OnBnClickedCtrlProp();
};
