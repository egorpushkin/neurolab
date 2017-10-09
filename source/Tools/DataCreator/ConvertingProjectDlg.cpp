// ConvertingProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "ConvertingProjectDlg.h"
#include ".\convertingprojectdlg.h"

#include "NewConvertingProjectDlg.h"
#include "NewConverterItemDlg.h"

#include "SelectDataSymbolDlg.h"
#include "SelectCollectionGroupDlg.h"

#include "ExportCollectionDlg.h"

// CConvertingProjectDlg dialog

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
{
	LV_ITEM item;
    item.iItem = m_List->GetItemCount();
    item.iImage = icon;
	item.lParam = data;
   
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

	va_list params;
	va_start(params, num);
	char * temp = va_arg(params,char *);

	item.iSubItem = 0;
    item.pszText = temp;
    m_List->InsertItem(&item);

	for(int i = 1;i<num;i++)
	{
		temp = va_arg(params,char *);
		item.mask = LVIF_TEXT;
		item.iSubItem = i;
		item.pszText = temp;
		m_List->SetItem(&item);
	}
} 

IMPLEMENT_DYNAMIC(CConvertingProjectDlg, CDialog)
CConvertingProjectDlg::CConvertingProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertingProjectDlg::IDD, pParent)
	, mDCName(_T(""))
	, mDFOutputsCount(_T(""))
	, mProjectName(_T(""))
{
	bModified = false;
}

CConvertingProjectDlg::~CConvertingProjectDlg()
{
}

void CConvertingProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROJECT_CONTENT, mProjectContent);
	DDX_Text(pDX, IDC_DATA_COLLECTION_NAME, mDCName);
	DDX_Text(pDX, IDC_DATA_FILE_OUTPUTS, mDFOutputsCount);
	DDX_Text(pDX, IDC_PROJ_NAME, mProjectName);
}


BEGIN_MESSAGE_MAP(CConvertingProjectDlg, CDialog)
	ON_BN_CLICKED(IDC_NEW_PROJECT, OnBnClickedNewProject)
	ON_BN_CLICKED(IDC_CLOSE_PROJECT, OnBnClickedCloseProject)
	ON_BN_CLICKED(IDC_LOAD_PROJECT, OnBnClickedLoadProject)
	ON_BN_CLICKED(IDC_SAVE_PROJECT, OnBnClickedSaveProject)
	ON_BN_CLICKED(IDC_ADD_ENTRY, OnBnClickedAddEntry)
	ON_BN_CLICKED(IDC_EDIT_ENTRY, OnBnClickedEditEntry)
	ON_BN_CLICKED(IDC_REMOVE_ENTRY, OnBnClickedRemoveEntry)
	ON_BN_CLICKED(IDC_DATA_COLLECTION_DETAILS, OnBnClickedDataCollectionDetails)
	ON_BN_CLICKED(IDC_DATA_FILE_DETAILS, OnBnClickedDataFileDetails)
	ON_BN_CLICKED(IDC_EXPORT_PROJECT, OnBnClickedExportProject)
END_MESSAGE_MAP()


// CConvertingProjectDlg message handlers

