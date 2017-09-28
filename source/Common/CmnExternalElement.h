#pragma once

#include "CmnElement.h"

interface IExternalElementsContainer : public IObject
{
	virtual void			SetBuilderControl(IBuilderControl* pDevice) = 0;
	virtual void			SetAppFolder(CString& AppFolder) = 0;
	virtual void			SetMediaDirectory(CString& MediaDir) = 0;    

	virtual void			ProcessLoadMediaData() = 0;

	// Elements oparations
	virtual IElement*		TryCreateElement(CString& ElementSysName) = 0;
	virtual bool			TryReleaseElement(IElement* pElement) = 0;
    
	// Elements info
    virtual CString			GetGroupName() = 0;
	INTERFACE_ENUMERATOR_DECLARATION(sElement*, CreateEnumerator, GetNextElement)
};