//	This code is a part of 'Network Import Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: NeuroFactory.cpp
//	Description: The CNeuroFactory implementation.  

#include "NeuroFactory.h"

using namespace NetworkImportingKit;
using namespace BuilderElementsCommonKit;
using namespace ExternalOutputEngine;

CNeuroFactory::CNeuroFactory(void)
	: piNetworkElements_(NULL)
	, piGroupsContainer_(NULL)
	, piFunctionsFactory_(NULL)
	, numRef_(0)
{
	CContainer<IElement*>* pElementsContainer = new CContainer<IElement*>;

	pElementsContainer->QueryInterface(IID_IContainer, (void**)&piNetworkElements_);
}

CNeuroFactory::~CNeuroFactory(void)
{
	ReleaseElementsList();

	assert(piNetworkElements_ != NULL);
	piNetworkElements_->Release();

	if (piGroupsContainer_)
		piGroupsContainer_->Release();
	if (piFunctionsFactory_)
		piFunctionsFactory_->Release();
}

//////////////////////////////////////////////////////////////////////////
// Internal tools
//////////////////////////////////////////////////////////////////////////
void CNeuroFactory::ReleaseElementsList()
{
	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();
		piElement->Release();
	}
	piEnumerator->Release();      

	piNetworkElements_->Clear();
}

CConnection* CNeuroFactory::FindConnectionByPrevPtr(dword_ptr connection)
{
	CConnection* pFoundConnection = NULL;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
			QueryInterface(piElement, IID_IDataConnector);

		pFoundConnection = piDataConnector->FindConnectionByPrevPtr(connection);

		piDataConnector->Release();

		if (pFoundConnection)
			break;
	}
	piEnumerator->Release();  

	return pFoundConnection;
}

void CNeuroFactory::EstablishConnectionsAfterSerialization()
{
	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{		
		IElement* piElement = piEnumerator->GetSelected();

		IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
			QueryInterface(piElement, IID_IDataConnector);

		IConnectionsFactory* piFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

		IConnectionsEnumerator* piConnEnumerator = piFactory->GetConnectionsEnumerator();
		for(bool hasElements = piConnEnumerator->SelectFirst();hasElements;hasElements = piConnEnumerator->SelectNext())
		{					
			CConnection* pConnection = piConnEnumerator->GetSelected();
			CConnection* pOpositeConnection = FindConnectionByPrevPtr(pConnection->prevOpositePtr_);

			if (!pOpositeConnection)
			{
				piFactory->RemoveConnection(pConnection);	
				continue;
			}

			pOpositeConnection->pOpposite_ = pConnection;
			pOpositeConnection->piElement_ = piElement;

			pConnection->pOpposite_ = pOpositeConnection;
		}
		piConnEnumerator->Release();

		piFactory->Release();

		piFactory = piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);

		piConnEnumerator = piFactory->GetConnectionsEnumerator();
		for(bool hasElements = piConnEnumerator->SelectFirst();hasElements;hasElements = piConnEnumerator->SelectNext())
		{	
			CConnection* pConnection = piConnEnumerator->GetSelected();
			CConnection* pOpositeConnection = FindConnectionByPrevPtr(pConnection->prevOpositePtr_);

			if (!pOpositeConnection)
			{
				piFactory->RemoveConnection(pConnection);				
				continue;
			}

			pOpositeConnection->pOpposite_ = pConnection;
			pOpositeConnection->piElement_ = piElement;

			pConnection->pOpposite_ = pOpositeConnection;
		}
		piConnEnumerator->Release();

		piFactory->Release();

		piDataConnector->Release();
	}
	piEnumerator->Release();
}

void CNeuroFactory::RemoveConnections(IElement* piElement)
{
	if (!piElement)
		return;

	IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
		QueryInterface(piElement, IID_IDataConnector);

	IConnectionsFactory* piFactory = piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
	piFactory->RemoveConnections();
	piFactory->Release();

	piFactory = piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	piFactory->RemoveConnections();
	piFactory->Release();

	piDataConnector->Release();
}

