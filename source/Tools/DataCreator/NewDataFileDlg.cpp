// NewDataFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "NewDataFileDlg.h"


// CNewDataFileDlg dialog

IMPLEMENT_DYNAMIC(CNewDataFileDlg, CDialog)
CNewDataFileDlg::CNewDataFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDataFileDlg::IDD, pParent)
	, mInputLength(0)
	, mOutputLength(0)
{
}

CNewDataFileDlg::~CNewDataFileDlg()
{
}

void CNewDataFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_LENGTH, mInputLength);
	DDV_MinMaxInt(pDX, mInputLength, 1, 100000000);
	DDX_Text(pDX, IDC_OUTPUT_LENGTH, mOutputLength);
	DDV_MinMaxInt(pDX, mOutputLength, 1, 100000000);
}


BEGIN_MESSAGE_MAP(CNewDataFileDlg, CDialog)
END_MESSAGE_MAP()


// CNewDataFileDlg message handlers
