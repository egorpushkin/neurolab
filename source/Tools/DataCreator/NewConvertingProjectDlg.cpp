// NewConvertingProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "NewConvertingProjectDlg.h"
#include ".\newconvertingprojectdlg.h"


// CNewConvertingProjectDlg dialog

IMPLEMENT_DYNAMIC(CNewConvertingProjectDlg, CDialog)
CNewConvertingProjectDlg::CNewConvertingProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewConvertingProjectDlg::IDD, pParent)
	, mProjectName(_T(""))
	, mDCFileName(_T(""))
	, mDCName(_T(""))
	, mDFFileName(_T(""))
	, mDFOutputsCount(0)
{
}

CNewConvertingProjectDlg::~CNewConvertingProjectDlg()
{
}

void CNewConvertingProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROJECT_NAME, mProjectName);
	DDX_Text(pDX, IDC_DATA_COLLECTION_FILE_NAME, mDCFileName);
	DDX_Text(pDX, IDC_DATA_COLLECTION_NAME, mDCName);
	DDX_Text(pDX, IDC_DATA_FILE_FILE_NAME, mDFFileName);
	DDX_Text(pDX, IDC_DATA_FILE_OUTPUTS_COUNT, mDFOutputsCount);
}


BEGIN_MESSAGE_MAP(CNewConvertingProjectDlg, CDialog)
	ON_BN_CLICKED(IDC_DATA_COLLECTION_LOAD, OnBnClickedDataCollectionLoad)
	ON_BN_CLICKED(IDC_DATA_FILE_LOAD, OnBnClickedDataFileLoad)
	ON_BN_CLICKED(IDC_DETAILS_DATA_COLLECTION, OnBnClickedDetailsDataCollection)
	ON_BN_CLICKED(IDC_DETEILS_DATA_FILE, OnBnClickedDeteilsDataFile)
END_MESSAGE_MAP()


// CNewConvertingProjectDlg message handlers

void CNewConvertingProjectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mProjectName == _T(""))
	{
		AfxMessageBox("You must enter project name.");
		return;
	}

	if (!mDataFile.IsLoaded())
	{
		AfxMessageBox("You must load data file to create converting project.");
		return;		
	}

	if (!mDataCollection.IsCreated())
	{
		AfxMessageBox("You must load data collection to create converting project.");
		return;		
	}

	CDialog::OnOK();
}

void CNewConvertingProjectDlg::OnBnClickedDataCollectionLoad()
{
	// TODO: Add your control notification handler code here
	bool bLoadDC = true;

	if (mDataCollection.IsCreated())
	{
		int res = AfxMessageBox("Data collection is already loaded.\nDo you want to close it and open another one?", MB_YESNO);
		if (res != IDYES)
			bLoadDC = false;
	}

	if (bLoadDC)
	{
		CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Collection File v1.0|*.nlcfile||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			if (mDataCollection.LoadCollection(mFileDlg.GetPathName()))
			{
				csDataCollectionFileName = mFileDlg.GetPathName();
				
				UpdateCollectionInformation();
			}
		}		
	}
}

void CNewConvertingProjectDlg::OnBnClickedDataFileLoad()
{
	// TODO: Add your control notification handler code here
	bool bLoadDF = true;

	if (mDataFile.IsLoaded())
	{
		int res = AfxMessageBox("Data file is already loaded.\nDo you want to close it and open another one?", MB_YESNO);
		if (res != IDYES)
			bLoadDF = false;
	}

	if (bLoadDF)
	{
		CFileDialog	mFileDlg(true, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			if (mDataFile.LoadFile(mFileDlg.GetPathName()))
			{
				csDataFileName = mFileDlg.GetPathName();
			
				UpdateDataFileInformation();
			}
		}	
	}
}

void CNewConvertingProjectDlg::OnBnClickedDetailsDataCollection()
{
	// TODO: Add your control notification handler code here
}

void CNewConvertingProjectDlg::OnBnClickedDeteilsDataFile()
{
	// TODO: Add your control notification handler code here
}

void CNewConvertingProjectDlg::UpdateCollectionInformation()
{
	UpdateData(TRUE);

	if (mDataCollection.IsCreated())
	{
		mDCFileName = csDataCollectionFileName;
		mDCName = mDataCollection.GetCollectionName();		
	} else
	{
		mDCFileName = _T("");
		mDCName = _T("");
	}

	GetDlgItem(IDC_DETAILS_DATA_COLLECTION)->EnableWindow(mDataCollection.IsCreated());

	UpdateData(FALSE);
}

void CNewConvertingProjectDlg::UpdateDataFileInformation()
{
	UpdateData(TRUE);

	if (mDataFile.IsLoaded())
	{
		mDFFileName = csDataFileName;
		mDFOutputsCount = mDataFile.GetOutputSymbolsCount();		
	} else
	{
		mDFFileName = _T("");
		mDFOutputsCount = 0;
	}

	GetDlgItem(IDC_DETEILS_DATA_FILE)->EnableWindow(mDataFile.IsLoaded());

	UpdateData(FALSE);	


}