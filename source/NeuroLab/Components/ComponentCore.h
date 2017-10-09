#pragma once

#include "CmnObjects.h"
#include "CmnApp.h"

typedef CString	(*PGET_COMPONENT_NAME_ROUTINE)(void);
typedef CString	(*PGET_COMPONENT_VERSION_ROUTINE)(void);

interface IComponent : public IObject
{
public:
	virtual bool			LoadComponent() = 0;
	virtual bool			UnloadComponent() = 0;
	virtual bool			VerifyWhetherExists() = 0;

	virtual CString			GetComponentName() = 0;
	virtual CString			GetComponentVersion() = 0;

	virtual CString			GetStateStringWhenLoading() = 0;

	virtual void			SetAppController(IAppController* pController) = 0;
};
