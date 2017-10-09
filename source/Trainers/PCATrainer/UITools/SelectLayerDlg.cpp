// SelectLayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SelectLayerDlg.h"
#include ".\selectlayerdlg.h"

#define WM_UPDATE_TIMER			WM_USER + 1

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
{
	LV_ITEM item;
    item.iItem = m_List->GetItemCount();
    item.iImage = icon;
	item.lParam = data;
   
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

	va_list params;
	va_start(params, num);
	char * temp = va_arg(params,char *);

	item.iSubItem = 0;
    item.pszText = temp;
    m_List->InsertItem(&item);

	for(int i = 1;i<num;i++)
	{
		temp = va_arg(params,char *);
		item.mask = LVIF_TEXT;
		item.iSubItem = i;
		item.pszText = temp;
		m_List->SetItem(&item);
	}
} 

// CSelectLayerDlg dialog

IMPLEMENT_DYNAMIC(CSelectLayerDlg, CDialog)
CSelectLayerDlg::CSelectLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectLayerDlg::IDD, pParent)
{
	pElementsCollection = NULL;
	pLayerControl = NULL;
}

CSelectLayerDlg::~CSelectLayerDlg()
{
}

void CSelectLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAYERS_LIST, mLayersList);
}


BEGIN_MESSAGE_MAP(CSelectLayerDlg, CDialog)
END_MESSAGE_MAP()


// CSelectLayerDlg message handlers

BOOL CSelectLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	CRect rect;
	mLayersList.GetClientRect(&rect);
	mLayersList.InsertColumn(0, _T("Layer Name"), LVCFMT_LEFT, rect.Width()*5/7); 
	mLayersList.InsertColumn(1, _T("Dimension"), LVCFMT_LEFT, rect.Width()*2/7); 
	mLayersList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);		
	
	int iLayersCount = 0;

	pElementsCollection->CreateElementsEnumerator(6);
	while (IElement* pElement = pElementsCollection->GetNextElement(6))
	{
		ILayerControl* pLayer = NULL;
		pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayer);

		if (pLayer && pElement->GetElementType() == ET_PROCESSOR)	
		{
			CString csDimension, csName;
			csDimension.Format("%d", pLayer->GetDimension());
			csName.Format("%s %d", pElement->GetElementTitle(), pElement->GetElementID());

			AddListItem(&mLayersList, -1, (LPARAM)pLayer, 2, csName, csDimension);
					
			iLayersCount++;
		}
	}

	if (iLayersCount == 0)
	{
		pLogProvider->AddLogMessage(CString("TE"), 
			CString("Network does not contain any layers."), 
			CString("PCA Trainer"));

		EndDialog(IDCANCEL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSelectLayerDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	int iCurSel = mLayersList.GetNextItem(-1, LVNI_SELECTED);
	if (iCurSel == -1)
	{
		AfxMessageBox("You must select layer to train.");
		return;
	}

	ILayerControl* pLayer = (ILayerControl*)mLayersList.GetItemData(iCurSel);
	if (!pLayer)
	{
		AfxMessageBox("Wrong list control item selected.");
		return;		
	}

	pLayerControl = pLayer;

	CDialog::OnOK();
}
