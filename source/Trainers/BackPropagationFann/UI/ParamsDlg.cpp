// ParamsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ParamsDlg.h"
#include ".\paramsdlg.h"

#include "fann.h"

#include "FannAboutDlg.h"

// CParamsDlg dialog

IMPLEMENT_DYNAMIC(CParamsDlg, CDialog)
CParamsDlg::CParamsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamsDlg::IDD, pParent)
	, fromValue_(0)
	, toValue_(0)
	, constValue_(0)
	, hiddenSpeed_(0)
	, mse_(0)
	, loops_(0)
{
}

CParamsDlg::~CParamsDlg()
{
}

void CParamsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_START_RANDOM_VALUE, fromValue_);
	DDX_Text(pDX, IDC_END_RANDOM_VALUE, toValue_);
	DDX_Text(pDX, IDC_CONSTANT_INIT_VALUE, constValue_);
	DDX_Control(pDX, IDC_TRAINING_METHOD, trainingMethod_);
	DDX_Text(pDX, IDC_HIDDEN_SPEED, hiddenSpeed_);
	DDX_Text(pDX, IDC_NETWORK_ERROR, mse_);
	DDX_Text(pDX, IDC_LOOPS_NUMBER, loops_);
	DDX_Control(pDX, IDC_FANN_CONSTR_APPROACH, approach_);
	DDX_Control(pDX, IDC_HIDDEN_ACT, hiddenActivation_);
	DDX_Control(pDX, IDC_OUTPUT_ACT, outputActivation_);
}


BEGIN_MESSAGE_MAP(CParamsDlg, CDialog)
	ON_BN_CLICKED(IDC_RANDOM_VALUES, OnBnClickedRandomValues)
	ON_BN_CLICKED(IDC_CONSTANT_VALUE, OnBnClickedConstantValue)
	ON_BN_CLICKED(IDC_ADOPTIVE_METHOD, OnBnClickedAdoptiveMethod)
	ON_BN_CLICKED(IDC_SHOW_FANN_ABOUT, OnBnClickedShowFannAbout)
	ON_BN_CLICKED(IDC_NO_INIT_WEIGHTS, OnBnClickedNoInitWeights)
END_MESSAGE_MAP()


// CParamsDlg message handlers

BOOL CParamsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Weights initialization
	SetupWeightsInit(pSettings_->iWeightsInitMethod);	
	fromValue_ = pSettings_->fStartRange;
	toValue_ = pSettings_->fEndRange;
	constValue_ = pSettings_->fConstant;

	// Training section
	trainingMethod_.AddString(_T("Standard backpropagation incremental or online training"));
	trainingMethod_.AddString(_T("Standard backpropagation batch training"));
	trainingMethod_.AddString(_T("The iRprop- training algorithm"));
	trainingMethod_.AddString(_T("The QuickProp training algorithm"));
	trainingMethod_.SetCurSel(pSettings_->iTrainingMethod);

	hiddenSpeed_ = pSettings_->fHiddenTrainSpeed;

	// Termination conditions
	mse_ = pSettings_->fMaxError;
	loops_ = pSettings_->iMaxLoopsCount;

	// Network structure
	approach_.AddString(_T("Automatically parse network"));
	approach_.AddString(_T("Use network construction tool"));
	approach_.SetCurSel(pSettings_->iNetStruct);	

	hiddenActivation_.AddString(_T("Sigmoid activation function"));
	hiddenActivation_.AddString(_T("Symmetric sigmoid activation function"));
	hiddenActivation_.SetItemData(0, FANN_SIGMOID);
	hiddenActivation_.SetItemData(1, FANN_SIGMOID_SYMMETRIC);
	SelectActivation(hiddenActivation_, pSettings_->iHiddenActivation);

	outputActivation_.AddString(_T("Sigmoid activation function"));
	outputActivation_.AddString(_T("Symmetric sigmoid activation function"));
	outputActivation_.SetItemData(0, FANN_SIGMOID);
	outputActivation_.SetItemData(1, FANN_SIGMOID_SYMMETRIC);
	SelectActivation(outputActivation_, pSettings_->iOutputActivation);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CParamsDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	
	// Weights initialization
	pSettings_->iWeightsInitMethod = GetWeightsInitMethod();
	pSettings_->fStartRange = fromValue_;
	pSettings_->fEndRange = toValue_;
	pSettings_->fConstant = constValue_;

	// Training section
	pSettings_->iTrainingMethod = trainingMethod_.GetCurSel();
	pSettings_->fHiddenTrainSpeed = hiddenSpeed_;

	// Termination conditions
	pSettings_->fMaxError = mse_;
	pSettings_->iMaxLoopsCount = loops_;

	// Network structure
	pSettings_->iNetStruct = approach_.GetCurSel();	
	pSettings_->iHiddenActivation = GetActivation(hiddenActivation_);
	pSettings_->iOutputActivation = GetActivation(outputActivation_);

	CDialog::OnOK();
}

