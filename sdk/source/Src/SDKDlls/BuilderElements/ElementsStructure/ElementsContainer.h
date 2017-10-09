//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ElementsContainer.h
//	Description: The CElementsContainer declaration.  

#ifndef ELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
#define ELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

// CElementsContainer declaration
class CElementsContainer 
	: public BuilderElementsCommonKit::IElementsContainer
{
public:
	CElementsContainer(void);
	virtual ~CElementsContainer(void);

	//////////////////////////////////////////////////////////////////////////
	// Construction/Destruction tools
	//////////////////////////////////////////////////////////////////////////
	void					SetTitle(const String& rTitle);
	BuilderElementsCommonKit::SysElement*							
		AddElement(const StringA& name, const StringA& title, const StringA& shortName);

	void					ReleaseElements();

public:
	//////////////////////////////////////////////////////////////////////////
	// IElementsContainer declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual const String&	GetTitle();

	virtual BuilderElementsCommonKit::ISysElementsEnumerator*	
		GetElementsEnumerator() = 0;

	//////////////////////////////////////////////////////////////////////////
	// ICommon declarations section	
	//////////////////////////////////////////////////////////////////////////
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	//////////////////////////////////////////////////////////////////////////
	// BuilderElementsCommonKit::IElementsContainer members
	//////////////////////////////////////////////////////////////////////////
	IContainer<BuilderElementsCommonKit::SysElement*>*		
		piElementsList_;
	
	String					title_;

	//////////////////////////////////////////////////////////////////////////
	// ICommon members
	//////////////////////////////////////////////////////////////////////////
	ulong					numRef_;
};

#endif // !ELEMENTSCONTAINER_H__BUILDERELEMENTS__INCLUDED_

