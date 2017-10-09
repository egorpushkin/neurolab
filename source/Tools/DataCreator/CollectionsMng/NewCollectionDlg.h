#pragma once


// CNewCollectionDlg dialog

class CNewCollectionDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewCollectionDlg)

public:
	CNewCollectionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewCollectionDlg();

// Dialog Data
	enum { IDD = IDD_NEW_COLLECTION_DLG };

	CString			mWmdTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mCollectionName;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
