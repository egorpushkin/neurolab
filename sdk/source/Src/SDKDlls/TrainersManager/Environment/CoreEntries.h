#ifndef COREENTRIES_H__TRAINERSMANAGER__INCLUDED_
#define COREENTRIES_H__TRAINERSMANAGER__INCLUDED_

#include "../TrainersManager.h"

TRAINERSMNG_FUNC_DECLARE result			DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppObject);
TRAINERSMNG_FUNC_DECLARE result			CanUnloadNow();

TRAINERSMNG_FUNC_DECLARE void				GetComponentName(String& rComponentName);
TRAINERSMNG_FUNC_DECLARE void				GetComponentVersion(String& rComponentVersion);

#endif // !COREENTRIES_H__TRAINERSMANAGER__INCLUDED_
