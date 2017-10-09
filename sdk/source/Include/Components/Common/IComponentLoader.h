//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ComponentLoader.h
//	Description: The IComponentLoader declaration file.   

#ifndef ICOMPONENTLOADER_H__COMPONENTS__INCLUDED_
#define ICOMPONENTLOADER_H__COMPONENTS__INCLUDED_

// IComponentLoader declaration
interface IComponentLoader : public ICommon
{
	virtual void			SetLibraryName(const StringA& rLibraryName) = 0;
	virtual StringA			GetLibraryName() = 0;

	virtual result			VerifyWhetherExists() = 0;	

	virtual result			InitializeComponentInstance(REFCLSID rCLSID) = 0;
	virtual result			ReleaseComponentInstance() = 0;	

	virtual bool			IsLoaded() = 0;

	virtual result			QueryComponentObject(REFIID rIID, void** ppObject) = 0;

	virtual String			GetComponentName() = 0;
	virtual String			GetComponentVersion() = 0;
};

#endif // !ICOMPONENTLOADER_H__COMPONENTS__INCLUDED_
