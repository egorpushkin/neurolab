#include "stdafx.h"
#include "ProjectTree.h"

// Handlers
#include "../Interfaces/IHandler.h"
#include "ProjectTreeHandlers/AreaHandler.h"
#include "ProjectTreeHandlers/BandHandler.h"

using namespace Workspace;
using namespace NetworkImportingKit;

namespace ProjectUI
{

ProjectTree::ProjectTree()
	: pProjectTree_(NULL)
	, rootTreeItem_(NULL)
{
}

ProjectTree::~ProjectTree()
{
	CleanUpHandlers();
}

// Initialization interface
//////////////////////////////////////////////////////////////////////////
void ProjectTree::SetProjectTree(CTreeCtrl* pProjectTree)
{
	pProjectTree_ = pProjectTree;
}

// Public interface
//////////////////////////////////////////////////////////////////////////
result ProjectTree::DislpayEmptyProject()
{
	ReleaseProject();

	rootTreeItem_ = pProjectTree_->InsertItem(_T("Empty solution"));

	return S_OK;
}

result ProjectTree::DislpayProject(IAreasProject* piAreasProject)
{
	ReleaseProject();

	USES_CONVERSION;

	// Step 1. Creating project root node
	StringA rootNodeName = piAreasProject->GetProjectName();
	rootTreeItem_ = pProjectTree_->InsertItem(
		TVIF_TEXT | TVIF_STATE | TVIF_IMAGE, 
		rootNodeName.c_str(), 0, 0, TVIS_BOLD, TVIS_BOLD, 
		NULL, NULL, NULL);

	// Step 2. Creating image node
	StringA imageNodeName = 
		StringA("Image '") + 
		piAreasProject->GetMultispecImage()->GetImageName() + 
		StringA("'");
	HTREEITEM imageNode = pProjectTree_->InsertItem(imageNodeName.c_str(), 2, 2, rootTreeItem_);

	// Step 2.1 Adding image bands
	IBandsEnumerator* piBandsEnum = piAreasProject->GetMultispecImage()->GetBandsEnumerator();
	for (bool hasBand = piBandsEnum->SelectFirst();hasBand;hasBand = piBandsEnum->SelectNext())
	{
		Band* pBand = piBandsEnum->GetSelected();

		StringA bandNodeName = 
			StringA("Band '") + 
			pBand->GetBandName() + 
			StringA("'");
		HTREEITEM bandItem = pProjectTree_->InsertItem(bandNodeName.c_str(), 1, 1, imageNode);

		BandHandler* pBandHandler = new BandHandler(piAreasProject, pBand);
		IHandler* piHandler = QueryTool<BandHandler, IHandler>::QueryInterface(pBandHandler, IID_IHandler);

		pProjectTree_->SetItemData(bandItem, (DWORD_PTR)piHandler);

		handlersList_.push_back(piHandler);
	}
	piBandsEnum->Release();

	// Step 2.2 Expand image node
	pProjectTree_->Expand(imageNode, TVE_EXPAND);

	// Step 3. Creating network node
	StringA networkNodeName = 
		StringA("Neural Network '") + 
		piAreasProject->GetNetworkProject()->GetProjectName() + 
		StringA("'");
	pProjectTree_->InsertItem(networkNodeName.c_str(), 15, 15, rootTreeItem_);	

	// Step 4. Creating map configuration node
	StringA configNodeName = StringA("Map Configuration");
	HTREEITEM configNode = pProjectTree_->InsertItem(configNodeName.c_str(), 20, 20, rootTreeItem_);	

	// Step 4.1 Creating parameters list	
	for (
		MapConfig::ParametersConstIterator iter = piAreasProject->GetMapConfig()->parametersBegin();
		iter != piAreasProject->GetMapConfig()->parametersEnd();
		iter++)
	{
		StringA parameterNodeName = 
			StringA("'") + 
			iter->first + 
			StringA("' = '") + 
			iter->second + 
			StringA("'");
		pProjectTree_->InsertItem(parameterNodeName.c_str(), 20, 20, configNode);
	}

	// Step 4.2 Expand config node
	pProjectTree_->Expand(configNode, TVE_EXPAND);

	// Step 5. Creating areas node
	StringA areasNodeName = StringA("Built Areas");
	HTREEITEM areasNode = pProjectTree_->InsertItem(areasNodeName.c_str(), 3, 3, rootTreeItem_);	

	// Step 5.1 Creating classes' nodes
	INetworkProcessor* piNetProc = piAreasProject->GetNetworkProject()->GetProcessor();
	IElementsCollection* piElements = QueryTool<INetworkProcessor, IElementsCollection>::
		QueryInterface(piNetProc, IID_IElementsCollection);

	uint classesCount = piElements->GetOutputsCount();

	piElements->Release();
	piNetProc->Release();

	for (uint i = 0;i < classesCount;i++)
	{
		char classMame[MAX_PATH];
		sprintf(classMame, "Area %d", i);

		HTREEITEM areaItem = pProjectTree_->InsertItem(classMame, 3, 3, areasNode);	

		AreaHandler* pAreaHandler = new AreaHandler(piAreasProject, i);
		IHandler* piHandler = QueryTool<AreaHandler, IHandler>::QueryInterface(pAreaHandler, IID_IHandler);

        pProjectTree_->SetItemData(areaItem, (DWORD_PTR)piHandler);

		handlersList_.push_back(piHandler);
	}

	// Step 5.2 Expand areas node
	pProjectTree_->Expand(areasNode, TVE_EXPAND);
    
	// Step 6. Expand root node
	pProjectTree_->Expand(rootTreeItem_, TVE_EXPAND);

	return S_OK;
}

// Private tools
//////////////////////////////////////////////////////////////////////////
void ProjectTree::ReleaseProject()
{
	assert(pProjectTree_ != NULL);

	if (rootTreeItem_)
	{
		pProjectTree_->DeleteItem(rootTreeItem_);
		rootTreeItem_ = NULL;
	}

	CleanUpHandlers();
}

void ProjectTree::CleanUpHandlers()
{
	for (HandlersIterator iter = handlersList_.begin();iter != handlersList_.end();iter++)
		(*iter)->Release();

	handlersList_.clear();
}




















}