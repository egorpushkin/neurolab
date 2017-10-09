// ProcessVisualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessNetwork.h"
#include "ProcessVisualDlg.h"
#include ".\processvisualdlg.h"

#include "interface_idds.h"
#include "CmnFactory.h"

#include "Math.h"

// CProcessVisualDlg dialog

IMPLEMENT_DYNAMIC(CProcessVisualDlg, CDialog)
CProcessVisualDlg::CProcessVisualDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessVisualDlg::IDD, pParent)
	, mInputsCount(0)
	, mOutputsCount(0)
	, mRequiredTime(0)
{
	iInXDimension = 0;
	iInYDimension = 0;
	iOutXDimension = 0;
	iOutYDimension = 0;
}

CProcessVisualDlg::~CProcessVisualDlg()
{
	mInputCtrlData.ReleaseFactory();
	mOutputCtrlData.ReleaseFactory();
}

void CProcessVisualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_CTRL_SETTINGS, mInputPropCtrl);
	DDX_Control(pDX, IDC_INPUT_CTRL_MARKER, mInputMarkerCtrl);
	DDX_Control(pDX, IDC_OUTPUT_CTRL_SETTINGS, mOutputPropCtrl);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Text(pDX, IDC_OUTPUTS_COUNT, mOutputsCount);
	DDX_Control(pDX, IDC_INPUT_CTRL_EDITOR, mInputEditorCtrl);
	DDX_Text(pDX, IDC_REQUIRED_TIME, mRequiredTime);
}

BEGIN_MESSAGE_MAP(CProcessVisualDlg, CDialog)
	ON_BN_CLICKED(IDC_PROCESS_NETWORK, OnBnClickedProcessNetwork)
	ON_BN_CLICKED(IDC_INPUT_CTRL_SETTINGS, OnBnClickedInputCtrlSettings)
	ON_BN_CLICKED(IDC_INPUT_CTRL_MARKER, OnBnClickedInputCtrlMarker)
	ON_BN_CLICKED(IDC_OUTPUT_CTRL_SETTINGS, OnBnClickedOutputCtrlSettings)
	ON_BN_CLICKED(IDC_INPUT_CTRL_EDITOR, OnBnClickedInputCtrlEditor)
END_MESSAGE_MAP()

void CProcessVisualDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// CProcessVisualDlg message handlers

void CProcessVisualDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CProcessVisualDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

BOOL CProcessVisualDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	int bRet = CDialog::Create(IDD, pParentWnd);

	if (bRet)
	{
		IElementsCollection* pElementsCollection = NULL;
		pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

		int iInputDataLength = pElementsCollection->GetInputsCount();
		int iOutputDataLength = pElementsCollection->GetOutputsCount();	

		if (iInputDataLength == 0)
		{
			iInXDimension = 0;
			iInXDimension = 0;
		} else
		{
			iInXDimension = sqrt((iInputDataLength - 1)*1.0f) + 1;
			iInYDimension = (iInputDataLength - 1)/iInXDimension + 1;

			mInputCtrlData.CreateFactory(iInputDataLength);
		}

		if (iOutputDataLength == 0)
		{
			iOutXDimension = 0;
			iOutYDimension = 0;
		} else
		{
			iOutXDimension = sqrt((iOutputDataLength - 1)*1.0f) + 1;
			iOutYDimension = (iOutputDataLength - 1)/iOutXDimension + 1;
		
			mOutputCtrlData.CreateFactory(iOutputDataLength);
		}
		
		mInputCtrl.SetCtrlData(&mInputCtrlData);
		mOutputCtrl.SetCtrlData(&mOutputCtrlData);

		mInputCtrl.SetCtrlParams(iInXDimension, iInYDimension, true);
		mOutputCtrl.SetCtrlParams(iOutXDimension, iOutYDimension);

		int iXCoord = 25;
		int iYCoord = 70;

		//mInputCtrl.SetToolTipID(IDC_INPUT_CTRL_TOOL);
		mInputCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 220, iYCoord + 220), 
			this, IDC_INPUT_CTRL);

		iXCoord = 260;
		iYCoord = 70;

		//mOutputCtrl.SetToolTipID(IDC_OUTPUT_CTRL_TOOL);
		mOutputCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 220, iYCoord + 220), 
			this, IDC_OUTPUT_CTRL);

		mInputPropCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));
		mInputMarkerCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_MARKER));
		mOutputPropCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));
		mInputEditorCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_EDITOR));

		mInputsCount = iInputDataLength;
		mOutputsCount = iOutputDataLength;
		UpdateData(FALSE);
	}

	return bRet;
}

void CProcessVisualDlg::OnBnClickedProcessNetwork()
{
	// TODO: Add your control notification handler code here
    INetworkProcessor* pNetworkProcessor = NULL;
	pAppController->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	LARGE_INTEGER liCounterBefore;	
	LARGE_INTEGER liCounterAfter;	 
	LARGE_INTEGER liFrequency;	
	QueryPerformanceFrequency(&liFrequency);

	QueryPerformanceCounter(&liCounterBefore);

	pNetworkProcessor->SetInputData(&mInputCtrlData);	
	pNetworkProcessor->ProcessNetwork();
	pNetworkProcessor->GetOutputData(&mOutputCtrlData);

	QueryPerformanceCounter(&liCounterAfter);

	UpdateData(TRUE);
	LONGLONG llCounterTacts = liCounterAfter.QuadPart - liCounterBefore.QuadPart;
	mRequiredTime = ((llCounterTacts*1.0f)*1000.0f)/liFrequency.QuadPart;
	UpdateData(FALSE);

	mOutputCtrl.Invalidate();
}

void CProcessVisualDlg::OnBnClickedInputCtrlSettings()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowPropertiesDlg();
}

void CProcessVisualDlg::OnBnClickedInputCtrlMarker()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowSelectMarkerDlg();
}

void CProcessVisualDlg::OnBnClickedOutputCtrlSettings()
{
	// TODO: Add your control notification handler code here
	mOutputCtrl.ShowPropertiesDlg();
}
void CProcessVisualDlg::OnBnClickedInputCtrlEditor()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowAdvancedEditorDlg();
}
