// ProcessNetworkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessNetwork.h"
#include "ProcessNetworkDlg.h"
#include ".\processnetworkdlg.h"

#include "interface_idds.h"

#include "CmnFactory.h"
#include "CmnDataFactory.h"

bool IsEnableEditItems(int iItem, int iSubItem)
{
	if (iSubItem == 1)
		return true;
	return false;	
}

// CProcessNetworkDlg dialog

IMPLEMENT_DYNAMIC(CProcessNetworkDlg, CDialog)
CProcessNetworkDlg::CProcessNetworkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessNetworkDlg::IDD, pParent)
	, mTotalInputs(0)
	, mTotalOutputs(0)
{
}

CProcessNetworkDlg::~CProcessNetworkDlg()
{
}

void CProcessNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTS_CTRL, mInputsCtrl);
	DDX_Control(pDX, IDC_OUTPUTS_CTRL, mOutputsCtrl);
	DDX_Text(pDX, IDC_TOTAL_INPUTS, mTotalInputs);
	DDX_Text(pDX, IDC_TOTAL_OUTPUTS, mTotalOutputs);
}


BEGIN_MESSAGE_MAP(CProcessNetworkDlg, CDialog)
	ON_BN_CLICKED(IDC_PROCESS_NETWORK, OnBnClickedProcessNetwork)
END_MESSAGE_MAP()

void CProcessNetworkDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// CProcessNetworkDlg message handlers

BOOL CProcessNetworkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	CRect rect;
	mInputsCtrl.GetClientRect(&rect);
	mInputsCtrl.InsertColumn(0, _T("Name"), LVCFMT_LEFT,  rect.Width()*6/10); 
	mInputsCtrl.InsertColumn(1, _T("Value"), LVCFMT_LEFT,  rect.Width()*3/10); 
	mInputsCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mInputsCtrl.SetVerifyingFunc(IsEnableEditItems);

	mOutputsCtrl.GetClientRect(&rect);
	mOutputsCtrl.InsertColumn(0, _T("Name"), LVCFMT_LEFT,  rect.Width()*6/10); 
	mOutputsCtrl.InsertColumn(1, _T("Value"), LVCFMT_LEFT,  rect.Width()*3/10); 
	mOutputsCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	IElementsCollection* pElementsCollection = NULL;
	pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

	mTotalInputs = pElementsCollection->GetInputsCount();
	mTotalOutputs = pElementsCollection->GetOutputsCount();

	UpdateData(FALSE);

	pElementsCollection->CreateElementsEnumerator();
	while (IElement* pElement = pElementsCollection->GetNextElement())
	{
		CString tmName, tmValue;
		tmName.Format("%s %d", pElement->GetElementTitle(), pElement->GetElementID());
		tmValue.Format("%f", 0.0f);

		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		CString tmNamePrepared = tmName;
		int iDataLength = pDataFlow->GetDataFactory()->GetDataLength();

		if (pElement->GetElementType() == ET_INPUT)
		{
			if (!pDataFlow->RequireData())
				continue;
			
			for (int i = 0;i < iDataLength;i++)
			{
				if (iDataLength > 1)
					tmNamePrepared.Format("%s - %d", tmName, i);
				AddListItem(&mInputsCtrl, -1, NULL, 2, tmNamePrepared, tmValue);
			}
		}
		if (pElement->GetElementType() == ET_OUTPUT)
			for (int i = 0;i < iDataLength;i++)
			{
				if (iDataLength > 1)
					tmNamePrepared.Format("%s - %d", tmName, i);
				AddListItem(&mOutputsCtrl, -1, NULL, 2, tmNamePrepared, tmValue);		
			}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProcessNetworkDlg::OnBnClickedProcessNetwork()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDataFactory tmFactory;
	tmFactory.CreateFactory(mTotalInputs);
    
	char tmValue[100];
	for (int i = 0;i<mInputsCtrl.GetItemCount();i++)
	{
		mInputsCtrl.GetItemText(i, 1, tmValue, 100);
		
		tmFactory.SetItemData(i, atof(tmValue));
	}
	
    INetworkProcessor* pNetworkProcessor = NULL;
	pAppController->QueryInterface(IDD_INetworkProcessor, (void**)&pNetworkProcessor);
	
	pNetworkProcessor->SetInputData(&tmFactory);
	pNetworkProcessor->ProcessNetwork();
	pNetworkProcessor->GetOutputData(&tmFactory);

	for (int i = 0;i < mOutputsCtrl.GetItemCount();i++)
	{
		sprintf(tmValue, "%f", tmFactory.GetItemData(i));
		mOutputsCtrl.SetItemText(i, 1, tmValue);	
	}
}

void CProcessNetworkDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CProcessNetworkDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}
