#include "Common/Includes.h"

#include "Common/BasicDevice.h"

#ifndef WINVER				
#define WINVER 0x0400		
#endif

#include <afxwin.h> 
#include <afxext.h>  
#include <gdiplus.h>

#include "GdipDevice.h"

namespace Simple2dCharting
{

	GdipDevice::GdipDevice()
		: pWnd_(NULL)
		, pHandle_(NULL)
		, pRect_(NULL)
		, pSourceDevice_(NULL)
		, pBufferBitmap_(NULL)
		, pBufferDevice_(NULL)        
	{
	}

	GdipDevice::~GdipDevice()
	{
	}

	// Pure interface
	void GdipDevice::ConstructFromHandle(void* pWnd, void* pHandle)
	{
		pWnd_ = pWnd;
		pHandle_ = pHandle;

		pSourceDevice_ = new Gdiplus::Graphics((HDC)pHandle_);
	
		pRect_ = new CRect;
		GetClientRect((HWND)pWnd_, pRect_);
		
		pBufferBitmap_ = new Gdiplus::Bitmap(pRect_->right, pRect_->bottom);

		pBufferDevice_ = Gdiplus::Graphics::FromImage(pBufferBitmap_);
	}

	void GdipDevice::DumpContext()
	{
		pSourceDevice_->DrawImage(pBufferBitmap_, pRect_->left, pRect_->top, pRect_->right, pRect_->bottom);
        
		delete pBufferDevice_;
		delete pBufferBitmap_;
		delete pRect_;
		delete pSourceDevice_;

		pWnd_ = NULL;
		pHandle_ = NULL;
		pRect_ = NULL;
		pSourceDevice_ = NULL;
		pBufferBitmap_ = NULL;
		pBufferDevice_ = NULL;      
	}

	unsigned int GdipDevice::GetWidth()
	{
		if ( !pRect_ )
			return 0;

		return pRect_->Width();
	}

	unsigned int GdipDevice::GetHeight()
	{
		if ( !pRect_ )
			return 0;

		return pRect_->Height();
	}

	void GdipDevice::FillRectangle(Color color, float x, float y, float width, float height)
	{
		if ( !pBufferDevice_ ) 
			return;

		Gdiplus::SolidBrush	brush(color);		
		pBufferDevice_->FillRectangle(&brush, x, y, width, height);
	}

	void GdipDevice::DrawLine(Color color, float fromX, float fromY, float toX, float toY, float thickness)
	{
		if ( !pBufferDevice_ ) 
			return;

		Gdiplus::Pen pen(color, thickness);
		pBufferDevice_->DrawLine(&pen, fromX, fromY, toX, toY);		
	}

	void GdipDevice::DrawString(Color color, const std::string& font, float size, FontStyle style, float x, float y, const std::string& text)
	{
		if ( !pBufferDevice_ ) 
			return;

		USES_CONVERSION;

		Gdiplus::FontFamily fontFamily(A2W(font.c_str()));
		Gdiplus::Font fnt(&fontFamily, size, style, Gdiplus::UnitPixel);
		Gdiplus::PointF point(x, y);
		Gdiplus::SolidBrush brush(color);
		pBufferDevice_->DrawString(A2W(text.c_str()), -1, &fnt, point, &brush);
	}

} // Simple2dCharting
