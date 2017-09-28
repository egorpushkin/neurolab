#pragma once

#include "Templates\Enumerator.h"
#include "ExternalManagerInstance.h"

class CExtrenalsManager
{
public:
	CExtrenalsManager();

	void			InitializeManager();
	void			ReleaseManager();

	void			SetBuilderControl(IBuilderControl* pDevice);
	void			SetAppFolder(CString& AppFolder);
	void			SetMediaDirectory(CString& MediaDir);

	void			ProcessLoadMediaData();

	// Elements operations
	IElement*		TryCreateElement(CString& ElementSysName);
	bool			TryReleaseElement(IElement* pElement);

	ENUMERATOR(mContainers, CExternalManagerInstance*, CreateEnumerator, GetNextContainer, posContainersEnum)
private:
	void			AddExternalManager(CString& csFilePath, CString& csFileName);

	CList<CExternalManagerInstance*, CExternalManagerInstance*> mContainers;

	IBuilderControl*		pBuilderControl;
	CString					csAppFolder;
	CString					csMediaDirectory;
};