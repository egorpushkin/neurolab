#include "StdAfx.h"
#include ".\componentscontainer.h"

#include "interface_idds.h"
#include "PluginsManagerComponent.h"
#include "BuilderElementsComponent.h"
#include "NetworkTrainersComponent.h"

CComponentsContainer::CComponentsContainer(void)
{
	pAppController = NULL;
}

CComponentsContainer::~CComponentsContainer(void)
{
	ReleaseComponetsTable();
}

void CComponentsContainer::FillComponentsTable()
{
	// Adding Plugins Manager Component
	CPluginsManagerComponent* pPMComponent = new CPluginsManagerComponent;
	IComponent* pComponent = NULL;
	pPMComponent->QueryInterface(IDD_IComponent, (void**)&pComponent);
	if (pComponent)
	{
		pComponent->SetAppController(pAppController);
		mComponents.AddTail(pComponent);
	}

	CBuilderElementsComponent* pBMComponent = new CBuilderElementsComponent;
	pComponent = NULL;
	pBMComponent->QueryInterface(IDD_IComponent, (void**)&pComponent);
	if (pComponent)
	{
		pComponent->SetAppController(pAppController);
		mComponents.AddTail(pComponent);
	}

	CNetworkTrainersComponent* pNTComponent = new CNetworkTrainersComponent;
	pComponent = NULL;
	pNTComponent->QueryInterface(IDD_IComponent, (void**)&pComponent);
	if (pComponent)
	{
		pComponent->SetAppController(pAppController);
		mComponents.AddTail(pComponent);
	}
}

void CComponentsContainer::ReleaseComponetsTable()
{
	for(;mComponents.GetCount() > 0;)
	{
		IComponent* pComponent = mComponents.GetHead();
		mComponents.RemoveHead();
		delete pComponent;       	
	}
}

IComponent*	CComponentsContainer::GetComponentByName(CString& csComponentName)
{
	for(POSITION pos = mComponents.GetHeadPosition();pos;)
	{
		IComponent* pComponent = mComponents.GetNext(pos);
		if (csComponentName == pComponent->GetComponentName())
			return pComponent;
	}

	return NULL;
}

void CComponentsContainer::SetAppController(IAppController* pController)
{
	pAppController = pController;
}