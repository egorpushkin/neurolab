#ifndef TRAINERIMPLTYPES_H__DEFINITIONS__MODEL__TRAINERSMANAGER__INCLUDED_
#define TRAINERIMPLTYPES_H__DEFINITIONS__MODEL__TRAINERSMANAGER__INCLUDED_

/**
* (Identifier, Neural network) storage typedefs.
*
* @version 1.0.1
*/
typedef std::pair< 
	CLSID, 
	NiKit::INetworkProcessor*
> NetworkPair;

typedef Container::Container< 
	NetworkPair, 
	Container::MapStorage, 
	Container::Copy, 
	Container::MapRefs 
> NetworksContainer;

typedef Container::IContainer< 
	NetworkPair
> INetworksContainer;

typedef Container::IEnumerator< 
	NetworkPair
> INetworksEnum;

typedef Loki::SmartPtr<	
	INetworksEnum,	
	Loki::COMRefCounted 
> INetworksEnumPtr;

/**
* (Identifier, Data object) storage typedefs.
*
* @version 1.0.1
*/
typedef std::pair< 
	CLSID, 
	DpKit::IDataFile*
> DataObjectPair;

typedef Container::Container< 
	DataObjectPair, 
	Container::MapStorage, 
	Container::Copy, 
	Container::MapRefs 
> DataObjectsContainer;

typedef Container::IContainer< 
	DataObjectPair
> IDataObjectsContainer;

typedef Container::IEnumerator< 
	DataObjectPair
> IDataObjectsEnum;

typedef Loki::SmartPtr<	
	IDataObjectsEnum,	
	Loki::COMRefCounted 
> IDataObjectsEnumPtr;

#endif // !TRAINERIMPLTYPES_H__DEFINITIONS__MODEL__TRAINERSMANAGER__INCLUDED_