//////////////////////////////////////////////////////////////////////////
// IFactoryControl implementations section
//////////////////////////////////////////////////////////////////////////
void CNeuroFactory::SetBuilderElementsControls(
	IGroupsContainer* piGroupsContainer,
	IFunctionsFactory* piFunctionsFactory)
{
	if (piGroupsContainer_)
		piGroupsContainer_->Release();

	piGroupsContainer_ = piGroupsContainer;

	if (piGroupsContainer_)
		piGroupsContainer_->AddRef();

	if (piFunctionsFactory_)
		piFunctionsFactory_->Release();

	piFunctionsFactory_ = piFunctionsFactory;

	if (piFunctionsFactory_)
		piFunctionsFactory_->AddRef();
}

//////////////////////////////////////////////////////////////////////////
// IStructureBuilder implementations section
//////////////////////////////////////////////////////////////////////////
IElement* CNeuroFactory::AddElement(const StringA& sysName, bool registerElement)
{
	SysElement sysElement(sysName, "", "");

	// Creating element using hosted Builder Elements component
	IElement* piElement = piGroupsContainer_->CreateElement(&sysElement);

	IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
		QueryInterface(piElement, IID_IDataFlow);

	piDataFlow->SetElementFunction(piFunctionsFactory_->GetHeadFunction());

	piDataFlow->Release();

	// Registring element in internal container
	if (registerElement)
		piNetworkElements_->Add(piElement);

	// Generating unique identificator for newly created element
	uint uniqueId = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		if ((piElement->GetSysName() == sysName) && 
			(piElement->GetElementID() > uniqueId))
			uniqueId = piElement->GetElementID();
	}
	piEnumerator->Release();

    piElement->SetElementID(uniqueId + 1);

	piElement->AddRef();

	return piElement;
}

result CNeuroFactory::ConnectElements(IElement* piElementSrc, IElement* piElementDest, uint connectionSize)
{
	IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
		QueryInterface(piElementSrc, IID_IDataConnector);

	piDataConnector->SetAddConnectionState(DC_OUTPUTS_FACTORY, connectionSize);
	result resultCode = piDataConnector->ProcessAddConnection(piElementDest);

	piDataConnector->Release();

	return resultCode;
}

CConnection* CNeuroFactory::CreateConnection(uint connectionSize)
{
	CConnection* pConnection = new CConnection;
	pConnection->SizeConnection(connectionSize);

	return pConnection;
}

result CNeuroFactory::ApplyTransferFunction(IElement* piElement, const StringA& functionName)
{
	TransferFunction* pFunction = piFunctionsFactory_->GetFunctionByName(functionName);
	if (!pFunction)
		return NI_E_FUNCTIONNOTFOUND;

	IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
		QueryInterface(piElement, IID_IDataFlow);

	piDataFlow->SetElementFunction(pFunction);

	piDataFlow->Release();

	return S_OK;
}

result CNeuroFactory::LocateElement(IElement* piElement, uint positionX, uint positionY)
{
	IBuilderElement* piBuilderElement = 
		QueryTool<IElement, IBuilderElement>::
			QueryInterface(piElement, IID_IBuilderElement);

	BuilderPoint point;
	point.x = (long)positionX;
	point.y = (long)positionY;

	piBuilderElement->SetElementPosition(point);

	piBuilderElement->Release();

	return S_OK;
}

result CNeuroFactory::RemoveElement(IElement* /* piElement */)
{
	return E_NOTIMPL;
}

result CNeuroFactory::DisconnectElements(IElement* /* piElementSrc */, IElement* /* piElementDest */, bool /* removeAllConnections */)
{
	return E_NOTIMPL;
}

result CNeuroFactory::ReleaseContent()
{
	ReleaseElementsList();

	return S_OK;
}

void CNeuroFactory::EstablishConnections()
{
	EstablishConnectionsAfterSerialization();
}

