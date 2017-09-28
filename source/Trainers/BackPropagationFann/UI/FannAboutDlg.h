#pragma once

#include "Resource.h"

// CFannAboutDlg dialog

class CFannAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CFannAboutDlg)

public:
	CFannAboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFannAboutDlg();

// Dialog Data
	enum { IDD = IDD_FANN_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
