// DataImageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DataImageCtrl.h"

#include "../Devices/GDIPDevice.h"

#include "DataImageCtrlPropDlg.h"
#include "DataImageCtrlMarkerDlg.h"
#include "DataImageCtrlEditorDlg.h"

using namespace Gdiplus;

// CDataImageCtrl

IMPLEMENT_DYNAMIC(CDataImageCtrl, CWnd)
CDataImageCtrl::CDataImageCtrl()
{
	iXDimension = 10;
	iYDimension = 8;
	
	bEnableEdit = false;
	pDataFactory = NULL;

	bPressed = false;

	fMarker = -1.0f;
	iMarkerDiameter = 1;

	// Color range options
	fMinDataValue = 0.0f;
	fMaxDataValue = 1.0f;

 	bUseRedMask = true;
	bUseGreenMask = true;
	bUseBlueMask = true;

	iRedComponent = 0;
	iGreenComponent = 0;
	iBlueComponent = 0;

	fCurrentValue = 0.0f;

	bShowGrid = false;
	bShowInfo = true;

	iScale = 1;
	iXOffset = 0;
	iYOffset = 0;
}

CDataImageCtrl::~CDataImageCtrl()
{
}


BEGIN_MESSAGE_MAP(CDataImageCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


void CDataImageCtrl::SetCtrlParams(int XDimension, int YDimension, bool EnableEdit)
{
	iXDimension = XDimension;
	iYDimension = YDimension;

	bEnableEdit = EnableEdit;

	if (GetSafeHwnd())
		Invalidate();
}

void CDataImageCtrl::SetCtrlParams(int XDimension, int YDimension)
{
	iXDimension = XDimension;
	iYDimension = YDimension;

	if (GetSafeHwnd())
		Invalidate();
}

void CDataImageCtrl::SetCtrlData(IDataFactory* pData)
{
	pDataFactory = pData;

	if (GetSafeHwnd())
		Invalidate();
}

void CDataImageCtrl::EnableEdit(bool EnableEdit)
{
	bEnableEdit = EnableEdit;	
}

void CDataImageCtrl::SetMarker(float Marker)
{
	fMarker = Marker;
}

int CDataImageCtrl::GetXDimension()
{
	return iXDimension;
}

int	CDataImageCtrl::GetYDimension()
{
	return iYDimension;
}

/*void CDataImageCtrl::SetToolTipID(int ID)
{
	iToolTipID = ID;
}*/

void CDataImageCtrl::ShowPropertiesDlg()
{
	CDataImageCtrlPropDlg mDlg;

	if (pDataFactory)
		mDlg.mDataLength = pDataFactory->GetDataLength();
	else
		mDlg.mDataLength = iXDimension*iYDimension;
	mDlg.mXDimension = iXDimension;
	mDlg.mYDimension = iYDimension;
	
	mDlg.mMinDataValue = fMinDataValue;
	mDlg.mMaxDataValue = fMaxDataValue;

	mDlg.mRedComponent = iRedComponent;
	mDlg.mGreenComponent = iGreenComponent;
	mDlg.mBlueComponent = iBlueComponent;

	mDlg.mUseRedMask = bUseRedMask;
	mDlg.mUseGreenMask = bUseGreenMask;
	mDlg.mUseBlueMask = bUseBlueMask;

	mDlg.mShowGrid = bShowGrid;
	mDlg.mShowInfo = bShowInfo;

	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		iXDimension = mDlg.mXDimension;
		iYDimension = mDlg.mYDimension;
		
		fMinDataValue = mDlg.mMinDataValue;
		fMaxDataValue = mDlg.mMaxDataValue;

		iRedComponent = mDlg.mRedComponent;
		iGreenComponent = mDlg.mGreenComponent;
		iBlueComponent = mDlg.mBlueComponent;

		bUseRedMask = mDlg.mUseRedMask;
		bUseGreenMask = mDlg.mUseGreenMask;
		bUseBlueMask = mDlg.mUseBlueMask;

		bShowGrid = mDlg.mShowGrid;
		bShowInfo = mDlg.mShowInfo;
		
		Invalidate();
	}
}