BOOL CConvertingProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect	rect;
	mProjectContent.GetClientRect(&rect);

	mProjectContent.InsertColumn(0, _T("Group Name"), LVCFMT_LEFT,  rect.Width()*7.5/10); 
	mProjectContent.InsertColumn(1, _T("Symbol"), LVCFMT_LEFT,  rect.Width()*2/10); 
	mProjectContent.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConvertingProjectDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CConvertingProjectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CConvertingProjectDlg::OnBnClickedNewProject()
{
	// TODO: Add your control notification handler code here
	bool bShowAddNewProjDlg = true;

	if (mDataConverter.IsCreated())
	{
		int res = AfxMessageBox("The project is already created.\nAre you sure that you want to close it?", MB_YESNO);
		if (res != IDYES)
			bShowAddNewProjDlg = false;
		else
			if (bModified)
			{
				res = AfxMessageBox("The project has been modified since the last save operation.\nDo you want to save it?", MB_YESNO);
				if (res == IDYES)
					OnBnClickedSaveProject();
			}		

		if (bShowAddNewProjDlg)
			ProcessCloseProject();
	}

	if (bShowAddNewProjDlg)
	{
		CNewConvertingProjectDlg mNewProj;
		int res = mNewProj.DoModal();
		if (res == IDOK)
		{
			if (mDataConverter.CreateProject(
				mNewProj.mProjectName,
				mNewProj.csDataFileName, 
				mNewProj.csDataCollectionFileName))
			{
				UpdateProjectInformation();
				UpdateCollectionInformation();
				UpdateDataFileInformation();
				
				EnableInterface(TRUE);

				bModified = true;
			} else
			{
				EnableInterface(FALSE);			
			}
		}
	}
}

void CConvertingProjectDlg::OnBnClickedCloseProject()
{
	// TODO: Add your control notification handler code here
	if (!mDataConverter.IsCreated())
	{
		AfxMessageBox("The project has not been created yet.");
		return;
	}

	if (bModified)
	{
		int res = AfxMessageBox("The project has been modified since the last save operation.\nDo you want to save it?", MB_YESNO);
		if (res == IDYES)
			OnBnClickedSaveProject();
	}	

	ProcessCloseProject();
}

void CConvertingProjectDlg::OnBnClickedLoadProject()
{
	// TODO: Add your control notification handler code here
	bool bLoadProj = true;
	if (mDataConverter.IsCreated())
	{
		int res = AfxMessageBox("The project has already been created.\nAre you sure that you want to close it?", MB_YESNO);
		if (res != IDYES)
			bLoadProj = false;
		else
			if (bModified)
			{
				res = AfxMessageBox("The project has been modified since the last save operation.\nDo you want to save it?", MB_YESNO);
				if (res == IDYES)
					OnBnClickedSaveProject();
			}	

		if (bLoadProj)
			ProcessCloseProject();
	}

	if (bLoadProj)
	{
		CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Collection Converting Project v1.0|*.nlccproj||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			if (mDataConverter.LoadProject(mFileDlg.GetPathName()))
			{				
				bModified = false;

				EnableInterface(TRUE);
				ShowConverterProjectItems();
				
				UpdateProjectInformation();	
				UpdateCollectionInformation();
				UpdateDataFileInformation();
					
				AfxMessageBox("Converting project was successfully loaded.");
			}		
		}
	}
}

void CConvertingProjectDlg::OnBnClickedSaveProject()
{
	// TODO: Add your control notification handler code here
	if (!mDataConverter.IsCreated())
	{
		AfxMessageBox("The project has not been created yet.");
		return;
	}

	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Collection Converting Project v1.0|*.nlccproj||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		if (mDataConverter.SaveProject(mFileDlg.GetPathName()))
		{				
			bModified = false;
			
			AfxMessageBox("Converting project was successfully saved.");
		}		
	}
}

void CConvertingProjectDlg::EnableInterface(BOOL bEnable)
{
	GetDlgItem(IDC_DATA_COLLECTION_DETAILS)->EnableWindow(bEnable);
	GetDlgItem(IDC_DATA_FILE_DETAILS)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROJECT_CONTENT)->EnableWindow(bEnable);
	GetDlgItem(IDC_ADD_ENTRY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ENTRY)->EnableWindow(bEnable);
	GetDlgItem(IDC_REMOVE_ENTRY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EXPORT_PROJECT)->EnableWindow(bEnable);
}

void CConvertingProjectDlg::UpdateCollectionInformation()
{
	UpdateData(TRUE);

	if (mDataConverter.GetDataCollection()->IsCreated())
	{
		mDCName = mDataConverter.GetDataCollection()->GetCollectionName();	
	} else
	{
		mDCName = _T("<not loaded>");
	}

	UpdateData(FALSE);
}

