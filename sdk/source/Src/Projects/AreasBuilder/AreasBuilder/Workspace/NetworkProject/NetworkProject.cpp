#include "stdafx.h"

#include "NetworkProject.h"

using namespace NetworkImportingKit;

namespace Workspace
{

NetworkProject::NetworkProject()
	: piNetProc_(NULL)
	, fileName_("")
	, projectName_("")
{
}

NetworkProject::~NetworkProject()
{
	CleanUp();
}

result NetworkProject::LoadProject(const StringA& fileName, const StringA& project)
{
	CleanUp();

	if (FAILED(netHelper_.Initialize()))
		return WS_E_IMPORTMNG;

    result resultCode = netHelper_.LoadNLProject(fileName, &piNetProc_);
	if (FAILED(resultCode))
	{
		CleanUp();
	}

	fileName_ = fileName;
	projectName_ = project;

	return S_OK;
}

INetworkProcessor* NetworkProject::GetProcessor()
{
	if (piNetProc_)
		piNetProc_->AddRef();

	return piNetProc_;
}

StringA NetworkProject::GetFileName()
{
	return fileName_;
}

StringA	NetworkProject::GetProjectName()
{
	return projectName_;
}

// Private tools
//////////////////////////////////////////////////////////////////////////
void NetworkProject::CleanUp()
{
	fileName_ = "";
	projectName_ = "";

	if (piNetProc_)
		piNetProc_->Release();

	netHelper_.Free();
}

}
