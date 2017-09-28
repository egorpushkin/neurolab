#pragma once

#include "MemDC.h"

class CGDIPDevice
{
public:
	CGDIPDevice();
	~CGDIPDevice();

	Gdiplus::Graphics*		CreateGraphics(CDC* pDC);
	void					ReleaseGraphics();

private:
	Gdiplus::Graphics*		pGraphicsObj;
	CMemDC*					pMemDC;

	bool					IsContextAcctive;
};