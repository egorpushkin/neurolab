#pragma once
#include "afxcmn.h"

#include "CmnApp.h"
// ProcessHLDlg dialog

#include "Resource.h"

#include "LearnLayerDlg.h"

class CProcessHLDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessHLDlg)

public:
	CProcessHLDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessHLDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_HL_DLG };

	CLearnLayerDlg		mLearnLayerDlg;
	CDialog*			pOnTop;

	void				SetAppController(IAppController* pController)
	{
		pAppController = pController;	
	}

private:
	IAppController*		pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mMainTab;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult);
};
