// TrainingPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "TrainingPropertiesDlg.h"


// CTrainingPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CTrainingPropertiesDlg, CDialog)
CTrainingPropertiesDlg::CTrainingPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainingPropertiesDlg::IDD, pParent)
	, mUseNetworkMap(FALSE)
{
}

CTrainingPropertiesDlg::~CTrainingPropertiesDlg()
{
}

void CTrainingPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_USE_NETWORK_MAP, mUseNetworkMap);
}


BEGIN_MESSAGE_MAP(CTrainingPropertiesDlg, CDialog)
END_MESSAGE_MAP()


// CTrainingPropertiesDlg message handlers
