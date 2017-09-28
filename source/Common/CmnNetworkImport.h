#pragma once

#include "CmnObjects.h"

interface IImportManager : public IObject
{
	virtual bool			InitializeManager() = 0;
	virtual void			RelaseManager() = 0;

	virtual bool			LoadNLProject(CString& FileName) = 0;
};

