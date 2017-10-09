#pragma once

#include "CmnExternalElement.h"

class CPackageManager : public IExternalElementsContainer
{
public:
	CPackageManager();
	~CPackageManager();

// IExternalElementsContainer declarations section
	// CPackageManager tools
	virtual void			SetBuilderControl(IBuilderControl* pDevice);
	virtual void			SetAppFolder(CString& AppFolder);
	virtual void			SetMediaDirectory(CString& MediaDir);    

	// CPackageManager init
	virtual void			ProcessLoadMediaData();

	// Elements oparations
	virtual IElement*		TryCreateElement(CString& ElementSysName);
	virtual bool			TryReleaseElement(IElement* pElement);
    
	// Elements info
    virtual CString			GetGroupName();
	ENUMERATOR(mElements, sElement*, CreateEnumerator, GetNextElement, posElementsEnum)

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	void					CreateElementsStructure();

	IBuilderControl*		pBuilderControl;
	CString					csAppFolder;
	CString					csMediaDirectory;

	CList<sElement*, sElement*> mElements;

	CList<IElement*, IElement*> mSessionAllocations;
};