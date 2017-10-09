// LayersExporterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LayersExporter.h"
#include "LayersExporterDlg.h"
#include ".\layersexporterdlg.h"

#include "LayerOperations.h"

#include "AboutDlg.h"

// CLayersExporterDlg dialog

IMPLEMENT_DYNAMIC(CLayersExporterDlg, CDialog)
CLayersExporterDlg::CLayersExporterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayersExporterDlg::IDD, pParent)
	, pAppController(NULL)
{
}

CLayersExporterDlg::~CLayersExporterDlg()
{
}

void CLayersExporterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAYERS_LIST, mLayersList);
}


BEGIN_MESSAGE_MAP(CLayersExporterDlg, CDialog)
	ON_BN_CLICKED(IDC_EXPORT_LAYER_DATA, OnBnClickedExportLayerData)
	ON_BN_CLICKED(IDC_IMPORT_LAYER_DATA, OnBnClickedImportLayerData)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LAYERS_LIST, OnLvnItemchangedLayersList)
	ON_BN_CLICKED(IDC_ABOUT, OnBnClickedAbout)
END_MESSAGE_MAP()


// CLayersExporterDlg message handlers

BOOL CLayersExporterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pAppController != NULL);
	
	// Initializing UI
	mLayersList.SetExtendedStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	mLayersList.InsertColumn(0, _T("Layer Name"), LVCFMT_LEFT, 100);
	mLayersList.InsertColumn(1, _T("ID"), LVCFMT_LEFT, 30);
	mLayersList.InsertColumn(2, _T("Type"), LVCFMT_LEFT, 100);
	mLayersList.InsertColumn(3, _T("Inputs"), LVCFMT_LEFT, 70);
	mLayersList.InsertColumn(4, _T("Dimension"), LVCFMT_LEFT, 70);
	
	// Initializing layers list 
	CLayerOperations::FillLayersList(
		pAppController, 
		&mLayersList);

	EnableLayerOperations(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLayersExporterDlg::OnBnClickedExportLayerData()
{
	// TODO: Add your control notification handler code here
	int iItem = mLayersList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
		return;

	IElement* pElement = (IElement*)mLayersList.GetItemData(iItem);

	CLayerOperations::ExportLayerData(pElement);
}

void CLayersExporterDlg::OnBnClickedImportLayerData()
{
	// TODO: Add your control notification handler code here
	int iItem = mLayersList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
		return;

	IElement* pElement = (IElement*)mLayersList.GetItemData(iItem);

	CLayerOperations::ImportLayerData(pElement);
}

void CLayersExporterDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here
	CAboutDlg mDlg;
	mDlg.DoModal();
}

void CLayersExporterDlg::OnLvnItemchangedLayersList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	bool bEnableControls = false;

	if (pNMLV->iItem != -1)
	{
		IElement* pElement = (IElement*)mLayersList.GetItemData(pNMLV->iItem);
		
		if (pElement)
		{
			bEnableControls = true;
		}
	}

	EnableLayerOperations(bEnableControls);

	*pResult = 0;
}

void CLayersExporterDlg::EnableLayerOperations(BOOL bEnable)
{
	GetDlgItem(IDC_EXPORT_LAYER_DATA)->EnableWindow(bEnable);
	GetDlgItem(IDC_IMPORT_LAYER_DATA)->EnableWindow(bEnable);
}
