//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: GroupsContainer.h
//	Description: The CGroupsContainer declaration.  

#include "GroupsContainer.h"

#include "../Elements/ElementHeaders.h"

#include "Tools/ElementsFactory.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;

CGroupsContainer::CGroupsContainer(void)
	: piElementContainersList_(NULL)
	, piFunctionsFactory_(NULL)
	, piBuilderControl_(NULL)
	, rootDirectory_(_T(""))
	, mediaSubDirectory_(_T(""))
	, numRef_(0)
{
	CContainer<IElementsContainer*>* pElementContainersContainer = 
		new CContainer<IElementsContainer*>;

	pElementContainersContainer->QueryInterface(IID_IContainer, (void**)&piElementContainersList_);

	BuildElementsStructure();
}

CGroupsContainer::~CGroupsContainer(void)
{
	ReleaseElementsStructure();

	piElementContainersList_->Release();

	if (piFunctionsFactory_)
		piFunctionsFactory_->Release();
	if (piBuilderControl_)
		piBuilderControl_->Release();
}

//////////////////////////////////////////////////////////////////////////
// Creation/Destruction tools
//////////////////////////////////////////////////////////////////////////
void CGroupsContainer::BuildElementsStructure()
{
	// Creates elements structure for future usage in external editor tools.
	// Warning. NOT IMPLEMENTED.
}

void CGroupsContainer::ReleaseElementsStructure()
{
	IElementContainersEnumerator* pElementConteinersEnum = piElementContainersList_->Clone();
	for(bool haSysElements = pElementConteinersEnum->SelectFirst();haSysElements;haSysElements = pElementConteinersEnum->SelectNext())
	{
		IElementsContainer* piElementsConteiner = pElementConteinersEnum->GetSelected();

		piElementsConteiner->Release();
	}
	pElementConteinersEnum->Release();	

	piElementContainersList_->Clear();

//	mExternalsManager.ReleaseManager();
}

//////////////////////////////////////////////////////////////////////////
// IGroupsContainer implementations section
//////////////////////////////////////////////////////////////////////////
void CGroupsContainer::SetMediaSubDirectory(const String& rMediaDir)
{
	mediaSubDirectory_ = rMediaDir;
}

void CGroupsContainer::SetRootDirectory(const String& rAppFolder)
{
	rootDirectory_ = rAppFolder;
}

void CGroupsContainer::SetBuilderControl(IBuilderControl* piBuilderControl)
{
	if (piBuilderControl_)
		piBuilderControl_->Release();

	piBuilderControl_ = piBuilderControl;
	
	if (piBuilderControl_)
		piBuilderControl_->AddRef();
}

void CGroupsContainer::SetFunctionsFactory(IFunctionsFactory* pFactory)
{
	if (piFunctionsFactory_)
		piFunctionsFactory_->Release();

	piFunctionsFactory_ = pFactory;

	if (piFunctionsFactory_)
		piFunctionsFactory_->AddRef();
}

