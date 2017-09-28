#pragma once

#include "CmnApp.h"
#include "afxcmn.h"

// CProcessSignalsDlg dialog

class CProcessSignalsDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessSignalsDlg)

public:
	CProcessSignalsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessSignalsDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_SIGNALS };

	void			SetAppController(IAppController* pController);

	CDataFactory	mInputCtrlData;
	CDataFactory	mOutputCtrlData;

	int				iInXDimension;
	int				iInYDimension;

private:
	IAppController* pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);

	CButton mInputPropCtrl;
	CButton mInputMarkerCtrl;
	CButton mInputEditorCtrl;

	CDataImageCtrl	mInputCtrl;
	CFuncShowCtrl	mOutputCtrl;

	afx_msg void OnBnClickedInputCtrlEditor();
	afx_msg void OnBnClickedInputCtrlSettings();
	afx_msg void OnBnClickedInputCtrlMarker();
	int mInputsCount;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CSliderCtrl mOutputZoom;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedProcessNetwork();
};
