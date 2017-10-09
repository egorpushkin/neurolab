// ChartsViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../../../ScriptEnv.h"
#include "ChartsViewDlg.h"
#include ".\chartsviewdlg.h"


// CChartsViewDlg dialog

IMPLEMENT_DYNAMIC(CChartsViewDlg, CDialog)
CChartsViewDlg::CChartsViewDlg(const std::string& name /*=_T("")*/, CWnd* pParent /*=NULL*/)
	: CDialog(CChartsViewDlg::IDD, pParent)
	, name_(name)
	, alwaysOnTop_(false)
	, onTopBtn_()
	, displayed_(false)
	, removeAtExit_(false)
{
	chartCtrl_.AddChart(
		new Simple2dCharting::BasicChart, 
		new Simple2dCharting::BackgroundRenderer(0xffe0dfe3), 
		new Simple2dCharting::BasicLocator, 
		"background");

	Simple2dCharting::AxisRendererPtr axis = new Simple2dCharting::AxisRenderer;

	Simple2dCharting::AxisRenderer::Parameters params = axis->GetParameters();
	params.rangeX_ = 10.0f;
	params.rangeY_ = 10.0f;
	axis->SetParameters(params);	

	chartCtrl_.AddChart(
		new Simple2dCharting::BasicChart,
		axis, 
		new Simple2dCharting::CartesiansLocator, 
		"axes");
}

CChartsViewDlg::~CChartsViewDlg()
{
}

void CChartsViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ONTOP, onTopBtn_);
}


BEGIN_MESSAGE_MAP(CChartsViewDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_CHARTS_LIST, OnLbnSelchangeChartsList)
	ON_BN_CLICKED(IDC_ONTOP, OnBnClickedOntop)
END_MESSAGE_MAP()


// CChartsViewDlg message handlers
void CChartsViewDlg::OnLbnSelchangeChartsList()
{
	// TODO: Add your control notification handler code here
}

void CChartsViewDlg::OnBnClickedOntop()
{
	alwaysOnTop_ = !alwaysOnTop_;

	// Feature implementation
	HWND wndInsertAfter; 
	if (alwaysOnTop_)
		wndInsertAfter = HWND_TOPMOST;
	else
		wndInsertAfter = HWND_NOTOPMOST;

	CRect rect;
	GetWindowRect(rect);

	::SetWindowPos(m_hWnd ,  
		wndInsertAfter,
		rect.left,    
		rect.top,     
		rect.Width(),  
		rect.Height(), 
		SWP_SHOWWINDOW);

	UpdateAlwaysOnTopButton();
}

void CChartsViewDlg::UpdateAlwaysOnTopButton()
{
	if (alwaysOnTop_)
		onTopBtn_.SetIcon(AfxGetApp()->LoadIcon(IDI_AONTOP_TRUE));	
	else
		onTopBtn_.SetIcon(AfxGetApp()->LoadIcon(IDI_AONTOP_FALSE));	
}
void CChartsViewDlg::OnCancel()
{
	CDialog::OnCancel();

	displayed_ = false;

	if ( removeAtExit_ )
	{
		delete this;
	}
}

void CChartsViewDlg::OnOK()
{
	CDialog::OnOK();

	displayed_ = false;

	if ( removeAtExit_ )
	{
		delete this;
	}
}

BOOL CChartsViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateAlwaysOnTopButton();

	CString wndText;
	GetWindowText(wndText);
	wndText += CString(" ") + CString(name_.c_str());
	SetWindowText(wndText);

	CRect rect;
	GetDlgItem(IDC_CHARTS_CTRL_HOLDER)->GetClientRect(&rect);
	GetDlgItem(IDC_CHARTS_CTRL_HOLDER)->ClientToScreen(&rect);
	ScreenToClient(&rect); 

	chartCtrl_.Create(NULL, "", WS_CHILD | WS_VISIBLE, rect, this, IDC_CHARTING_CTRL);

	displayed_ = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CChartsViewDlg::IsDisplayed()
{
	return displayed_;
}

void CChartsViewDlg::SafeInvalideteChart()
{
    if ( IsDisplayed() )
		chartCtrl_.Invalidate();
}

void CChartsViewDlg::HandleRemove()
{
	removeAtExit_ = true;

	if ( !IsDisplayed() )
	{
		delete this;
	}
}