result CGroupsContainer::ProcessLoadMediaData()
{
	if (!piBuilderControl_ || rootDirectory_ == _T("") || mediaSubDirectory_ == _T(""))
		return E_INVALIDARG;

	IOutputDevice* piOutputDevice = NULL;
	result resultCode = piBuilderControl_->QueryInterface(IID_IOutputDevice, (void**)&piOutputDevice);
	if (FAILED(resultCode) || !piOutputDevice)
		return COMP_E_INTERFACENOTSUPPORTED;

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Neuron_Passive.bmp")), String(_T("Neuron_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Neuron_Active.bmp")), String(_T("Neuron_Active")));
	
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Input_Passive.bmp")), String(_T("Input_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Input_Active.bmp")), String(_T("Input_Active")));

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Output_Passive.bmp")), String(_T("Output_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Output_Active.bmp")), String(_T("Output_Active")));

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Layer_Passive.bmp")), String(_T("Layer_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Layer_Active.bmp")), String(_T("Layer_Active")));	

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Input_Factory_Passive.bmp")), String(_T("Input_Factory_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Input_Factory_Active.bmp")), String(_T("Input_Factory_Active")));	

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Output_Factory_Passive.bmp")), String(_T("Output_Factory_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Output_Factory_Active.bmp")), String(_T("Output_Factory_Active")));	

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Neurons_Layer_Passive.bmp")), String(_T("Neurons_Layer_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Neurons_Layer_Active.bmp")), String(_T("Neurons_Layer_Active")));	

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("RBF_Layer_Passive.bmp")), String(_T("RBF_Layer_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("RBF_Layer_Active.bmp")), String(_T("RBF_Layer_Active")));	

	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Winner_Layer_Passive.bmp")), String(_T("Winner_Layer_Passive")));
	piOutputDevice->LoadImage(mediaSubDirectory_ + String(_T("/")) + String(_T("Winner_Layer_Active.bmp")), String(_T("Winner_Layer_Active")));

	piOutputDevice->Release();

	//////////////////////////////////////////////////////////////////////////
	//// Initializing special fields in mExternalsManager object and
	////  loading media data for all external maagers
	//mExternalsManager.SetBuilderControl(pBuilderControl);
	//mExternalsManager.SetMediaDirectory(csMediaDirectory);
	//
	//mExternalsManager.ProcessLoadMediaData();
	//////////////////////////////////////////////////////////////////////////

	return S_OK;
}

IElement* CGroupsContainer::CreateElement(SysElement* pElement)
{
	IElement* piElement = NULL;

	if (pElement->name_ == "Input")
	{
		piElement = CElementsFactory<CInput>::CreateElement();
	} else if (pElement->name_ == "InputFactory")
	{
		piElement = CElementsFactory<CInputFactory>::CreateElement();
	} else if (pElement->name_  == "ConstantInput")
	{
		piElement = CElementsFactory<CConstantInput>::CreateElement();
	} else if (pElement->name_ == "Output")
	{
		piElement = CElementsFactory<COutput>::CreateElement();
	} else if (pElement->name_ == "OutputFactory")
	{
		piElement = CElementsFactory<COutputFactory>::CreateElement();
	} else if (pElement->name_ == "Neuron")
	{
		piElement = CElementsFactory<CNeuron>::CreateElement();
	} else if (pElement->name_  == "HopfieldLayer")
	{
		piElement = CElementsFactory<CHopfieldLayer>::CreateElement();
	} else if (pElement->name_ == "NeuronsLayer")
	{
		piElement = CElementsFactory<CNeuronsLayer>::CreateElement();
	} else if (pElement->name_ == "RBFLayer")
	{
		piElement = CElementsFactory<CRBFLayer>::CreateElement();
	} else if (pElement->name_ == "WinnerLayer")
	{
		piElement = CElementsFactory<CWinnerLayer>::CreateElement();
	}

	//////////////////////////////////////////////////////////////////////////
	//if (!pElement)
	//{
	//	// Verifying whether required element supported by any external manager
	//	pElement = mExternalsManager.TryCreateElement(pSysElement->csName);
	//}
	//////////////////////////////////////////////////////////////////////////

	if (piElement)
	{
		// Initializing IBuilderElement internal members
		IBuilderElement* piBuilderElement = QueryTool<IElement, IBuilderElement>::
			QueryInterface(piElement, IID_IBuilderElement);
		
		piBuilderElement->SetOutputControl(piBuilderControl_);

		piBuilderElement->Release();

		// Initializing IDataFlow internal members
		IDataFlow* pDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		if (piFunctionsFactory_)
			pDataFlow->SetElementFunction(piFunctionsFactory_->GetHeadFunction());

		pDataFlow->Release();
	}

	return piElement;
}


IElementContainersEnumerator* CGroupsContainer::GetElementContainersEnumerator()
{
	return piElementContainersList_->Clone();
}

//////////////////////////////////////////////////////////////////////////
// ICommon implementations section
//////////////////////////////////////////////////////////////////////////
ulong CGroupsContainer::AddRef()
{
	return ++numRef_;						
}

ulong CGroupsContainer::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CGroupsContainer::GetClassString() const
{
	return _T("CGroupsContainer");
}

result CGroupsContainer::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = (ICommon*)this;
	}
	else if (rIID == IID_IGroupsContainer)
	{
		*ppObject = (IGroupsContainer*)this;
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)this)->AddRef();
	return S_OK;
}
