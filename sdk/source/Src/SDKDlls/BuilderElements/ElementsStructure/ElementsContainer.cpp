//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ElementsContainer.cpp
//	Description: The CElementsContainer implementation.  

#include "ElementsContainer.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;

CElementsContainer::CElementsContainer(void)
	: piElementsList_(NULL)
	, title_(_T(""))
	, numRef_(0)
{
	CContainer<SysElement*, VectorStorage, Copy, NoRefs>* pElementsContainer = 
		new CContainer<SysElement*, VectorStorage, Copy, NoRefs>;

	pElementsContainer->QueryInterface(IID_IContainer, (void**)&piElementsList_);
}

CElementsContainer::~CElementsContainer(void)
{
	ReleaseElements();

	piElementsList_->Release();
}

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction tools
//////////////////////////////////////////////////////////////////////////
void CElementsContainer::SetTitle(const String& rTitle)
{
	title_ = rTitle;
}

SysElement* CElementsContainer::AddElement(const StringA& name, const StringA& title, const StringA& shortName)
{
	SysElement* pElement = new SysElement(name, title, shortName);

	piElementsList_->Add(pElement);

    return pElement;	
}

void CElementsContainer::ReleaseElements()
{
	ISysElementsEnumerator* pElementsEnum = piElementsList_->Clone();
	for(bool haSysElements = pElementsEnum->SelectFirst();haSysElements;haSysElements = pElementsEnum->SelectNext())
	{
		SysElement* pElement = pElementsEnum->GetSelected();

		delete pElement;
	}
	pElementsEnum->Release();	
}

//////////////////////////////////////////////////////////////////////////
// IElementsContainer implementations section
//////////////////////////////////////////////////////////////////////////
const String& CElementsContainer::GetTitle()
{
	return title_;
}

ISysElementsEnumerator* CElementsContainer::GetElementsEnumerator()
{
	return piElementsList_->Clone();
}

//////////////////////////////////////////////////////////////////////////
// ICommon implementations section
//////////////////////////////////////////////////////////////////////////
ulong CElementsContainer::AddRef()
{
	return ++numRef_;						
}

ulong CElementsContainer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CElementsContainer::GetClassString() const
{
	return _T("CElementsContainer");
}

result CElementsContainer::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IElementsContainer)
	{
		*ppObject = (IElementsContainer*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
