#pragma once


// CProcessNetworkDlg dialog
#include "Resource.h"
#include "afxcmn.h"

#include "CmnApp.h"

bool IsEnableEditItems(int iItem, int iSubItem);

#include "StandartControls\EditListCtrl.h"

class CProcessNetworkDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessNetworkDlg)

public:
	CProcessNetworkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessNetworkDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_NETWORK };

	void			SetAppController(IAppController* pController);

private:
	IAppController* pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEditListCtrl mInputsCtrl;
	CEditListCtrl mOutputsCtrl;
	int mTotalInputs;
	int mTotalOutputs;
	afx_msg void OnBnClickedProcessNetwork();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
