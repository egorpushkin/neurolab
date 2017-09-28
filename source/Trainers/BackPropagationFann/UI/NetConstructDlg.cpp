// NetConstructDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../Common/BackPropagationFann.h"

#include "NetConstructDlg.h"
#include ".\netconstructdlg.h"

// CNetConstructDlg dialog

IMPLEMENT_DYNAMIC(CNetConstructDlg, CDialog)
CNetConstructDlg::CNetConstructDlg(
	IElementsCollection* piElementsCollection,
	GenericNetwork* pGenericNetwork)
	: CDialog(CNetConstructDlg::IDD, NULL)
	, piElementsCollection_(piElementsCollection)
	, pGenericNetwork_(pGenericNetwork)
{
}

CNetConstructDlg::~CNetConstructDlg()
{
}

void CNetConstructDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_LIST, sourceList_);
	DDX_Control(pDX, IDC_TARGET_LIST, targetList_);
	DDX_Control(pDX, IDC_NET_DESCR, netDescr_);
}


BEGIN_MESSAGE_MAP(CNetConstructDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_SINGLE, OnBnClickedAddSingle)
	ON_BN_CLICKED(IDC_REMOVE_SINGLE, OnBnClickedRemoveSingle)
	ON_BN_CLICKED(IDC_MOVE_UP, OnBnClickedMoveUp)
	ON_BN_CLICKED(IDC_MOVE_DOWN, OnBnClickedMoveDown)
	ON_LBN_DBLCLK(IDC_SOURCE_LIST, OnLbnDblclkSourceList)
	ON_LBN_DBLCLK(IDC_TARGET_LIST, OnLbnDblclkTargetList)
END_MESSAGE_MAP()


// CNetConstructDlg message handlers

void CNetConstructDlg::OnBnClickedAddSingle()
{
	// TODO: Add your control notification handler code here
    while ( sourceList_.GetSelCount() > 0 )
	{
		TransferSelectedItem(sourceList_, targetList_);
	}

	DumpNetwork();
}

void CNetConstructDlg::OnBnClickedRemoveSingle()
{
	// TODO: Add your control notification handler code here
	while ( targetList_.GetSelCount() > 0 )
	{
		TransferSelectedItem(targetList_, sourceList_);
	}

	DumpNetwork();
}

void CNetConstructDlg::OnLbnDblclkSourceList()
{
	OnBnClickedAddSingle();
}

void CNetConstructDlg::OnLbnDblclkTargetList()
{
	OnBnClickedRemoveSingle();
}


void CNetConstructDlg::OnBnClickedMoveUp()
{
	// TODO: Add your control notification handler code here
	if ( targetList_.GetSelCount() != 1 )
		return;

	int index;
	targetList_.GetSelItems(1, &index);

	if ( index == 0 )
		return;

	IElement* piElement = (IElement*)targetList_.GetItemData(index);
	CString text;
	targetList_.GetText(index, text);	

	int newIndex = targetList_.InsertString(index - 1, text);
	targetList_.SetItemData(newIndex, (DWORD_PTR)piElement);

	targetList_.DeleteString(index + 1);
	targetList_.SetSel(newIndex, TRUE);

	DumpNetwork();
}

void CNetConstructDlg::OnBnClickedMoveDown()
{
	// TODO: Add your control notification handler code here
	if ( targetList_.GetSelCount() != 1 )
		return;

	int index;
	targetList_.GetSelItems(1, &index);

	if ( index == targetList_.GetCount() - 1 )
		return;

	IElement* piElement = (IElement*)targetList_.GetItemData(index);
	CString text;
	targetList_.GetText(index, text);	

	int newIndex = targetList_.InsertString(index + 2, text);
	targetList_.SetItemData(newIndex, (DWORD_PTR)piElement);

	targetList_.DeleteString(index);
	targetList_.SetSel(newIndex - 1, TRUE);

	DumpNetwork();
}

BOOL CNetConstructDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitialDisplayNetworks();

	DumpNetwork();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNetConstructDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	pGenericNetwork_->GetNetwork().clear();

	for ( int i = 0; i < targetList_.GetCount(); ++i )
	{
		IElement* piElement = (IElement*)targetList_.GetItemData(i);
		pGenericNetwork_->GetNetwork().push_back(piElement);
	}

	CDialog::OnOK();
}


// Private interface
void CNetConstructDlg::InitialDisplayNetworks()
{
	GenericNetwork::NetworkContainer srcNetwork;
	pGenericNetwork_->UpdateNetwork(srcNetwork);

	// Fill lists
	FillList(sourceList_, srcNetwork);
	FillList(targetList_, pGenericNetwork_->GetNetwork());
}

void CNetConstructDlg::FillList(CListBox& listControl, GenericNetwork::NetworkContainer& network)
{
	GenericNetwork::NetworkContainer::iterator iter = network.begin();
	GenericNetwork::NetworkContainer::iterator end = network.end();

	for ( ; iter != end ; ++iter )
	{
		CString layerName;
		layerName.Format(_T("%s %d"), (*iter)->GetElementTitle(), (*iter)->GetElementID());
		int index = listControl.AddString(layerName);
		listControl.SetItemData(index, (DWORD_PTR)(*iter));
	}
}

void CNetConstructDlg::TransferSelectedItem(CListBox& from, CListBox& to)
{
	int index;
	from.GetSelItems(1, &index);

	IElement* piElement = (IElement*)from.GetItemData(index);
	CString text;
	from.GetText(index, text);

	from.DeleteString(index);

    int newIndex = to.AddString(text);
	to.SetItemData(newIndex, (DWORD_PTR)piElement);
}

void CNetConstructDlg::DumpNetwork()
{
	if ( targetList_.GetCount() == 0 )
	{
		netDescr_.SetWindowText(_T("Network does not contain any elements."));
		return;
	}

	CString descr = 
		CString(_T("Network has ")) + GetElementDim(0) + CString(_T(" input(s)."));

	if ( targetList_.GetCount() > 1 )
		descr += 
			CString(_T("\r\nNetwork has the following list of layers:"));

    for ( int i = 1 ; i < targetList_.GetCount() ; ++i )
	{
		descr += 
			CString(_T("\r\nLayer with ")) + GetElementDim(i) + CString(_T(" neuron(s)."));
	}

	netDescr_.SetWindowText(descr);
}

CString CNetConstructDlg::GetElementDim(int index)
{
	if ( index >= targetList_.GetCount() )
		return _T("");

	IElement* piElement = (IElement*)targetList_.GetItemData(index);
	ILayerControl* piLayerControl = NULL;
	piElement->QueryInterface(IDD_ILayerControl, (void**)&piLayerControl);

	CString dim;
	dim.Format(_T("%d"), piLayerControl->GetDimension());

	return dim;
}
