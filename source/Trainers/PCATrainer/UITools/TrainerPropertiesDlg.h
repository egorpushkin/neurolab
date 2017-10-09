#pragma once

#include "../Trainer/PCATrainerImpl.h"

// CTrainerPropertiesDlg dialog

class CTrainerPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrainerPropertiesDlg)

public:
	CTrainerPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainerPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_PCA_TRAINER_PROPERTIES };

	sPCASettings*			pSettings;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mVectorsCount;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
