#include "stdafx.h"

#include "BufferCore.h"

namespace Drawing
{
	
	RgbColor::RgbColor()
		: r_(0)
		, g_(0)
		, b_(0)
		, a_(0)

	{
	}

	RgbColor::RgbColor(int r, int g, int b, int a)
		: r_(r)
		, g_(g)
		, b_(b)
		, a_(a)
	{
	}

	bool RgbColor::operator==(const RgbColor& color)
	{
		return ( color.r_ == r_ ) && ( color.g_ == g_ ) && ( color.b_ == b_ );	
	}

	bool RgbColor::operator!=(const RgbColor& color)
	{
		return ( color.r_ != r_ ) || ( color.g_ != g_ ) || ( color.b_ != b_ );	
	}

	BitmapBuffer* AcquireBuffer(Gdiplus::Graphics* pGraphics)
	{
		Gdiplus::Rect boundRect;
		pGraphics->GetVisibleClipBounds(&boundRect);

		BITMAPINFO bitmatInfo;
		bitmatInfo.bmiHeader.biSize = sizeof(bitmatInfo.bmiHeader);
		bitmatInfo.bmiHeader.biWidth = boundRect.Width;
		bitmatInfo.bmiHeader.biHeight = - boundRect.Height;
		bitmatInfo.bmiHeader.biPlanes = 1;
		bitmatInfo.bmiHeader.biBitCount = 32;
		bitmatInfo.bmiHeader.biCompression = BI_RGB;
		bitmatInfo.bmiHeader.biSizeImage = boundRect.Width * 4 * boundRect.Height;
		bitmatInfo.bmiHeader.biClrUsed = 0;
		bitmatInfo.bmiHeader.biClrImportant = 0;

		BitmapBuffer* pBitmapBuffer = new BitmapBuffer;
		pBitmapBuffer->width_ = boundRect.Width;
		pBitmapBuffer->height_ = boundRect.Height;
		pBitmapBuffer->pBitmapData_ = 
			new RgbColor[boundRect.Width * boundRect.Height];

		pBitmapBuffer->pGraphics_ = pGraphics;
		pBitmapBuffer->pBufferHdc_ = pGraphics->GetHDC();

		pBitmapBuffer->pCompatibleHdc_ = ::CreateCompatibleDC(
			pBitmapBuffer->pBufferHdc_);
		pBitmapBuffer->pBufferBitmap_ = ::CreateCompatibleBitmap(
			pBitmapBuffer->pBufferHdc_, 
			boundRect.Width, 
			boundRect.Height);
		pBitmapBuffer->pDefaultBitmap_ = (HBITMAP)::SelectObject(
			pBitmapBuffer->pCompatibleHdc_, 
			pBitmapBuffer->pBufferBitmap_);

		::BitBlt(pBitmapBuffer->pCompatibleHdc_, 
			0, 0, 
			pBitmapBuffer->width_, pBitmapBuffer->height_, 
			pBitmapBuffer->pBufferHdc_,	
			0, 0, SRCCOPY);

		int res = ::GetDIBits(
			pBitmapBuffer->pCompatibleHdc_, 
			pBitmapBuffer->pBufferBitmap_, 
			0, boundRect.Height, 
			pBitmapBuffer->pBitmapData_, 
			&bitmatInfo, 
			DIB_RGB_COLORS);
		if ( !res )
		{
			::SelectObject(pBitmapBuffer->pCompatibleHdc_, pBitmapBuffer->pDefaultBitmap_);
			::DeleteObject(pBitmapBuffer->pBufferBitmap_);
			::DeleteObject(pBitmapBuffer->pCompatibleHdc_);

			pGraphics->ReleaseHDC(pBitmapBuffer->pBufferHdc_);

			delete pBitmapBuffer->pBitmapData_;
			delete pBitmapBuffer;

			return NULL;
		}

		return pBitmapBuffer;
	}

	result ReleaseBuffer(BitmapBuffer* pBitmapBuffer)
	{
		BITMAPINFO bitmatInfo;
		bitmatInfo.bmiHeader.biSize = sizeof(bitmatInfo.bmiHeader);
		bitmatInfo.bmiHeader.biWidth = pBitmapBuffer->width_;
		bitmatInfo.bmiHeader.biHeight = -((int)pBitmapBuffer->height_);
		bitmatInfo.bmiHeader.biPlanes = 1;
		bitmatInfo.bmiHeader.biBitCount = 32;
		bitmatInfo.bmiHeader.biCompression = BI_RGB;
		bitmatInfo.bmiHeader.biSizeImage = pBitmapBuffer->width_ * 4 * pBitmapBuffer->height_;
		bitmatInfo.bmiHeader.biClrUsed = 0;
		bitmatInfo.bmiHeader.biClrImportant = 0;

		int res = ::SetDIBits(
			pBitmapBuffer->pCompatibleHdc_, 
			pBitmapBuffer->pBufferBitmap_, 
			0, pBitmapBuffer->height_, 
			pBitmapBuffer->pBitmapData_, 
			&bitmatInfo, 
			DIB_RGB_COLORS);
		if ( !res )
		{
			// Error
		}

		::BitBlt(pBitmapBuffer->pBufferHdc_, 
			0, 0, 
			pBitmapBuffer->width_, pBitmapBuffer->height_, 
			pBitmapBuffer->pCompatibleHdc_,	
			0, 0, SRCCOPY);

		pBitmapBuffer->pGraphics_->ReleaseHDC(pBitmapBuffer->pBufferHdc_);

		::SelectObject(pBitmapBuffer->pCompatibleHdc_, pBitmapBuffer->pDefaultBitmap_);
		::DeleteObject(pBitmapBuffer->pBufferBitmap_);
		::DeleteObject(pBitmapBuffer->pCompatibleHdc_);

		delete pBitmapBuffer->pBitmapData_;
		delete pBitmapBuffer;	

		return S_OK;
	}

	result PutPixel(BitmapBuffer* pBitmapBuffer, unsigned int x, unsigned int y, const RgbColor& color)
	{
		if ( x >= pBitmapBuffer->width_ || y >= pBitmapBuffer->height_ )
			return S_FALSE;

		unsigned int offset = x + y * pBitmapBuffer->width_;
		memcpy(&(pBitmapBuffer->pBitmapData_[offset]), &color, sizeof(RgbColor));
        
		return S_OK;
	}

} // namespace Drawing
