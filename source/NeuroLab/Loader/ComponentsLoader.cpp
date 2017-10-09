#include "StdAfx.h"
#include ".\ComponentsLoader.h"

#include "LoadStatDlg.h"
#include "CmnDecl.h"

CComponentsLoader::CComponentsLoader(void)
{
}

CComponentsLoader::~CComponentsLoader(void)
{
}

void CComponentsLoader::SetComponentsContainer(CComponentsContainer* Container)
{
	pContainer = Container;
}

void CComponentsLoader::ProcessLoadingComponents()
{
	mLoadStatDlg.SetComponentsLoader(this);
	mLoadStatDlg.DoModal();
}

void CComponentsLoader::LoadComponents()
{
	pContainer->CreateEnumerator();
	while (IComponent* pComponent = pContainer->GetNextComponent())
	{
		mLoadStatDlg.mStatMess.SetWindowText(pComponent->GetStateStringWhenLoading());
		pComponent->LoadComponent();
	}
}

void CComponentsLoader::UnloadComponents()
{
	pContainer->CreateEnumerator();
	while (IComponent* pComponent = pContainer->GetNextComponent())
		pComponent->UnloadComponent();
}
