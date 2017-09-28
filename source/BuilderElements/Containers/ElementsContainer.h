#pragma once

#include "ElementsCore.h"

class CElementsContainer : public IElementsContainer
{
public:
	CElementsContainer(void);
	~CElementsContainer(void);

// Initialization functions
	void					SetTitle(CString& Title);
	void					AddElement(sElement* pElement);

// IElementsContainer declarations section
public:
	virtual void			ReleaseElements();

	virtual CString			GetTitle();

	ENUMERATOR(mElementsList, sElement*, CreateEnumerator, GetNextElement, posElementsEnum)

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CList<sElement*, sElement*>	mElementsList;
	
	CString					csTitle;
};
