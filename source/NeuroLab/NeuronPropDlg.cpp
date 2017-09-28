// NeuronPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "NeuronPropDlg.h"
#include ".\neuronpropdlg.h"

#include "interface_idds.h"

#include "SelectFunctionDlg.h"
// CNeuronPropDlg dialog

CNeuronPropDlg * mGlobObj;

void OnSelChangeDendrites(void * Param)
{
	IParDef(ObjItem, ObjData, Param, CConnection);

	mGlobObj->UpdateData(TRUE);
	mGlobObj->mDendrWeight = ObjData->mWeights.GetItemData(0);
	mGlobObj->mDendriteCount = ObjData->mWeights.GetDataLength();
	mGlobObj->UpdateData(FALSE);        	

	bool bEnableWeightEdit = (ObjData->mWeights.GetDataLength() == 1);

	mGlobObj->mCtrlDendrWeight.EnableWindow(bEnableWeightEdit);	
	mGlobObj->mCtrlRemoveDendr.EnableWindow(TRUE);	

	mGlobObj->mUpMoveDendrite.EnableWindow(TRUE);
	mGlobObj->mDownMoveDendrite.EnableWindow(TRUE);
	
	bool bEnable = mGlobObj->EnableEditConnectionDimension(ObjData);
	mGlobObj->mCtrlDendriteCount.EnableWindow(bEnable);
}

void OnSelChangeDendritesAddit(void * Param)
{
	CATreeCtrl * mTree = (CATreeCtrl *)Param;
	HTREEITEM htiItem = mTree->GetSelectedItem();
	if (!htiItem)
	{
		mGlobObj->mCtrlDendrWeight.EnableWindow(FALSE);	
		mGlobObj->mCtrlRemoveDendr.EnableWindow(FALSE);	

		mGlobObj->mUpMoveDendrite.EnableWindow(FALSE);	
		mGlobObj->mDownMoveDendrite.EnableWindow(FALSE);	

		mGlobObj->UpdateData(TRUE);
		mGlobObj->mDendrWeight = 0;
		mGlobObj->mDendriteCount = 0;
		mGlobObj->UpdateData(FALSE);  

		mGlobObj->mCtrlDendriteCount.EnableWindow(FALSE);
	}
}

void OnSelChangeAxons(void * Param)
{
	IParDef(ObjItem, ObjData, Param, CConnection);

	mGlobObj->UpdateData(TRUE);
	mGlobObj->mAxonCount = ObjData->mWeights.GetDataLength();
	mGlobObj->UpdateData(FALSE);  

	mGlobObj->mCtrlRemoveAxon.EnableWindow(TRUE);	

	mGlobObj->mUpMoveAxon.EnableWindow(TRUE);
	mGlobObj->mDownMoveAxon.EnableWindow(TRUE);

	bool bEnable = mGlobObj->EnableEditConnectionDimension(ObjData);
	mGlobObj->mCtrlAxonCount.EnableWindow(bEnable);
}

void OnSelChangeAxonsAddit(void * Param)
{
	CATreeCtrl * mTree = (CATreeCtrl *)Param;
	HTREEITEM htiItem = mTree->GetSelectedItem();
	if (!htiItem)
	{
		mGlobObj->mCtrlRemoveAxon.EnableWindow(FALSE);	

		mGlobObj->mUpMoveAxon.EnableWindow(FALSE);	
		mGlobObj->mDownMoveAxon.EnableWindow(FALSE);

		mGlobObj->UpdateData(TRUE);
		mGlobObj->mAxonCount = 0;
		mGlobObj->UpdateData(FALSE);  

		mGlobObj->mCtrlAxonCount.EnableWindow(FALSE);
	}
}

IMPLEMENT_DYNAMIC(CNeuronPropDlg, CDialog)
CNeuronPropDlg::CNeuronPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeuronPropDlg::IDD, pParent)
	, mNeuronID(0)
	, mElTitle(_T(""))
	, mDendrWeight(0)
	, mDendriteCount(0)
	, mAxonCount(0)
{
	pActiveElement = NULL;

	mGlobObj = this;

	mDendrites.OnSelChange = OnSelChangeDendritesAddit;
	mAxons.OnSelChange = OnSelChangeAxonsAddit;
}

