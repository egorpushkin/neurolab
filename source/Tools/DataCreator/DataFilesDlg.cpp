// DataFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataCreator.h"
#include "DataFilesDlg.h"
#include ".\datafilesdlg.h"

#include "Math.h"

#include "NewDataFileDlg.h"

// CDataFilesDlg dialog

IMPLEMENT_DYNAMIC(CDataFilesDlg, CDialog)
CDataFilesDlg::CDataFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataFilesDlg::IDD, pParent)
	, mFileName(_T(""))
	, mInputLength(0)
	, mOutputLength(0)
	, mModifiedState(_T(""))
	, mInputNumber(0)
	, mOutputNumber(0)
	, mTotalInputs(0)
	, mTotalOutputs(0)
	, mInputMarker(0)
	, mOutputMarker(0)
{
}

CDataFilesDlg::~CDataFilesDlg()
{
}

void CDataFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UP_LIST_INPUTS, mUpListInputs);
	DDX_Control(pDX, IDC_DOWN_LIST_INPUTS, mDownListInputs);
	DDX_Control(pDX, IDC_UP_LIST_OUTPUTS, mUpListOutputs);
	DDX_Control(pDX, IDC_DOWN_LIST_OUTPUTS, mDownListOutputs);
	DDX_Text(pDX, IDC_FILE_NAME, mFileName);
	DDX_Text(pDX, IDC_INPUT_LENGTH, mInputLength);
	DDX_Text(pDX, IDC_OUTPUT_LENGTH, mOutputLength);
	DDX_Text(pDX, IDC_MODIFIED_STATE, mModifiedState);
	DDX_Control(pDX, IDC_SAVE, mSaveCtrl);
	DDX_Text(pDX, IDC_INPUT_NUMBER, mInputNumber);
	DDX_Text(pDX, IDC_OUTPUT_NUMBER, mOutputNumber);
	DDX_Text(pDX, IDC_TOTAL_INPUTS, mTotalInputs);
	DDX_Text(pDX, IDC_TOTAL_OUTPUTS, mTotalOutputs);
	DDX_Text(pDX, IDC_INPUT_MARKER, mInputMarker);
	DDX_Text(pDX, IDC_OUTPUT_MARKER, mOutputMarker);
	DDX_Control(pDX, IDC_ADD_INPUT_SYMBOL, mAddInput);
	DDX_Control(pDX, IDC_REMOVE_INPUT_SYMBOL, mRemoveInput);
	DDX_Control(pDX, IDC_SET_INPUT_MARKER, mSetInputMarker);
	DDX_Control(pDX, IDC_ADD_OUTPUT_SYMBOL, mAddOutput);
	DDX_Control(pDX, IDC_REMOVE_OUTPUT_SYMBOL, mRemoveOutput);
	DDX_Control(pDX, IDC_SET_OUTPUT_MARKER, mSetOutputMarker);
	DDX_Control(pDX, IDC_INPUT_CTRL_PROP, mInputCtrlProp);
	DDX_Control(pDX, IDC_OUTPUT_CTRL_PROP, mOutputCtrlProp);
	DDX_Control(pDX, IDC_SAVE_AS, mSaveAsCtrl);
	DDX_Control(pDX, IDC_INPUT_CTRL_EDITOR, mInputCtrlEditor);
	DDX_Control(pDX, IDC_OUTPUT_CTRL_EDITOR, mOutputCtrlEditor);
}


BEGIN_MESSAGE_MAP(CDataFilesDlg, CDialog)
	ON_BN_CLICKED(IDC_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_ADD_INPUT_SYMBOL, OnBnClickedAddInputSymbol)
	ON_BN_CLICKED(IDC_REMOVE_INPUT_SYMBOL, OnBnClickedRemoveInputSymbol)
	ON_BN_CLICKED(IDC_SET_INPUT_MARKER, OnBnClickedSetInputMarker)
	ON_BN_CLICKED(IDC_UP_LIST_INPUTS, OnBnClickedUpListInputs)
	ON_BN_CLICKED(IDC_DOWN_LIST_INPUTS, OnBnClickedDownListInputs)
	ON_BN_CLICKED(IDC_INPUT_CTRL_PROP, OnBnClickedInputCtrlProp)
	ON_BN_CLICKED(IDC_ADD_OUTPUT_SYMBOL, OnBnClickedAddOutputSymbol)
	ON_BN_CLICKED(IDC_REMOVE_OUTPUT_SYMBOL, OnBnClickedRemoveOutputSymbol)
	ON_BN_CLICKED(IDC_SET_OUTPUT_MARKER, OnBnClickedSetOutputMarker)
	ON_BN_CLICKED(IDC_UP_LIST_OUTPUTS, OnBnClickedUpListOutputs)
	ON_BN_CLICKED(IDC_DOWN_LIST_OUTPUTS, OnBnClickedDownListOutputs)
	ON_BN_CLICKED(IDC_OUTPUT_CTRL_PROP, OnBnClickedOutputCtrlProp)
	ON_BN_CLICKED(IDC_LOAD, OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_SAVE_AS, OnBnClickedSaveAs)
	ON_BN_CLICKED(IDC_INPUT_CTRL_EDITOR, OnBnClickedInputCtrlEditor)
	ON_BN_CLICKED(IDC_OUTPUT_CTRL_EDITOR, OnBnClickedOutputCtrlEditor)