//////////////////////////////////////////////////////////////////////////
// IElementsCollection implementations section
//////////////////////////////////////////////////////////////////////////
result CNeuroFactory::SelectElement(IElement* /* pElement */, bool /* shift */, bool /* ctrl */)
{
	// This method has not been implemented.
	return E_NOTIMPL;
}

uint CNeuroFactory::GetInputsCount()
{
	int dataLength = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		if (piElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			IDataFactory* piElementData = piDataFlow->GetDataFactory();

			if ( piDataFlow->RequireData() )
				dataLength += piElementData->GetDataLength();

			piElementData->Release();

			piDataFlow->Release();
		}
	}
	piEnumerator->Release();  

	return dataLength;
}

uint CNeuroFactory::GetOutputsCount()
{
	int dataLength = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();
		
		if (piElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			IDataFactory* piElementData = piDataFlow->GetDataFactory();

			if ( piDataFlow->RequireData() )
				dataLength += piElementData->GetDataLength();

			piElementData->Release();

			piDataFlow->Release();
		}
	}
	piEnumerator->Release();  

	return dataLength;
}

IElementsEnumerator* CNeuroFactory::GetElementsEnumerator()
{
	return piNetworkElements_->Clone();
}

//////////////////////////////////////////////////////////////////////////
// INetworkProcessor implementations section
//////////////////////////////////////////////////////////////////////////
result CNeuroFactory::ProcessNetwork()
{
	list<IElement*> inputsList;
	list<IElement*> outputsList;
	list<IElement*> processorsList;

	list<IElement*>::const_iterator listIter;

	// Receiving enumerator for network elements
	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();

	// Step 1. Parsing network structure. Preparing arrays with elements of each type
	//  (ET_INPUT, ET_OUTPUT, ET_PROCESSOR).
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataConnector* piDataConnector = QueryTool<IElement, IDataConnector>::
			QueryInterface(piElement, IID_IDataConnector);

		IConnectionsFactory* piConnectionsFactory = 
			piDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);

		uint inputConnectionsCount = piConnectionsFactory->GetConnectionsCount();
		uint elementType = piElement->GetElementType();

		piConnectionsFactory->Release();
		piDataConnector->Release();

		if (inputConnectionsCount == 0 && elementType != ET_INPUT)
			continue;

		switch (elementType)
		{
		case ET_INPUT:
			inputsList.push_back(piElement);
			break;
		case ET_OUTPUT:
			outputsList.push_back(piElement);
			break;
		case ET_PROCESSOR:
			processorsList.push_back(piElement);
			break;
		default:
			continue;
		}

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		piDataFlow->SetWaitDataState();

		piDataFlow->Release();
	}

	// Step 2. Flow data through input elements
	for (listIter = inputsList.begin(); listIter != inputsList.end(); listIter++)
	{
		IElement* piElement = *listIter;

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		piDataFlow->FlowData();		

		piDataFlow->Release();
	}
	
	// Step 3. Processing network
	int outputElementsCount = -1;
	int processorElementsCount = -1;

	while (outputsList.size() > 0)
	{
		// Step 3.1. Processing nets which already have all necessary input data		
		for (listIter = processorsList.begin(); listIter != processorsList.end(); listIter++)
		{
			IElement* piElement = *listIter;		

			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			if (piDataFlow->IsReadyForProcessing())
			{
				piDataFlow->ProcessElement();
				piDataFlow->FlowData();

				--listIter;
				processorsList.remove(piElement);
			}

			piDataFlow->Release();
		}	

		// Step 3.2. Processing outputs which already have all necessary input data
		for (listIter = outputsList.begin(); listIter != outputsList.end(); listIter++)
		{
			IElement* piElement = *listIter;		

			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			if (piDataFlow->IsReadyForProcessing())
			{
				piDataFlow->ProcessElement();

				--listIter;
				outputsList.remove(piElement);
			}

			piDataFlow->Release();
		}	

		// Step 3.3. Terminating processing in case of wrong algorithm behaviour
		if (((int)processorsList.size() == processorElementsCount) && 
			((int)outputsList.size() == outputElementsCount))
			break;

		processorElementsCount = (int)processorsList.size();
		outputElementsCount = (int)outputsList.size();
	}
		
	// Releasing network elements' enumerator
	piEnumerator->Release();  

	return S_OK;
}

