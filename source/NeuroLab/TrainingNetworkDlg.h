#pragma once
#include "afxwin.h"

#include "CmnDataFile.h"
#include "CmnTrainers.h"
#include "afxcmn.h"
// CTrainingNetworkDlg dialog

class CTrainingNetworkDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrainingNetworkDlg)

public:
	CTrainingNetworkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainingNetworkDlg();

	void					SetAppController(IAppController* pController);
	void					SetTrainersContainer(ITrainersContainer* pContainer);

// Dialog Data
	enum { IDD = IDD_TRAINING_NETWORK_DLG };

private:
	IAppController*			pAppController;
	ITrainersContainer*		pTrainersContainer;

	// Data members
	bool					bIsDataLoaded;

	CDataFile				mDataFile;				

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);
	afx_msg void OnBnClickedDataDetails();
	afx_msg void OnBnClickedLoadData();
	CString mDataState;
	CButton mDataDetailsCtrl;
	int mInputsCount;
	int mInputSymbolLength;
	int mOutputsCount;
	int mOutputSymbolLength;
	CTreeCtrl mTrainingsTree;
	CButton mConfigureTrainer;
	CButton mStartTraining;
	afx_msg void OnTvnSelchangedTrainingMethodsTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConfigureMethod();
	afx_msg void OnBnClickedStartTraining();
	afx_msg void OnNMDblclkTrainingMethodsTree(NMHDR *pNMHDR, LRESULT *pResult);
};
