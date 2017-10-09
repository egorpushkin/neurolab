//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ConstructionFactory.h
//	Description: The CConstructionFactory declaration.  

#ifndef ELEMENTSNFACTORY_H__BUILDERELEMENTS__INCLUDED_
#define ELEMENTSNFACTORY_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

template
<
	class T
>
class NoPostInitialization
{
public:
	static void PostInitialize(T* /* elementObject */)
	{
		// No action is being performed
	}
};

template
<
	class T
>
class PostInitialization
{
public:
	static void PostInitialize(T* elementObject)
	{
		elementObject->PostInitialize();		
	}
};

template
<
	class T,
	template <class> class PostInitPolicy = PostInitialization
>
class CElementsFactory
	: public PostInitPolicy<T>
{
public:
	static NetworkImportingKit::IElement* CreateElement()
	{
		T* pElementObject = new T;

		NetworkImportingKit::IElement* piElement = QueryTool<T, NetworkImportingKit::IElement>::QueryInterface(pElementObject, NetworkImportingKit::IID_IElement);

		PostInitPolicy<T>::PostInitialize(pElementObject);

		return piElement;
	}
};

#endif // !ELEMENTSNFACTORY_H__BUILDERELEMENTS__INCLUDED_
