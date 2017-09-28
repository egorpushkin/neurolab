#include "StdAfx.h"
#include ".\devicedriver.h"

#include "interface_idds.h"

CDeviceDriver::CDeviceDriver(CDC* pDC, CRect& rect)
{
	pWndDeviceContext = pDC;
	wndRect = rect;

	CalculateCoefficients();
}

CDeviceDriver::~CDeviceDriver(void)
{
}

// System device operations
void CDeviceDriver::CalculateCoefficients()
{
	fXKoeff = 2.97f / wndRect.Width();
	fYKoeff = 2.0f / wndRect.Height();

	fZKoeff = fYKoeff; // !!
}

void CDeviceDriver::UpdateWindowRect(CRect& rect)
{
	wndRect = rect;
}

BOOL CDeviceDriver::SwapBuffers()
{
	if (pWndDeviceContext && pWndDeviceContext->m_hDC)
		return ::SwapBuffers(pWndDeviceContext->m_hDC);
	return FALSE;
}

// IDeviceDriver implementations section
CRect CDeviceDriver::GetWindowRect()
{
	return wndRect;
}

void CDeviceDriver::Color3f(float red, float green, float blue)
{
	glColor3f(red, green, blue);
}

void CDeviceDriver::Color4f(float red, float green, float blue, float alpha)
{
	glColor4f(red, green, blue, alpha);
}

void CDeviceDriver::Color3rgb(int red, int green, int blue)
{
	glColor3f(red / 255.0f, green / 255.0f, blue / 255.0f);
}

void CDeviceDriver::Begin(UINT mode)
{
	glBegin(mode);
}

void CDeviceDriver::End()
{
	glEnd();
}

void CDeviceDriver::Rotatef(float angle, float x, float y, float z)
{
	glRotatef(angle, x, y, z);
}

CPoint CDeviceDriver::TransformPoint(CPoint& ptOld)
{
	return CPoint(ptOld.x - wndRect.Width()/2, 
		wndRect.Height()/2 - ptOld.y);
}

void CDeviceDriver::LineWidth(float width)
{
	glLineWidth(width);
}

void CDeviceDriver::Enable(UINT cap)
{
	glEnable(cap);
}

void CDeviceDriver::Disable(UINT cap)
{
	glDisable(cap);
}

void CDeviceDriver::LineStipple(int factor, unsigned short int pattern)
{
	glLineStipple(factor, pattern);
}

void CDeviceDriver::BlendFunc(UINT sfactor, UINT dfactor)
{
	glBlendFunc(sfactor, dfactor);
}

CDC	* CDeviceDriver::GetWindowDC()
{
	return pWndDeviceContext;
}

void CDeviceDriver::Disk(GLUquadric * qobj, double innerRadius, double outerRadius, int slices, int loops)
{
	gluDisk(qobj, innerRadius * fXKoeff, outerRadius * fXKoeff, slices, loops);
}

void CDeviceDriver::RasterPos2f(float x, float y)
{
	glRasterPos2f(x * fXKoeff, y * fYKoeff);
}

void CDeviceDriver::Vertex3f(float x, float y, float z)
{
	glVertex3f(x * fXKoeff, y * fYKoeff, z * fZKoeff);
}

void CDeviceDriver::Translatef(float x, float y, float z)
{
	glTranslatef(x * fXKoeff, y * fYKoeff, z * fZKoeff);
}

void CDeviceDriver::DrawDeviceBitmap(sDeviceBitmap* pBitmap, float x, float y)
{
	RasterPos2f(x, y);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
		
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);

	glDrawPixels(pBitmap->pImage->sizeX, pBitmap->pImage->sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, pBitmap->pImage->data);     

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

void CDeviceDriver::DrawTexturedQuad(unsigned int iTextureID, 
	float fX1, float fY1, float fX2, float fY2, float fZ,
	float fTexX1, float fTexY1, float fTexX2, float fTexY2)
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);		
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);

	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0f, 1.0f, 1.0f);

	glCallList(iTextureID);

	glBegin(GL_QUADS);
	glTexCoord2f(fTexX1 , fTexY1); 
	this->Vertex3f(fX1,	fY1, fZ);

	glTexCoord2f(fTexX2, fTexY1);
	this->Vertex3f(fX2, fY1, fZ);

	glTexCoord2f(fTexX2, fTexY2); 
	this->Vertex3f(fX2, fY2, fZ);

	glTexCoord2f(fTexX1, fTexY2); 
	this->Vertex3f(fX1, fY2, fZ);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

// IObject implementations section
CString CDeviceDriver::GetClassString()
{
	return _T("CDeviceDriver");
}

void CDeviceDriver::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IDeviceDriver:
		*ppvObject = (IDeviceDriver*)this;
		break;
	}
}