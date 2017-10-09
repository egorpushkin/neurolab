// NeuronQuickInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeuroLab.h"
#include "NeuronQuickInfoDlg.h"
#include ".\neuronquickinfodlg.h"

#include "interface_idds.h"

#define WM_QUICKTIMEREVENT			WM_USER + 1

#define	NQS_TOTAL_TO_ELAPSE			1000
#define	NQS_PERIOD					100
// CNeuronQuickInfoDlg dialog

IMPLEMENT_DYNAMIC(CNeuronQuickInfoDlg, CDialog)
CNeuronQuickInfoDlg::CNeuronQuickInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeuronQuickInfoDlg::IDD, pParent)
	, mFunctionName(_T(""))
	, mDendrCount(0)
	, mAxonsCount(0)
	, mFuncExpr(_T(""))
	, mElementType(_T(""))
	, mElementName(_T(""))
	, mSystemName(_T(""))
	, mElementID(0)
	, mRequiresData(_T(""))
	, mDataLength(0)
{
//	mCurElement = NULL;

	iTimeElapsed = 0;
}

CNeuronQuickInfoDlg::~CNeuronQuickInfoDlg()
{
}

void CNeuronQuickInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FUNCTIONNAME, mFunctionName);
	DDX_Text(pDX, IDC_DENDRCOUNT, mDendrCount);
	DDX_Text(pDX, IDC_AXONSCOUNT, mAxonsCount);
	DDX_Text(pDX, IDC_FUNCTIONEXPRESSION, mFuncExpr);
	DDX_Text(pDX, IDC_ELEMENT_TYPE, mElementType);
	DDX_Text(pDX, IDC_ELEMENT_NAME, mElementName);
	DDX_Text(pDX, IDC_SYSTEM_NAME, mSystemName);
	DDX_Text(pDX, IDC_ELEMENT_ID, mElementID);
	DDX_Text(pDX, IDC_REQUIRES_DATA, mRequiresData);
	DDX_Text(pDX, IDC_DATA_LENGTH, mDataLength);
	DDX_Control(pDX, IDC_FUNC_VIEW_SCALE, mFuncViewScale);
}


BEGIN_MESSAGE_MAP(CNeuronQuickInfoDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CNeuronQuickInfoDlg message handlers

void CNeuronQuickInfoDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnOK();
}

void CNeuronQuickInfoDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialog::OnCancel();
}

HBRUSH CNeuronQuickInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  Change any attributes of the DC here
	if ((nCtlColor == CTLCOLOR_BTN) || (nCtlColor == CTLCOLOR_STATIC))
	{
		pDC->SetBkMode (TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if ((nCtlColor == CTLCOLOR_DLG))
	{
		HBRUSH hbr = ::CreateSolidBrush(RGB(255, 255, 225));
		return hbr;
	}

	// TODO:  Return a different brush if the default is not desired
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

BOOL CNeuronQuickInfoDlg::Create(int iIDD, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CDialog::Create(iIDD, pParentWnd);	

	if (bRet)
	{
		mFuncShow.Create(NULL, "", WS_VISIBLE | WS_BORDER, CRect(180, 66, 340, 200), this, ID_QUICKFUNCTIONSHOWCTRL);	
		mFuncViewScale.SetRange(20, 100);
		mFuncViewScale.SetPos(40);

		long l = GetWindowLong(m_hWnd, GWL_EXSTYLE);
		l |= WS_EX_LAYERED;
		SetWindowLong(m_hWnd, GWL_EXSTYLE, l);
		::SetLayeredWindowAttributes(m_hWnd, 0, 210, LWA_ALPHA);
	}
	
	return bRet;
}

void CNeuronQuickInfoDlg::ShowElement(IElement* pElementObj, CPoint& point)
{
	if (!m_hWnd)
		return;
	if (!pElementObj)
	{	
		pElement = NULL;
		KillTimer(WM_QUICKTIMEREVENT);
		ShowWindow(SW_HIDE);
		return;
	}

	if (pElement == pElementObj)
		return;

	pElement = pElementObj;
	pntCurPoint = point;

	iTimeElapsed = 0;
	SetTimer(WM_QUICKTIMEREVENT, NQS_PERIOD, NULL);
}

void CNeuronQuickInfoDlg::ShowDlgWnd()
{
	if (pElement)
	{
		UpdateData(TRUE);

		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

		sFunction* pFunction = pDataFlow->GetElementFunction();
		if (pFunction)
		{
			mFuncShow.SetFunction(pFunction->pfnProcessFunction);
			mFuncShow.FunctionParam = pFunction;
			mFunctionName = pFunction->csTitle;	
			mFuncExpr = pFunction->csExpression;
		}
		else
		{
			mFuncShow.SetFunction(NULL);
			mFunctionName = "Not selected yet";
			mFuncExpr = "No expression";
		}
		mFuncShow.Invalidate();

		mDendrCount = -1;
		mAxonsCount = -1;

		switch (pElement->GetElementType())
		{
		case ET_INPUT:
			mElementType = _T("ET_INPUT");
			break;
		case ET_PROCESSOR:
			mElementType = _T("ET_PROCESSOR");
			break;
		case ET_OUTPUT:
			mElementType = _T("ET_OUTPUT");
			break;		
		default:
			mElementType = _T("Unknown");
		}

		mElementName = pElement->GetElementTitle();
		mSystemName = pElement->GetSysName();
		mElementID = pElement->GetElementID();

		if (pDataFlow->RequireData())
			mRequiresData = _T("true");
		else
			mRequiresData = _T("false");

		mDataLength = pDataFlow->GetDataFactory()->GetDataLength();

		CDataFactory tmDataFactory;
		pDataFlow->SplitConnectionsData(&tmDataFactory, DC_INPUTS_FACTORY);
		mDendrCount = tmDataFactory.GetDataLength();

		pDataFlow->SplitConnectionsData(&tmDataFactory, DC_OUTPUTS_FACTORY);
		mAxonsCount = tmDataFactory.GetDataLength();

		UpdateData(FALSE);

		CRect rect;
		GetWindowRect(&rect);
		MoveWindow(pntCurPoint.x, pntCurPoint.y, rect.Width(), rect.Height());

		ShowWindow(SW_SHOW);
		Invalidate();
	}
}

void CNeuronQuickInfoDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	iTimeElapsed += NQS_PERIOD;
	if (iTimeElapsed >= NQS_TOTAL_TO_ELAPSE)
	{
		ShowDlgWnd();

		KillTimer(WM_QUICKTIMEREVENT);
	}

	CDialog::OnTimer(nIDEvent);
}

void CNeuronQuickInfoDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

//	pElement = NULL;
/*	KillTimer(WM_QUICKTIMEREVENT);
	ShowWindow(SW_HIDE);*/
	// TODO: Add your message handler code here
}

void CNeuronQuickInfoDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar*)&mFuncViewScale)
	{
		int iRange = mFuncViewScale.GetPos();
		mFuncShow.SetScale(iRange);
		mFuncShow.Invalidate();	
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
