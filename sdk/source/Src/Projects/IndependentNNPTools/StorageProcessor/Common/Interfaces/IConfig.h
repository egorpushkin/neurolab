//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: IConfig.h
//	Description: The IConfig declaration.  

#ifndef ICONFIG_H__STORAGEPROCESSOR__INCLUDED_
#define ICONFIG_H__STORAGEPROCESSOR__INCLUDED_

// Network topology data structures
typedef struct tagLayerData
{
	StringA	layerName_;
	StringA transferFunction_;
	uint neurons_;
	bool hasBias_;
} LayerData;

typedef Loki::SmartPtr< LayerData > LayerDataPtr;

typedef Container::IEnumerator< 
	LayerDataPtr 
> ILayersEnum;

typedef Container::IContainer< 
	LayerDataPtr 
> ILayersContainer;

typedef Container::Container< 
	LayerDataPtr, 
	Container::VectorStorage, 
	Container::Copy, 
	Container::NoRefs 
> LayersContainer;

typedef MinCOM::ComPtr< ILayersEnum > ILayersEnumPtr;
typedef MinCOM::ComPtr< ILayersContainer > ILayersContainerPtr;
typedef const ILayersContainerPtr& ILayersContainerRef;

// Arguments enumerator
typedef std::pair< 
	StringA, 
	MinCOM::CommonVariant 
> ArgumentsPair;

typedef Container::IEnumerator< 
	ArgumentsPair
> IArgumentsEnum;

typedef Container::Container< 
	ArgumentsPair, 
	Container::MapStorage, 
	Container::Copy, 
	Container::NoRefs 
> ArgumentsContainer;

typedef Container::IContainer< 
	ArgumentsPair
> IArgumentsContainer;

typedef MinCOM::ComPtr< IArgumentsEnum > IArgumentsEnumPtr;
typedef MinCOM::ComPtr< IArgumentsContainer > IArgumentsContainerPtr;
typedef const IArgumentsContainerPtr& IArgumentsContainerRef;

// IConfig declaration
interface IConfig : public ICommon
{
	virtual result SerializeConfig(const StringA& fileName, bool loading) = 0;

	virtual ILayersEnumPtr GetLayersEnum() = 0;	
	virtual IArgumentsEnumPtr GetArgumentsEnum() = 0;	

	virtual REFCLSID GetTrainerClsid() = 0;
};

#endif // !ICONFIG_H__STORAGEPROCESSOR__INCLUDED_
