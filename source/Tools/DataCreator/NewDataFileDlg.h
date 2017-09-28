#pragma once


// CNewDataFileDlg dialog

class CNewDataFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDataFileDlg)

public:
	CNewDataFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDataFileDlg();

// Dialog Data
	enum { IDD = IDD_NEW_FILE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mInputLength;
	int mOutputLength;
};
