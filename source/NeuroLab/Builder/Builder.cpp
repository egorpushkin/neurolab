// Builder.cpp : implementation file
//

#include "stdafx.h"
#include "..\NeuroLab.h"
#include "Builder.h"

#include "interface_idds.h" 

#include "GridCtrl.h"

#include "..\BuilderPropertiesDlg.h"

// CBuilder

IMPLEMENT_DYNAMIC(CBuilder, COutputDevice)
CBuilder::CBuilder()
{
	iGridRange = 10;
	bShowGrid = true;
	bAttachToGrid = true;

	pNeuroFactory = NULL;
	pAppController = NULL;

	iBuilderState = BS_NO_ACTION;

	pActiveElement = NULL;
}

CBuilder::~CBuilder()
{
}

BEGIN_MESSAGE_MAP(CBuilder, COutputDevice)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUILDER_PROPERTIES, OnShowBuilderProperties)
	ON_COMMAND(ID_BUILDER_SELECTALL, OnSelectAllElements)
END_MESSAGE_MAP()

// Creating and initialization functions
BOOL CBuilder::CreateBuilder(CRect& rect, CWnd * pParentWnd, UINT ctrlId)
{
	BOOL bRet = CreateDevice(rect, pParentWnd, ctrlId);
	
	SetScrollRange(SB_HORZ, 0, iMaxXScrollPos, FALSE);
	SetScrollRange(SB_VERT, 0, iMaxXScrollPos, TRUE);

	mNeuronInfoDlg.Create(CNeuronQuickInfoDlg::IDD, this);

	return bRet;
}

void CBuilder::SetAppController(IAppController* pController)
{
	pAppController = pController;
	pAppController->QueryInterface(IDD_IElementsCollection, (void**)&pNeuroFactory);
}

// Elements placement functions
CPoint CBuilder::AttachElementToGrid(CPoint& ptAbsPosition, bool bOffsetPoint)
{
	CPoint tmPoint = ptAbsPosition; 

	if (bOffsetPoint)
		tmPoint.Offset(-iXScrollOffset,	-iYScrollOffset);

	if (!bAttachToGrid)
		return tmPoint;
			
	int iXRight = tmPoint.x % iGridRange;
	int iYBottom = tmPoint.y % iGridRange;    

	if (iXRight >= iGridRange/2)
		tmPoint.x += (iGridRange - iXRight - 1);
	else
		tmPoint.x -= iXRight;

	if (iYBottom >= iGridRange/2)
		tmPoint.y += (iGridRange - iYBottom - 1);
	else
		tmPoint.y -= iYBottom;
	
	return tmPoint;
}

IElement* CBuilder::GetElementUnderMouse(CPoint& Point)
{
	CPoint tmPoint = Point;
	tmPoint.Offset(-iXScrollOffset, -iYScrollOffset);

	IBuilderElement* pBuilderElement = NULL;

	pNeuroFactory->CreateElementsEnumerator();
	while (IElement* pElement = pNeuroFactory->GetNextElement())
	{
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);

		if (pBuilderElement->IsClicked(tmPoint))
			return pElement;			
	}
	return NULL;
}

void CBuilder::SelectElement(IElement* pElement)
{
	if (!pElement)
	{
		pActiveElement = NULL;
		return;
	}

	SHORT	sShiftState = GetKeyState(VK_SHIFT);
	sShiftState = sShiftState>>7;

	SHORT	sCtrlState = GetKeyState(VK_LCONTROL) | GetKeyState(VK_RCONTROL);
	sCtrlState = sCtrlState>>7;

	if (!sShiftState)
	{
		pActiveElement = pElement;
		pAppController->ShowElementProperties(pActiveElement);
	}

	pNeuroFactory->SelectElement(pElement, sShiftState, sCtrlState);
}

void CBuilder::SelectElements(CPoint& point1, CPoint& point2)
{	
	int tmX = point1.x;
	if (point1.x > point2.x)
		tmX = point2.x;
	int tmY = point1.y;
	if (point1.y > point2.y)
		tmY = point2.y;

	CRect rZoneRect(tmX, tmY, 
		tmX + abs(point1.x - point2.x),
		tmY + abs(point1.y - point2.y));
	rZoneRect.OffsetRect(-iXScrollOffset, -iYScrollOffset);

	SHORT	sShiftState = GetKeyState(VK_SHIFT);
	sShiftState = sShiftState>>7;

	SHORT	sCtrlState = GetKeyState(VK_LCONTROL) | GetKeyState(VK_RCONTROL);
	sCtrlState = sCtrlState>>7;

	IBuilderElement* pBuilderElement = NULL;

	pNeuroFactory->CreateElementsEnumerator();	
	while (IElement* pElement = pNeuroFactory->GetNextElement())
	{
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		
		CPoint tmElementPosition = pBuilderElement->GetElementPosition();
		if (rZoneRect.PtInRect(tmElementPosition))
		{
			if (sCtrlState)
				pBuilderElement->SelectElement(true);
			else if (sShiftState)
				pBuilderElement->SelectElement(false);
			else
				pBuilderElement->SelectElement(true);		
		} else
		{
			if (!sCtrlState && !sShiftState)
				pBuilderElement->SelectElement(false);
		}		
	}
}

