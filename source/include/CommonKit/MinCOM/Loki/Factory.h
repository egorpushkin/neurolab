#ifndef FACTORY_H__MINCOM__LOKI__INCLUDED_
#define FACTORY_H__MINCOM__LOKI__INCLUDED_

// Loki::Factory extensions and enhancements
//////////////////////////////////////////////////////////////////////////

namespace Loki
{

	// Factory for ICommon based object creators driven by CLSID-based object identifiers	
	typedef Functor
	<
		MinCOM::ICommon, 
		NullType
	>
	CommonCreatorSpec;

	/*
		The following code can be used to define CommonFactorySpec:

		typedef Factory
		<
			MinCOM::ICommon, CLSID, CommonCreatorSpec
		>
		CommonFactorySpec;

		loki.lib must be linked in this case (problem with symbols redifinitions was not solved).
		The following syntax must be used during entries registration:
			Loki::CommonCreatorSpec(Loki::CreateObject< $Class_Name$ >)		
	*/
	
	typedef Factory
	<
		typename MinCOM::ICommon, CLSID
	>
	CommonFactorySpec;

	typedef Loki::SingletonHolder
	<
		CommonFactorySpec 
	> 
	CommonFactory;

	// Default internal creator routine
	template
	<
		class T
	>
	MinCOM::ICommon* ObjectCreator()
	{
		T* object = new T;
		MinCOM::ICommon* piCommon = NULL; 
		object->QueryInterface(MinCOM::IID_ICommon, (void**)&piCommon);

		/*
			// Standard behavior for function which returns COM interface
			piCommon->AddRef();
			// Releasing local reference
			piCommon->Release();

			The code was reduced during optimization.
		*/ 

		return piCommon;
	}

	// Default factory accessor routine
	inline CommonFactory::ObjectType& GetCommonFactory()
	{
		return CommonFactory::Instance();
	}

	// Default client creator routine
	inline MinCOM::ICommon* CreateObject(REFCLSID clsid)
	{
		return GetCommonFactory().CreateObject(clsid);
	}

}

#endif // !FACTORY_H__MINCOM__LOKI__INCLUDED_
