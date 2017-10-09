#pragma once

#include "Templates\Enumerator.h"

#include "CmnApp.h"

#include "ComponentCore.h"

#include "..\PluginsMng\Environment\PluginsPanelCore.h"
#include "..\BuilderElements\Containers\ElementsCore.h"

class CComponentsContainer
{
public:
	CComponentsContainer(void);
	~CComponentsContainer(void);

	void				FillComponentsTable();
	void				ReleaseComponetsTable();

	IComponent*			GetComponentByName(CString& csComponentName); 

	void				SetAppController(IAppController* pController);
private:
	CList<IComponent*, IComponent*>		mComponents;

	ENUMERATOR(mComponents, IComponent*, CreateEnumerator, GetNextComponent, posEnumComponents)

	IAppController*		pAppController;
};