void CBuilder::MoveSelectedElements(int XOffset, int YOffset, bool bAttachToGrid)
{
	IBuilderElement* pBuilderElement = NULL;

	pNeuroFactory->CreateElementsEnumerator();	
	while (IElement* pElement = pNeuroFactory->GetNextElement())
	{
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		
		if (pBuilderElement->IsSelected())
		{
			CPoint tmElementPosition = pBuilderElement->GetElementPosition();

			tmElementPosition.Offset(XOffset, YOffset);
			if (bAttachToGrid)
				tmElementPosition = AttachElementToGrid(tmElementPosition, false);

			pBuilderElement->SetElementPosition(tmElementPosition);
		}
	}
}

// Drawing functions
void CBuilder::ShowElements(CDeviceDriver* pDriver)
{
	IBuilderElement* pBuilderElement = NULL;

	UpdateEnvironmentSettings();

	pNeuroFactory->CreateElementsEnumerator();
	while (IElement* pElement = pNeuroFactory->GetNextElement())
	{
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		pBuilderElement->ShowElement();
	}
}

void CBuilder::ShowSelectedZone(CDeviceDriver* pDriver)
{
	CPoint	pntCursorPos;
	GetCursorPos(&pntCursorPos);
	ScreenToClient(&pntCursorPos);

	CPoint ptPrevPos = pDriver->TransformPoint(pntPrevDragPos);
	pntCursorPos = pDriver->TransformPoint(pntCursorPos);

	UpdateEnvironmentSettings();

    pDriver->Enable(GL_LINE_STIPPLE); 		
	pDriver->LineStipple(6, 21845);
	pDriver->LineWidth(2.0f);      
	pDriver->Color3f(0.2f, 0.2f, 0.2f);    

	pDriver->Begin(GL_LINE_LOOP);
	pDriver->Vertex3f(ptPrevPos.x, ptPrevPos.y, 0.3);
	pDriver->Vertex3f(pntCursorPos.x, ptPrevPos.y, 0.3);
	pDriver->Vertex3f(pntCursorPos.x, pntCursorPos.y, 0.3);
	pDriver->Vertex3f(ptPrevPos.x, pntCursorPos.y, 0.3);
	pDriver->End();

	pDriver->LineWidth(1.0f);      
    pDriver->Disable(GL_LINE_STIPPLE); 
}

// CBuilder message handlers
void CBuilder::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CDeviceDriver* pDriver = CreateDeviceDriver(&dc);

	if (bShowGrid)
	{
		CGridCtrl mGrid(pDriver, iGridRange, iXScrollOffset, iYScrollOffset);
		mGrid.ShowGrid();
	}

	ShowElements(pDriver);
	
	if (iBuilderState == BS_ZONE_SELECTING)
		ShowSelectedZone(pDriver);

	ReleaseDeviceDriver(pDriver);
}

void CBuilder::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool bSkipTesting = false;

	mNeuronInfoDlg.ShowElement(NULL, CPoint(0, 0));

	if (iBuilderState != BS_CONNECTING)
	{
		IElement* tmElement = GetElementUnderMouse(point);
		if (tmElement)
		{
			// Starting item dragging
			SetCapture();

			pntPrevDragPos = point;
			
			SelectElement(tmElement);

			iBuilderState = BS_DRAGGING;

			bSkipTesting = true;
		}

		if (!bSkipTesting)
		{
			// Starting zone selecting
			SetCapture();

			pActiveElement = NULL;
			pAppController->ShowElementProperties(NULL);

			pntPrevDragPos = point;

			CRect rClipRect;
			GetClientRect(rClipRect);
			ClientToScreen(&rClipRect);
			ClipCursor(&rClipRect);

			iBuilderState = BS_ZONE_SELECTING;
		}
	}

	COutputDevice::OnLButtonDown(nFlags, point);
}

