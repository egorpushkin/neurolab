#pragma once

#include "Resource.h"
// CVerificationDlg dialog

#include "afxcmn.h"

#include "CmnDataFile.h"

#include "CmnApp.h"
#include "CmnLog.h"

#define VS_CONDITION_EQUAL			0x0001
#define VS_CONDITION_COINSIDE		0x0002
#define VS_CONDITION_ERROR			0x0003

struct sVerificationSettings
{
	sVerificationSettings()
	{
		iCondition = VS_CONDITION_ERROR;
		fMaxError = 0.1f;
	}

	int				iCondition;
	
	float			fMaxError;
};

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...);

class CVerificationDlg : 
	public CDialog,
	public ILogProvider
{
	DECLARE_DYNAMIC(CVerificationDlg)

public:
	CVerificationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVerificationDlg();

// Dialog Data
	enum { IDD = IDD_VERIFIER_DLG };

	void					EnableInterface(BOOL bEnable);
	void					UpdateConverterInformation();

	void					SetAppController(IAppController* pController);

private:
	IAppController*			pAppController;

	CDataFile				mDataFile;

	CString					csFileName;

	sVerificationSettings	mSettings;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mConverterFileName;
	afx_msg void OnBnClickedLoadConverterProject();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedVerificationSettings();
	afx_msg void OnBnClickedTestResults();
	CListCtrl mResultsList;

public:
// ILogProvider declarations section
	virtual void			ClearLog();
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);
};
