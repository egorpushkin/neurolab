#pragma once

#include "..\Resource.h"
#include "afxwin.h"
// CLoadStatDlg dialog

#include "ComponentsLoader.h"

class CComponentsLoader;

class CLoadStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadStatDlg)

public:
	CLoadStatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoadStatDlg();

// Dialog Data
	enum { IDD = IDD_LOAD_STAT_DLG };

	void SetComponentsLoader(CComponentsLoader * Loader);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic mStatMess;
	afx_msg void OnPaint();

private:
	int					iLoadState;
	CComponentsLoader*	pLoader; 
protected:
	virtual void OnOK();
	virtual void OnCancel();
};