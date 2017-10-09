// PluginPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\PluginsMng.h"
#include "PluginPropertiesDlg.h"
#include ".\pluginpropertiesdlg.h"

#include "interface_idds.h"

// CPluginPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CPluginPropertiesDlg, CDialog)
CPluginPropertiesDlg::CPluginPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginPropertiesDlg::IDD, pParent)
{
	pPluginInstance = NULL;

	mOnTop = NULL;
	
	bIsInited = false;

	pPluginPropPage = NULL;
}

CPluginPropertiesDlg::~CPluginPropertiesDlg()
{
}

void CPluginPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLUGIN_PROPERTIES_TAB, mPropTab);
}


BEGIN_MESSAGE_MAP(CPluginPropertiesDlg, CDialog)
	ON_WM_PAINT()
	ON_NOTIFY(TCN_SELCHANGE, IDC_PLUGIN_PROPERTIES_TAB, OnTcnSelchangePluginPropertiesTab)
END_MESSAGE_MAP()

void CPluginPropertiesDlg::SetPluginInstance(CPluginInstance* pInstance)
{
	pPluginInstance = pInstance;
}

// CPluginPropertiesDlg message handlers

BOOL CPluginPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("Common");
	mPropTab.InsertItem(0, &tcItem);

	CRect rPropRect;

	if (pPluginInstance->mPluginInfo.bHasPropertiesPage)
	{
		IPluginPropertiesControl* pPluginPropControl = NULL;
		pPluginInstance->pPluginControl->QueryInterface(IDD_IPluginPropertiesControl, 
			(void**)&pPluginPropControl);

		if (pPluginPropControl)
		{
			CString csPluginProrTitle = pPluginPropControl->GetPropertyPageTitle();
			tcItem.pszText = csPluginProrTitle.GetBuffer(255);
			mPropTab.InsertItem(1, &tcItem);

			pPluginPropPage = pPluginPropControl->GetPropertyDialog();
			pPluginPropPage->Create(pPluginPropControl->GetDialogIDD(), &mPropTab);

			pPluginPropPage->GetClientRect(&rPropRect);
			pPluginPropPage->MoveWindow(6, 25, rPropRect.Width(), rPropRect.Height());
		}
	}

	mCommonPropDlg.Create(CCommonPluginPropDlg::IDD, &mPropTab);
	mCommonPropDlg.GetClientRect(&rPropRect);
	mCommonPropDlg.MoveWindow(6, 25, rPropRect.Width(), rPropRect.Height());
	mCommonPropDlg.UpdatePropertyPage(pPluginInstance);
	mCommonPropDlg.ShowWindow(SW_SHOW);

	mOnTop = &mCommonPropDlg;

	CString csWindowText;
	GetWindowText(csWindowText);
	SetWindowText(csWindowText+CString(" : ")+pPluginInstance->mPluginInfo.csName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPluginPropertiesDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	if (!bIsInited)
	{		
		bIsInited = true;
	}

}

void CPluginPropertiesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (pPluginInstance->mPluginInfo.bHasPropertiesPage)
	{
		IPluginPropertiesControl* pPluginPropControl = NULL;
		pPluginInstance->pPluginControl->QueryInterface(IDD_IPluginPropertiesControl, 
			(void**)&pPluginPropControl);

		if (pPluginPropControl)
		{	
			pPluginPropControl->ProcessUpdateProperties();
			pPluginPropControl->GetPropertyDialog()->SendMessage(WM_CLOSE);
		}
	}

	CDialog::OnOK();
}

void CPluginPropertiesDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::OnCancel();
}

void CPluginPropertiesDlg::OnTcnSelchangePluginPropertiesTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (mOnTop)
		mOnTop->ShowWindow(SW_HIDE);
	
	int iCurSel = mPropTab.GetCurSel();
	switch (iCurSel)
	{
	case 0:
		mOnTop = &mCommonPropDlg;
		break;
	case 1:
		mOnTop = pPluginPropPage;
		break;
	}
		
	if (mOnTop)
		mOnTop->ShowWindow(SW_SHOW);
}
