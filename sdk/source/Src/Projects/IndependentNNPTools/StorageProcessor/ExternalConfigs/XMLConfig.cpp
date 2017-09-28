//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: XMLConfig.cpp
//	Description: The CXMLConfig implementation.  

#include "../StorageProcessor.h"

#include "XMLConfig.h"

#include "XMLSerializationTools/SerializeConfig.h"

CXMLConfig::CXMLConfig()
	: layersContainer_(new SpKit::LayersContainer, Container::IID_IContainer)
	, argumentsContainer_(new SpKit::ArgumentsContainer, Container::IID_IContainer)
	, trainerClsid_()
{
}

CXMLConfig::~CXMLConfig()
{
}

// IConfig implementations section
result CXMLConfig::SerializeConfig(const StringA& fileName, bool loading)
{
	return CSerializeConfig::Serialize(
		fileName, 
		layersContainer_, 
		argumentsContainer_, 
		trainerClsid_, 
		loading);		
}

SpKit::ILayersEnumPtr CXMLConfig::GetLayersEnum()
{
	return SpKit::ILayersEnumPtr(layersContainer_->Clone());
}

SpKit::IArgumentsEnumPtr CXMLConfig::GetArgumentsEnum()
{
	return SpKit::IArgumentsEnumPtr(argumentsContainer_->Clone());
}

REFCLSID CXMLConfig::GetTrainerClsid()
{
	return trainerClsid_;
}

// ICommon implementations section
result CXMLConfig::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == SpKit::IID_IConfig)
	{
		*ppObject = (SpKit::IConfig*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}

