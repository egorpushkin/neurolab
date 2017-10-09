#pragma once

#include "CmnObjects.h"
#include "CmnElement.h"

typedef DWORD (*PCALLBACK_ROUTIME)(DWORD dwParam); 

interface IAppController : public IObject
{
	virtual void			ExecuteCallback(PCALLBACK_ROUTIME pfnRoutine, DWORD dwData) = 0;

 	virtual void			CreatePluginBar(CDialog* pPluginBar, int iIDD) = 0;
	virtual void			ShowPluginBar(CDialog* pPluginBar, CString& csBarTitle) = 0;

	virtual void			ShowElementProperties(IElement* pElement) = 0;
};