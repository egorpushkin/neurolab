// NeuronFuncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "NeuronFuncDlg.h"
#include ".\neuronfuncdlg.h"

#include "interface_idds.h"

#include "ConfigureFuncDlg.h"
// CNeuronFuncDlg dialog

CNeuronFuncDlg	* mGlobObj;

void OnSelectFunction(void * Param)
{
	IParDef(ObjItem, ObjData, Param, sFunction);

	mGlobObj->mFuncShow.SetFunction(ObjData->pfnProcessFunction);
	mGlobObj->mFuncShow.FunctionParam = ObjData;
	mGlobObj->mFuncShow.Invalidate();

	mGlobObj->mCtrlConfigure.EnableWindow(TRUE);
}

void OnSelectFunctionAddit(void * Param)
{
	CATreeCtrl * mTree = (CATreeCtrl *)Param;
	HTREEITEM htiItem = mTree->GetSelectedItem();
	if (!htiItem)
	{
		mGlobObj->mCtrlConfigure.EnableWindow(FALSE);
	} else
	{
		ItemDataStruct * idsItem = (ItemDataStruct *)mTree->GetItemData(htiItem);
		if (!idsItem)
			mGlobObj->mCtrlConfigure.EnableWindow(FALSE);	
	}
}

IMPLEMENT_DYNAMIC(CNeuronFuncDlg, CDialog)
CNeuronFuncDlg::CNeuronFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeuronFuncDlg::IDD, pParent)
{
	mGlobObj = this;
}

CNeuronFuncDlg::~CNeuronFuncDlg()
{
}

void CNeuronFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FUNCTIONSTREE, mFuncTree);
	DDX_Control(pDX, IDC_FUNCCONFIGURE, mCtrlConfigure);
	DDX_Control(pDX, IDC_FUNC_SCALE, mFuncViewScale);
}


BEGIN_MESSAGE_MAP(CNeuronFuncDlg, CDialog)
	ON_BN_CLICKED(IDC_FUNCCONFIGURE, OnBnClickedFuncconfigure)
	ON_NOTIFY(NM_DBLCLK, IDC_FUNCTIONSTREE, OnNMDblclkFunctionstree)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CNeuronFuncDlg message handlers

void CNeuronFuncDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnOK();
}

void CNeuronFuncDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnCancel();
}

BOOL CNeuronFuncDlg::Create(int iID, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(iID, pParentWnd);

	htiBaseRoot = mFuncTree.InsertItem("Base functions");
	mFuncTree.OnSelChange = OnSelectFunctionAddit;

	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();
	IComponent* pComponent = pAppMain->mComponents.GetComponentByName(CString("BuilderElements"));
	if (pComponent)
	{
		IFunctionsFactory* pFunctionsFactory = NULL;
		pComponent->QueryInterface(IDD_IFunctionsFactory, (void**)&pFunctionsFactory);
		if (pFunctionsFactory)
		{
			pFunctionsFactory->CreateEnumerator();
			while (sFunction* tmFunction = pFunctionsFactory->GetNextFunction())
			{
				ItemDataStruct* idsItem = new ItemDataStruct;
				idsItem->ItemData = tmFunction;
				idsItem->Select = OnSelectFunction;

				HTREEITEM htiItem = mFuncTree.InsertActiveItem(tmFunction->csTitle, idsItem, htiBaseRoot);					
			}					
			mFuncTree.Expand(htiBaseRoot, TVE_EXPAND);
		}
	}

	CRect CfgRect, TreeRect;
	mCtrlConfigure.GetWindowRect(&CfgRect);
	ScreenToClient(&CfgRect);
	mCtrlConfigure.EnableWindow(FALSE);

	mFuncTree.GetWindowRect(&TreeRect);
	ScreenToClient(&TreeRect);

	mFuncShow.Create(0, "", WS_VISIBLE | WS_BORDER, 
		CRect(CfgRect.right + 7, TreeRect.top, CfgRect.right + 200, TreeRect.bottom), 
		this, ID_FUNCTIONSHOWCTRL);

	mFuncViewScale.SetRange(20, 100);
	mFuncViewScale.SetPos(40);

	return bRet;
}

void CNeuronFuncDlg::OnBnClickedFuncconfigure()
{
	HTREEITEM htiSltd = mFuncTree.GetSelectedItem();
	if (htiSltd)
	{
		ItemDataStruct * idsItem = (ItemDataStruct *)mFuncTree.GetItemData(htiSltd);
		if (idsItem)
		{
			if (idsItem->ItemData)
			{
				CConfigureFuncDlg mDlg;
				mDlg.pFunction = (sFunction*)idsItem->ItemData;
				int res = mDlg.DoModal();
				if (res == IDOK)
					mFuncShow.Invalidate();
			}
		}
	}
}
void CNeuronFuncDlg::OnNMDblclkFunctionstree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnBnClickedFuncconfigure();

	*pResult = 0;
}

void CNeuronFuncDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar*)&mFuncViewScale)
	{
		int iRange = mFuncViewScale.GetPos();
		mFuncShow.SetScale(iRange);
		mFuncShow.Invalidate();		
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
