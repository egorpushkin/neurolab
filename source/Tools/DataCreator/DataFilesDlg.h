#pragma once

#include "afxwin.h"

#include "CmnDataFile.h"
// CDataFilesDlg dialog

class CDataFilesDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataFilesDlg)

public:
	CDataFilesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataFilesDlg();

	// Input controls
	CDataImageCtrl			mInputBuilder;
	CButton					mUpListInputs;
	CButton					mDownListInputs;

	int						mInputNumber;
	int						mTotalInputs;	
	float					mInputMarker;

	CButton					mAddInput;
	CButton					mRemoveInput;
	CButton					mSetInputMarker;

	CButton					mInputCtrlProp;
	CButton					mInputCtrlEditor;

	// Output controls
	CDataImageCtrl			mOutputBuilder;
	CButton					mUpListOutputs;
	CButton					mDownListOutputs;

	int						mOutputNumber;
	int						mTotalOutputs;
	float					mOutputMarker;

	CButton					mAddOutput;
	CButton					mRemoveOutput;
	CButton					mSetOutputMarker;

	CButton					mOutputCtrlProp;
	CButton					mOutputCtrlEditor;

	// Common controls
	CString					mFileName;
	int						mInputLength;
	int						mOutputLength;
	CString					mModifiedState;
	CButton					mSaveCtrl;
	CButton					mSaveAsCtrl;

	// Interface operations
	void					EnableInterface(bool bEnable);
	void					SetModifiedState(bool bState);
	void					SetupControls(int InputLength, int OutputLength);
	void					SetupDataImageCtrl(CDataImageCtrl* pCtrl, int DataLength);

	void					ShowInputSymbol(int Index);
	void					ShowOutputSymbol(int Index);

	void					CloseFile();

	// Data
	CDataFile				mDataFile;
	bool					bModified;

// Dialog Data
	enum { IDD = IDD_DATA_FILES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL Create(int IDD, CWnd* pParentWnd = NULL);
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedAddInputSymbol();
	afx_msg void OnBnClickedRemoveInputSymbol();
	afx_msg void OnBnClickedSetInputMarker();
	afx_msg void OnBnClickedUpListInputs();
	afx_msg void OnBnClickedDownListInputs();
	afx_msg void OnBnClickedInputCtrlProp();
	afx_msg void OnBnClickedAddOutputSymbol();
	afx_msg void OnBnClickedRemoveOutputSymbol();
	afx_msg void OnBnClickedSetOutputMarker();
	afx_msg void OnBnClickedUpListOutputs();
	afx_msg void OnBnClickedDownListOutputs();
	afx_msg void OnBnClickedOutputCtrlProp();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSaveAs();
	afx_msg void OnBnClickedInputCtrlEditor();
	afx_msg void OnBnClickedOutputCtrlEditor();
};
