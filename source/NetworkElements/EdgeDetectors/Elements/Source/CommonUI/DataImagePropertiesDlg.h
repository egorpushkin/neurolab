#pragma once


// CDataImagePropertiesDlg dialog

class CDataImagePropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataImagePropertiesDlg)

public:
	CDataImagePropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataImagePropertiesDlg();

// Dialog Data
	enum { IDD = IDD_DATA_IMAGE_PROPERTIED_DLG };

	void			UpdateProperties();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mWidth;
	int mHeight;
protected:
	virtual void OnOK();
public:
	int mDataLength;
	afx_msg void OnEnChangeWidth();
	afx_msg void OnEnChangeHeight();
	virtual BOOL OnInitDialog();
};
