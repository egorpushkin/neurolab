#include "StdAfx.h"
#include ".\groupscontainer.h"

#include "interface_idds.h"

#include "ElementsContainer.h"
#include "ElementsHeaders.h"

CGroupsContainer::CGroupsContainer(void)
{
	pBuilderControl = NULL;
}

CGroupsContainer::~CGroupsContainer(void)
{
	ReleaseElementsStructure();
}

void CGroupsContainer::SetFunctionsFactory(IFunctionsFactory* pFactory)
{
	pFunctionsFactory = pFactory;
}

// IGroupsContainer implementations section
void CGroupsContainer::BuildElementsStructure()
{
	IElementsContainer* pContainer = NULL;

	// Data Flow Elements
	CElementsContainer* pElContainer = new CElementsContainer;
	pElContainer->QueryInterface(IDD_IElementsContainer, (void**)&pContainer);
	pElContainer->SetTitle(CString("Data Flow Elements"));

	// Input
	sElement* pElement = new sElement(CString("Input"), CString("Input"));
	pElContainer->AddElement(pElement);

	// Input Factory
	pElement = new sElement(CString("InputFactory"), CString("Input Factory"));
	pElContainer->AddElement(pElement);

	// Constant Input
	pElement = new sElement(CString("ConstantInput"), CString("Constant Input"));
	pElContainer->AddElement(pElement);

	// Output
	pElement = new sElement(CString("Output"), CString("Output"));
	pElContainer->AddElement(pElement);

	// Output Factory
	pElement = new sElement(CString("OutputFactory"), CString("Output Factory"));
	pElContainer->AddElement(pElement);

	mGroupsList.AddTail(pContainer);

	// Data Processors
	pElContainer = new CElementsContainer;
	pElContainer->QueryInterface(IDD_IElementsContainer, (void**)&pContainer);
	pElContainer->SetTitle(CString("Data Processors"));

	// Neuron
	pElement = new sElement(CString("Neuron"), CString("Neuron"));
	pElContainer->AddElement(pElement);

	mGroupsList.AddTail(pContainer);

	// Layers
	pElContainer = new CElementsContainer;
	pElContainer->QueryInterface(IDD_IElementsContainer, (void**)&pContainer);
	pElContainer->SetTitle(CString("Layers"));

	// Hopfield Layer
	pElement = new sElement(CString("HopfieldLayer"), CString("Hopfield Layer"));
	pElContainer->AddElement(pElement);

	// Neurons Layer
	pElement = new sElement(CString("NeuronsLayer"), CString("Neurons Layer"));
	pElContainer->AddElement(pElement);

	// RBF Layer
	pElement = new sElement(CString("RBFLayer"), CString("RBF Layer"));
	pElContainer->AddElement(pElement);

	// Winner Layer
	pElement = new sElement(CString("WinnerLayer"), CString("Winner Layer"));
	pElContainer->AddElement(pElement);

	mGroupsList.AddTail(pContainer);

	// Initializing external elements container and loading found libraries
	mExternalsManager.SetAppFolder(csAppFolder);
	mExternalsManager.InitializeManager();

	// Enumerating loaded managers and generating elements' list
	mExternalsManager.CreateEnumerator();
	while (CExternalManagerInstance* pInstance = mExternalsManager.GetNextContainer())
	{
		pElContainer = new CElementsContainer;
		pElContainer->QueryInterface(IDD_IElementsContainer, (void**)&pContainer);
		pElContainer->SetTitle(pInstance->GetContainer()->GetGroupName());

		pInstance->GetContainer()->CreateEnumerator();
		while (sElement* pElement = pInstance->GetContainer()->GetNextElement())
		{
			sElement* pNewElement = new sElement(pElement->csName, pElement->csTitle);
			pElContainer->AddElement(pNewElement);
		}
		   
		mGroupsList.AddTail(pContainer);     
	}
}

void CGroupsContainer::ReleaseElementsStructure()
{
	for (;mGroupsList.GetCount() > 0;)
	{
		IElementsContainer* pElContainer = mGroupsList.GetHead();
		mGroupsList.RemoveHead();
		
		pElContainer->ReleaseElements();
		delete pElContainer;
	}

	mExternalsManager.ReleaseManager();
}

void CGroupsContainer::SetBuilderControl(IBuilderControl* pControl)
{
	pBuilderControl = pControl;
}

void CGroupsContainer::SetAppFolder(CString& AppFolder)
{
	csAppFolder = AppFolder;
}

