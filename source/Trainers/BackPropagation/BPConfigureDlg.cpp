#include "stdafx.h"
#include "BPConfigureDlg.h"
#include ".\bpconfiguredlg.h"

// CBPConfigureDlg dialog

IMPLEMENT_DYNAMIC(CBPConfigureDlg, CDialog)
CBPConfigureDlg::CBPConfigureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBPConfigureDlg::IDD, pParent)
	, fOutputSpeed(0)
	, fHiddenSpeed(0)
	, fOutputChange(0)
	, fHiddenChange(0)
	, fMaxError(0)
	, iLoopsCount(0)
	, bOutputIncrement(false)
	, bHiddenIncrement(false)
	, mSaveNeuronWeights(FALSE)
	, mInitializeWeights(FALSE)
	, mStartValue(0)
	, mEndValue(0)
	, mConstantValue(0)
	, mSelectRandowSymbolForTraining(FALSE)
{
}

CBPConfigureDlg::~CBPConfigureDlg()
{
}

void CBPConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUTPUT_SPEED, fOutputSpeed);
	DDX_Text(pDX, IDC_HIDDEN_SPEED, fHiddenSpeed);
	DDX_Text(pDX, IDC_CHANGE_INPUT_SPEED, fOutputChange);
	DDX_Text(pDX, IDC_CHANGE_OUTPUT_SPEED, fHiddenChange);
	DDX_Text(pDX, IDC_NETWORK_ERROR, fMaxError);
	DDX_Text(pDX, IDC_LOOPS_NUMBER, iLoopsCount);
	DDX_Check(pDX, IDC_SAVE_NEURON_WEIGHTS, mSaveNeuronWeights);
	DDX_Check(pDX, IDC_INITIALIZE_WEIGHTS, mInitializeWeights);
	DDX_Control(pDX, IDC_START_RANDOM_VALUE, mStartValueCtrl);
	DDX_Control(pDX, IDC_END_RANDOM_VALUE, mEndValueCtrl);
	DDX_Control(pDX, IDC_CONSTANT_INIT_VALUE, mConstantValueCtrl);
	DDX_Text(pDX, IDC_START_RANDOM_VALUE, mStartValue);
	DDX_Text(pDX, IDC_END_RANDOM_VALUE, mEndValue);
	DDX_Text(pDX, IDC_CONSTANT_INIT_VALUE, mConstantValue);
	DDX_Control(pDX, IDC_INIT_STATIC_TO, mInitStaticTo);
	DDX_Check(pDX, IDC_TRAIN_RANDOM_SYMBOL, mSelectRandowSymbolForTraining);
}


BEGIN_MESSAGE_MAP(CBPConfigureDlg, CDialog)
	ON_BN_CLICKED(IDC_OUTPUT_INCREMENT, OnBnClickedOutputIncrement)
	ON_BN_CLICKED(IDC_HIDDEN_INCREMENT, OnBnClickedHiddenIncrement)
	ON_BN_CLICKED(IDC_OUTPUT_MULTIPLIER, OnBnClickedOutputMultiplier)
	ON_BN_CLICKED(IDC_HIDDEN_MULTIPLIER, OnBnClickedHiddenMultiplier)
	ON_BN_CLICKED(IDC_INITIALIZE_WEIGHTS, OnBnClickedInitializeWeights)
	ON_BN_CLICKED(IDC_RANDOM_VALUES, OnBnClickedRandomValues)
	ON_BN_CLICKED(IDC_CONSTANT_VALUE, OnBnClickedConstantValue)
END_MESSAGE_MAP()


// CBPConfigureDlg message handlers

