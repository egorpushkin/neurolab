#include "StdAfx.h"
#include ".\gridctrl.h"

CGridCtrl::CGridCtrl(IDeviceDriver * pDrv, int iRange, int xOff, int yOff)
{
	pDriver = pDrv;
	iGridRange = iRange;

	iXOffset = -xOff;
	iYOffset = -yOff;
}

CGridCtrl::~CGridCtrl(void)
{
}

void CGridCtrl::ShowGrid()
{
	CRect wndRect = pDriver->GetWindowRect();

	int iXLeft = iGridRange - iXOffset % iGridRange - 1;
	int iYTop = iGridRange - iYOffset % iGridRange - 1;

	int iXGridLinesCount = (wndRect.Width() - iXLeft) / iGridRange;
	int iYGridLinesCount = (wndRect.Height() - iYTop) / iGridRange;

	int iXRight = iXLeft + iXGridLinesCount * iGridRange;
	int iYBotttom = iYTop + iYGridLinesCount * iGridRange;

	pDriver->LineWidth(1.0f);      
	pDriver->Color3rgb(67, 225, 223);

	for (int i = 0; i < iXGridLinesCount + 1;i++)
	{
		CPoint ptStartPoint = pDriver->TransformPoint(CPoint(iXLeft + i * iGridRange, iYTop));
		CPoint ptEndPoint = pDriver->TransformPoint(CPoint(iXLeft + i * iGridRange, iYBotttom));

		pDriver->Begin(GL_LINES);     
		pDriver->Vertex3f(ptStartPoint.x, ptStartPoint.y, -0.1); 
		pDriver->Vertex3f(ptEndPoint.x, ptEndPoint.y, -0.1);  
		pDriver->End();
	}

	for (int i = 0; i < iYGridLinesCount + 1;i++)
	{
		CPoint ptStartPoint = pDriver->TransformPoint(CPoint(iXLeft, iYTop + i * iGridRange));
		CPoint ptEndPoint = pDriver->TransformPoint(CPoint(iXRight, iYTop + i * iGridRange));

		pDriver->Begin(GL_LINES);     
		pDriver->Vertex3f(ptStartPoint.x, ptStartPoint.y, -0.1); 
		pDriver->Vertex3f(ptEndPoint.x, ptEndPoint.y, -0.1);  
		pDriver->End();
	}	
}

