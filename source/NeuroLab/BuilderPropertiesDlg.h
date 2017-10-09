#pragma once


// CBuilderPropertiesDlg dialog

class CBuilderPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CBuilderPropertiesDlg)

public:
	CBuilderPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBuilderPropertiesDlg();

	void EnableGridControls(BOOL bEnable);

// Dialog Data
	enum { IDD = IDD_BUILDER_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL mShowGrid;
	int mGridRange;
	BOOL mAttachToGrid;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedShowGrid();
};
