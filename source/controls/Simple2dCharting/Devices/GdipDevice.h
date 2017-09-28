#ifndef GDIPDEVICE_H__S2DCHARTING__INCLUDED_
#define GDIPDEVICE_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class GdipDevice : public BasicDevice
	{
	public:

		GdipDevice();
		virtual ~GdipDevice();

		// Pure interface
		virtual void ConstructFromHandle(void* pWnd, void* pHandle);
		virtual void DumpContext();

		virtual unsigned int GetWidth();
		virtual unsigned int GetHeight();

		virtual void FillRectangle(Color color, float x, float y, float width, float height);
		virtual void DrawLine(Color color, float fromX, float fromY, float toX, float toY, float thickness = 1.0);
		virtual void DrawString(Color color, const std::string& font, float size, FontStyle style, float x, float y, const std::string& text);

	private:

		void* pWnd_;
		void* pHandle_;
		
		CRect* pRect_;
		Gdiplus::Graphics* pSourceDevice_;
		Gdiplus::Bitmap* pBufferBitmap_;
		Gdiplus::Graphics* pBufferDevice_;        

	}; // GdipDevice

} // Simple2dCharting

#endif // !GDIPDEVICE_H__S2DCHARTING__INCLUDED_