END_MESSAGE_MAP()


// CDataFilesDlg message handlers

void CDataFilesDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CDataFilesDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
}

BOOL CDataFilesDlg::Create(int IDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(IDD, pParentWnd);

	if (bRet)
	{
		int iXCoord = 24;
		int iYCoord = 150;

		mInputBuilder.SetCtrlParams(10, 10, true);
		mInputBuilder.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 202, iYCoord + 177), 
			this, IDC_INPUT_SYMBOL_BUILDER);
		
		iXCoord = 297;
		iYCoord = 150;

		mOutputBuilder.SetCtrlParams(10, 10, true);
		mOutputBuilder.Create(NULL, "", WS_VISIBLE | WS_BORDER, 
			CRect(iXCoord, iYCoord, iXCoord + 202, iYCoord + 177), 
			this, IDC_OUTPUT_SYMBOL_BUILDER);

		mUpListInputs.SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
		mDownListInputs.SetIcon(AfxGetApp()->LoadIcon(IDI_DOWNARROW));

		mUpListOutputs.SetIcon(AfxGetApp()->LoadIcon(IDI_UPARROW));
		mDownListOutputs.SetIcon(AfxGetApp()->LoadIcon(IDI_DOWNARROW));

		mInputCtrlProp.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));
		mOutputCtrlProp.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_PROP));

		mInputCtrlEditor.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_EDITOR));
		mOutputCtrlEditor.SetIcon(AfxGetApp()->LoadIcon(IDI_CTRL_EDITOR));

		EnableInterface(FALSE);

		mInputMarker = -1.0f;
		mOutputMarker = -1.0f;

		UpdateData(FALSE);

		mInputBuilder.SetMarker(mInputMarker);
		mOutputBuilder.SetMarker(mOutputMarker);
	}

	return bRet;
}

void CDataFilesDlg::EnableInterface(bool bEnable)
{
	mInputBuilder.EnableWindow(bEnable);
	mUpListInputs.EnableWindow(bEnable);
	mDownListInputs.EnableWindow(bEnable);

	mAddInput.EnableWindow(bEnable);
	mRemoveInput.EnableWindow(bEnable);
	mSetInputMarker.EnableWindow(bEnable);

	mOutputBuilder.EnableWindow(bEnable);
	mUpListOutputs.EnableWindow(bEnable);
	mDownListOutputs.EnableWindow(bEnable);

	mAddOutput.EnableWindow(bEnable);
	mRemoveOutput.EnableWindow(bEnable);
	mSetOutputMarker.EnableWindow(bEnable);	

	mSaveCtrl.EnableWindow(bEnable);
	mSaveAsCtrl.EnableWindow(bEnable);

	mInputCtrlProp.EnableWindow(bEnable);
	mOutputCtrlProp.EnableWindow(bEnable);

	mInputCtrlEditor.EnableWindow(bEnable);
	mOutputCtrlEditor.EnableWindow(bEnable);

	UpdateData(TRUE);

	mInputNumber = 0;
	mTotalInputs = 0;	

	mOutputNumber = 0;
	mTotalOutputs = 0;

	mInputLength = 0;
	mOutputLength = 0;

	UpdateData(FALSE);

	SetModifiedState(false);
}

void CDataFilesDlg::SetModifiedState(bool bState)
{
	UpdateData(TRUE);
	bModified = bState;
	if (bState)
		mModifiedState = _T("True");
	else
		mModifiedState = _T("False");
	UpdateData(FALSE);	
}

void CDataFilesDlg::SetupControls(int InputLength, int OutputLength)
{
	SetModifiedState(false);

	UpdateData(TRUE);
	
	mInputLength = InputLength;
	mOutputLength = OutputLength;

	UpdateData(FALSE);

	SetupDataImageCtrl(&mInputBuilder, mInputLength);
	SetupDataImageCtrl(&mOutputBuilder, mOutputLength);
}

