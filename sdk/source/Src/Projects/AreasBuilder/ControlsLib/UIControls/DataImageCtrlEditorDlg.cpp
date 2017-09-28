// DataImageCtrlEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataImageCtrlEditorDlg.h"
#include ".\dataimagectrleditordlg.h"

//#include "CollectionConverter/Operation_LoadImage.h"

// CDataImageCtrlEditorDlg dialog

IMPLEMENT_DYNAMIC(CDataImageCtrlEditorDlg, CDialog)
CDataImageCtrlEditorDlg::CDataImageCtrlEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataImageCtrlEditorDlg::IDD, pParent)
	, mDataLength(0)
	, mFillValue(0)
{
}

CDataImageCtrlEditorDlg::~CDataImageCtrlEditorDlg()
{
}

void CDataImageCtrlEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_LENGTH, mDataLength);
	DDX_Text(pDX, IDC_FILL_VALUE, mFillValue);
}


BEGIN_MESSAGE_MAP(CDataImageCtrlEditorDlg, CDialog)
	ON_COMMAND(ID_DICEM_FILE_OPEN, OnDicemFileOpen)
	ON_BN_CLICKED(IDC_PROCESS_FILL, OnBnClickedProcessFill)
END_MESSAGE_MAP()

void CDataImageCtrlEditorDlg::SetDataFactory(IDataFactory* pData)
{
	pDataFactory = pData;
}

// CDataImageCtrlEditorDlg message handlers

void CDataImageCtrlEditorDlg::OnDicemFileOpen()
{
	// TODO: Add your command handler code here
	ASSERT(pDataFactory != NULL);		

/*	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "PGM Files|*.pgm|BMP Files|*.bmp||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		IDataFactory* pFactory = CCollectionConverterOperation_LoadImage::LoadImage(
			mFileDlg.GetPathName());
		if (pFactory)
		{
			if (pFactory->GetDataLength() == pDataFactory->GetDataLength())
				pDataFactory->SetData(pFactory->GetData(), pDataFactory->GetDataLength());
			else
				AfxMessageBox("Wrong image size.");	

			pFactory->ReleaseFactory();
			delete pFactory;
		} else
			AfxMessageBox("Wrong data file.");
	}*/
}

BOOL CDataImageCtrlEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT(pDataFactory != NULL);
	
	mDataLength = pDataFactory->GetDataLength();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataImageCtrlEditorDlg::OnBnClickedProcessFill()
{
	// TODO: Add your control notification handler code here
	ASSERT(pDataFactory != NULL);	

	UpdateData(TRUE);

	pDataFactory->FillFactory(mFillValue);
}
