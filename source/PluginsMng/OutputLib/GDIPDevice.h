#pragma once

#include "MemDC.h"

class CGDIPDevice
{
public:
	CGDIPDevice();
	~CGDIPDevice();

	Graphics * CreateGraphics(CDC* pDC);
	void ReleaseGraphics();

private:
	Graphics*	pGraphicsObj;
	CMemDC*		pMemDC;

	bool		IsContextAcctive;
};