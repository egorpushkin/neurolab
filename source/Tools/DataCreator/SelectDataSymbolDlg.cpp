// SelectDataSymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "SelectDataSymbolDlg.h"
#include ".\selectdatasymboldlg.h"

#include "Math.h"

// CSelectDataSymbolDlg dialog

IMPLEMENT_DYNAMIC(CSelectDataSymbolDlg, CDialog)
CSelectDataSymbolDlg::CSelectDataSymbolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDataSymbolDlg::IDD, pParent)
	, mOutputsCount(0)
	, mSymbolDimension(0)
	, mSymbolIndex(0)
{
	pDataFile = NULL;
	iCtrlMode = SDS_MODE_VIEW;
}

CSelectDataSymbolDlg::~CSelectDataSymbolDlg()
{
}

void CSelectDataSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYMBOLS_COUNT, mOutputsCount);
	DDX_Text(pDX, IDC_SYMBOL_DIMENSION, mSymbolDimension);
	DDX_Text(pDX, IDC_SYMBOL_INDEX, mSymbolIndex);
}


BEGIN_MESSAGE_MAP(CSelectDataSymbolDlg, CDialog)
	ON_BN_CLICKED(IDC_UP_SYMBOL, OnBnClickedUpSymbol)
	ON_BN_CLICKED(IDC_DOWN_SYMBOL, OnBnClickedDownSymbol)
	ON_BN_CLICKED(IDC_SYMBOL_PROPERTIES, OnBnClickedSymbolProperties)
END_MESSAGE_MAP()


// CSelectDataSymbolDlg message handlers

void CSelectDataSymbolDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

BOOL CSelectDataSymbolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	ASSERT(pDataFile!=NULL);
		
	int iXDimension = sqrt((GetDataLength() - 1)*1.0f) + 1;
	int iYDimension = (GetDataLength() - 1)/iXDimension + 1;

	mSymbolCtrl.SetCtrlParams(iXDimension, iYDimension, false);
	mSymbolCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
		CRect(18, 55, 267, 262), 
		this, IDC_SYMBOL_CTRL);

	if (GetSymbolsCount() != 0)
	{
		mSymbolCtrl.SetCtrlData(GetSymbol(0));
		mSymbolIndex = 0;
	}

	mOutputsCount = GetSymbolsCount();
	mSymbolDimension = GetDataLength();

	UpdateData(FALSE);	

	((CButton*)GetDlgItem(IDC_UP_SYMBOL))->SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
	((CButton*)GetDlgItem(IDC_DOWN_SYMBOL))->SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
	((CButton*)GetDlgItem(IDC_SYMBOL_PROPERTIES))->SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));

	if (iCtrlMode == SDS_MODE_VIEW)
		SetWindowText("Loaded data symbols");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDataSymbolDlg::SetDataFile(IDataFile* pFile, bool bInputs)
{
	pDataFile = pFile;
	bShowInputs = bInputs;
}
	
int CSelectDataSymbolDlg::GetDataLength()
{
	ASSERT(pDataFile!=NULL);

	if (bShowInputs)
		return pDataFile->GetInputSymbolLength();
	else 
		return pDataFile->GetOutputSymbolLength();
}

int CSelectDataSymbolDlg::GetSymbolsCount()
{
	ASSERT(pDataFile!=NULL);

	if (bShowInputs)
		return pDataFile->GetInputSymbolsCount();
	else 
		return pDataFile->GetOutputSymbolsCount();
}

IDataFactory* CSelectDataSymbolDlg::GetSymbol(int Symbol)
{
	ASSERT(pDataFile!=NULL);

	if (bShowInputs)
		return pDataFile->GetInputSymbol(Symbol);
	else 
		return pDataFile->GetOutputSymbol(Symbol);
}

void CSelectDataSymbolDlg::OnBnClickedUpSymbol()
{	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mSymbolIndex == 0)
		return;

	mSymbolIndex--;
	mSymbolCtrl.SetCtrlData(GetSymbol(mSymbolIndex));
	mSymbolCtrl.Invalidate();

	UpdateData(FALSE);
}

void CSelectDataSymbolDlg::OnBnClickedDownSymbol()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mSymbolIndex == GetSymbolsCount() - 1)
		return;

	mSymbolIndex++;
	mSymbolCtrl.SetCtrlData(GetSymbol(mSymbolIndex));
	mSymbolCtrl.Invalidate();

	UpdateData(FALSE);
}

void CSelectDataSymbolDlg::OnBnClickedSymbolProperties()
{
	// TODO: Add your control notification handler code here
	mSymbolCtrl.ShowPropertiesDlg();
}

void CSelectDataSymbolDlg::SetCtrlMode(int Mode)
{
	iCtrlMode = Mode;
}