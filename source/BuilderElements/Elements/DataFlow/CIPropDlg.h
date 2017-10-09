#pragma once


// CCIPropDlg dialog

class CCIPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CCIPropDlg)

public:
	CCIPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCIPropDlg();

// Dialog Data
	enum { IDD = IDD_CONSTANT_INPUT_PROP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float mValue;
};
