#pragma once

#include "..\Components\ComponentsContainer.h"
#include "LoadStatDlg.h"

//DWORD fnLoadComponents(DWORD dwParam);

class CComponentsLoader
{
public:
	CComponentsLoader(void);
	~CComponentsLoader(void);

	void SetComponentsContainer(CComponentsContainer* Container);

	void ProcessLoadingComponents();
	void LoadComponents();

	void UnloadComponents();

	//HANDLE							hEvent;				
	CLoadStatDlg					mLoadStatDlg;

private:
	CComponentsContainer*			pContainer;			
};
