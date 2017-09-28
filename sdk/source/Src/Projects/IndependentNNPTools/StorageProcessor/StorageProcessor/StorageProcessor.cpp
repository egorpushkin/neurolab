//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StorageProcessor.cpp
//	Description: The CStorageProcessor implementation.  

#include "StorageProcessor.h"

// Including external serializers & config processors
#include "../ExternalSerializers/XMLSerializer.h"
#include "../ExternalConfigs/XMLConfig.h"

using namespace StorageProcessorCommonKit;

CStorageProcessor::CStorageProcessor()
	: numRef_(0)
{
}

CStorageProcessor::~CStorageProcessor()
{
}

// IStorageProcessor declarations section
result CStorageProcessor::QueryExternalSerializer(REFCLSID clsid, IExternalSerializer** ppiSerializer)
{
	if (clsid == CLSID_XMLSerializer)
	{
		*ppiSerializer = CConstructTool<CXMLSerializer, IExternalSerializer>::
			ConstructObject(IID_IExternalSerializer);
	}

	if (!*ppiSerializer)
	{
		return REGDB_E_CLASSNOTREG;
	}
	
	return S_OK;
}

result CStorageProcessor::QueryConfigProcessor(REFCLSID clsid, IConfig** ppiConfig)
{
	if (clsid == CLSID_XMLConfig)
	{
		*ppiConfig = CConstructTool<CXMLConfig, IConfig>::
			ConstructObject(IID_IConfig);
	}

	if (!*ppiConfig)
	{
		return REGDB_E_CLASSNOTREG;
	}

	return S_OK;
}

// ICommon implementations section
ulong CStorageProcessor::AddRef()
{
	return ++numRef_;						
}

ulong CStorageProcessor::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CStorageProcessor::GetClassString() const
{
	return _T("CStorageProcessor");
}

result CStorageProcessor::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IStorageProcessor)
	{
		*ppObject = (IStorageProcessor*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
