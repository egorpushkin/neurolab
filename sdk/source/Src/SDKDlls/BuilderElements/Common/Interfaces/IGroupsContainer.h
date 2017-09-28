//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IGroupsContainer.h
//	Description: The IGroupsContainer declaration.  

#ifndef IGROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
#define IGROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_

// IGroupsContainer declaration
interface IGroupsContainer : public ICommon
{
	virtual void			SetRootDirectory(const String& rAppDir) = 0;
	virtual void			SetMediaSubDirectory(const String& rMediaDir) = 0;
	virtual void			SetBuilderControl(
		ExternalOutputEngine::IBuilderControl* piBuilderControl) = 0;
	virtual void			SetFunctionsFactory(
		BuilderElementsCommonKit::IFunctionsFactory* pFactory) = 0;


	virtual result			ProcessLoadMediaData() = 0;
	
	virtual NetworkImportingKit::IElement*			
		CreateElement(SysElement* pElement) = 0;

	virtual IElementContainersEnumerator*			
		GetElementContainersEnumerator() = 0;
};

#endif // !IGROUPSCONTAINER_H__BUILDERELEMENTS__INCLUDED_
