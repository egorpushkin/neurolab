//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: XMLSerializer.cpp
//	Description: The CXMLSerializer implementation.  

#include "XMLSerializer.h"

// Serialization tools and policies
#include "XMLSerializationTools/SerializeDocument.h"

using namespace StorageProcessorCommonKit;
using namespace NetworkImportingKit;

CXMLSerializer::CXMLSerializer()
	: numRef_(0)
	, flags_(0)
{
	flags_ = 
		FlagsProcessor::Prepare(FLAG_ET_INPUT_OFFSET, 0) |
		FlagsProcessor::Prepare(FLAG_ET_OUTPUT_OFFSET, 0) |
		FlagsProcessor::Prepare(FLAG_ET_PROCESSOR_OFFSET, FLAG_STORE_WEIGHTS | FLAG_STORE_DELTAS) |
		FlagsProcessor::Prepare(FLAG_ET_CONNECTION_OFFSET, FLAG_STORE_WEIGHTS);
}

CXMLSerializer::~CXMLSerializer()
{
}

// IExternalSerializer declarations section
result CXMLSerializer::SerializeNLProject(const StringA& fileName, INetworkProcessor* piNetProc, bool loading)
{
	if (!piNetProc)
		return E_INVALIDARG;

	return CSerializeDocument::Serialize(fileName, piNetProc, flags_, loading);
}

void CXMLSerializer::SetFlags(dword flags)
{
	flags_ = flags;
}

// ICommon implementations section
ulong CXMLSerializer::AddRef()
{
	return ++numRef_;						
}

ulong CXMLSerializer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CXMLSerializer::GetClassString() const
{
	return _T("CXMLSerializer");
}

result CXMLSerializer::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IExternalSerializer)
	{
		*ppObject = (IExternalSerializer*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
