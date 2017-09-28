#ifndef BUFFERCORE_H__BUFFER__DRAWING__LUA_PACKAGE__INCLUDED_
#define BUFFERCORE_H__BUFFER__DRAWING__LUA_PACKAGE__INCLUDED_

namespace Drawing
{
	
	struct RgbColor
	{
		
		RgbColor();
		RgbColor(int rr, int gg, int bb, int aa = 0);

		bool operator==(const RgbColor& color);
		bool operator!=(const RgbColor& color);

		unsigned char b_;
		unsigned char g_;
		unsigned char r_;
		unsigned char a_;

	};

	struct BitmapBuffer
	{

		RgbColor* pBitmapData_;

		unsigned int width_;
		unsigned int height_;

		Gdiplus::Graphics* pGraphics_;
		HDC pBufferHdc_;
		HDC pCompatibleHdc_;
		HBITMAP pBufferBitmap_;
		HBITMAP pDefaultBitmap_;

	};	

	BitmapBuffer* AcquireBuffer(Gdiplus::Graphics* pGraphics);
	result ReleaseBuffer(BitmapBuffer* pBitmapBuffer);
	result PutPixel(BitmapBuffer* pBitmapBuffer, unsigned int x, unsigned int y, const RgbColor& color);
	
} // namespace Drawing

#endif // !BUFFERCORE_H__BUFFER__DRAWING__LUA_PACKAGE__INCLUDED_
