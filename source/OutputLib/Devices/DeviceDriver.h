#pragma once

#include "DeviceFont.h"

#include "CmnOutput.h"

class DLL_FUNC_DECLARE CDeviceDriver : 
	public IDeviceDriver
{
public:
	CDeviceDriver(CDC * pDC, CRect& rect);
	~CDeviceDriver(void);

	// System device operations
	BOOL				SwapBuffers();

	void				CalculateCoefficients();
	void				UpdateWindowRect(CRect& rect);

// IDeviceDriver declarations section
public:
	virtual void			Color3f(float red, float green, float blue);
	virtual void			Color4f(float red, float green, float blue, float alpha);
	virtual void			Color3rgb(int red, int green, int blue);

	virtual void			Begin(UINT mode);
	virtual void			End();

	virtual void			Enable(UINT cap);
	virtual void			Disable(UINT cap);

	virtual void			Vertex3f(float x, float y, float z);
	virtual void			Rotatef(float angle, float x, float y, float z);

	virtual void			LineWidth(float width);

	virtual void			Translatef(float x, float y, float z);

	virtual CRect			GetWindowRect();
	virtual CDC*			GetWindowDC();

	virtual CPoint			TransformPoint(CPoint& ptOld);

	virtual void			LineStipple(int factor, unsigned short int pattern);

	virtual void			BlendFunc(UINT sfactor, UINT dfactor);

	virtual void			RasterPos2f(float x, float y);

	virtual void			Disk(GLUquadric * qobj, double innerRadius, 
		double outerRadius, int slices, int loops);

	virtual void			DrawDeviceBitmap(sDeviceBitmap* pBitmap, float x, float y);
	virtual void			DrawTexturedQuad(unsigned int iTextureID, 
		float fX1, float fY1, float fX2, float fY2, float fZ,
		float fTexX1, float fTexY1, float fTexX2, float fTexY2);



// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CRect			wndRect;

	CDC*			pWndDeviceContext;

	float			fXKoeff;
	float			fYKoeff;
	float			fZKoeff;
};