void CNeuroFactory::SetInputData(const IDataFactory* piDataFactory)
{
	int dataOffset = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		if (piElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			if (!piDataFlow->RequireData())
			{
				piDataFlow->Release();
				continue;
			}

			IDataFactory* piElementData = piDataFlow->GetDataFactory();
			uint dataLength = piElementData->GetDataLength();
			
			if (dataOffset + dataLength > piDataFactory->GetDataLength())			
			{
				piElementData->Release();
				piDataFlow->Release();
				break;
			}
			
			piElementData->SetData(
				piDataFactory->GetData() + dataOffset,
				piElementData->GetDataLength());
		
			dataOffset += piElementData->GetDataLength();

			piElementData->Release();

			piDataFlow->Release();
		}
	}
	piEnumerator->Release();
}

void CNeuroFactory::SetOutputData(const IDataFactory* piDataFactory)
{
	int dataOffset = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		if (piElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);

			if (!piDataFlow->RequireData())
			{
				piDataFlow->Release();
				continue;
			}

			IDataFactory* piElementData = piDataFlow->GetDataFactory();
			uint dataLength = piElementData->GetDataLength();

			if (dataOffset + dataLength > piDataFactory->GetDataLength())
			{
				piElementData->Release();
				piDataFlow->Release();
				break;
			}

			piElementData->SetData(
				piDataFactory->GetData() + dataOffset,
				piElementData->GetDataLength());

			dataOffset += piElementData->GetDataLength();

			piElementData->Release();
			piDataFlow->Release();
		}
	}
	piEnumerator->Release();
}

void CNeuroFactory::GetInputData(IDataFactory* piDataFactory)
{
	uint dataLength = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		if (piElement->GetElementType() == ET_INPUT && piDataFlow->RequireData())
		{
			IDataFactory* piElementData = piDataFlow->GetDataFactory();
			dataLength += piElementData->GetDataLength();
			piElementData->Release();
		}

		piDataFlow->Release();
	}	

	if (piDataFactory->GetDataLength() != dataLength)
		piDataFactory->CreateFactory(dataLength);	

	uint dataOffset = 0;

	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		if (piElement->GetElementType() == ET_INPUT && piDataFlow->RequireData())
		{
			IDataFactory* piElementData = piDataFlow->GetDataFactory();
					
			memcpy(piDataFactory->GetData() + dataOffset,
				piElementData->GetData(),
				piElementData->GetDataLength() * sizeof(float));

			dataOffset += piElementData->GetDataLength();			

			piElementData->Release();
		}

		piDataFlow->Release();
	}	

	piEnumerator->Release();
}

void CNeuroFactory::GetOutputData(IDataFactory* piDataFactory)
{
	uint dataLength = 0;

	IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		if (piElement->GetElementType() == ET_OUTPUT && piDataFlow->RequireData())
		{
			IDataFactory* piElementData = piDataFlow->GetDataFactory();
			dataLength += piElementData->GetDataLength();
			piElementData->Release();
		}

		piDataFlow->Release();
	}	

	if (piDataFactory->GetDataLength() != dataLength)
		piDataFactory->CreateFactory(dataLength);	

	uint dataOffset = 0;

	for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
	{
		IElement* piElement = piEnumerator->GetSelected();

		IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
			QueryInterface(piElement, IID_IDataFlow);

		if (piElement->GetElementType() == ET_OUTPUT && piDataFlow->RequireData())
		{
			IDataFactory* piElementData = piDataFlow->GetDataFactory();

			memcpy(piDataFactory->GetData() + dataOffset,
				piElementData->GetData(),
				piElementData->GetDataLength() * sizeof(float));

			dataOffset += piElementData->GetDataLength();			

			piElementData->Release();		
		}

		piDataFlow->Release();
	}	

	piEnumerator->Release();
}

