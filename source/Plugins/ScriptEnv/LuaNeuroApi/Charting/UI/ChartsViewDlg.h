#pragma once
#include "afxwin.h"

#include <string>

// CChartsViewDlg dialog

class CChartsViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CChartsViewDlg)

public:
	CChartsViewDlg(const std::string& name = _T(""), CWnd* pParent = NULL);   // standard constructor
	virtual ~CChartsViewDlg();

	bool IsDisplayed();
	void SafeInvalideteChart();
	void HandleRemove();

protected:
	virtual void			DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void			OnCancel();
	virtual void			OnOK();
	virtual BOOL			OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void			OnLbnSelchangeChartsList();
	afx_msg void			OnBnClickedOntop();
	
	// Custom operations
	//////////////////////////////////////////////////////////////////////////
	void					UpdateAlwaysOnTopButton();

private:
	// Dialog Data
	//////////////////////////////////////////////////////////////////////////
	const std::string		name_;

	enum { IDD = IDD_CHARTING_MAIN };

	bool					alwaysOnTop_;

	CButton					onTopBtn_;

	bool					displayed_;
	bool					removeAtExit_;

public:

	Simple2dCharting::ChartCwndCtrl chartCtrl_;

};
