#pragma once

#include "ElementsCore.h"
#include "CmnFunction.h"

#include "..\ExternalElements\ExternalsManager.h"

class CGroupsContainer : public IGroupsContainer
{
public:
	CGroupsContainer(void);
	~CGroupsContainer(void);

	void				SetFunctionsFactory(IFunctionsFactory* pFactory);

// IGroupsContainer declarations section
	virtual void			BuildElementsStructure();
	virtual void			ReleaseElementsStructure();	

	virtual void			SetBuilderControl(IBuilderControl* pDevice);
	virtual void			SetAppFolder(CString& AppFolder);
	virtual void			SetMediaDirectory(CString& MediaDir);

	virtual void			ProcessLoadMediaData();

	virtual IElement*		CreateElement(sElement* psElement);
	virtual void			ReleaseElement(IElement* pElement);

	ENUMERATOR(mGroupsList, IElementsContainer*, CreateEnumerator, GetNextContainer, posContainersEnum)

// IObject declarations section
public:
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void ** ppvObject);

private:
	CList<IElementsContainer*, IElementsContainer*>	mGroupsList;

	IBuilderControl*		pBuilderControl;
	CString					csAppFolder;
	CString					csMediaDirectory;

	IFunctionsFactory*		pFunctionsFactory;

	CExtrenalsManager		mExternalsManager;
};
