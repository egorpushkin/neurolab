#include "stdafx.h"
#include "GDIPDevice.h"

using namespace Gdiplus;

CGDIPDevice::CGDIPDevice()
{
	pGraphicsObj = NULL;
	pMemDC = NULL;

	IsContextAcctive = false;
}

CGDIPDevice::~CGDIPDevice()
{
	ReleaseGraphics();
}

Graphics* CGDIPDevice::CreateGraphics(CDC* pDC)
{
	if (IsContextAcctive)
		ReleaseGraphics();

	pMemDC = new CMemDC(pDC);
	pGraphicsObj = new Graphics(pMemDC->m_hDC);

	IsContextAcctive = true;

	return pGraphicsObj;
}

void CGDIPDevice::ReleaseGraphics()
{
	if (IsContextAcctive)
	{
		delete pGraphicsObj;
		delete pMemDC;

		pGraphicsObj = NULL;
		pMemDC = NULL;
	}

	IsContextAcctive = false;
}