#pragma once
#include "afxwin.h"

#include "CmnTrainers.h"
#include "CmnLog.h"
#include "afxcmn.h"

// CTrainerToolDlg dialog
DWORD ProcessTrainingThread(DWORD dwParam);

class CTrainerToolDlg : public CDialog,
	public ILogProvider
{
	DECLARE_DYNAMIC(CTrainerToolDlg)

public:
	CTrainerToolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainerToolDlg();

	void				SetTrainer(ITrainer* pTrainerObj);
	ITrainer*			GetTrainer();

	void				EnableControlButtons(BOOL bEnable);

	void				OnFinishTraining();

	bool				OnTryingToExit();

// Dialog Data
	enum { IDD = IDD_TRAINER_TOOL_DLG };

	void			InitializeButtonIcons();

// ILogProvider declarations section
	virtual void			ClearLog();
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	ITrainer*			pTrainer;
	bool				bIsPaused;

	HANDLE				hProcessingThread;

	int					iTrainerDataType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedTrainingProperties();
	afx_msg void OnBnClickedConfigureTrainer();
	afx_msg void OnBnClickedProcessTraining();
	afx_msg void OnBnClickedPauseTraining();
	afx_msg void OnBnClickedStopTraining();

	afx_msg void OnTimer(UINT nIDEvent);

	virtual BOOL OnInitDialog();

	CButton mProcessTrainingCtrl;
	CButton mPauseTrainingCtrl;
	CButton mStopTrainingCtrl;

	CListCtrl mEventsLog;
	
	CString mTrainerName;
	CString mTrainerVersion;

	CProgressCtrl mTrainingProgress;
	int mCurrentPercent;
	CStatic mCurrentPercentCtrl;
	CButton mConfigureTrainerCtrl;
	CButton mToolPropertiesCtrl;
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