void CGroupsContainer::SetMediaDirectory(CString& MediaDir)
{
	csMediaDirectory = MediaDir;
}

void CGroupsContainer::ProcessLoadMediaData()
{
	ASSERT(pBuilderControl != NULL);
	ASSERT(csAppFolder != _T(""));
	ASSERT(csMediaDirectory != _T(""));

	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Neuron_Passive.bmp"), CString("Neuron_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Neuron_Active.bmp"), CString("Neuron_Active"));
	
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Input_Passive.bmp"), CString("Input_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Input_Active.bmp"), CString("Input_Active"));

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Output_Passive.bmp"), CString("Output_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Output_Active.bmp"), CString("Output_Active"));

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Layer_Passive.bmp"), CString("Layer_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Layer_Active.bmp"), CString("Layer_Active"));	

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Input_Factory_Passive.bmp"), CString("Input_Factory_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Input_Factory_Active.bmp"), CString("Input_Factory_Active"));	

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Output_Factory_Passive.bmp"), CString("Output_Factory_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Output_Factory_Active.bmp"), CString("Output_Factory_Active"));	

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Neurons_Layer_Passive.bmp"), CString("Neurons_Layer_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Neurons_Layer_Active.bmp"), CString("Neurons_Layer_Active"));	

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("RBF_Layer_Passive.bmp"), CString("RBF_Layer_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("RBF_Layer_Active.bmp"), CString("RBF_Layer_Active"));	

	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Winner_Layer_Passive.bmp"), CString("Winner_Layer_Passive"));
	pOutputDevice->LoadImage(csMediaDirectory + CString("\\") + CString("Winner_Layer_Active.bmp"), CString("Winner_Layer_Active"));	

	// Initializing special fields in mExternalsManager object and
	//  loading media data for all external maagers
	mExternalsManager.SetBuilderControl(pBuilderControl);
	mExternalsManager.SetMediaDirectory(csMediaDirectory);

	mExternalsManager.ProcessLoadMediaData();
}

IElement* CGroupsContainer::CreateElement(sElement* psElement)
{
	IElement* pElement = NULL;

	if (psElement->csName == _T("Input"))
	{
		CInput* pInput = new CInput;
		pInput->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("InputFactory"))
	{
		CInputFactory* pInputFactory = new CInputFactory;
		pInputFactory->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("ConstantInput"))
	{
		CConstantInput* pConstantInput = new CConstantInput;
		pConstantInput->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("Output"))
	{
		COutput* pOutput = new COutput;
		pOutput->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("OutputFactory"))
	{
		COutputFactory* pOutputFactory = new COutputFactory;
		pOutputFactory->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("Neuron"))
	{
		CNeuron* pNeuron = new CNeuron;
		pNeuron->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("HopfieldLayer"))
	{
		CHopfieldLayer* pHopfieldLayer = new CHopfieldLayer;
		pHopfieldLayer->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("NeuronsLayer"))
	{
		CNeuronsLayer* pNeuronsLayer = new CNeuronsLayer;
		pNeuronsLayer->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("RBFLayer"))
	{
		CRBFLayer* pRBFLayer = new CRBFLayer;
		pRBFLayer->QueryInterface(IDD_IElement, (void**)&pElement);
	}
	if (psElement->csName == _T("WinnerLayer"))
	{
		CWinnerLayer* pWinnerLayer = new CWinnerLayer;
		pWinnerLayer->QueryInterface(IDD_IElement, (void**)&pElement);
	}

	if (!pElement)
	{
		// Verifying whether required element supported by any external manager
		pElement = mExternalsManager.TryCreateElement(psElement->csName);
	}

	if (pElement)
	{
		pElement->SetSysName(psElement->csName);
		pElement->SetSysTitle(psElement->csTitle);

		IBuilderElement* pBuilderElement = NULL;
		pElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		pBuilderElement->SetOutputControl(pBuilderControl);

		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);
		pDataFlow->SetElementFunction(pFunctionsFactory->GetHeadFunction());
	}

	return pElement;
}

void CGroupsContainer::ReleaseElement(IElement* pElement)
{
	// Verifying whether required element belongs to external library
	if (mExternalsManager.TryReleaseElement(pElement))
        return;

	delete pElement;
}

// IObject implementations section
CString CGroupsContainer::GetClassString()
{
	return _T("CGroupsContainer");
}

void CGroupsContainer::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IGroupsContainer:
		*ppvObject = (IGroupsContainer*)this;
		break;
	}
}