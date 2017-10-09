#include "StdAfx.h"
#include ".\pluginscontainer.h"

#include "interface_idds.h"

#include "..\System\Directory.h"

CPluginsContainer::CPluginsContainer(void)
{
	pAppController = NULL;
}

CPluginsContainer::~CPluginsContainer(void)
{
	ReleaseInstalledPlugins();
}

void CPluginsContainer::AddPlugin(CString& csPluginFilePath, CString& csPluginFileName)
{
	CPluginInstance* pPluginInstance = new CPluginInstance(csPluginFilePath);

	if (pPluginInstance->CreatePluginInstance())
	{
		pPluginInstance->pPluginControl->SetAppController(pAppController);
		mPluginsList.AddTail(pPluginInstance);
	}
	else 
	{
		delete pPluginInstance;
		mWrongFiles.AddTail(csPluginFileName);
	}
}

// IPluginsContainer implementations section
void CPluginsContainer::LoadInstalledPlugins(CString& csAppFolder)
{
	ReleaseInstalledPlugins();

	CDirectoryEnumerator mDirEnum(csAppFolder + CString("\\Plugins\\*.dll"));
	mDirEnum.EnumerateDirectoryEntries();

	for(POSITION pos = mDirEnum.mFilesList.GetHeadPosition();pos;)
	{
		CString csFileName = mDirEnum.mFilesList.GetNext(pos);		
		CString csPluginFileName = csAppFolder+CString("\\Plugins\\")+csFileName;

		AddPlugin(csPluginFileName, csFileName);
	}	
}

void CPluginsContainer::RefreshPluginsList(CString& csAppFolder)
{
	CDirectoryEnumerator mDirEnum(csAppFolder + CString("\\Plugins\\*.dll"));
	mDirEnum.EnumerateDirectoryEntries();

	mWrongFiles.RemoveAll();

	for(POSITION pos = mDirEnum.mFilesList.GetHeadPosition();pos;)
	{
		CString csFileName = mDirEnum.mFilesList.GetNext(pos);
		CString csPluginFileName = csAppFolder+CString("\\Plugins\\")+csFileName;

		bool bIsFound = false;
		for (POSITION posPl = mPluginsList.GetHeadPosition();posPl;)
		{
			CPluginInstance* pPluginInstance = mPluginsList.GetNext(posPl);
			if (pPluginInstance->csPluginFileName == csPluginFileName)
			{
				bIsFound = true;
				break;
			}
		}

		if (!bIsFound)		
			AddPlugin(csPluginFileName, csFileName);
	}
}

void CPluginsContainer::ReleaseInstalledPlugins()
{
	for (;mPluginsList.GetCount() > 0;)
	{	
		CPluginInstance* pPluginInstance = mPluginsList.GetHead();
		mPluginsList.RemoveHead();

		pPluginInstance->ReleasePluginInstance();
		delete pPluginInstance;	
	}

	mWrongFiles.RemoveAll();
}

void CPluginsContainer::GetWrongFilesList(CList<CString, CString>* pList)
{
	pList->AddTail(&mWrongFiles);
}

void CPluginsContainer::SetAppController(IAppController* pController)
{
	pAppController = pController;
}

// IObject implementations section
CString	CPluginsContainer::GetClassString()
{
	return CString("CPluginsContainer");
}

void CPluginsContainer::QueryInterface(int iIDD, void ** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IPluginsContainer:
		*ppvObject = (IPluginsContainer*)this;
		break;
	}
}