void CConvertingProjectDlg::UpdateDataFileInformation()
{
	UpdateData(TRUE);

	if (mDataConverter.GetDataFile()->IsLoaded())
	{
		mDFOutputsCount.Format("%d", mDataConverter.GetDataFile()->GetOutputSymbolsCount());
	} else
	{
		mDFOutputsCount = _T("<not loaded>");
	}

	UpdateData(FALSE);
}

void CConvertingProjectDlg::UpdateProjectInformation()
{
	UpdateData(TRUE);

	mProjectName = mDataConverter.GetProjectName();

	UpdateData(FALSE);
}

void CConvertingProjectDlg::OnBnClickedAddEntry()
{
	// TODO: Add your control notification handler code here
	CNewConverterItemDlg mDlg;

	IDataFile* pDataFile = NULL;
	mDataConverter.GetDataFile()->QueryInterface(IDD_IDataFile, (void**)&pDataFile);
	mDlg.SetDataFile(pDataFile);

	IDataCollection* pDataCollection = NULL;
	mDataConverter.GetDataCollection()->QueryInterface(IDD_IDataCollection, (void**)&pDataCollection);
	mDlg.SetDataCollection(pDataCollection);

	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		CConverterItem* pItem = mDataConverter.AddConverterItem(mDlg.mGroupName, mDlg.mSymbolIndex);

		CString tmSymbol;
		tmSymbol.Format("%d", mDlg.mSymbolIndex);

		AddListItem(&mProjectContent, -1, (LPARAM)pItem, 2, mDlg.mGroupName, tmSymbol);

		bModified = true;
	}
}

void CConvertingProjectDlg::OnBnClickedEditEntry()
{
	// TODO: Add your control notification handler code here
}

void CConvertingProjectDlg::OnBnClickedRemoveEntry()
{
	// TODO: Add your control notification handler code here

}

void CConvertingProjectDlg::OnBnClickedDataCollectionDetails()
{
	// TODO: Add your control notification handler code here
	CSelectCollectionGroupDlg mDlg;

	IDataCollection* pDataCollection = NULL;
	mDataConverter.GetDataCollection()->QueryInterface(IDD_IDataCollection, (void**)&pDataCollection);
	mDlg.SetDataCollection(pDataCollection);

	mDlg.DoModal();
}

void CConvertingProjectDlg::OnBnClickedDataFileDetails()
{
	// TODO: Add your control notification handler code here
	CSelectDataSymbolDlg mDlg;
	
	IDataFile* pDataFile = NULL;
	mDataConverter.GetDataFile()->QueryInterface(IDD_IDataFile, (void**)&pDataFile);
	mDlg.SetDataFile(pDataFile, false);
	
	mDlg.DoModal();
}

void CConvertingProjectDlg::ShowConverterProjectItems()
{
	mProjectContent.DeleteAllItems();

	mDataConverter.CreateEnumerator();
	while (CConverterItem* pItem = mDataConverter.GetNextItem())
	{
		CString tmSymbol;
		tmSymbol.Format("%d", pItem->iDataSymbol);

		AddListItem(&mProjectContent, -1, (LPARAM)pItem, 2, pItem->csCollectionGroupName, tmSymbol);
	}			
}

void CConvertingProjectDlg::ProcessCloseProject()
{
	mDataConverter.ReleaseProject();

	EnableInterface(FALSE);
	UpdateCollectionInformation();
	UpdateDataFileInformation();	
	UpdateProjectInformation();	
	
	mProjectContent.DeleteAllItems();
}

void CConvertingProjectDlg::OnBnClickedExportProject()
{
	// TODO: Add your control notification handler code here
	CExportCollectionDlg mDlg;
	mDlg.SetCollectionConverter(&mDataConverter);
	mDlg.DoModal();
}