void CDataFilesDlg::SetupDataImageCtrl(CDataImageCtrl* pCtrl, int DataLength)
{
	int iXDimension = sqrt((DataLength - 1)*1.0f) + 1;
	int iYDimension = (DataLength - 1)/iXDimension + 1;

	pCtrl->SetCtrlParams(iXDimension, iYDimension);
	
	pCtrl->Invalidate();
}

void CDataFilesDlg::ShowInputSymbol(int Index)
{
	if (Index >= mDataFile.GetInputSymbolsCount() || Index < 0)
		return;

	UpdateData(TRUE);	
	mInputNumber = Index+1;
	UpdateData(FALSE);

	mInputBuilder.SetCtrlData(mDataFile.GetInputSymbol(Index));
	mInputBuilder.Invalidate();
}

void CDataFilesDlg::ShowOutputSymbol(int Index)
{
	if (Index >= mDataFile.GetOutputSymbolsCount() || Index < 0)
		return;

	UpdateData(TRUE);	
	mOutputNumber = Index+1;
	UpdateData(FALSE);

	mOutputBuilder.SetCtrlData(mDataFile.GetOutputSymbol(Index));
	mOutputBuilder.Invalidate();
}

void CDataFilesDlg::OnBnClickedNew()
{
	// TODO: Add your control notification handler code here
	if (bModified)
	{
		int res = AfxMessageBox(_T("Data was modified and would be lost in case of creating new data file.\nWould you like to save changes before performing the operation?"), MB_YESNO);
		if (res == IDYES)
		{
			OnBnClickedSave();
		}
	}

	CNewDataFileDlg mDlg;
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		mDataFile.CreateNewFile(mDlg.mInputLength, mDlg.mOutputLength);

		EnableInterface(TRUE);
		mSaveCtrl.EnableWindow(FALSE);

		SetupControls(mDlg.mInputLength, mDlg.mOutputLength);

		mInputBuilder.SetCtrlData(NULL);
		mInputBuilder.Invalidate();
		mOutputBuilder.SetCtrlData(NULL);
		mOutputBuilder.Invalidate();
		
		UpdateData(TRUE);
		mInputNumber = 0;
		mTotalInputs = 0;	
		mOutputNumber = 0;
		mTotalOutputs = 0;
		
		mFileName = _T("");
		UpdateData(FALSE);

		SetModifiedState(false);
	}
}
void CDataFilesDlg::OnBnClickedAddInputSymbol()
{
	// TODO: Add your control notification handler code here
	mDataFile.AddInputSymbol(mInputMarker);

	UpdateData(TRUE);	
	mTotalInputs++;
	UpdateData(FALSE);

    ShowInputSymbol(mTotalInputs - 1);

	SetModifiedState(true);
}

void CDataFilesDlg::OnBnClickedRemoveInputSymbol()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mTotalInputs == 0)
		return;

	mInputBuilder.SetCtrlData(NULL);	

	mDataFile.RemoveInputSymbol(mInputNumber - 1);

	if (mTotalInputs != 1)
	    ShowInputSymbol(0);
	else
	{
		mInputNumber = 0;
		mInputBuilder.Invalidate();
	}

	mTotalInputs--;

	UpdateData(FALSE);

	SetModifiedState(true);
}

void CDataFilesDlg::OnBnClickedSetInputMarker()
{
	// TODO: Add your control notification handler code here
	mInputBuilder.ShowSelectMarkerDlg();

	UpdateData(TRUE);	
	mInputMarker = mInputBuilder.GetMarkerValue();
	UpdateData(FALSE);
}

void CDataFilesDlg::OnBnClickedUpListInputs()
{
	// TODO: Add your control notification handler code here
    ShowInputSymbol(mInputNumber - 2);
}

void CDataFilesDlg::OnBnClickedDownListInputs()
{
	// TODO: Add your control notification handler code here
    ShowInputSymbol(mInputNumber);
}

void CDataFilesDlg::OnBnClickedInputCtrlProp()
{
	// TODO: Add your control notification handler code here
	mInputBuilder.ShowPropertiesDlg();
}

void CDataFilesDlg::OnBnClickedAddOutputSymbol()
{
	// TODO: Add your control notification handler code here
	mDataFile.AddOutputSymbol(mOutputMarker);

	UpdateData(TRUE);	
	mTotalOutputs++;
	UpdateData(FALSE);

    ShowOutputSymbol(mTotalOutputs - 1);

	SetModifiedState(true);
}

