#pragma once

#include "CmnElement.h"

// CNeuronQuickInfoDlg dialog
#include "UIControls\\FuncShowCtrl.h"
#include "StandartControls\BkGrSliderCtrl.h"

class CNeuronQuickInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CNeuronQuickInfoDlg)

public:
	void	ShowElement(IElement* pElementObj, CPoint& point);

	CNeuronQuickInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNeuronQuickInfoDlg();

	CFuncShowCtrl	mFuncShow;

// Dialog Data
	enum { IDD = IDD_NEURONQUICKINFODLG };

private:
	IElement*		pElement;

	int				iTimeElapsed;
	CPoint			pntCurPoint;

	void			ShowDlgWnd();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL Create(int iIDD, CWnd* pParentWnd = NULL);
	afx_msg void OnTimer(UINT nIDEvent);
	CString mFunctionName;
	int mDendrCount;
	int mAxonsCount;
	CString mFuncExpr;
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	CString mElementType;
	CString mElementName;
	CString mSystemName;
	int mElementID;
	CString mRequiresData;
	int mDataLength;
	CBkGrSliderCtrl mFuncViewScale;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
