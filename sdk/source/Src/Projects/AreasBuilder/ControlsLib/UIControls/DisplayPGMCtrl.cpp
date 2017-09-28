// DataImageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DisplayPGMCtrl.h"

#include "../Devices/GDIPDevice.h"

using namespace Gdiplus;

// CDisplayPGMCtrl
IMPLEMENT_DYNAMIC(CDisplayPGMCtrl, CWnd)
CDisplayPGMCtrl::CDisplayPGMCtrl()
	: piSourceBitmap_(NULL)
	, deviceBitmap_(NULL)
{
}

CDisplayPGMCtrl::~CDisplayPGMCtrl()
{
	if (piSourceBitmap_)
		piSourceBitmap_->Release();

	delete deviceBitmap_;
}


BEGIN_MESSAGE_MAP(CDisplayPGMCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CDisplayPGMCtrl::SetBitmap(IPGMBitmap* piSourceBitmap)
{
	if (piSourceBitmap_)
		piSourceBitmap_->Release();

	piSourceBitmap_ = piSourceBitmap;
	piSourceBitmap_->AddRef();

	PrepareBitmapContext();
}

void CDisplayPGMCtrl::OnPaint()
{
	CPaintDC dc(this); 

	CRect clientRect;
	GetClientRect(&clientRect);

	CGDIPDevice	dgipDevice;
	Graphics* pGraphics = dgipDevice.CreateGraphics(&dc);

	// Displaying previously prepared bitmap context
	Rect destinationRect(0, 0, clientRect.Width(), clientRect.Height());

	pGraphics->DrawImage(
		deviceBitmap_, 
		destinationRect, 
		0, 0,
		deviceBitmap_->GetWidth(), deviceBitmap_->GetHeight(),
		UnitPixel);
}

BOOL CDisplayPGMCtrl::OnEraseBkgnd(CDC* /* pDC */)
{
	return TRUE;
}

BOOL CDisplayPGMCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	BOOL ret = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	PrepareBitmapContext();

	return ret;
}

bool CDisplayPGMCtrl::PrepareBitmapContext()
{
	if (!GetSafeHwnd() || !piSourceBitmap_)
		return false;

	// Removing previous context
	delete deviceBitmap_;

	// Receiving bitmap data accessing control interface 
	IDataBitmap* piData = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piSourceBitmap_, IID_IDataBitmap);

	// Preparing bitmap data
	deviceBitmap_ = new Bitmap(
		piData->GetWidth(),
		piData->GetHeight(),
		PixelFormat8bppIndexed);	

	BitmapData bitmapData;
	Rect rect(0, 0, piData->GetWidth(), piData->GetHeight());

	deviceBitmap_->LockBits(
		&rect,
		ImageLockModeWrite,
		PixelFormat8bppIndexed,
		&bitmapData);

	for (uint i = 0;i < piData->GetHeight();i++)
		memcpy(
			(char*)bitmapData.Scan0 + i * bitmapData.Stride, 
			(char*)piData->GetData() + i * piData->GetWidth(), 
			piData->GetWidth() * 1);

	deviceBitmap_->UnlockBits(&bitmapData);

	// Preparing bitmap palette
	uint paletteSize = deviceBitmap_->GetPaletteSize();
	ColorPalette* palette = (ColorPalette*)malloc(paletteSize);

	deviceBitmap_->GetPalette(palette, paletteSize);

	for(uint i = 0; i < 256; ++i)
		palette->Entries[i] = (0xff << 24) | (i << 16) | (i << 8) | (i);

	deviceBitmap_->SetPalette(palette);

	free(palette);

	// Releasing queried interface
	piData->Release();

	return true;
}

void CDisplayPGMCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
/*	SetCapture();
	SetFocus();

	ClientToScreen(&point);
	CWnd* wndUnderMouse = WindowFromPoint(point);
	if (wndUnderMouse != this)
	{		
		GetOwner()->SetFocus();
		ReleaseCapture();
		return;
	}	*/

	CWnd::OnMouseMove(nFlags, point);
}
