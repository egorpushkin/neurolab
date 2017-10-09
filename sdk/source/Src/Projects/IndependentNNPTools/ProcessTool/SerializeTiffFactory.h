//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeDataFactory.h
//	Description: The CSerializeDataFactory declaration.  

#ifndef SERIALIZETIFFFACTORY_H__PROCESSTOOL__INCLUDED_
#define SERIALIZETIFFFACTORY_H__PROCESSTOOL__INCLUDED_

class SerializeTiffFactory
{

public:

	static result Serialize(const StringA& fileName, IDataFactory* piDataFactory, bool loading);

private:

	// Internal serialization helpers
	static result Store(const StringA& fileName, IDataFactory* piDataFactory);
	static result Load(const StringA& fileName, IDataFactory* piDataFactory);

};

#endif // !SERIALIZETIFFFACTORY_H__PROCESSTOOL__INCLUDED_
