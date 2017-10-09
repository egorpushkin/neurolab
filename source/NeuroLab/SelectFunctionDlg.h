#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSelectFunctionDlg dialog
#include "StandartControls\\ATreeCtrl.h"

void OnNPSelectFunction(void * Param);
void OnNPSelectFunctionAddit(void * Param);

class CSelectFunctionDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectFunctionDlg)

public:
	CSelectFunctionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectFunctionDlg();

	HTREEITEM			htiBaseRoot;
	sFunction*			pSelectedFunction;

// Dialog Data
	enum { IDD = IDD_SELECTFUNCTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CATreeCtrl mFnList;
	CEdit mFnExpression;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnNMDblclkFntree(NMHDR *pNMHDR, LRESULT *pResult);
};
