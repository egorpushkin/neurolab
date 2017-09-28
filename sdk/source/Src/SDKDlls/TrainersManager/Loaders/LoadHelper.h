#ifndef LOADHELPER_H__TRAINERSMANAGER__INCLUDED_
#define LOADHELPER_H__TRAINERSMANAGER__INCLUDED_

class LoadHelper
{
public:

	static result TryLoadLibrary(
		const StringA& libName,  
		ComponentsKit::IComponentLoader** ppiLoader)
	{
		*ppiLoader = NULL;

		ComponentsKit::IComponentLoader* piLoader = 
			CConstructTool<ComponentsKit::CComponentLoader, ComponentsKit::IComponentLoader>
				::ConstructObject(ComponentsKit::IID_IComponentLoader);
		assert(piLoader != NULL);

		piLoader->SetLibraryName(libName);
		
		if (FAILED(piLoader->InitializeComponentInstance(TrainersManagerKit::CLSID_Trainer)))
		{
			piLoader->Release();
			return TR_E_WRONGTRAINERLIB;
		}

		(*ppiLoader) = piLoader;
        
		return S_OK;
	}

};

#endif // !LOADHELPER_H__TRAINERSMANAGER__INCLUDED_