// IStorageController implementations section
result CNeuroFactory::Serialize(FILEDev& fileDev, bool loading)
{
	StringA fileInd("#NL_PROJECT_FILE");
	StringA fileVersion("1.0.0.0a");

	if (loading)
	{
		StringA readFileInd;
		StringA readFileVersion;

		fileDev.ReadStringA(readFileInd);
		fileDev.ReadStringA(readFileVersion);

		if (fileInd != readFileInd || 
			fileVersion != readFileVersion)
			return STG_E_INVALIDHEADER;

		ReleaseElementsList();

		SysElement sysElement(StringA(""), StringA(""), StringA(""));

		if (!piGroupsContainer_ || !piFunctionsFactory_)
			return E_INVALIDARG;

		uint elementsCount;
        fileDev.Read(&elementsCount, sizeof(uint));
		for(uint i = 0;i < elementsCount;i++)
		{
			StringA sysName;
			StringA sysTitle;

			fileDev.ReadStringA(sysName);
			fileDev.ReadStringA(sysTitle);

			sysElement.name_ = sysName;
			sysElement.title_ = sysTitle;

			IElement* piElement = piGroupsContainer_->CreateElement(&sysElement);
			if (!piElement)
			{
				ReleaseElementsList();

				return STG_E_INVALIDFORMAT;
			}

			IStorageController* piStorageController = QueryTool<IElement, IStorageController>::
				QueryInterface(piElement, IID_IStorageController);	

			piStorageController->Serialize(fileDev, loading);

            piStorageController->Release();

			IDataFlow* piDataFlow = QueryTool<IElement, IDataFlow>::
				QueryInterface(piElement, IID_IDataFlow);


			TransferFunction* pTransferFunction = 
				piFunctionsFactory_->GetFunctionByName(piDataFlow->GetFunctionName());
			piDataFlow->SetElementFunction(pTransferFunction);
			
			piDataFlow->Release();

			piNetworkElements_->Add(piElement);
		}

		EstablishConnectionsAfterSerialization();
	
	} else
	{
		fileDev.WriteStringA(fileInd);
		fileDev.WriteStringA(fileVersion); 

		uint elementsCount = piNetworkElements_->Size();
		fileDev.Write(&elementsCount, sizeof(uint));

		IElementsEnumerator* piEnumerator = piNetworkElements_->Clone();
		for(bool hasElements = piEnumerator->SelectFirst();hasElements;hasElements = piEnumerator->SelectNext())
		{		
			IElement* piElement = piEnumerator->GetSelected();

			IStorageController* piStorageController = 
				QueryTool<IElement, IStorageController>::
					QueryInterface(piElement, IID_IStorageController);

			piStorageController->Serialize(fileDev, loading);		

			piStorageController->Release();
		}
		piEnumerator->Release();
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// ICommon implementations section
//////////////////////////////////////////////////////////////////////////
ulong CNeuroFactory::AddRef()
{
	return ++numRef_;						
}

ulong CNeuroFactory::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String CNeuroFactory::GetClassString() const
{
	return _T("CNeuroFactory");	
}

result CNeuroFactory::QueryInterface(REFIID refIID, void** ppvObject)
{
	if (refIID == IID_ICommon)
	{
		*ppvObject = (ICommon*)(IElementsCollection*)this;
	}
	else if (refIID == IID_IStorageController)
	{
		*ppvObject = (IStorageController*)this;
	}
	else if (refIID == IID_IElementsCollection)
	{
		*ppvObject = (IElementsCollection*)this;
	}
	else if (refIID == IID_INetworkProcessor)
	{
		*ppvObject = (INetworkProcessor*)this;
	}
	else if (refIID == IID_IFactoryControl)
	{
		*ppvObject = (IFactoryControl*)this;
	} else if (refIID == IID_IStructureBuilder)
	{
		*ppvObject = (IStructureBuilder*)this;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((ICommon*)(IElementsCollection*)this)->AddRef();
	return S_OK;
}