void CParamsDlg::OnBnClickedNoInitWeights()
{
	// TODO: Add your control notification handler code here
	SetupWeightsInit(WIM_NOINIT);
}

void CParamsDlg::OnBnClickedRandomValues()
{
	// TODO: Add your control notification handler code here
	SetupWeightsInit(WIM_RANDOM);
}

void CParamsDlg::OnBnClickedConstantValue()
{
	// TODO: Add your control notification handler code here
	SetupWeightsInit(WIM_CONSTANT);
}

void CParamsDlg::OnBnClickedAdoptiveMethod()
{
	// TODO: Add your control notification handler code here
	SetupWeightsInit(WIM_ADOPTIVE);
}

void CParamsDlg::SetupWeightsInit(int method)
{
	switch (method)
	{
	case WIM_NOINIT: 
		((CButton*)GetDlgItem(IDC_NO_INIT_WEIGHTS))->SetCheck(BST_CHECKED);
		break;
	case WIM_RANDOM: 
		((CButton*)GetDlgItem(IDC_RANDOM_VALUES))->SetCheck(BST_CHECKED);
		break;
	case WIM_CONSTANT: 
		((CButton*)GetDlgItem(IDC_CONSTANT_VALUE))->SetCheck(BST_CHECKED);
		break;
	case WIM_ADOPTIVE: 
		((CButton*)GetDlgItem(IDC_ADOPTIVE_METHOD))->SetCheck(BST_CHECKED);
		break;
	}
}

int CParamsDlg::GetWeightsInitMethod()
{
	if (((CButton*)GetDlgItem(IDC_NO_INIT_WEIGHTS))->GetCheck() == BST_CHECKED)
		return WIM_NOINIT;
	else if (((CButton*)GetDlgItem(IDC_RANDOM_VALUES))->GetCheck() == BST_CHECKED)
		return WIM_RANDOM;
	else if (((CButton*)GetDlgItem(IDC_CONSTANT_VALUE))->GetCheck() == BST_CHECKED)
		return WIM_CONSTANT;
	else if (((CButton*)GetDlgItem(IDC_ADOPTIVE_METHOD))->GetCheck() == BST_CHECKED)
		return WIM_ADOPTIVE;

	return 0;
}

/*void CParamsDlg::EnableWeightsSection(BOOL enable)
{
	GetDlgItem(IDC_RANDOM_VALUES)->EnableWindow(enable);
	GetDlgItem(IDC_CONSTANT_VALUE)->EnableWindow(enable);
	GetDlgItem(IDC_ADOPTIVE_METHOD)->EnableWindow(enable);

	GetDlgItem(IDC_START_RANDOM_VALUE)->EnableWindow(enable);
	GetDlgItem(IDC_END_RANDOM_VALUE)->EnableWindow(enable);
	GetDlgItem(IDC_CONSTANT_INIT_VALUE)->EnableWindow(enable);
	
	GetDlgItem(IDC_INIT_STATIC_TO)->EnableWindow(enable);
}*/

void CParamsDlg::OnBnClickedShowFannAbout()
{
	// TODO: Add your control notification handler code here
	CFannAboutDlg fannAbout;
	fannAbout.DoModal();
}

void CParamsDlg::SelectActivation(CComboBox& combo, unsigned int function)
{
	switch (function)
	{
	case FANN_SIGMOID:
		combo.SetCurSel(0);
		break;
	case FANN_SIGMOID_SYMMETRIC:
		combo.SetCurSel(1);
		break;
	}
}

unsigned int CParamsDlg::GetActivation(CComboBox& combo)
{
	int index = combo.GetCurSel();

	unsigned int function = FANN_SIGMOID;
	switch (index)
	{
	case 0:
		function = FANN_SIGMOID;
		break;
	case 1:
		function = FANN_SIGMOID_SYMMETRIC;
		break;
	}

	return function;
}
