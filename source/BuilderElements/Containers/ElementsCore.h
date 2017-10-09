#pragma once

#include "Templates\Enumerator.h"

#include "CmnObjects.h"
#include "CmnElement.h"

interface IElementsContainer : public IObject
{
	virtual void			ReleaseElements() = 0;
	
	virtual CString			GetTitle() = 0;

	INTERFACE_ENUMERATOR_DECLARATION(sElement*, CreateEnumerator, GetNextElement)
};

interface IGroupsContainer : public IObject
{
	virtual void			BuildElementsStructure() = 0;
	virtual void			ReleaseElementsStructure() = 0;

	virtual void			SetMediaDirectory(CString& MediaDir) = 0;
	virtual void			SetAppFolder(CString& AppFolder) = 0;
	virtual void			SetBuilderControl(IBuilderControl* pControl) = 0;

	virtual void			ProcessLoadMediaData() = 0;
	
	virtual IElement*		CreateElement(sElement* pElement) = 0;
	virtual void			ReleaseElement(IElement* pElement) = 0;

	INTERFACE_ENUMERATOR_DECLARATION(IElementsContainer*, CreateEnumerator, GetNextContainer)
};
