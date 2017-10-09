#pragma once


// CTrainingPropertiesDlg dialog

class CTrainingPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrainingPropertiesDlg)

public:
	CTrainingPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainingPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_TRAINING_PROPERTIES_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL mUseNetworkMap;
};
