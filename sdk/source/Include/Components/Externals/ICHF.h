//	This code is a part of 'Components SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ICHF.h (Instance Creation Helper Functions)
//	Description: Declaration of external helpers.  

#ifndef ICHF_H__COMPONENTS__INCLUDED_
#define ICHF_H__COMPONENTS__INCLUDED_

/*
#ifdef COMPKIT_LIBRARY_INTERNAL
#define COMPKIT_FUNC_DECLARE EXPORT_SYMBOL_SIGNATURE
#else
#define COMPKIT_FUNC_DECLARE IMPORT_SYMBOL_SIGNATURE
#endif
*/

// CreateKitInstance declaration
/*COMPKIT_FUNC_DECLARE */result				CreateKitInstance(
	REFCLSID		clsid,
	ICommon*		piCommon,
	dword			clsContext,
	REFIID			iid,
	void**			ppObject);

#endif // !ICHF_H__COMPONENTS__INCLUDED_
