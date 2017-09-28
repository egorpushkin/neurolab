#pragma once

#include "..\..\Resource.h"
#include "afxwin.h"
// CDataImageCtrlPropDlg dialog

class CDataImageCtrlPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataImageCtrlPropDlg)

public:
	CDataImageCtrlPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataImageCtrlPropDlg();

// Dialog Data
	enum { IDD = IDD_DATA_IMAGE_CTRL_PROP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mDataLength;
	int mXDimension;
	int mYDimension;
	float mMinDataValue;
	float mMaxDataValue;
	int mRedComponent;
	int mGreenComponent;
	int mBlueComponent;
	BOOL mUseRedMask;
	BOOL mUseGreenMask;
	BOOL mUseBlueMask;
	afx_msg void OnBnClickedUseMaskRed();
	afx_msg void OnBnClickedUseMaskGreen();
	afx_msg void OnBnClickedUseMaskBlue();
	CEdit mRedComponentCtrl;
	CEdit mGreenComponentCtrl;
	CEdit mBlueComponentCtrl;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	BOOL mShowGrid;
	BOOL mShowInfo;
};
