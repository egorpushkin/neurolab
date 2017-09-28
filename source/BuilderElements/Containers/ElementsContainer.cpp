#include "StdAfx.h"
#include ".\elementscontainer.h"

#include "interface_idds.h"

CElementsContainer::CElementsContainer(void)
{
}

CElementsContainer::~CElementsContainer(void)
{
	ReleaseElements();
}

// Initialization functions
void CElementsContainer::SetTitle(CString& Title)
{
	csTitle = Title;
}

void CElementsContainer::AddElement(sElement* pElement)
{
	mElementsList.AddTail(pElement);
}

CString CElementsContainer::GetTitle()
{
	return csTitle;
}

// IElementsContainer implementations section
void CElementsContainer::ReleaseElements()
{
	for (;mElementsList.GetCount() > 0;)
	{
		sElement* pElement = mElementsList.GetHead();
		mElementsList.RemoveHead();	
		
		delete pElement;
	}	
}

// IObject implementations section
CString CElementsContainer::GetClassString()
{
	return _T("CElementsContainer");
}

void CElementsContainer::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IElementsContainer:
		*ppvObject = (IElementsContainer*)this;
		break;
	}
}
