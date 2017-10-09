#pragma once

#include "CmnNetworkImport.h"

// Internal NeuroFactory realization
#include "..\NeuroFactory\NeuroFactoryMng.h"
// Internal BuilderElementsComponent realization
#include "..\BuilderElements\BuilderElementsComponent.h"

class CImportManager
	: public IImportManager
{
public:
	CImportManager();
	~CImportManager();

	// IImportManager declarations section	
	virtual bool			InitializeManager();
	virtual void			RelaseManager();

	virtual bool			LoadNLProject(CString& FileName);

	// IObject declarations section	
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void ** ppvObject);

private:
	CNeuroFactoryMng		mNeuroFactoryMng;			
	CBuilderElementsComponent	mBuilderElementsComponent;

    bool					bIsInitialized;
};