// LearnLayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HopfieldLearning.h"
#include "LearnLayerDlg.h"
#include ".\learnlayerdlg.h"

#include "interface_idds.h"
#include "CmnFactory.h"

#include "Math.h"

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

// CLearnLayerDlg dialog

IMPLEMENT_DYNAMIC(CLearnLayerDlg, CDialog)
CLearnLayerDlg::CLearnLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLearnLayerDlg::IDD, pParent)
	, mSymbols(0)
	, mSymbol(0)
{
}

CLearnLayerDlg::~CLearnLayerDlg()
{
	ReleaseDataSymbols();
}

void CLearnLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SYMBOLS_COUNT, mSymbolsCount);
	DDX_Control(pDX, IDC_SYMBOL_NUMBER, mSymbolNumber);
	DDX_Control(pDX, IDC_UPSHOW, mUpShowSymbol);
	DDX_Control(pDX, IDC_DOWNSHOW, mDownShowSymbol);
	DDX_Control(pDX, IDC_FILENAME, mFileName);
	DDX_Text(pDX, IDC_SYMBOLS_COUNT, mSymbols);
	DDX_Text(pDX, IDC_SYMBOL_NUMBER, mSymbol);
	DDX_Control(pDX, IDC_STUDY_LAYER_LOG, mStudyLog);
	DDX_Control(pDX, IDC_RESET_WEIGHTS, mResetWeights);
	DDX_Control(pDX, IDC_STUDY_LAYERS, mStudyLayers);
	DDX_Control(pDX, IDC_LAYERS_LIST, mLayersList);
	DDX_Control(pDX, IDC_CTRL_PROP, mCtrlProp);
}


BEGIN_MESSAGE_MAP(CLearnLayerDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_LOAD_FILE, OnBnClickedLoadFile)
	ON_BN_CLICKED(IDC_UPSHOW, OnBnClickedUpshow)
	ON_BN_CLICKED(IDC_DOWNSHOW, OnBnClickedDownshow)
	ON_BN_CLICKED(IDC_STUDY_LAYER, OnBnClickedStudyLayer)
	ON_BN_CLICKED(IDC_RESET_WEIGHTS, OnBnClickedResetWeights)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LAYERS_LIST, OnLvnItemchangedLayersList)
	ON_BN_CLICKED(IDC_CTRL_PROP, OnBnClickedCtrlProp)
END_MESSAGE_MAP()


// CLearnLayerDlg message handlers

void CLearnLayerDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CLearnLayerDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CLearnLayerDlg::EnumerateLayers()
{
	IElementsCollection* pElementsCollection = NULL;
	pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

	int iFoundLayersCount = 0;

	pElementsCollection->CreateElementsEnumerator();
	while (IElement* pElement = pElementsCollection->GetNextElement())
	{
		if (pElement->GetElementTitle() == _T("Hopfield Layer"))
		{
			iFoundLayersCount++;

			ILayerControl* pLayerControl = NULL;
			pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

			CString tmTitle;
			tmTitle.Format("Hopfield Layer %d", pElement->GetElementID());
			CString tmDimension;
			tmDimension.Format("%d", pLayerControl->GetDimension());

			AddListItem(&mLayersList, -1, (LPARAM)pElement, 2, tmTitle, tmDimension);
		}
	}

	if (iFoundLayersCount == 0)
	{
		AfxMessageBox("Network does not contain any Hopfield Layers.");
		
		mLayersList.EnableWindow(FALSE);
	}
}

BOOL CLearnLayerDlg::Create(int iIDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(iIDD, pParentWnd);

	if (bRet)
	{
		mDataImageCtrl.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(24, 250, 215, 250 + 191), 
			this, IDC_L_DATAIMAGECTRL);

		mUpShowSymbol.SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
		mDownShowSymbol.SetIcon(AfxGetApp()->LoadIcon(IDI_DOWNARROW));	

		mCtrlProp.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));	

		EnableDataControlSection(FALSE);
		mResetWeights.EnableWindow(FALSE);

		CRect rect;
		mLayersList.GetClientRect(&rect);
		mLayersList.InsertColumn(0, _T("Name"), LVCFMT_LEFT,  rect.Width()*8/10); 
		mLayersList.InsertColumn(1, _T("Dimension"), LVCFMT_LEFT,  rect.Width()*2/10); 
		mLayersList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

		EnumerateLayers();
	}	

	return bRet;
}

void CLearnLayerDlg::EnableDataControlSection(BOOL bEnable)
{
	mDataImageCtrl.EnableWindow(bEnable);
	mSymbolsCount.EnableWindow(bEnable);
	mSymbolNumber.EnableWindow(bEnable);
	mUpShowSymbol.EnableWindow(bEnable);
	mDownShowSymbol.EnableWindow(bEnable);
	mCtrlProp.EnableWindow(bEnable);

	if (mLayersList.GetItemCount() == 0)
		bEnable = FALSE;
	mStudyLayers.EnableWindow(bEnable);	
}

void CLearnLayerDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data file v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
		mFileName.SetWindowText(mFileDlg.GetPathName());
}

void CLearnLayerDlg::ReleaseDataSymbols()
{
	mDataFile.FreeLoadedData();
}

void CLearnLayerDlg::OnBnClickedLoadFile()
{
	// TODO: Add your control notification handler code here
	CString csFileName;
	mFileName.GetWindowText(csFileName);

	if (csFileName.GetLength() < 1)
	{
		AfxMessageBox("Wrong data file name.");
		return;
	}

	if (!mDataFile.LoadFile(csFileName))
	{
		AfxMessageBox("Wrong data file.");
		return;	
	}

	if (mDataFile.GetInputSymbolsCount() == 0)
	{
		AfxMessageBox("Wrong data file contexts.\nData file does not contain any symbols for training layer(s).");
		return;	
	}

	UpdateData(TRUE);
	mSymbols = mDataFile.GetInputSymbolsCount();
	mSymbol	= 1;
	UpdateData(FALSE);

	int iXDimension = sqrt((mDataFile.GetInputSymbolLength() - 1)*1.0f) + 1;
	int iYDimension = (mDataFile.GetInputSymbolLength() - 1)/iXDimension + 1;

	mDataImageCtrl.SetCtrlParams(iXDimension, iYDimension);
	mDataImageCtrl.SetCtrlData(mDataFile.GetInputSymbol(0));
	mDataImageCtrl.Invalidate();

	EnableDataControlSection(TRUE);
}

void CLearnLayerDlg::OnBnClickedUpshow()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mSymbol > 1)
	{
		mSymbol--;
		mDataImageCtrl.SetCtrlData(mDataFile.GetInputSymbol(mSymbol-1));
		mDataImageCtrl.Invalidate();
	}
	
	UpdateData(FALSE);
}

void CLearnLayerDlg::OnBnClickedDownshow()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mSymbol < mDataFile.GetInputSymbolsCount())
	{
		mSymbol++;
		mDataImageCtrl.SetCtrlData(mDataFile.GetInputSymbol(mSymbol-1));
		mDataImageCtrl.Invalidate();
	}
	
	UpdateData(FALSE);
}

void CLearnLayerDlg::OnBnClickedStudyLayer()
{	
	// TODO: Add your control notification handler code here

	mStudyLog.ResetContent();

	bool bLayersFound = false;

	AddLogMessage(CString("Enumerating checked layers..."));

    for (int i = 0;i < mLayersList.GetItemCount();i++)
	{
		if (mLayersList.GetCheck(i))
		{			
			bLayersFound = true;

			IElement* pElement = (IElement*)mLayersList.GetItemData(i);
			ILayerControl* pLayerControl = NULL;
			pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);

			if (pLayerControl->GetDimension() != mDataFile.GetInputSymbolLength())
			{
				CString tmErrorString;
				tmErrorString.Format("Error: Layer %d. Layer's dimension does not equal", pElement->GetElementID());
				AddLogMessage(tmErrorString);
				AddLogMessage(CString("   to the length of loaded data symbols."));
				continue;		
			}

			for(int j = 0;j < mDataFile.GetInputSymbolsCount();j++)
			{					
				pLayerControl->SetInputData(mDataFile.GetInputSymbol(j));
				pLayerControl->ModifyWeights();	
			}

			CString tmMessageString;
			tmMessageString.Format("Layer %d. Training finished.", pElement->GetElementID());
			AddLogMessage(tmMessageString);
		}	
	}

	if (!bLayersFound)
		AddLogMessage(CString("No layers where checked to be trained."));
}

void CLearnLayerDlg::OnBnClickedResetWeights()
{
	// TODO: Add your control notification handler code here
	int iItem = mLayersList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem != -1)
	{
		IElement* pElement = (IElement*)mLayersList.GetItemData(iItem);
		ILayerControl* pLayerControl = NULL;
		pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);			

		pLayerControl->ResetWeights(0.0f);
	}
}

void CLearnLayerDlg::OnLvnItemchangedLayersList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int iSelectedCount = mLayersList.GetSelectedCount();
	if (iSelectedCount == 1)
		mResetWeights.EnableWindow(TRUE);
	else
		mResetWeights.EnableWindow(FALSE);
}

void CLearnLayerDlg::AddLogMessage(CString& message)
{
	mStudyLog.AddString(message);
}

void CLearnLayerDlg::OnBnClickedCtrlProp()
{
	// TODO: Add your control notification handler code here
	mDataImageCtrl.ShowPropertiesDlg();
}
