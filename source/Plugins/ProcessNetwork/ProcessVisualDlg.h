#pragma once

#include "CmnApp.h"
#include "CmnDataFactory.h"

#include "Resource.h"
#include "afxwin.h"

// CProcessVisualDlg dialog

class CProcessVisualDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessVisualDlg)

public:
	CProcessVisualDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessVisualDlg();

// Dialog Data
	enum { IDD = IDD_PROCESS_VISUAL };

	void			SetAppController(IAppController* pController);

private:
	IAppController* pAppController;

	CDataImageCtrl	mInputCtrl;
	CDataImageCtrl	mOutputCtrl;

	CDataFactory	mInputCtrlData;
	CDataFactory	mOutputCtrlData;

	int				iInXDimension;
	int				iInYDimension;
	int				iOutXDimension;
	int				iOutYDimension;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);
	afx_msg void OnBnClickedProcessNetwork();
	afx_msg void OnBnClickedInputCtrlSettings();
	afx_msg void OnBnClickedInputCtrlMarker();
	afx_msg void OnBnClickedOutputCtrlSettings();
	CButton mInputPropCtrl;
	CButton mInputMarkerCtrl;
	CButton mOutputPropCtrl;
	int mInputsCount;
	int mOutputsCount;
	CButton mInputEditorCtrl;
	afx_msg void OnBnClickedInputCtrlEditor();
	float mRequiredTime;
};