CNeuronPropDlg::~CNeuronPropDlg()
{
}

void CNeuronPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AXONSTREE, mAxons);
	DDX_Text(pDX, IDC_NURONID, mNeuronID);
	DDX_Text(pDX, IDC_ELTITLE, mElTitle);
	DDX_Text(pDX, IDC_DENDRITEWEIGHT, mDendrWeight);
	DDX_Control(pDX, IDC_DENDRTREE, mDendrites);
	DDX_Control(pDX, IDC_DENDRITEWEIGHT, mCtrlDendrWeight);
	DDX_Control(pDX, IDC_REMOVEDENDRITE, mCtrlRemoveDendr);
	DDX_Control(pDX, IDC_REMOVEAXON, mCtrlRemoveAxon);
	DDX_Control(pDX, IDC_FUNCTIONNAME, mCtrlFunctionName);
	DDX_Control(pDX, IDC_SELECTFUNCTION, mCtrlSelectFunction);
	DDX_Control(pDX, IDC_DOWN_MOVE_DENDRITE, mDownMoveDendrite);
	DDX_Control(pDX, IDC_UP_MOVE_DENDRITE, mUpMoveDendrite);
	DDX_Control(pDX, IDC_UP_MOVE_AXON, mUpMoveAxon);
	DDX_Control(pDX, IDC_DOWN_MOVE_AXON, mDownMoveAxon);
	DDX_Control(pDX, IDC_DENDRITE_COUNT, mCtrlDendriteCount);
	DDX_Control(pDX, IDC_AXON_COUNT, mCtrlAxonCount);
	DDX_Text(pDX, IDC_DENDRITE_COUNT, mDendriteCount);
	DDX_Text(pDX, IDC_AXON_COUNT, mAxonCount);
}


BEGIN_MESSAGE_MAP(CNeuronPropDlg, CDialog)
	ON_BN_CLICKED(IDC_REMOVEDENDRITE, OnBnClickedRemovedendrite)
	ON_EN_CHANGE(IDC_DENDRITEWEIGHT, OnEnChangeDendriteweight)
	ON_BN_CLICKED(IDC_REMOVEAXON, OnBnClickedRemoveaxon)
	ON_BN_CLICKED(IDC_SELECTFUNCTION, OnBnClickedSelectfunction)
	ON_BN_CLICKED(IDC_UP_MOVE_DENDRITE, OnBnClickedUpMoveDendrite)
	ON_BN_CLICKED(IDC_DOWN_MOVE_DENDRITE, OnBnClickedDownMoveDendrite)
	ON_BN_CLICKED(IDC_UP_MOVE_AXON, OnBnClickedUpMoveAxon)
	ON_BN_CLICKED(IDC_DOWN_MOVE_AXON, OnBnClickedDownMoveAxon)
	ON_EN_CHANGE(IDC_DENDRITE_COUNT, OnEnChangeDendriteCount)
	ON_EN_CHANGE(IDC_AXON_COUNT, OnEnChangeAxonCount)
END_MESSAGE_MAP()

// Creation and initialization functions
void CNeuronPropDlg::EnableInterface(bool bIsToEnable)
{
	if (!bIsToEnable)
	{
		mElTitle = "No Element";
		mNeuronID = 0;

		mAxons.DeleteAllItems();
		mDendrites.DeleteAllItems();
		
		mCtrlFunctionName.SetWindowText("");
	}
	mDendrWeight = 0;
	mDendriteCount = 0;
	mAxonCount = 0;

	mAxons.EnableWindow(bIsToEnable);
	mDendrites.EnableWindow(bIsToEnable);

	mCtrlDendrWeight.EnableWindow(bIsToEnable);
	mCtrlRemoveDendr.EnableWindow(bIsToEnable);
	mCtrlRemoveAxon.EnableWindow(bIsToEnable);

	mCtrlFunctionName.EnableWindow(bIsToEnable);
	mCtrlSelectFunction.EnableWindow(bIsToEnable);

	mUpMoveDendrite.EnableWindow(bIsToEnable);
	mDownMoveDendrite.EnableWindow(bIsToEnable);

	mUpMoveAxon.EnableWindow(bIsToEnable);
	mDownMoveAxon.EnableWindow(bIsToEnable);

	mCtrlDendriteCount.EnableWindow(FALSE);
	mCtrlAxonCount.EnableWindow(FALSE);

	UpdateData(FALSE);
}

