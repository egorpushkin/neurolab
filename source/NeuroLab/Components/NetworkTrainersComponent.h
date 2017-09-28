#pragma once

#include "CmnManager.h"

typedef IManagerControl* (*PCREATE_NETWORK_TRAINERS_ROUTINE)(void);
typedef void (*PRELEASE_NETWORK_TRAINERS_ROUTINE)(IManagerControl * pManager);

#include "ComponentDefinitions.h"

class CNetworkTrainersComponent : public INetworkTrainersComponent
{
public:
	CNetworkTrainersComponent(void);
	~CNetworkTrainersComponent(void);

// INetworkTrainersComponent declarations section

// IComponent declarations section	
	virtual bool			LoadComponent();
	virtual bool			UnloadComponent();
	virtual bool			VerifyWhetherExists();

	virtual CString			GetComponentName();
	virtual CString			GetComponentVersion();

	virtual CString			GetStateStringWhenLoading();

	virtual void			SetAppController(IAppController* pController);

// IObject declarations section	
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void ** ppvObject);

private:

// Component state
	bool			bIsLoaded;

	CString			csLibraryName;

	IAppController*	pAppController;

// Component handlers and references
	HMODULE			hLibrary;

	PGET_COMPONENT_NAME_ROUTINE					pfnGetComponentName;
	PGET_COMPONENT_VERSION_ROUTINE				pfnGetComponentVersion;

	PCREATE_NETWORK_TRAINERS_ROUTINE			pfnCreateNetworkTrainers;
	PRELEASE_NETWORK_TRAINERS_ROUTINE			pfnReleaseNetworkTrainers;

	IManagerControl*							pManagerControl;
};
