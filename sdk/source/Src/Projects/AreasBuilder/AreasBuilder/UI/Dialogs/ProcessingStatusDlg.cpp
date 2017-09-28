#include "stdafx.h"
#include "../../AreasBuilder.h"

#include "../ProjectManager/ProjectManager.h"

#include "../Interfaces/IStatusUIProvider.h"

#include "ProcessingStatusDlg.h"

using namespace Workspace;
using namespace ProjectUI;

#define WM_UPDATE_AREA_TIMER			WM_USER + 1

// CProcessingStatusDlg dialog

IMPLEMENT_DYNAMIC(CProcessingStatusDlg, CDialog)
CProcessingStatusDlg::CProcessingStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessingStatusDlg::IDD, pParent)
	, numRef_(0)
	, allowedToClose_(false)
	, pProjectManager_(NULL)
	, piAreasProject_(NULL)
	, enableVisualization_(TRUE)
	, dragging_(false)
{
}

CProcessingStatusDlg::~CProcessingStatusDlg()
{
	if (piAreasProject_)
		piAreasProject_->Release();
}

// IStatusUIProvider declarations section
//////////////////////////////////////////////////////////////////////////
void CProcessingStatusDlg::SetAreasProject(IAreasProject* piAreasProject)
{
	if (piAreasProject_)
		piAreasProject_->Release();
	
	piAreasProject_ = piAreasProject;
	piAreasProject_->AddRef();
}

void CProcessingStatusDlg::SetProjectManager(ProjectManager* pProjectManager)
{
	pProjectManager_ = pProjectManager;
}

INT_PTR	CProcessingStatusDlg::ShowModalDialog()
{
	return DoModal();
}

void CProcessingStatusDlg::CloseModalDialog()
{
	AllowCloseDialog();

	SendMessage(WM_CLOSE);
}

void CProcessingStatusDlg::InitialUpdateUI()
{
	assert(piAreasProject_ != NULL);
	assert(areaMapCtrl_.GetSafeHwnd() != NULL);
	assert(areaSelector_.GetSafeHwnd() != NULL);
	
	areaMapCtrl_.SetCtrlParams(
		piAreasProject_->GetAreasHolder()->GetMapWidth(), 
		piAreasProject_->GetAreasHolder()->GetMapHeight()); 

	areaMapCtrl_.SetCtrlData(piAreasProject_->GetAreasHolder()->GetArea(0));

	for (uint i = 0;i < piAreasProject_->GetAreasHolder()->GetAreasCount();i++)
	{
		char className[MAX_PATH];
		sprintf(className, "Class %d", i);

		int index = areaSelector_.AddString(className);
		areaSelector_.SetItemData(index, index);
    }
	areaSelector_.SetCurSel(0);

	SetTimer(WM_UPDATE_AREA_TIMER, 100, NULL);
}

void CProcessingStatusDlg::AllowCloseDialog()
{
	UpdatePercentage(100);

	allowedToClose_ = true;
	GetDlgItem(IDOK)->EnableWindow(TRUE);	
	GetDlgItem(IDC_TERMINATE_BUILDING)->EnableWindow(FALSE);	
}

void CProcessingStatusDlg::UpdatePercentage(uint percentage)
{
	buildingProgress_.SetPos(percentage);
	
	char percentageStr[MAX_PATH];
	sprintf(percentageStr, "%d %%", percentage);
	buildingStatus_.SetWindowText(percentageStr);
}

// ICommon implementations section
ulong CProcessingStatusDlg::AddRef()
{
	return ++numRef_;						
}

ulong CProcessingStatusDlg::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CProcessingStatusDlg::GetClassString() const
{
	return _T("CProcessingStatusDlg");
}

result CProcessingStatusDlg::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = static_cast<ICommon*>(this);
	}
	if (rIID == IID_IStatusUIProvider)
	{		
		*ppObject = static_cast<IStatusUIProvider*>(this);
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	static_cast<ICommon*>(this)->AddRef();
	return S_OK;
}

// Dialog members
//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CProcessingStatusDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ENABLE_VISUALIZATION, OnBnClickedEnableVisualization)
	ON_CBN_SELCHANGE(IDC_CLASS_TO_DISPLAY, OnCbnSelchangeClassToDisplay)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_TERMINATE_BUILDING, OnBnClickedTerminateBuilding)
