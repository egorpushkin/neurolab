#pragma once
#include "afxcmn.h"

#include "CmnLog.h"
// CNetworkVerificationDlg dialog

class CNetworkVerificationDlg 
	: public CDialog
	, public ILogProvider
{
	DECLARE_DYNAMIC(CNetworkVerificationDlg)

public:
	CNetworkVerificationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetworkVerificationDlg();

	void					SetAppController(IAppController* pController);

// Dialog Data
	enum { IDD = IDD_NETWORK_VERIFICATION_DLG };

// ILogProvider declarations section
	virtual void			ClearLog();
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	IAppController*			pAppController;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	CListCtrl mResultsList;
	afx_msg void OnBnClickedVerify();
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);
	int mErrorsCount;
	int mWarningsCount;
};
