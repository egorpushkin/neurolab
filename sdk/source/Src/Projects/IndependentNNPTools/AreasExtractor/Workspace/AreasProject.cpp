#include "../PrecompiledHeader.h"

#include "AreasProject.h"

namespace Workspace
{

AreasProject::AreasProject()
	: numRef_(0)
	, projectName_("")
	, pMultispecImage_(NULL)
	, pNetworkProject_(NULL)
	, pMapConfig_(NULL)
	, pAreasHolder_(NULL)
	, wasBuilt_(false)
{
	pMultispecImage_ = new MultispectralImage;
	pNetworkProject_ = new NetworkProject;
	pMapConfig_ = new MapConfig;
	pAreasHolder_ = new AreasHolder;
}

AreasProject::~AreasProject()
{
	CleanUp();
}

// IAreasProject implementations section
////////////////////////////////////////////////////////////////////////// 
void AreasProject::SetProjectName(const StringA& projectName)
{
	projectName_ = projectName;
}

StringA AreasProject::GetProjectName()
{
	return projectName_;
}

MultispectralImage* AreasProject::GetMultispecImage()
{
	return pMultispecImage_;
}

NetworkProject* AreasProject::GetNetworkProject()
{
	return pNetworkProject_;
}

MapConfig* AreasProject::GetMapConfig()
{
	return pMapConfig_;
}

AreasHolder* AreasProject::GetAreasHolder()
{
	return pAreasHolder_;
}

bool AreasProject::IsBuilt()
{
	return wasBuilt_;
}

void AreasProject::SetBuilt()
{
	wasBuilt_ = true;
}

// ICommon implementations section
ulong AreasProject::AddRef()
{
	return ++numRef_;						
}

ulong AreasProject::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String AreasProject::GetClassString() const
{
	return _T("AreasProject");
}

result AreasProject::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = static_cast<ICommon*>(this);
	}
	if (rIID == IID_IAreasProject)
	{		
		*ppObject = static_cast<IAreasProject*>(this);
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	static_cast<ICommon*>(this)->AddRef();
	return S_OK;
}

// Private tools
////////////////////////////////////////////////////////////////////////// 
void AreasProject::CleanUp()
{
	delete pMultispecImage_;
	delete pNetworkProject_;
	delete pMapConfig_;
	delete pAreasHolder_;

	pMultispecImage_ = NULL;
	pNetworkProject_ = NULL;
	pMapConfig_ = NULL;
	pAreasHolder_ = NULL;
}

}
