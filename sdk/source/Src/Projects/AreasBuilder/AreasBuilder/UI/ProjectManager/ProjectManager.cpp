#include "stdafx.h"
#include "../../AreasBuilder.h"

#include "../Common/Providers.h"

#include "ProjectTree.h"
#include "ProjectManager.h"

#include "../Interfaces/ILogOutputManager.h"
#include "../Interfaces/IStatusUIProvider.h"

#include "../Dialogs/ProcessingStatusDlg.h"

#include "../../AreasBuilder/Threading.h"
#include "../../AreasBuilder/BuilderThread.h"

using namespace Workspace;
using namespace AreasBuilder;

namespace ProjectUI
{

ProjectManager::ProjectManager()
	: piAreasProject_(NULL)
	, pProjectTreeManager_(NULL)
	, piLogOutputManager_(NULL)
	, buildThreadHandle_(NULL)
	, piCurrentStatusProvider_(NULL)
	, terminateImmediately_(false)
{
	pProjectTreeManager_ = new ProjectTree;
}

ProjectManager::~ProjectManager()
{
	if (piAreasProject_)
		piAreasProject_->Release();

	if (piLogOutputManager_)
		piLogOutputManager_->Release();

	delete pProjectTreeManager_;
}

// Initialization interface
//////////////////////////////////////////////////////////////////////////
void ProjectManager::SetProjectTree(CTreeCtrl* pProjectTree)
{
	pProjectTreeManager_->SetProjectTree(pProjectTree);
}

void ProjectManager::SetLogOutputManager(ILogOutputManager* piLogOutputManager)
{
	if (piLogOutputManager_)
		piLogOutputManager_->Release();
	
	piLogOutputManager_ = piLogOutputManager;
	piLogOutputManager_->AddRef();
}

// Public interface. Common
//////////////////////////////////////////////////////////////////////////
result ProjectManager::DisplayLogMessage(const String& providerName, const String& message)
{
	return piLogOutputManager_->DisplayLogMessage(providerName, message);
}

result ProjectManager::ClearLog(const String& providerName)
{
	return piLogOutputManager_->ClearLog(providerName);
}

// Public interface. Builder engine
//////////////////////////////////////////////////////////////////////////
void ProjectManager::SetLastError(result errorCode)
{
	InterlockedExchange(&errorCode_, errorCode);	
}

result ProjectManager::GetLastError()
{	
	return InterlockedExchange(&errorCode_, errorCode_);
}

IStatusUIProvider* ProjectManager::GetStatusProvider()
{
	if (piCurrentStatusProvider_)
		piCurrentStatusProvider_->AddRef();

	return piCurrentStatusProvider_;
}

IAreasProject* ProjectManager::GetAreasProject()
{
	if (piAreasProject_)
		piAreasProject_->AddRef();

	return piAreasProject_;
}

// Public interface. Application UI
//////////////////////////////////////////////////////////////////////////
result ProjectManager::DislpayEmptyProject()
{
	if (piAreasProject_)
	{
		piAreasProject_->Release();
		piAreasProject_ = NULL;
	}	

	return pProjectTreeManager_->DislpayEmptyProject();
}

result ProjectManager::DislpayProject(IAreasProject* piAreasProject)
{
	assert(piAreasProject != NULL);

	if (piAreasProject_)
	{
		piAreasProject_->Release();
		piAreasProject_ = NULL;
	}

	piAreasProject_ = piAreasProject;
	piAreasProject_->AddRef();

	return pProjectTreeManager_->DislpayProject(piAreasProject);
}

result ProjectManager::BuildDisplayedProject()
{
	if (!piAreasProject_)
	{
		DisplayLogMessage(PROJECT_LOG, _T("Project has not been loaded yet."));	
        return S_FALSE;
	}

	if (piAreasProject_->IsBuilt())
	{
		DisplayLogMessage(PROJECT_LOG, _T("Project has been already built."));	
		return S_FALSE;
	}

	// Initializing internal state
	SetLastError(S_OK);
	SetTerminationFlag(false);

	// Step 1. Initialize dialog
	CProcessingStatusDlg* processingDialog = new CProcessingStatusDlg;
	piCurrentStatusProvider_ = QueryTool<CProcessingStatusDlg, IStatusUIProvider>::
		QueryInterface(processingDialog, IID_IStatusUIProvider);

	piCurrentStatusProvider_->SetAreasProject(piAreasProject_);
	piCurrentStatusProvider_->SetProjectManager(this);
	
	// Step 2. Configure and execute thread
	unsigned threadId = 0;
	buildThreadHandle_ = __beginthreadex(NULL, 0, BuilderThread, this, CREATE_SUSPENDED, &threadId);

	// Step 3. Display status dialog
	piCurrentStatusProvider_->ShowModalDialog();
	piCurrentStatusProvider_->Release();
	piCurrentStatusProvider_ = NULL;

	CloseHandle(buildThreadHandle_);
	buildThreadHandle_ = NULL;

	// Step 4. Display final message
	result errorCode = GetLastError();
	if (SUCCEEDED(errorCode))
		DisplayLogMessage(PROJECT_LOG, _T("Project was successfully built."));	
	else 
	{
		DisplayLogMessage(PROJECT_LOG, _T("Error occupied during building project."));			
		DisplayLogMessage(PROJECT_LOG, _T("Check 'Processing Events' log for details."));			
	}
		
	return S_OK;
}

// Public interface. Status dialog
//////////////////////////////////////////////////////////////////////////

void ProjectManager::ResumeBuilding()
{
	ResumeThread(buildThreadHandle_);
}

void ProjectManager::SetTerminationFlag(bool terminate)
{
	InterlockedExchange(&terminateImmediately_, terminate);
}

LONG ProjectManager::IsTerminationFlagSet()
{
	return InterlockedExchange(&terminateImmediately_, terminateImmediately_);
}

}
