// BandPaneContentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../../../AreasBuilder.h"
#include "BandPaneContentDlg.h"

// BandPaneContentDlg dialog

IMPLEMENT_DYNAMIC(BandPaneContentDlg, CDialog)
BandPaneContentDlg::BandPaneContentDlg(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand, CWnd* pParent /*=NULL*/)
	: CDialog(BandPaneContentDlg::IDD, pParent)
	, bandDisplayCtrl_()
	, piAreasProject_(piAreasProject)
	, pBand_(pBand)
{
}

BandPaneContentDlg::~BandPaneContentDlg()
{
}

void BandPaneContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BandPaneContentDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// BandPaneContentDlg message handlers

BOOL BandPaneContentDlg::Create(UINT resourceId, CWnd* pParentWnd)
{
	BOOL ret = CDialog::Create(resourceId, pParentWnd);

	if (ret)
	{
		bandDisplayCtrl_.Create(NULL, _T(""), WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, IDC_BAND_MAP_STATUS_CTRL);

		IPGMBitmap* piBitmap = pBand_->GetBitmap();
		bandDisplayCtrl_.SetBitmap(piBitmap);
		piBitmap->Release();
	}

	return ret;
}

void BandPaneContentDlg::OnOK()
{
}

void BandPaneContentDlg::OnCancel()
{
}

void BandPaneContentDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (bandDisplayCtrl_.GetSafeHwnd())
	{
		bandDisplayCtrl_.MoveWindow(0, 0, cx, cy);
	}
}
