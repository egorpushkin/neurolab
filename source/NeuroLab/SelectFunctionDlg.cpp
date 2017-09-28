// SelectFunctionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "SelectFunctionDlg.h"
#include ".\selectfunctiondlg.h"

#include "CmnFunction.h"

#include "interface_idds.h"

// CSelectFunctionDlg dialog

CSelectFunctionDlg	* mGlobObj;

void OnNPSelectFunction(void * Param)
{
	IParDef(ObjItem, ObjData, Param, sFunction);

	mGlobObj->mFnExpression.EnableWindow(TRUE);
	mGlobObj->mFnExpression.SetWindowText(ObjData->csExpression);

	mGlobObj->pSelectedFunction = ObjData;
}

void OnNPSelectFunctionAddit(void * Param)
{
	CATreeCtrl* mTree = (CATreeCtrl *)Param;
	HTREEITEM htiItem = mTree->GetSelectedItem();
	if (!htiItem)
	{
		mGlobObj->mFnExpression.EnableWindow(FALSE);
		mGlobObj->mFnExpression.SetWindowText("");
		mGlobObj->pSelectedFunction = NULL;
	} else
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mTree->GetItemData(htiItem);
		if (!idsItem)
		{
			mGlobObj->mFnExpression.EnableWindow(FALSE);
			mGlobObj->mFnExpression.SetWindowText("");		
			mGlobObj->pSelectedFunction = NULL;
		}
	}
}

IMPLEMENT_DYNAMIC(CSelectFunctionDlg, CDialog)
CSelectFunctionDlg::CSelectFunctionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFunctionDlg::IDD, pParent)
{
	pSelectedFunction = NULL;

	mGlobObj = this;
}

CSelectFunctionDlg::~CSelectFunctionDlg()
{
}

void CSelectFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FNTREE, mFnList);
	DDX_Control(pDX, IDC_FUNCEXPRESSION, mFnExpression);
}


BEGIN_MESSAGE_MAP(CSelectFunctionDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_FNTREE, OnNMDblclkFntree)
END_MESSAGE_MAP()


// CSelectFunctionDlg message handlers

BOOL CSelectFunctionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	sFunction* pSavedSelected = pSelectedFunction;
	HTREEITEM htiSelectedItem = NULL;

	htiBaseRoot = mFnList.InsertItem("Base functions");
	mFnList.OnSelChange = OnNPSelectFunctionAddit;

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
				idsItem->Select = OnNPSelectFunction;

				HTREEITEM htiItem = mFnList.InsertActiveItem(tmFunction->csTitle, idsItem, htiBaseRoot);					

				if (tmFunction == pSavedSelected)
					htiSelectedItem = htiItem;
			}					

			mFnList.Expand(htiBaseRoot, TVE_EXPAND);
			mFnList.SelectItem(htiSelectedItem);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectFunctionDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (!pSelectedFunction)
	{	
		AfxMessageBox("You must select function from the list.");	
		return;
	}

	CDialog::OnOK();
}

void CSelectFunctionDlg::OnNMDblclkFntree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM htiSltd = mFnList.GetSelectedItem();
	if (htiSltd)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mFnList.GetItemData(htiSltd);
		if (idsItem)
		{
			if (idsItem->ItemData)
			{
				pSelectedFunction = (sFunction*)idsItem->ItemData;
				CDialog::OnOK();
			}
		}
	}
}
