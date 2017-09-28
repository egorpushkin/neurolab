#ifndef PROPERTIES_H__TRAINERSMANAGER__INCLUDED_
#define PROPERTIES_H__TRAINERSMANAGER__INCLUDED_

typedef std::pair< 
	StringA, 
	MinCOM::CommonVariant 
> PropertiesPair;

typedef Container::IEnumerator< 
	PropertiesPair
> IPropsEnum;

typedef Container::Container< 
	PropertiesPair, 
	Container::MapStorage, 
	Container::Copy, 
	Container::NoRefs 
> PropertiesContainer;

typedef Container::IContainer< 
	PropertiesPair
> IPropertiesContainer;

typedef Loki::SmartPtr<	
	IPropsEnum,	
	Loki::COMRefCounted 
> IPropsEnumPtr;

#endif // !PROPERTIES_H__TRAINERSMANAGER__INCLUDED_
