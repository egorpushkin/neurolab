// DataImageCtrlMarkerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../Resource.h"
#include "DataImageCtrlMarkerDlg.h"


// CDataImageCtrlMarkerDlg dialog

IMPLEMENT_DYNAMIC(CDataImageCtrlMarkerDlg, CDialog)
CDataImageCtrlMarkerDlg::CDataImageCtrlMarkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataImageCtrlMarkerDlg::IDD, pParent)
	, mMarker(0)
	, mMarkerDiameter(0)
{
}

CDataImageCtrlMarkerDlg::~CDataImageCtrlMarkerDlg()
{
}

void CDataImageCtrlMarkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MARKER, mMarker);
	DDX_Text(pDX, IDC_MARKER_DIAMETER, mMarkerDiameter);
}


BEGIN_MESSAGE_MAP(CDataImageCtrlMarkerDlg, CDialog)
END_MESSAGE_MAP()


// CDataImageCtrlMarkerDlg message handlers