BOOL CBPConfigureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	fOutputSpeed = pSettings->fOutputTrainSpeed;
	fHiddenSpeed = pSettings->fHiddenTrainSpeed;

	fOutputChange = pSettings->fOutputChange;
	fHiddenChange = pSettings->fHiddenChange;

	fMaxError = pSettings->fMaxError;
	iLoopsCount = pSettings->iMaxLoopsCount;

	if (pSettings->iOutputSpeedChange == VCT_INCREMENT)
	{
		((CButton*)GetDlgItem(IDC_OUTPUT_INCREMENT))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_OUTPUT_MULTIPLIER))->SetCheck(BST_UNCHECKED);

		bOutputIncrement = true;
	} else if (pSettings->iOutputSpeedChange == VCT_MULTIPLY)
	{
		((CButton*)GetDlgItem(IDC_OUTPUT_INCREMENT))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_OUTPUT_MULTIPLIER))->SetCheck(BST_CHECKED);

		bOutputIncrement = false;
	}

	if (pSettings->iHiddenSpeedChange == VCT_INCREMENT)
	{
		((CButton*)GetDlgItem(IDC_HIDDEN_INCREMENT))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_HIDDEN_MULTIPLIER))->SetCheck(BST_UNCHECKED);

		bHiddenIncrement = true;
	} else if (pSettings->iHiddenSpeedChange == VCT_MULTIPLY)
	{
		((CButton*)GetDlgItem(IDC_HIDDEN_INCREMENT))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_HIDDEN_MULTIPLIER))->SetCheck(BST_CHECKED);	

		bHiddenIncrement = false;
	}

	mSelectRandowSymbolForTraining = pSettings->bSelectRandomSymbolForTraining;

	mSaveNeuronWeights = pSettings->bSaveNeuronWeights;

	EnableInitSection(pSettings->bInitializeWeights);
	
	mStartValue = pSettings->fStartRange;
	mEndValue = pSettings->fEndRange;
	mConstantValue = pSettings->fConstant;

	if (pSettings->iWeightsInitializationType == WIT_RANDOM)
	{
		((CButton*)GetDlgItem(IDC_RANDOM_VALUES))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_CONSTANT_VALUE))->SetCheck(BST_UNCHECKED);		

		bUseRandomIntialization = true;
	} else if (pSettings->iWeightsInitializationType == WIT_CONSTANT)
	{
		((CButton*)GetDlgItem(IDC_RANDOM_VALUES))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CONSTANT_VALUE))->SetCheck(BST_CHECKED);		

		bUseRandomIntialization = false;
	}

	mInitializeWeights = pSettings->bInitializeWeights;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBPConfigureDlg::EnableInitSection(BOOL bEnable)
{
	GetDlgItem(IDC_RANDOM_VALUES)->EnableWindow(bEnable);
	GetDlgItem(IDC_CONSTANT_VALUE)->EnableWindow(bEnable);

	mStartValueCtrl.EnableWindow(bEnable);
	mEndValueCtrl.EnableWindow(bEnable);
	mConstantValueCtrl.EnableWindow(bEnable);

	mInitStaticTo.EnableWindow(bEnable);
}

void CBPConfigureDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);

	if (mStartValue > mEndValue)
	{
		AfxMessageBox("Wrong range for random values.");
		return;
	}

	pSettings->fOutputTrainSpeed = fOutputSpeed;
	pSettings->fHiddenTrainSpeed = fHiddenSpeed;

	pSettings->fOutputChange = fOutputChange;
	pSettings->fHiddenChange = fHiddenChange;

	pSettings->fMaxError = fMaxError;
	pSettings->iMaxLoopsCount = iLoopsCount;

	if (bOutputIncrement)
		pSettings->iOutputSpeedChange = VCT_INCREMENT;
	else
		pSettings->iOutputSpeedChange = VCT_MULTIPLY;

	if (bHiddenIncrement)
		pSettings->iHiddenSpeedChange = VCT_INCREMENT;
	else
		pSettings->iHiddenSpeedChange = VCT_MULTIPLY;

	pSettings->bSelectRandomSymbolForTraining = mSelectRandowSymbolForTraining;

	pSettings->bSaveNeuronWeights = mSaveNeuronWeights;

	pSettings->bInitializeWeights = mInitializeWeights;

	pSettings->fStartRange = mStartValue;
	pSettings->fEndRange = mEndValue;
	pSettings->fConstant = mConstantValue;

	if (bUseRandomIntialization)
		pSettings->iWeightsInitializationType = WIT_RANDOM;		
	else
		pSettings->iWeightsInitializationType = WIT_CONSTANT;		

	CDialog::OnOK();
}

void CBPConfigureDlg::OnBnClickedOutputIncrement()
{
	// TODO: Add your control notification handler code here
	bOutputIncrement = true;
}

void CBPConfigureDlg::OnBnClickedHiddenIncrement()
{
	// TODO: Add your control notification handler code here
	bHiddenIncrement = true;
}

void CBPConfigureDlg::OnBnClickedOutputMultiplier()
{
	// TODO: Add your control notification handler code here
	bOutputIncrement = false;
}

void CBPConfigureDlg::OnBnClickedHiddenMultiplier()
{
	// TODO: Add your control notification handler code here
	bHiddenIncrement = false;
}

void CBPConfigureDlg::OnBnClickedInitializeWeights()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	EnableInitSection(mInitializeWeights);
}
void CBPConfigureDlg::OnBnClickedRandomValues()
{
	// TODO: Add your control notification handler code here
	bUseRandomIntialization = true;
}

void CBPConfigureDlg::OnBnClickedConstantValue()
{
	// TODO: Add your control notification handler code here
	bUseRandomIntialization = false;
}