void CBuilder::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPoint	pntCursorPos;
	IElement* tmElement;

	mNeuronInfoDlg.ShowElement(NULL, CPoint(0, 0));

	switch (iBuilderState)
	{
	case BS_ZONE_SELECTING:
		iBuilderState = BS_NO_ACTION;

		GetCursorPos(&pntCursorPos);
		ScreenToClient(&pntCursorPos);

		SelectElements(pntCursorPos, pntPrevDragPos);

		ClipCursor(NULL);
		ReleaseCapture();
		Invalidate();
		break;
	case BS_DRAGGING:
		iBuilderState = BS_NO_ACTION;

		MoveSelectedElements(point.x - pntPrevDragPos.x, point.y - pntPrevDragPos.y, true);
		
		ReleaseCapture();
		Invalidate();	
		break;
	case BS_CONNECTING:	
		iBuilderState = BS_NO_ACTION;

		HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_ARROW);
		HCURSOR hOldCur = SetCursor(hCur);
		DeleteObject(hOldCur);	 

		tmElement = GetElementUnderMouse(point);
		if (tmElement && pActiveElement)
		{
			IDataConnector* pDataConnector = NULL;				
			pActiveElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

			pDataConnector->ProcessAddConnection(tmElement);

			pAppController->ShowElementProperties(pActiveElement);
		}
		
		Invalidate();
		break;
	}

	SetFocus();

	COutputDevice::OnLButtonUp(nFlags, point);
}

void CBuilder::OnMouseMove(UINT nFlags, CPoint point)
{
	IElement* tmElement;
	CPoint tmPoint(point);

	switch (iBuilderState)
	{
	case BS_ZONE_SELECTING:
		Invalidate();
		break;	
	case BS_DRAGGING:
		MoveSelectedElements(point.x - pntPrevDragPos.x, point.y - pntPrevDragPos.y, false);

		pntPrevDragPos = point;	
		Invalidate();
		break;
	case BS_CONNECTING:
		tmElement = GetElementUnderMouse(point);
		if (tmElement && tmElement != pActiveElement)
		{		
			HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_POINTER_LINK_ACCEPTED);
			HCURSOR hOldCur = SetCursor(hCur);
			DeleteObject(hOldCur);			
		} else
		{
			HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_POINTER_LINK);
			HCURSOR hOldCur = SetCursor(hCur);
			DeleteObject(hOldCur);		
		}
		break;
	default:
		tmElement = GetElementUnderMouse(point);
		ClientToScreen(&tmPoint);

		mNeuronInfoDlg.ShowElement(tmElement, tmPoint);
		break;
	}

	COutputDevice::OnMouseMove(nFlags, point);
}

void CBuilder::OnRButtonUp(UINT nFlags, CPoint point)
{
	mNeuronInfoDlg.ShowElement(NULL, CPoint(0, 0));

	IElement* pElement = GetElementUnderMouse(point);
	if (pElement)
	{
		pActiveElement = pElement;		
		pNeuroFactory->SelectElement(pElement, false, false);
		pAppController->ShowElementProperties(pActiveElement);

		IBuilderElement* pBuilderElement = NULL;
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);

		Invalidate();

		pBuilderElement->TrackPopupMenu(point);
	} else
	{
		pActiveElement = NULL;
		pAppController->ShowElementProperties(NULL);
	}

	COutputDevice::OnRButtonUp(nFlags, point);
}

// CBuilder command handlers
void CBuilder::OnShowBuilderProperties()
{
	CBuilderPropertiesDlg mDlg;
	
	mDlg.mShowGrid = bShowGrid;
	mDlg.mGridRange = iGridRange;
	mDlg.mAttachToGrid = bAttachToGrid;

	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		bShowGrid = mDlg.mShowGrid;
		iGridRange = mDlg.mGridRange;
		bAttachToGrid = mDlg.mAttachToGrid;		

		Invalidate();
	}
}

void CBuilder::OnSelectAllElements()
{
	IBuilderElement* pBuilderElement = NULL;

	pNeuroFactory->CreateElementsEnumerator();	
	while (IElement* pElement = pNeuroFactory->GetNextElement())
	{
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		
		pBuilderElement->SelectElement(true);
	}	
}

BOOL CBuilder::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class	
	if (pActiveElement)
		pActiveElement->CommandNotify(wParam, lParam);

	Invalidate();

    pAppController->ShowElementProperties(pActiveElement);
	
	return __super::OnCommand(wParam, lParam);
}

// IBuilderControl implementations section	
CWnd* CBuilder::GetControlWindow()
{
	return (CWnd*)this;
}

void CBuilder::SetBuilderState(int iState)
{
	iBuilderState = iState;

	if (iBuilderState == BS_CONNECTING)
	{
		HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_POINTER_LINK);
		HCURSOR hOldCur = SetCursor(hCur);
		DeleteObject(hOldCur); 	
	}
}

void CBuilder::SetActiveElement(IElement* pElement)
{
	pActiveElement = pElement;
}

// IObject implementations section
CString CBuilder::GetClassString()
{
	return _T("CBuilder");
}	

void CBuilder::QueryInterface(int iIDD, void** ppvObject)
{
	COutputDevice::QueryInterface(iIDD, ppvObject);

	switch(iIDD)
	{
	case IDD_IBuilderControl:
        *ppvObject = (IBuilderControl*)this;
		break;
	case IDD_IElementsCollection:
		*ppvObject = pNeuroFactory;
		break;	
	}
}