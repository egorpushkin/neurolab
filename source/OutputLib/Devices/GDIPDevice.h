#pragma once

#include "MemDC.h"

class DLL_FUNC_DECLARE CGDIPDevice
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