END_MESSAGE_MAP()

void CProcessingStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUILD_PROGRESS, buildingProgress_);
	DDX_Control(pDX, IDC_PERCENT_COMPLETE, buildingStatus_);
	DDX_Control(pDX, IDC_CLASS_TO_DISPLAY, areaSelector_);
	DDX_Check(pDX, IDC_ENABLE_VISUALIZATION, enableVisualization_);
}

BOOL CProcessingStatusDlg::OnInitDialog()
{
	assert(piAreasProject_ != NULL);

	CDialog::OnInitDialog();

	CRect areaCtrlRect;
	GetDlgItem(IDC_HOLDER_AREA_VIEW)->GetClientRect(&areaCtrlRect);
	GetDlgItem(IDC_HOLDER_AREA_VIEW)->ClientToScreen(&areaCtrlRect);
	ScreenToClient(&areaCtrlRect);

	areaMapCtrl_.Create(NULL, _T(""), WS_VISIBLE | WS_BORDER, areaCtrlRect, this, IDC_AREA_MAP_STATUS_CTRL);

	buildingProgress_.SetRange(0, 100);
	UpdatePercentage(0);

	pProjectManager_->ResumeBuilding();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProcessingStatusDlg::OnOK()
{
	if (!allowedToClose_)
		OnBnClickedTerminateBuilding();
	else
		CDialog::OnOK();
}

void CProcessingStatusDlg::OnCancel()
{
	if (!allowedToClose_)
		OnBnClickedTerminateBuilding();
	else
		CDialog::OnCancel();
}

void CProcessingStatusDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == WM_UPDATE_AREA_TIMER)
	{
		areaMapCtrl_.Invalidate();
	}

	CDialog::OnTimer(nIDEvent);
}

void CProcessingStatusDlg::OnBnClickedEnableVisualization()
{
	EnableVisualization();
}

void CProcessingStatusDlg::OnCbnSelchangeClassToDisplay()
{
	DisplaySelectedArea();
}

void CProcessingStatusDlg::OnBnClickedTerminateBuilding()
{
	int res = AfxMessageBox(_T("Are you sure that you want to terminate building?\nAreas would be built from the very beginning next time."), MB_YESNO);
	if (res == IDYES)
	{
		pProjectManager_->SetTerminationFlag(true);
	}
}

void CProcessingStatusDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	dragging_ = true;
	prevDragPos_ = point;
	SetCapture();

	CDialog::OnLButtonDown(nFlags, point);
}

void CProcessingStatusDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	dragging_ = false;

	CDialog::OnLButtonUp(nFlags, point);
}

void CProcessingStatusDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (dragging_)
	{
		CRect clientRect;
		GetClientRect(&clientRect);

		ClientToScreen(&clientRect);

		int xDiff = (point.x - prevDragPos_.x);
		int yDiff = (point.y - prevDragPos_.y);

		clientRect.OffsetRect(xDiff, yDiff);
		clientRect.InflateRect(0, 0, 2, 2);

		MoveWindow(clientRect);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CProcessingStatusDlg::EnableVisualization()
{
	UpdateData(TRUE);

	GetDlgItem(IDC_CLASS_TO_DISPLAY)->EnableWindow(enableVisualization_);
	GetDlgItem(IDC_STATIC_CLASS)->EnableWindow(enableVisualization_);
	areaMapCtrl_.EnableWindow(enableVisualization_);	

	if (!enableVisualization_)
	{		
		areaMapCtrl_.SetCtrlData(NULL);
		KillTimer(WM_UPDATE_AREA_TIMER);
	}
	else
	{
		DisplaySelectedArea();
		SetTimer(WM_UPDATE_AREA_TIMER, 100, NULL);
	}
}

void CProcessingStatusDlg::DisplaySelectedArea()
{
	int selectedArea = areaSelector_.GetCurSel();
	if (selectedArea == -1)
		return;

	areaMapCtrl_.SetCtrlData(piAreasProject_->GetAreasHolder()->GetArea(selectedArea));
}
