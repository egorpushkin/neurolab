#ifndef COREENTRIES_H__TRAINER__INCLUDED_
#define COREENTRIES_H__TRAINER__INCLUDED_

TRAINER_FUNC_DECLARE result			DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppObject);
TRAINER_FUNC_DECLARE result			CanUnloadNow();

TRAINER_FUNC_DECLARE void			GetComponentName(String& componentName);
TRAINER_FUNC_DECLARE void			GetComponentVersion(String& componentVersion);

#endif // !COREENTRIES_H__TRAINER__INCLUDED_
