//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: SerializeConfig.h
//	Description: The CSerializeConfig declaration.  

#ifndef SERIALIZECONFIG_H__STORAGEPROCESSOR__INCLUDED_
#define SERIALIZECONFIG_H__STORAGEPROCESSOR__INCLUDED_

class CSerializeConfig
{
public:
	static result Serialize(
		const StringA& fileName,
		SpKit::ILayersContainerRef layersContainer,
		SpKit::IArgumentsContainerRef argumentsContainer,
		CLSID& trainerId,
		bool loading);

private:
	// Internal serialization helpers
	static result ParseProject(xmlNodePtr pProjectNode, 
		SpKit::ILayersContainerRef layersContainer);

	static result ParseArguments(xmlNodePtr pArgumentsNode, 
		SpKit::IArgumentsContainerRef argumentsContainer);

	static result ParseTrainer(xmlNodePtr pTrainerNode, 
		CLSID& trainerId);

	static result ParseArgument(const StringA& value, const StringA& type, MinCOM::CommonVariant& arg);

};


#endif // !SERIALIZECONFIG_H__STORAGEPROCESSOR__INCLUDED_
