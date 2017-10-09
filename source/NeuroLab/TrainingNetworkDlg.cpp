// TrainingNetworkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "TrainingNetworkDlg.h"
#include ".\trainingnetworkdlg.h"

#include "TrainerToolDlg.h"

// CTrainingNetworkDlg dialog

IMPLEMENT_DYNAMIC(CTrainingNetworkDlg, CDialog)
CTrainingNetworkDlg::CTrainingNetworkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainingNetworkDlg::IDD, pParent)
	, mDataState(_T(""))
	, mInputsCount(0)
	, mInputSymbolLength(0)
	, mOutputsCount(0)
	, mOutputSymbolLength(0)
{
	bIsDataLoaded = false;

	pAppController = NULL;
	pTrainersContainer = NULL;
}

CTrainingNetworkDlg::~CTrainingNetworkDlg()
{
}

void CTrainingNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_STATUS, mDataState);
	DDX_Control(pDX, IDC_DATA_DETAILS, mDataDetailsCtrl);
	DDX_Text(pDX, IDC_INPUTS_COUNT, mInputsCount);
	DDX_Text(pDX, IDC_INPUT_SYMBOL_LENGTH, mInputSymbolLength);
	DDX_Text(pDX, IDC_OUTPUTS_COUNT, mOutputsCount);
	DDX_Text(pDX, IDC_OUTPUT_SYMBOL_LENGTH, mOutputSymbolLength);
	DDX_Control(pDX, IDC_TRAINING_METHODS_TREE, mTrainingsTree);
	DDX_Control(pDX, IDC_CONFIGURE_METHOD, mConfigureTrainer);
	DDX_Control(pDX, IDC_START_TRAINING, mStartTraining);
}


BEGIN_MESSAGE_MAP(CTrainingNetworkDlg, CDialog)
	ON_BN_CLICKED(IDC_DATA_DETAILS, OnBnClickedDataDetails)
	ON_BN_CLICKED(IDC_LOAD_DATA, OnBnClickedLoadData)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TRAINING_METHODS_TREE, OnTvnSelchangedTrainingMethodsTree)
	ON_BN_CLICKED(IDC_CONFIGURE_METHOD, OnBnClickedConfigureMethod)
	ON_BN_CLICKED(IDC_START_TRAINING, OnBnClickedStartTraining)
	ON_NOTIFY(NM_DBLCLK, IDC_TRAINING_METHODS_TREE, OnNMDblclkTrainingMethodsTree)
END_MESSAGE_MAP()

void CTrainingNetworkDlg::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

void CTrainingNetworkDlg::SetTrainersContainer(ITrainersContainer* pContainer)
{
	pTrainersContainer = pContainer;
}

// CTrainingNetworkDlg message handlers

void CTrainingNetworkDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CTrainingNetworkDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

BOOL CTrainingNetworkDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(IDD, pParentWnd);

	if (bRet)
	{
		if (pTrainersContainer)
		{
			IElementsCollection* pCollection = NULL;
			pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pCollection);
			
			HTREEITEM htiRoot = mTrainingsTree.InsertItem("Network Trainers v1.0");
			
			pTrainersContainer->CreateEnumerator();
			while(ITrainer* pTrainer = pTrainersContainer->GetNextTrainer())
			{
				TRAINER_INFO tmInfo;					
				pTrainer->GetTrainerInfo(&tmInfo);

				HTREEITEM htiItem = mTrainingsTree.InsertItem(tmInfo.csTrainerName, htiRoot);
				mTrainingsTree.SetItemData(htiItem, (DWORD_PTR)pTrainer);			

				pTrainer->SetDataFile(&mDataFile);
				pTrainer->SetElementsFactory(pCollection);
			}	

			mTrainingsTree.Expand(htiRoot, TVE_EXPAND);
		
		} else
			mTrainingsTree.InsertItem("No trainers found");		

		mDataState = _T("Not loaded");

		UpdateData(FALSE);	

		mConfigureTrainer.EnableWindow(FALSE);
		mStartTraining.EnableWindow(FALSE);	
	}

	return bRet;
}

void CTrainingNetworkDlg::OnBnClickedDataDetails()
{
	// TODO: Add your control notification handler code here
}

void CTrainingNetworkDlg::OnBnClickedLoadData()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data file v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		bIsDataLoaded = mDataFile.LoadFile(mFileDlg.GetPathName());

		if (bIsDataLoaded)
		{
			UpdateData(TRUE);
			mDataState = _T("Loaded");

			mInputsCount = mDataFile.GetInputSymbolsCount();
			mInputSymbolLength = mDataFile.GetInputSymbolLength();
			mOutputsCount = mDataFile.GetOutputSymbolsCount();
			mOutputSymbolLength = mDataFile.GetOutputSymbolLength();

			UpdateData(FALSE);			
		}
	}
}

void CTrainingNetworkDlg::OnTvnSelchangedTrainingMethodsTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	bool bFoundTrainer = false;

	HTREEITEM thiItem = mTrainingsTree.GetSelectedItem();
	if (thiItem)
	{
		ITrainer* pTrainer = (ITrainer*)mTrainingsTree.GetItemData(thiItem);
		if (pTrainer)
			bFoundTrainer = true;
	}

	mConfigureTrainer.EnableWindow(bFoundTrainer);
	mStartTraining.EnableWindow(bFoundTrainer);
}

void CTrainingNetworkDlg::OnBnClickedConfigureMethod()
{
	// TODO: Add your control notification handler code here
	HTREEITEM thiItem = mTrainingsTree.GetSelectedItem();
	if (thiItem)
	{
		ITrainer* pTrainer = (ITrainer*)mTrainingsTree.GetItemData(thiItem);
		if (pTrainer)
			pTrainer->Configure();
	}
}

void CTrainingNetworkDlg::OnBnClickedStartTraining()
{
	// TODO: Add your control notification handler code here
	HTREEITEM thiItem = mTrainingsTree.GetSelectedItem();
	if (thiItem)
	{
		ITrainer* pTrainer = (ITrainer*)mTrainingsTree.GetItemData(thiItem);
		if (pTrainer)
		{
			CTrainerToolDlg mDlg;
			mDlg.SetTrainer(pTrainer);
			mDlg.DoModal();
		}
	}
}

void CTrainingNetworkDlg::OnNMDblclkTrainingMethodsTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	OnBnClickedStartTraining();
}
