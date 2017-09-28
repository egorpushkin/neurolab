
#pragma once
#include "afxcmn.h"

#include "StandartControls\ATreeCtrl.h"
// CNeuronFuncDlg dialog

#include "UIControls\FuncShowCtrl.h"
#include "afxwin.h"

void OnSelectFunction(void * Param);
void OnSelectFunctionAddit(void * Param);

class CNeuronFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CNeuronFuncDlg)

public:
	HTREEITEM htiBaseRoot;

	CFuncShowCtrl	mFuncShow;

	CNeuronFuncDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNeuronFuncDlg();

// Dialog Data
	enum { IDD = IDD_NEURONFUNCTIONSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl mFuncList;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL Create(int iID, CWnd* pParentWnd = NULL);
	CATreeCtrl mFuncTree;
	CButton mCtrlConfigure;
	afx_msg void OnBnClickedFuncconfigure();
	afx_msg void OnNMDblclkFunctionstree(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl mFuncViewScale;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
