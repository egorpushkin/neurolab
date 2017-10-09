// ProcessSignalsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessNetwork.h"
#include "ProcessSignalsDlg.h"
#include ".\processsignalsdlg.h"

#include "interface_idds.h"
#include "CmnFactory.h"

#include "Math.h"

// CProcessSignalsDlg dialog

IMPLEMENT_DYNAMIC(CProcessSignalsDlg, CDialog)
CProcessSignalsDlg::CProcessSignalsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessSignalsDlg::IDD, pParent)
	, mInputsCount(0)
{
	iInXDimension = 0;
	iInYDimension = 0;
}

CProcessSignalsDlg::~CProcessSignalsDlg()
{
}

void CProcessSignalsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_CTRL_SETTINGS, mInputPropCtrl);
	DDX_Control(pDX, IDC_INPUT_CTRL_MARKER, mInputMarkerCtrl);
	DDX_Control(pDX, IDC_INPUT_CTRL_EDITOR, mInputEditorCtrl);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Control(pDX, IDC_OUTPUT_ZOOM, mOutputZoom);
}


BEGIN_MESSAGE_MAP(CProcessSignalsDlg, CDialog)
	ON_BN_CLICKED(IDC_INPUT_CTRL_EDITOR, OnBnClickedInputCtrlEditor)
	ON_BN_CLICKED(IDC_INPUT_CTRL_SETTINGS, OnBnClickedInputCtrlSettings)
	ON_BN_CLICKED(IDC_INPUT_CTRL_MARKER, OnBnClickedInputCtrlMarker)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_PROCESS_NETWORK, OnBnClickedProcessNetwork)
END_MESSAGE_MAP()

// CProcessSignalsDlg message handlers
void CProcessSignalsDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}
BOOL CProcessSignalsDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bRet = CDialog::Create(IDD, pParentWnd);

	if (bRet)
	{
		IElementsCollection* pElementsCollection = NULL;
		pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

		int iInputDataLength = pElementsCollection->GetInputsCount();
		//int iOutputDataLength = pElementsCollection->GetOutputsCount();	

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

		/*if (iOutputDataLength == 0)
		{
			iOutXDimension = 0;
			iOutYDimension = 0;
		} else
		{
			iOutXDimension = sqrt((iOutputDataLength - 1)*1.0f) + 1;
			iOutYDimension = (iOutputDataLength - 1)/iOutXDimension + 1;
		
			mOutputCtrlData.CreateFactory(iOutputDataLength);
		}*/

		mInputCtrl.SetCtrlData(&mInputCtrlData);
		mOutputCtrl.SetCtrlData(&mOutputCtrlData);

		mInputCtrl.SetCtrlParams(iInXDimension, iInYDimension, true);

		int iXCoord = 25;
		int iYCoord = 31;

		mInputCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 180, iYCoord + 180), 
			this, IDC_INPUT_CTRL2);

		iXCoord = 25;
		iYCoord = 244;

		mOutputCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 445, iYCoord + 180), 
			this, IDC_OUTPUT_CTRL2);

		mOutputCtrl.iXOffset = -200;

		mInputPropCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));
		mInputMarkerCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_MARKER));
		mInputEditorCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_EDITOR));

		mOutputZoom.SetRange(5, 400);
		mOutputZoom.SetPos(40);
	}

	return bRet;
}

void CProcessSignalsDlg::OnBnClickedInputCtrlEditor()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowAdvancedEditorDlg();
}

void CProcessSignalsDlg::OnBnClickedInputCtrlSettings()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowPropertiesDlg();
}

void CProcessSignalsDlg::OnBnClickedInputCtrlMarker()
{
	// TODO: Add your control notification handler code here
	mInputCtrl.ShowSelectMarkerDlg();
}

void CProcessSignalsDlg::OnOK()
{
}

void CProcessSignalsDlg::OnCancel()
{
}

void CProcessSignalsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar*)&mOutputZoom)
	{
		int tmPos = mOutputZoom.GetPos();
		mOutputCtrl.SetScale(tmPos);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CProcessSignalsDlg::OnBnClickedProcessNetwork()
{
	// TODO: Add your control notification handler code here
    INetworkProcessor* pNetworkProcessor = NULL;
	pAppController->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);

	pNetworkProcessor->SetInputData(&mInputCtrlData);	
	pNetworkProcessor->ProcessNetwork();
	pNetworkProcessor->GetOutputData(&mOutputCtrlData);

	mOutputCtrl.Invalidate();
}
