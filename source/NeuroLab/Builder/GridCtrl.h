#pragma once

#include "CmnOutput.h"

class CGridCtrl
{
public:
	CGridCtrl(IDeviceDriver * pDrv, int iRange, int xOff, int yOff);
	~CGridCtrl(void);

	void			ShowGrid();

private:	
	IDeviceDriver*	pDriver;

	int				iGridRange;
	CRect			mRect;

	int				iXOffset;
	int				iYOffset;
};
