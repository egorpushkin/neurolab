#pragma once

#include "CmnApp.h"

interface IManagerControl : public IObject
{
	virtual BOOL			InitializeManagerInstance() = 0;
	virtual BOOL			ReleaseManagerInstance() = 0;

	virtual void			SetAppFolder(CString& csFolder) = 0;

	virtual void			SetAppController(IAppController* pController) = 0;
};