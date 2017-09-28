// ExportCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "ExportCollectionDlg.h"
#include ".\exportcollectiondlg.h"

#include "interface_idds.h"

#include "CollectionConverter/Operation_Convert.h"

// CExportCollectionDlg dialog

IMPLEMENT_DYNAMIC(CExportCollectionDlg, CDialog)
CExportCollectionDlg::CExportCollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportCollectionDlg::IDD, pParent)
	, mFileName(_T(""))
	, mDimension(0)
{
	mConverter = NULL;
}

CExportCollectionDlg::~CExportCollectionDlg()
{
}

void CExportCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESTINATION_FILE_NAME, mFileName);
	DDX_Text(pDX, IDC_DATA_FILE_INPUT_DIMENSION, mDimension);
	DDX_Control(pDX, IDC_LIST1, mLog);
}


BEGIN_MESSAGE_MAP(CExportCollectionDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_CONVERT, OnBnClickedConvert)
END_MESSAGE_MAP()


// CExportCollectionDlg message handlers

void CExportCollectionDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);

		mFileName = mFileDlg.GetPathName();

		UpdateData(FALSE);
	}
}

void CExportCollectionDlg::OnBnClickedConvert()
{
	// TODO: Add your control notification handler code here
	ASSERT(mConverter != NULL);

	UpdateData(TRUE);
    
	ClearLog();

	if (mDimension <= 0)
	{
		AddLogMessage(CString(""), 
			CString("You must enter symbol dimension before starting conversion."), 
			CString(""));
		return;
	}

	if (mFileName == _T(""))
	{
		AddLogMessage(CString(""), 
			CString("You must select destination file before starting conversion."), 
			CString(""));
		return;
	}

	AddLogMessage(CString(""), CString("Starting converting..."), CString(""));	
	AddLogMessage(CString(""), CString("------------------------------------------"), CString(""));	

	ILogProvider* pLog = NULL;
	QueryInterface(IDD_ILogProvider, (void**)&pLog);

	if (CCollectionConverterOperation_Convert::ProcessConverting(
		mConverter, mFileName, mDimension, pLog))
	{
		AddLogMessage(CString(""), CString("------------------------------------------"), CString(""));	
		AddLogMessage(CString(""), CString("Ñonverting successfully finished."), CString(""));	
	} else
	{
		AddLogMessage(CString(""), CString("------------------------------------------"), CString(""));	
		AddLogMessage(CString(""), CString("Ñonverting failed. See log for the details."), CString(""));	
	}
}

// ILogProvider implementations section
void CExportCollectionDlg::ClearLog()
{
	mLog.ResetContent();
}
void CExportCollectionDlg::AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection)
{
	mLog.AddString(Message);
}

// IObject implementations section
CString CExportCollectionDlg::GetClassString()
{
	return _T("CExportCollectionDlg");
}

void CExportCollectionDlg::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;

	switch (iIDD)
	{
	case IDD_ILogProvider:
		*ppvObject = (ILogProvider*)this;
		break;	
	}
}


void CExportCollectionDlg::SetCollectionConverter(CCollectionConverter* Converter)
{
	mConverter = Converter;
}

