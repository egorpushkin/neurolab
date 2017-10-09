// ScriptingElementWeightsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\..\ScriptsNet.h"
#include "ScriptingElementWeightsDlg.h"
#include ".\scriptingelementweightsdlg.h"

#include "CmnScriptingElement.h"
#include "ne_interface_idds.h"

// CScriptingElementWeightsDlg dialog

IMPLEMENT_DYNAMIC(CScriptingElementWeightsDlg, CDialog)
CScriptingElementWeightsDlg::CScriptingElementWeightsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptingElementWeightsDlg::IDD, pParent)
	, pElement(NULL)
	, mInputsCount(0)
	, mLayerDimension(0)
{
}

CScriptingElementWeightsDlg::~CScriptingElementWeightsDlg()
{
}

void CScriptingElementWeightsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Text(pDX, IDC_LAYER_DIMENSION, mLayerDimension);
}


BEGIN_MESSAGE_MAP(CScriptingElementWeightsDlg, CDialog)
	ON_BN_CLICKED(IDC_DONOT_STORE_WEIGHTS, OnBnClickedDonotStoreWeights)
	ON_BN_CLICKED(IDC_STORE_WEIGHTS, OnBnClickedStoreWeights)
END_MESSAGE_MAP()


void CScriptingElementWeightsDlg::SetElement(IElement* Element)
{
	pElement = Element;
}

// CScriptingElementWeightsDlg message handlers

BOOL CScriptingElementWeightsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pElement != NULL);

	IScriptingElementControl* pScriptingElementControl = NULL;
	pElement->QueryInterface(
		IDD_IScriptingElementControl, 
		(void**)&pScriptingElementControl);

	if (pScriptingElementControl->GetDimensionSE() != 0 &&
		pScriptingElementControl->GetInputsCountSE() != 0)
	{	
		((CButton*)GetDlgItem(IDC_STORE_WEIGHTS))->SetCheck(BST_CHECKED);
		EnableWeightsInfo(TRUE);
	} else
	{
		((CButton*)GetDlgItem(IDC_DONOT_STORE_WEIGHTS))->SetCheck(BST_CHECKED);
		EnableWeightsInfo(FALSE);
	}

	mInputsCount = pScriptingElementControl->GetInputsCountSE();
	mLayerDimension = pScriptingElementControl->GetDimensionSE();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CScriptingElementWeightsDlg::EnableWeightsInfo(BOOL bEnable)
{
	GetDlgItem(IDC_INPUTS_COUNT)->EnableWindow(bEnable);
	GetDlgItem(IDC_LAYER_DIMENSION)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_IC)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_LD)->EnableWindow(bEnable);
}

void CScriptingElementWeightsDlg::OnBnClickedDonotStoreWeights()
{
	// TODO: Add your control notification handler code here
	EnableWeightsInfo(FALSE);
}

void CScriptingElementWeightsDlg::OnBnClickedStoreWeights()
{
	// TODO: Add your control notification handler code here
	EnableWeightsInfo(TRUE);
}

void CScriptingElementWeightsDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (((CButton*)GetDlgItem(IDC_STORE_WEIGHTS))->GetCheck() == BST_CHECKED)
	{
		UpdateData(TRUE);

		if (mInputsCount == 0 || mLayerDimension == 0)
		{
            AfxMessageBox("You must enter inputs count and layer dimension.");		
			return;
		}	
	} else
	{
		mInputsCount = 0;
		mLayerDimension = 0;

		UpdateData(FALSE);	
	}

	CDialog::OnOK();
}
