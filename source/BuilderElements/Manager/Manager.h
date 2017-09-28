#pragma once

#include "..\Containers\GroupsContainer.h"

#include "..\Functions\FunctionsFactory.h"

#include "CmnManager.h"

class CManager : public IManagerControl
{
public:
	CManager(void);
	~CManager(void);

// IManagerControl declarations section
public:
	virtual BOOL			InitializeManagerInstance();
	virtual BOOL			ReleaseManagerInstance();
	virtual void			SetAppFolder(CString& csFolder);

	virtual void			SetAppController(IAppController* pController);

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CString					csAppFolder;

	IAppController*			pAppController;

// Elements Container
	CGroupsContainer		mGroupsContainer;
// Functions Container
	CFunctionsFactory		mFunctionsFactory;
};
