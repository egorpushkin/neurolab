#pragma once

#include <gl/gl.h>	
#include <gl/glu.h>	
#include <gl/glaux.h>

#include "CmnObjects.h"
#include "CmnElement.h"

#include "DefOutput.h"

interface IElement;

struct sDeviceBitmap
{
	AUX_RGBImageRec*		pImage;
	CString					csImageName;

	unsigned int			iTextureID;
};

interface IDeviceDriver : public IObject
{
	virtual void			Color3f(float red, float green, float blue) = 0;
	virtual void			Color4f(float red, float green, float blue, float alpha) = 0;
	virtual void			Color3rgb(int red, int green, int blue) = 0;

	virtual void			Begin(UINT mode) = 0;
	virtual void			End() = 0;

	virtual void			Enable(UINT cap) = 0;
	virtual void			Disable(UINT cap) = 0;

	virtual void			Vertex3f(float x, float y, float z) = 0;
	virtual void			Rotatef(float angle, float x, float y, float z) = 0;

	virtual void			LineWidth(float width) = 0;

	virtual void			Translatef(float x, float y, float z) = 0;

	virtual CRect			GetWindowRect() = 0;
	virtual CDC*			GetWindowDC() = 0;

	virtual CPoint			TransformPoint(CPoint& ptOld) = 0;

	virtual void			LineStipple(int factor, unsigned short int pattern) = 0;

	virtual void			BlendFunc(UINT sfactor, UINT dfactor) = 0;

	virtual void			RasterPos2f(float x, float y) = 0;

	virtual void			Disk(GLUquadric * qobj, double innerRadius, 
		double outerRadius, int slices, int loops) = 0;

	virtual void			DrawDeviceBitmap(sDeviceBitmap* pBitmap, float x, float y) = 0;
	virtual void			DrawTexturedQuad(unsigned int iTextureID, 
		float fX1, float fY1, float fX2, float fY2, float fZ,
		float fTexX1, float fTexY1, float fTexX2, float fTexY2) = 0;
};

interface IDeviceFont : public IObject
{
	virtual void			RenderString(CString& String, float xPos, float yPos, IDeviceDriver* pDriver) = 0;
};

interface IOutputDevice : public IObject
{
	virtual CPoint			TransformPoint(CPoint& Point) = 0;

	virtual IDeviceDriver*	GetDeviceDriver() = 0;
	virtual sDeviceBitmap*	GetImageByName(CString& ImageRecordName) = 0;     	

	virtual void			LoadImage(CString& FileName, CString& ImageRecordName) = 0;

	virtual IDeviceFont*	GetDefaultFont() = 0;
};

interface IBuilderControl : public IObject
{
	virtual CWnd*			GetControlWindow() = 0;
	virtual void			SetBuilderState(int iState) = 0;

	virtual void			SetActiveElement(IElement* pElement) = 0;
};