//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: XMLConfig.h
//	Description: The CXMLConfig declaration.  

#ifndef XMLCONFIG_H__STORAGEPROCESSOR__INCLUDED_
#define XMLCONFIG_H__STORAGEPROCESSOR__INCLUDED_

// CXMLSerializer declaration
class CXMLConfig 
	: public MinCOM::CommonImpl< SpKit::IConfig >
{
public:
	CXMLConfig();
	virtual ~CXMLConfig();

	// IConfig declarations section
	virtual result SerializeConfig(const StringA& fileName, bool loading);

	virtual SpKit::ILayersEnumPtr GetLayersEnum();	
	virtual SpKit::IArgumentsEnumPtr GetArgumentsEnum();

	virtual REFCLSID GetTrainerClsid();

	// ICommon declarations section	
	virtual result QueryInterface(REFIID rIID, void** ppObject);

private:
	SpKit::ILayersContainerPtr layersContainer_;
	SpKit::IArgumentsContainerPtr argumentsContainer_;

	CLSID trainerClsid_;
};

#endif // !XMLCONFIG_H__STORAGEPROCESSOR__INCLUDED_
