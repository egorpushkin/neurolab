// LayerPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LayerPropertiesDlg.h"
#include ".\layerpropertiesdlg.h"

// CLayerPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CLayerPropertiesDlg, CDialog)
CLayerPropertiesDlg::CLayerPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerPropertiesDlg::IDD, pParent)
	, mLayerID(0)
	, mInputsCount(0)
	, mLayerDimension(0)
{
}

CLayerPropertiesDlg::~CLayerPropertiesDlg()
{
}

void CLayerPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LAYER_ID, mLayerID);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Text(pDX, IDC_LAYER_DIMENSION, mLayerDimension);
	DDX_Control(pDX, IDC_WEIGHTS_LIST, mWeightsCtrl);
}


BEGIN_MESSAGE_MAP(CLayerPropertiesDlg, CDialog)
END_MESSAGE_MAP()

void CLayerPropertiesDlg::SetElement(IElement* Element)
{
	pElement = Element;
}


// CLayerPropertiesDlg message handlers

BOOL CLayerPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ILayerControl* pLayerControl = NULL;
	pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

	mLayerID = pElement->GetElementID();
	mLayerDimension = pLayerControl->GetDimension();
	mInputsCount = pLayerControl->GetInputsCount();

	UpdateData(FALSE);

	CRect rect;
	mWeightsCtrl.GetClientRect(&rect);

	if (mLayerDimension > 100 || mInputsCount > 100)
	{
		mWeightsCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, rect.Width()); 

		LV_ITEM lvItem;
		lvItem.iItem = 0;   
		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 0;
		lvItem.pszText = _T("Layer dimension or inputs count too large.");
		mWeightsCtrl.InsertItem(&lvItem);
	} else
	{
		mWeightsCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, rect.Width()/7); 
		for(int i = 0;i < mLayerDimension;i++)
			mWeightsCtrl.InsertColumn(i + 1, _T(""), LVCFMT_LEFT, rect.Width()/6); 
		mWeightsCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

		LV_ITEM lvItem;
		lvItem.iItem = 0;
		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 0;
		lvItem.pszText = _T("");
		mWeightsCtrl.InsertItem(&lvItem);

		CString	tmText;
		for(int j = 1;j <= mLayerDimension;j++)
		{
			tmText.Format("O %d", j - 1);

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = j;
			lvItem.pszText = tmText.GetBuffer();
			mWeightsCtrl.SetItem(&lvItem);
		}	

		for(int i = 1;i <= mInputsCount;i++)
		{
			tmText.Format("I %d", i - 1);

			lvItem.iItem = i;   
			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 0;
			lvItem.pszText = tmText.GetBuffer();
			mWeightsCtrl.InsertItem(&lvItem);

			for(int j = 1;j <= mLayerDimension;j++)
			{
				tmText.Format("%0.3f", pLayerControl->GetWeight(i - 1, j - 1));

				lvItem.mask = LVIF_TEXT;
				lvItem.iSubItem = j;
				lvItem.pszText = tmText.GetBuffer();
				mWeightsCtrl.SetItem(&lvItem);
			}	
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLayerPropertiesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if (mLayerDimension > 65535)
	{
		AfxMessageBox("Layer dimension cannot be more than 65535.");
		return;
	}
	if (mLayerDimension < 1)
	{
		AfxMessageBox("Layer dimension cannot be less than 1.");
		return;
	}

	if (mInputsCount > 65535)
	{
		AfxMessageBox("Layer inputs count cannot be more than 65535.");
		return;
	}
	if (mInputsCount < 0)
	{
		AfxMessageBox("Layer inputs count cannot be less than 0.");
		return;
	}

	CDialog::OnOK();
}
