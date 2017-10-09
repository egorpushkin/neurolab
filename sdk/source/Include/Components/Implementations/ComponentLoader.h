//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ComponentLoader.h
//	Description: The CComponentLoader declaration file.   

#ifndef COMPONENTLOADER_H__COMPONENTS__INCLUDED_
#define COMPONENTLOADER_H__COMPONENTS__INCLUDED_

// Component library external symbols
typedef result				(*PDLL_GET_CLASS_OBJECT_ROUTINE)(REFCLSID rCLSID, REFIID rIID, void** ppObject);
typedef result				(*PDLL_CAN_UNLOAD_NOW_ROUTINE)();

typedef void				(*PGET_COMPONENT_NAME_ROUTINE)(String& rComponentName);
typedef void				(*PGET_COMPONENT_VERSION_ROUTINE)(String& rComponentVersion);

// CComponentLoader declaration
class CComponentLoader : public IComponentLoader
{
public:
	CComponentLoader();
	CComponentLoader(const StringA& rLibraryName);

	virtual ~CComponentLoader();

	// IComponentLoader declarations section
	virtual void			SetLibraryName(const StringA& rLibraryName);
	virtual StringA			GetLibraryName();

	virtual result			VerifyWhetherExists();	

	virtual result			InitializeComponentInstance(REFCLSID rCLSID);
	virtual result			ReleaseComponentInstance();	

	virtual bool			IsLoaded();

	virtual result			QueryComponentObject(REFIID rIID, void** ppObject);

	virtual String			GetComponentName();
	virtual String			GetComponentVersion();

	// ICommon declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual	String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:
	StringA					libraryName_;
	void*					pLibrary_;
	
	PDLL_GET_CLASS_OBJECT_ROUTINE			pDllGetClassObject_;
	PDLL_CAN_UNLOAD_NOW_ROUTINE				pCanUnloadNow_;

	PGET_COMPONENT_NAME_ROUTINE				pGetComponentName_;
	PGET_COMPONENT_VERSION_ROUTINE			pGetComponentVersion_;

	ICommonFactory*			pComponentCommonFactory_;

	ulong					numRef_;
};

#endif // !COMPONENTLOADER_H__COMPONENTS__INCLUDED_