BOOL CNeuronPropDlg::Create(int iIDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(iIDD, pParentWnd);

	if (bRet)
	{		
		mUpMoveDendrite.SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
		mDownMoveDendrite.SetIcon(AfxGetApp()->LoadIcon(IDI_DOWNARROW));

		mUpMoveAxon.SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
		mDownMoveAxon.SetIcon(AfxGetApp()->LoadIcon(IDI_DOWNARROW));	

		EnableInterface(false);
	}

	return bRet;
}

void CNeuronPropDlg::SetBuilderControl(IBuilderControl* pControl)
{
	pBuilderControl = pControl;
}

// CNeuronPropDlg message handlers
void CNeuronPropDlg::OnOK()
{
}

void CNeuronPropDlg::OnCancel()
{
}

void CNeuronPropDlg::ShowElement(IElement* pNewElement)
{
	if (!pNewElement)
	{
		EnableInterface(false);
		pActiveElement = NULL;
	
		return;
	} 

	EnableInterface(true);

	pActiveElement = pNewElement;

	ShowDendrites();
	ShowAxons();

	UpdateData(TRUE);
	mNeuronID = pNewElement->GetElementID();
	mElTitle = pNewElement->GetElementTitle();
	UpdateData(FALSE);

	IDataFlow* pDataFlow = NULL;
	pActiveElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);
	
	sFunction* pFunction = pDataFlow->GetElementFunction();
	if (pFunction)
		mCtrlFunctionName.SetWindowText(pFunction->csTitle);
}

void CNeuronPropDlg::ShowDendrites(CConnection* pConnection)
{
	CString	tmStr;
	bool bEnableCtrls = false;

	IDataConnector* pDataConnector = NULL;
	pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

	IConnectionsFactory* pFactory = pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

	mDendrites.DeleteAllItems();

	pFactory->CreateEnumerator();
	while(CConnection* tmConnection = pFactory->GetNextConnection())
	{
		tmStr.Format("Dendrite to: %s %d", tmConnection->pElement->GetElementTitle(), 
			tmConnection->pElement->GetElementID());

		ItemDataStruct * idsItem = new ItemDataStruct;
		idsItem->Select = OnSelChangeDendrites;
		idsItem->ItemData = tmConnection;
		HTREEITEM htiItem = mDendrites.InsertActiveItem(tmStr, idsItem);		

		if (tmConnection == pConnection)
		{		
			mDendrites.SelectItem(htiItem);
			bEnableCtrls = true;
		}
	}

	mCtrlDendrWeight.EnableWindow(bEnableCtrls);	
	mCtrlRemoveDendr.EnableWindow(bEnableCtrls);	

	mUpMoveDendrite.EnableWindow(bEnableCtrls);
	mDownMoveDendrite.EnableWindow(bEnableCtrls);
}

void CNeuronPropDlg::ShowAxons(CConnection* pConnection)
{
	CString	tmStr;
	bool bEnableCtrls = false;

	IDataConnector* pDataConnector = NULL;
	pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

	IConnectionsFactory* pFactory = pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);

	mAxons.DeleteAllItems();

	pFactory->CreateEnumerator();
	while(CConnection* tmConnection = pFactory->GetNextConnection())
	{
		tmStr.Format("Axon to: %s %d", tmConnection->pElement->GetElementTitle(),
			tmConnection->pElement->GetElementID());

		ItemDataStruct * idsItem = new ItemDataStruct;
		idsItem->Select = OnSelChangeAxons;
		idsItem->ItemData = tmConnection;
		HTREEITEM htiItem = mAxons.InsertActiveItem(tmStr, idsItem);		

		if (tmConnection == pConnection)
		{
			mAxons.SelectItem(htiItem);
			bEnableCtrls = true;
		}
	}

	mCtrlRemoveAxon.EnableWindow(bEnableCtrls);	
	
	mUpMoveAxon.EnableWindow(bEnableCtrls);
	mDownMoveAxon.EnableWindow(bEnableCtrls);
}

