// AreaPaneContentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../../../AreasBuilder.h"
#include "AreaPaneContentDlg.h"


// AreaPaneContentDlg dialog

IMPLEMENT_DYNAMIC(AreaPaneContentDlg, CDialog)
AreaPaneContentDlg::AreaPaneContentDlg(Workspace::IAreasProject* piAreasProject, uint areaIndex, CWnd* pParent /*=NULL*/)
	: CDialog(AreaPaneContentDlg::IDD, pParent)
	, piAreasProject_(piAreasProject)
	, areaIndex_(areaIndex)
{
	assert(piAreasProject_ != NULL);
	piAreasProject_->AddRef();
}

AreaPaneContentDlg::~AreaPaneContentDlg()
{
	piAreasProject_->Release();
}

void AreaPaneContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AreaPaneContentDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// AreaPaneContentDlg message handlers

void AreaPaneContentDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (areaMapCtrl_.GetSafeHwnd())
	{
		areaMapCtrl_.MoveWindow(0, 0, cx, cy);
	}
}

BOOL AreaPaneContentDlg::Create(UINT resourceId, CWnd* pParentWnd)
{
	BOOL ret = CDialog::Create(resourceId, pParentWnd);

	if (ret)
	{
		areaMapCtrl_.Create(NULL, _T(""), WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, IDC_AREA_MAP_STATUS_CTRL);
		
		areaMapCtrl_.SetCtrlParams(
			piAreasProject_->GetAreasHolder()->GetMapWidth(), 
			piAreasProject_->GetAreasHolder()->GetMapHeight()); 

		areaMapCtrl_.SetCtrlData(piAreasProject_->GetAreasHolder()->GetArea(areaIndex_));
	}

	return ret;
}

void AreaPaneContentDlg::OnOK()
{
}

void AreaPaneContentDlg::OnCancel()
{
}
