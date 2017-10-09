//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: GroupsContainer.h
//	Description: The CGroupsContainer declaration.  

#ifndef GROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
#define GROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_

#include "../BuilderElements.h"

// CGroupsContainer declaration
class CGroupsContainer : public BuilderElementsCommonKit::IGroupsContainer
{
public:
	CGroupsContainer(void);
	virtual ~CGroupsContainer(void);

	//////////////////////////////////////////////////////////////////////////
	// Creation/Destruction tools
	//////////////////////////////////////////////////////////////////////////
	virtual void			BuildElementsStructure();
	virtual void			ReleaseElementsStructure();	

	//////////////////////////////////////////////////////////////////////////
	// IGroupsContainer declarations section
	//////////////////////////////////////////////////////////////////////////
	virtual void			SetRootDirectory(const String& rAppFolder);
	virtual void			SetMediaSubDirectory(const String& rMediaDir);
	virtual void			SetBuilderControl(
		ExternalOutputEngine::IBuilderControl* piBuilderControl);
	virtual void			SetFunctionsFactory(
		BuilderElementsCommonKit::IFunctionsFactory* pFactory);

	virtual result			ProcessLoadMediaData();

	virtual NetworkImportingKit::IElement*	
		CreateElement(BuilderElementsCommonKit::SysElement* pElement);

	virtual BuilderElementsCommonKit::IElementContainersEnumerator*	
		GetElementContainersEnumerator();

	//////////////////////////////////////////////////////////////////////////
	// ICommon declarations section	
	//////////////////////////////////////////////////////////////////////////
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:	
	//////////////////////////////////////////////////////////////////////////
	// BuilderElementsCommonKit::IGroupsContainer members
	//////////////////////////////////////////////////////////////////////////
	IContainer<BuilderElementsCommonKit::IElementsContainer*>*		
		piElementContainersList_;

	BuilderElementsCommonKit::IFunctionsFactory*		
		piFunctionsFactory_;

	ExternalOutputEngine::IBuilderControl*		
		piBuilderControl_;
	String					rootDirectory_;
	String					mediaSubDirectory_;

	//////////////////////////////////////////////////////////////////////////
	// ICommon members
	//////////////////////////////////////////////////////////////////////////
	ulong					numRef_;

	//////////////////////////////////////////////////////////////////////////
	//CExtrenalsManager		mExternalsManager;
	//////////////////////////////////////////////////////////////////////////
};

#endif // !GROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