void CDataImageCtrl::ShowSelectMarkerDlg()
{
	CDataImageCtrlMarkerDlg mDlg;
	mDlg.mMarker = fMarker;
	mDlg.mMarkerDiameter = iMarkerDiameter;
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		fMarker = mDlg.mMarker;
		iMarkerDiameter = mDlg.mMarkerDiameter; 
	}
}

void CDataImageCtrl::ShowAdvancedEditorDlg()
{
	if (!pDataFactory)
		return;

	CDataImageCtrlEditorDlg mDlg;
	mDlg.SetDataFactory(pDataFactory);
	mDlg.DoModal();

    Invalidate();
}

void CDataImageCtrl::ShowSaveAsDlg()
{
	if (!pDataFactory)
		return;

/*	CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "PGM File|*.pgm||");
	INT_PTR res = mFileDlg.DoModal();
	if (res == IDOK)
	{
		CDataFactory tmDataFactory;
		tmDataFactory.CreateFactory(pDataFactory->GetDataLength());
		tmDataFactory.SetData(pDataFactory->GetData(), pDataFactory->GetDataLength());

		for (int i = 0;i < pDataFactory->GetDataLength();i++)
		{
			float fValue = pDataFactory->GetItemData(i);
			if (fValue > fMaxDataValue)
				fValue = fMaxDataValue;
			if (fValue < fMinDataValue)
				fValue = fMinDataValue;
			float fColorGrad = (fValue - fMinDataValue)/(fMaxDataValue - fMinDataValue)*255;
			tmDataFactory.SetItemData(i, fColorGrad);
		}

		IDataFactory* pTmDataFactory = NULL;
		tmDataFactory.QueryInterface(IID_IDataFactory, (void**)&pTmDataFactory);

		CPGMBitmap tmPGMBitmap; 
		tmPGMBitmap.ConstructFromDataFactory(pTmDataFactory, iXDimension, iYDimension);
		tmPGMBitmap.SavePGMBitmap(mFileDlg.GetPathName());
	}*/
}

// CDataImageCtrl message handlers

void CDataImageCtrl::OnPaint()
{
	CPaintDC dc(this); // device contex/t for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CRect ClRect;
	GetClientRect(&ClRect);

	CGDIPDevice	mGDIDevice;
	Graphics* pGraphics = mGDIDevice.CreateGraphics(&dc);

	SolidBrush	BackGroundBrush(Color(224, 223, 227));
	pGraphics->FillRectangle(&BackGroundBrush, ClRect.left, ClRect.top,
		ClRect.Width(), ClRect.Height());

/*	Pen	BorderPen(Color(0, 0, 0), 1);
	pGraphics->DrawRectangle(&BorderPen, ClRect.left, ClRect.top, 
		ClRect.Width(), ClRect.Height());*/

	float fXStep = (ClRect.Width()*1.0/iXDimension);
	float fYStep = (ClRect.Height()*1.0/iYDimension);

	if (pDataFactory)
	{		
		SolidBrush DisabledBrush(Color(85, 102, 98));

		for (int i = 0;i < iYDimension;i++)
			for (int j = 0;j < iXDimension;j++)
				if (i*iXDimension + j < pDataFactory->GetDataLength())
				{
					float fValue = pDataFactory->GetItemData(i*iXDimension + j);
					if (fValue > fMaxDataValue)
						fValue = fMaxDataValue;
					if (fValue < fMinDataValue)
						fValue = fMinDataValue;
					int iColorGrad = (fValue - fMinDataValue)/(fMaxDataValue - fMinDataValue)*255;

					int iRed = iRedComponent;
					int iGreen = iGreenComponent;
					int iBlue = iBlueComponent;

					if (bUseRedMask)
						iRed = iColorGrad;
					if (bUseGreenMask)
						iGreen = iColorGrad;
					if (bUseBlueMask)
						iBlue = iColorGrad;
						
					SolidBrush FillBrush(Color(iRed, iGreen, iBlue));
					pGraphics->FillRectangle(&FillBrush, j*fXStep, i*fYStep,
						fXStep, fYStep);
				} else
				{
					pGraphics->FillRectangle(&DisabledBrush, j*fXStep, i*fYStep,
						fXStep, fYStep);
				}
	}

	Pen	GridPen(Color(100, 100, 100), 1);

	if (bShowGrid)
	{
		for (int i = 1;i < iYDimension;i++)
			pGraphics->DrawLine(&GridPen, (float)0, (float)i*fYStep, (float)ClRect.right, (float)i*fYStep);

		for (int i = 1;i < iXDimension;i++)
			pGraphics->DrawLine(&GridPen, (float)i*fXStep, (float)0, (float)i*fXStep, (float)ClRect.bottom);
	}

	if (pDataFactory && bShowInfo)
	{
		USES_CONVERSION;

		SolidBrush ValueBrush(Color(240, 240, 240));
		pGraphics->DrawRectangle(&GridPen, 3, 3, 55, 15);
		pGraphics->FillRectangle(&ValueBrush, 4, 5, 53, 13);

		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 11, FontStyleBold, UnitPixel);
		PointF      point(4, 4);
		SolidBrush  ValueFontBrush(Color(0, 0, 0));

		CString tmValue;
		tmValue.Format("%0.4f", fCurrentValue);

		pGraphics->DrawString(T2W(tmValue), -1, &font, point, &ValueFontBrush);
	}
}

void CDataImageCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bPressed)
	{
		//ReleaseCapture();

		ClipCursor(NULL);

		bPressed = false;			
	}

	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CDataImageCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CDataImageCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	SetFocus();

	CPoint tmPoint = point;
	ClientToScreen(&tmPoint);
    CWnd* wndUnderMouse = WindowFromPoint(tmPoint);
	if (wndUnderMouse != this)
	{		
		GetOwner()->SetFocus();
		ReleaseCapture();
		return;
	}

	if (bPressed)
		SetCheck(point);
	
	UpdateCurrentValue(point);

	CWnd::OnMouseMove(nFlags, point);
}

void CDataImageCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bPressed = true;
	//SetCapture();

	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);

	ClipCursor(&rect);

	SetCheck(point);

	CWnd::OnLButtonDown(nFlags, point);
}

void CDataImageCtrl::SetCheck(CPoint& point)
{
	if (pDataFactory && bEnableEdit)
	{
		CRect rRect;
		GetClientRect(&rRect);

		float fXStep = rRect.Width()*1.0/(iXDimension*1.0);
		float fYStep = rRect.Height()*1.0/(iYDimension*1.0);

		int iXIndex = (int)(point.x*1.0/fXStep);
		int iYIndex = (int)(point.y*1.0/fYStep);

		DisplayMarker(iXIndex, iYIndex);

		Invalidate();
	}	
}

void CDataImageCtrl::DisplayMarker(int XIndex, int YIndex)
{
	float fMarkerRadius = ((float)iMarkerDiameter) / 2.0f;
	int iMarkerRadius = ceil(fMarkerRadius);
	for (int i = -iMarkerRadius;i < iMarkerRadius;i++)
		for (int j = -iMarkerRadius;j < iMarkerRadius;j++)
		{
			float fDistance = (i*i + j*j);
			if (fDistance < fMarkerRadius * fMarkerRadius)
			{
				int iXCoord = XIndex + i;
				int iYCoord = YIndex + j;

				if (iXCoord >= 0 && iXCoord < iXDimension && 
					iYCoord >=0 && iYCoord < iYDimension)
					pDataFactory->SetItemData(
						iYCoord*iXDimension + iXCoord, 
						fMarker); 
			}
		}
}

void CDataImageCtrl::UpdateCurrentValue(CPoint& point)
{
	if (pDataFactory && bShowInfo)
	{	
		CRect rRect;
		GetClientRect(&rRect);

		float fXStep = rRect.Width()*1.0/(iXDimension*1.0);
		float fYStep = rRect.Height()*1.0/(iYDimension*1.0);

		int iXIndex = (int)(point.x*1.0/fXStep);
		int iYIndex = (int)(point.y*1.0/fYStep);		

		if (iYIndex*iXDimension + iXIndex < pDataFactory->GetDataLength())
		{
			fCurrentValue = pDataFactory->GetItemData(iYIndex*iXDimension + iXIndex);
		
			Invalidate();
		}
	}
}

BOOL CDataImageCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	return bRet;
}

BOOL CDataImageCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CDataImageCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (zDelta > 0)
	{
		if (iScale > 1)
			iScale--;
	}
	else
		iScale++;

	Invalidate();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

float CDataImageCtrl::GetMarkerValue()
{
	return fMarker;
}