void CNeuronPropDlg::OnBnClickedRemovedendrite()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mDendrites.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct*)mDendrites.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection*)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		pDataConnector->RemoveConnection(tmConnection);

		mDendrites.DeleteItem(htiItem);
		delete	idsItem;
		pBuilderControl->GetControlWindow()->Invalidate();
	}
}
void CNeuronPropDlg::OnEnChangeDendriteweight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	HTREEITEM htiItem = mDendrites.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mDendrites.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		UpdateData(TRUE);
		tmConnection->mWeights.SetItemData(0, mDendrWeight);
	}
}

void CNeuronPropDlg::OnBnClickedRemoveaxon()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mAxons.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct*)mAxons.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection*)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		pDataConnector->RemoveConnection(tmConnection);

		mAxons.DeleteItem(htiItem);
		delete	idsItem;
		pBuilderControl->GetControlWindow()->Invalidate();
	}
}

void CNeuronPropDlg::OnBnClickedSelectfunction()
{
	// TODO: Add your control notification handler code here
	if (pActiveElement)
	{
		IDataFlow* pDataFlow = NULL;
		pActiveElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		CSelectFunctionDlg	mDlg;
		mDlg.pSelectedFunction = pDataFlow->GetElementFunction();
		int res = mDlg.DoModal();
		if (res == IDOK)
		{
			pDataFlow->SetElementFunction(mDlg.pSelectedFunction);			
			mCtrlFunctionName.SetWindowText(mDlg.pSelectedFunction->csTitle);
		}
	}
}

void CNeuronPropDlg::OnBnClickedUpMoveDendrite()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mDendrites.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mDendrites.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		
		if (pDataConnector->MoveConnection(tmConnection, true))
		{
			ShowDendrites(tmConnection);
			pBuilderControl->GetControlWindow()->Invalidate();
		}
	}
}

void CNeuronPropDlg::OnBnClickedDownMoveDendrite()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mDendrites.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mDendrites.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		
		if (pDataConnector->MoveConnection(tmConnection))
		{
			ShowDendrites(tmConnection);
			pBuilderControl->GetControlWindow()->Invalidate();
		}
	}
}

void CNeuronPropDlg::OnBnClickedUpMoveAxon()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mAxons.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mAxons.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		
		if (pDataConnector->MoveConnection(tmConnection, true))
		{
			ShowAxons(tmConnection);	
			pBuilderControl->GetControlWindow()->Invalidate();
		}
	}
}

void CNeuronPropDlg::OnBnClickedDownMoveAxon()
{
	// TODO: Add your control notification handler code here
	HTREEITEM htiItem = mAxons.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mAxons.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		IDataConnector* pDataConnector = NULL;
		pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		
		if (pDataConnector->MoveConnection(tmConnection))
		{
			ShowAxons(tmConnection);			
			pBuilderControl->GetControlWindow()->Invalidate();
		}
	}
}

bool CNeuronPropDlg::EnableEditConnectionDimension(CConnection* pConnection)
{
/*	ILayerControl* pThisLayerControl = NULL;
	pConnection->pOpposite->pElement->QueryInterface(IDD_ILayerControl, (void**)&pThisLayerControl);

	if (!pThisLayerControl && 
		pConnection->pElement->GetElementType() == ET_OUTPUT)
		return false;*/

	return true;
}
void CNeuronPropDlg::OnEnChangeDendriteCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	HTREEITEM htiItem = mDendrites.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mDendrites.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		UpdateData(TRUE);
		tmConnection->SizeConnection(mDendriteCount);

		bool bEnableWeightEdit = (tmConnection->mWeights.GetDataLength() == 1);
		mCtrlDendrWeight.EnableWindow(bEnableWeightEdit);	

		pBuilderControl->GetControlWindow()->Invalidate();
	}
}

void CNeuronPropDlg::OnEnChangeAxonCount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	HTREEITEM htiItem = mAxons.GetSelectedItem();
	if (htiItem && pActiveElement)
	{
		ItemDataStruct* idsItem = (ItemDataStruct *)mAxons.GetItemData(htiItem);
		CConnection* tmConnection = (CConnection *)idsItem->ItemData;

		UpdateData(TRUE);
		tmConnection->SizeConnection(mAxonCount);

		pBuilderControl->GetControlWindow()->Invalidate();
	}
}
