#pragma once

#include "..\..\Resource.h"
// CDataImageCtrlEditorDlg dialog

#include "CmnDataFactory.h"

class CDataImageCtrlEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataImageCtrlEditorDlg)

public:
	CDataImageCtrlEditorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataImageCtrlEditorDlg();

// Dialog Data
	enum { IDD = IDD_DATA_IMAGE_CTRL_EDITOR_DLG };

	void			SetDataFactory(IDataFactory* pData);

private:
	IDataFactory*	pDataFactory;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDicemFileOpen();
	int mDataLength;
	virtual BOOL OnInitDialog();
	float mFillValue;
	afx_msg void OnBnClickedProcessFill();
};
