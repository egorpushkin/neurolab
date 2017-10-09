#pragma once

#include "CmnOutput.h"

class DLL_FUNC_DECLARE CDeviceFont : public IDeviceFont
{
public:
	CDeviceFont(HDC hDC, int Height, float r, float g, float b);
	~CDeviceFont();

	void			SetColor(float r, float g, float b);

	void			BuildFont(HDC hDC);
	void			KillFont();

// IDeviceFont declarations section
	virtual void			RenderString(CString& String, float xPos, float yPos, IDeviceDriver* pDriver);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:	
	int iFontHeight;

	float fRed, fGreen, fBlue;	

	GLuint	glDisplayList;
};