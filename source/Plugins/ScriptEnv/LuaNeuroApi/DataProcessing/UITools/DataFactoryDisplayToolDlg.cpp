// DataFactoryDisplayToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\ScriptEnv.h"
#include "DataFactoryDisplayToolDlg.h"
#include ".\datafactorydisplaytooldlg.h"


// CDataFactoryDisplayToolDlg dialog

IMPLEMENT_DYNAMIC(CDataFactoryDisplayToolDlg, CDialog)
CDataFactoryDisplayToolDlg::CDataFactoryDisplayToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataFactoryDisplayToolDlg::IDD, pParent)
	, pData(NULL)
	, bAlwaysOnTop(false)
{
}

CDataFactoryDisplayToolDlg::~CDataFactoryDisplayToolDlg()
{
}

void CDataFactoryDisplayToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTROL_PROPERTIES, mDataPropCtrl);
	DDX_Control(pDX, IDC_DATA_FACTORY_SAVE_AS, mCtrlDFSaveAs);
	DDX_Control(pDX, IDC_DF_TL_ALWAYS_ON_TOP, mAlwaysOnTop);
}


BEGIN_MESSAGE_MAP(CDataFactoryDisplayToolDlg, CDialog)
	ON_BN_CLICKED(IDC_CONTROL_PROPERTIES, OnBnClickedControlProperties)
	ON_BN_CLICKED(IDC_DATA_FACTORY_SAVE_AS, OnBnClickedDataFactorySaveAs)
	ON_BN_CLICKED(IDC_DF_TL_ALWAYS_ON_TOP, OnBnClickedDfTlAlwaysOnTop)
END_MESSAGE_MAP()


// CDataFactoryDisplayToolDlg message handlers

BOOL CDataFactoryDisplayToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  Add extra initialization here
	ASSERT(pData != NULL);
	
	mDataImageCtrl.SetCtrlData(&pData->mDataFactory);
	mDataImageCtrl.SetCtrlParams(pData->iWidth, pData->iHeight);
	
	mDataImageCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
		CRect(10, 10, 300, 300), 
		this, IDC_DATA_FACTORY_DISPLAY_TOOL_IMAGE_CTRL);
	
	mDataPropCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));
	mCtrlDFSaveAs.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_DF_SAVE_AS));

	CString tmWindowText;
	GetWindowText(tmWindowText);
	tmWindowText = tmWindowText + pData->csName;
	SetWindowText(tmWindowText);

	UpdateAlwaysOnTopButton();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataFactoryDisplayToolDlg::OnBnClickedControlProperties()
{
	// TODO: Add your control notification handler code here
	mDataImageCtrl.ShowPropertiesDlg();
}

void CDataFactoryDisplayToolDlg::OnBnClickedDataFactorySaveAs()
{
	// TODO: Add your control notification handler code here
	mDataImageCtrl.ShowSaveAsDlg();
}

void CDataFactoryDisplayToolDlg::OnBnClickedDfTlAlwaysOnTop()
{
	// TODO: Add your control notification handler code here
	bAlwaysOnTop = !bAlwaysOnTop;

	// Feature implementation
	HWND hWndInsertAfter; 
	if (bAlwaysOnTop)
		hWndInsertAfter = HWND_TOPMOST;
	else
		hWndInsertAfter = HWND_NOTOPMOST;

	CRect rect;
	GetWindowRect( rect );

	::SetWindowPos(m_hWnd ,  
		hWndInsertAfter,
		rect.left,    
		rect.top,     
		rect.Width(),  
		rect.Height(), 
		SWP_SHOWWINDOW);

	UpdateAlwaysOnTopButton();
}

void CDataFactoryDisplayToolDlg::UpdateAlwaysOnTopButton()
{
	if (bAlwaysOnTop)
		mAlwaysOnTop.SetIcon(AfxGetApp()->LoadIcon(IDI_AONTOP_TRUE));	
	else
		mAlwaysOnTop.SetIcon(AfxGetApp()->LoadIcon(IDI_AONTOP_FALSE));	
}
