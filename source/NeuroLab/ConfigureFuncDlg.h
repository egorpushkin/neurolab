#pragma once
#include "afxcmn.h"

#include "StandartControls\\EditListCtrl.h"

// CConfigureFuncDlg dialog
bool	IsEnableEditItems(int	iItem, int	iSubItem);

class CConfigureFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigureFuncDlg)

public:
	sFunction * pFunction;

	CConfigureFuncDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigureFuncDlg();

// Dialog Data
	enum { IDD = IDD_CONFIGUREFUNCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEditListCtrl mParameters;
	virtual BOOL OnInitDialog();
	CString mFuncExpr;
protected:
	virtual void OnOK();
};