void CDataFilesDlg::OnBnClickedRemoveOutputSymbol()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (mTotalOutputs == 0)
		return;

	mOutputBuilder.SetCtrlData(NULL);	

	mDataFile.RemoveOutputSymbol(mOutputNumber - 1);

	if (mTotalOutputs != 1)
	    ShowOutputSymbol(0);
	else
	{
		mOutputNumber = 0;
		mOutputBuilder.Invalidate();
	}

	mTotalOutputs--;

	UpdateData(FALSE);

	SetModifiedState(true);
}

void CDataFilesDlg::OnBnClickedSetOutputMarker()
{
	// TODO: Add your control notification handler code here
	mOutputBuilder.ShowSelectMarkerDlg();

	UpdateData(TRUE);	
	mOutputMarker = mOutputBuilder.GetMarkerValue();
	UpdateData(FALSE);
}

void CDataFilesDlg::OnBnClickedUpListOutputs()
{
	// TODO: Add your control notification handler code here
    ShowOutputSymbol(mOutputNumber - 2);
}

void CDataFilesDlg::OnBnClickedDownListOutputs()
{
	// TODO: Add your control notification handler code here
    ShowOutputSymbol(mOutputNumber);
}

void CDataFilesDlg::OnBnClickedOutputCtrlProp()
{
	// TODO: Add your control notification handler code here
	mOutputBuilder.ShowPropertiesDlg();
}

void CDataFilesDlg::OnBnClickedLoad()
{
	// TODO: Add your control notification handler code here
	if (bModified)
	{
		int res = AfxMessageBox(_T("Data was modified and would be lost in case of creating new data file.\nWould you like to save changes before performing the operation?"), MB_YESNO);
		if (res == IDYES)
		{
			OnBnClickedSave();
		}
	}

	CFileDialog	mFileDlg(true, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);		
		mFileName = mFileDlg.GetPathName();
		UpdateData(FALSE);	

		bool bRet = mDataFile.LoadFile(mFileName);
		if (bRet)
		{
			EnableInterface(TRUE);

			SetupControls(mDataFile.GetInputSymbolLength(), 
				mDataFile.GetOutputSymbolLength());

			if (mDataFile.GetInputSymbolsCount() > 0)
				ShowInputSymbol(0);
			else
			{
				mInputBuilder.SetCtrlData(NULL);
				mInputBuilder.Invalidate();
			}

			if (mDataFile.GetOutputSymbolsCount() > 0)
				ShowOutputSymbol(0);
			else
			{
				mOutputBuilder.SetCtrlData(NULL);
				mOutputBuilder.Invalidate();
			}
			
			UpdateData(TRUE);
			mTotalInputs = mDataFile.GetInputSymbolsCount();	
			mTotalOutputs = mDataFile.GetOutputSymbolsCount();
			UpdateData(FALSE);

			SetModifiedState(false);			
		} else
		{
 			AfxMessageBox("Error while tying to load data.\nPosibly file path is not more available.");
			SetModifiedState(true);

			UpdateData(TRUE);
			mFileName = _T("");
			UpdateData(FALSE);
		}
	}
}

void CDataFilesDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	if (mFileName == _T(""))
		OnBnClickedSaveAs();
	else
	{
		bool bRet = mDataFile.SaveToFile(mFileName);
		if (bRet)
		{
			SetModifiedState(false);
		} else
		{
			AfxMessageBox("Error while tying to save data.\nPosibly file path is not more available.");
			SetModifiedState(true);
			mSaveCtrl.EnableWindow(FALSE);

			UpdateData(TRUE);
			mFileName = _T("");
			UpdateData(FALSE);
		}
	}
}

void CDataFilesDlg::OnBnClickedSaveAs()
{
	// TODO: Add your control notification handler code here
	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Data File v1.0|*.nldfile||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		UpdateData(TRUE);		
		mFileName = mFileDlg.GetPathName();
		UpdateData(FALSE);	

        bool bRet = mDataFile.SaveToFile(mFileName);		
		if (bRet)
		{
			SetModifiedState(false);

			mSaveCtrl.EnableWindow(TRUE);
		} else
		{
			AfxMessageBox("Error while tying to save data.\nPosibly file path is not more available.");
			SetModifiedState(true);
			mSaveCtrl.EnableWindow(FALSE);

			UpdateData(TRUE);		
			mFileName = _T("");
			UpdateData(FALSE);	
		}		
	}
}

void CDataFilesDlg::OnBnClickedInputCtrlEditor()
{
	// TODO: Add your control notification handler code here
	mInputBuilder.ShowAdvancedEditorDlg();
}

void CDataFilesDlg::OnBnClickedOutputCtrlEditor()
{
	// TODO: Add your control notification handler code here
	mOutputBuilder.ShowAdvancedEditorDlg();
}
