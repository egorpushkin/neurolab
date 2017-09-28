#include "StdAfx.h"
#include ".\neurofactory.h"

#ifdef SOURCE_NEUROFACTORY_INTERNAL
#include "..\NeuroLab.h"
#include "..\\Resource.h"
#endif

#include "interface_idds.h"

#include "FactoryVerification.h"

CNeuroFactory::CNeuroFactory(void)
{
}

CNeuroFactory::~CNeuroFactory(void)
{
	ReleaseElementsList();
}

// Common elements processing functions
#ifdef SOURCE_NEUROFACTORY_INTERNAL
void CNeuroFactory::AddElement(IElement* pElement)
{
	// generating element ID
	CList<int, int> mIDs;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* tmElement = mNetworkElements.GetNext(pos);	
		if (tmElement->GetElementTitle() == pElement->GetElementTitle())
			mIDs.AddTail(tmElement->GetElementID());
	}

	int iID = 1;
	while (mIDs.Find(iID))
		iID++;

	pElement->SetElementID(iID);

	mNetworkElements.AddTail(pElement);
}

void CNeuroFactory::ReleaseElementsList()
{
	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();

	IGroupsContainer* pGroupsContainer = NULL;

	IComponent* pComponent = pAppMain->mComponents.GetComponentByName(CString("BuilderElements"));
	if (pComponent)
		pComponent->QueryInterface(IDD_IGroupsContainer, (void**)&pGroupsContainer);	

	for(;mNetworkElements.GetCount() > 0;)
	{
		IElement* pElement = mNetworkElements.GetHead();
		mNetworkElements.RemoveHead();

    	RemoveConnections(pElement);
		if (pGroupsContainer)
			pGroupsContainer->ReleaseElement(pElement);
	}
}

void CNeuroFactory::RemoveConnections(IElement* pElement)
{
	IDataConnector* pDataConnector = NULL;
	pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

	IConnectionsFactory* pFactory = pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
	pFactory->RemoveConnections();

	pFactory = pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	pFactory->RemoveConnections();
}

CConnection* CNeuroFactory::FindConnectionByPrevPtr(CConnection* pConnection)
{
	for (POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{			
		IElement* tmElement = mNetworkElements.GetNext(pos);
		IDataConnector* pDataConnector = NULL;
		tmElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

		CConnection* pFoundConnection = pDataConnector->FindConnectionByPrevPtr(pConnection);
		if (pFoundConnection)
			return pFoundConnection;
	}

	return NULL;
}
#endif

// INetworkVerifier implementations section
void CNeuroFactory::VerifyNetwork(int& ErrorsCount, int& WarningsCount, 
		ILogProvider* pLogProvider)
{
	IElementsCollection* pElementsCollection = NULL;
    QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

	CFactoryVerification::VerifyFactory(
		ErrorsCount, 
		WarningsCount, 
		pElementsCollection, 
		pLogProvider);
}

// IElementsCollection implementations section
#ifdef SOURCE_NEUROFACTORY_INTERNAL
void CNeuroFactory::RemoveElement(IElement* pElement)
{
	RemoveConnections(pElement);

	POSITION pos = mNetworkElements.Find(pElement);
	mNetworkElements.RemoveAt(pos);

	CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();
	IGroupsContainer* pGroupsContainer = NULL;
	IComponent* pComponent = pAppMain->mComponents.GetComponentByName(CString("BuilderElements"));		
	if (pComponent)
		pComponent->QueryInterface(IDD_IGroupsContainer, (void**)&pGroupsContainer);	    

	if (pGroupsContainer)
		pGroupsContainer->ReleaseElement(pElement);
}

void CNeuroFactory::SelectElement(IElement* pElement, bool bShift, bool bCtrl)
{
	IBuilderElement* pBuilderElement = NULL;

	for (POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* tmElement = mNetworkElements.GetNext(pos);

		tmElement->QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);

		if (pElement == tmElement)
		{
			if (bShift)
				pBuilderElement->SelectElement(false);
			else if (bCtrl)
				pBuilderElement->SelectElement(true);			
			else
				pBuilderElement->SelectElement(true);		
		} else
		{
			if (!bShift && !bCtrl)
				pBuilderElement->SelectElement(false);	
		}
	}	
}
#endif

int CNeuroFactory::GetInputsCount()
{
	int iDataLength = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			if (!pDataFlow->RequireData())
				continue;

			iDataLength += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}

	return iDataLength;
}

int CNeuroFactory::GetOutputsCount()
{
	int iDataLength = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			iDataLength += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}

	return iDataLength;
}

// INetworkProcessor implementations section
void CNeuroFactory::ProcessNetwork()
{
	CList<IElement*, IElement*>	mInputs;
	CList<IElement*, IElement*>	mOutputs;
	CList<IElement*, IElement*>	mNets;

	// prepering data for processing
	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);

		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
			DC_INPUTS_FACTORY);

		if (pConnectionsFactory->GetConnectionsCount() == 0 && 
			pElement->GetElementType() != ET_INPUT)
			continue;

		if (pElement->GetElementType() == ET_INPUT)
			mInputs.AddTail(pElement);
		else
		{
			if (pElement->GetElementType() == ET_OUTPUT)
				mOutputs.AddTail(pElement);
			else 
				if (pElement->GetElementType() == ET_PROCESSOR)
					mNets.AddTail(pElement);
				else 
					continue;

			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);	

			pDataFlow->SetWaitDataState();
		}
	}

	// processing network
	for(POSITION pos = mInputs.GetHeadPosition();pos;)
	{
		IElement* pElement = mInputs.GetNext(pos);
		
		IDataFlow* pDataFlow = NULL;
		pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);		
	
		pDataFlow->FlowData();
	}	

	int iOutputElementsCount = -1;
	int iProcessorElementsCount = -1;

	while (mOutputs.GetCount() > 0)
	{
		// processing nets that already has all necessary input data		
		for(POSITION pos = mNets.GetHeadPosition();pos;)
		{
			POSITION posPrev = pos;
			IElement* pElement = mNets.GetNext(pos);		

			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);	

			if (pDataFlow->IsReadyForProcessing())
			{
				pDataFlow->ProcessElement();
				pDataFlow->FlowData();

				mNets.RemoveAt(posPrev);
			}
		}

		// processing outputs that already has all necessary input data
		for(POSITION pos = mOutputs.GetHeadPosition();pos;)
		{
			POSITION posPrev = pos;
			IElement* pElement = mOutputs.GetNext(pos);		

			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);	

			if (pDataFlow->IsReadyForProcessing())
			{
				pDataFlow->ProcessElement();

				mOutputs.RemoveAt(posPrev);
			}
		}

		if ((mNets.GetCount() == iProcessorElementsCount) &&
			(mOutputs.GetCount() == iOutputElementsCount))
			break;

		iProcessorElementsCount = mNets.GetCount();
		iOutputElementsCount = mOutputs.GetCount();
	}
}

void CNeuroFactory::SetInputData(IDataFactory* pDataFactory)
{
	int iDataOffset = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			if (!pDataFlow->RequireData())
				continue;

			if (iDataOffset + pDataFlow->GetDataFactory()->GetDataLength() >
				pDataFactory->GetDataLength())
				break;

			pDataFlow->GetDataFactory()->SetData(
				pDataFactory->GetData() + iDataOffset,
				pDataFlow->GetDataFactory()->GetDataLength());
		
			iDataOffset += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	
}

void CNeuroFactory::SetOutputData(IDataFactory* pDataFactory)
{
	int iDataOffset = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			if (!pDataFlow->RequireData())
				continue;

			if (iDataOffset + pDataFlow->GetDataFactory()->GetDataLength() >
				pDataFactory->GetDataLength())
				break;

			pDataFlow->GetDataFactory()->SetData(
				pDataFactory->GetData() + iDataOffset,
				pDataFlow->GetDataFactory()->GetDataLength());
		
			iDataOffset += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	
}

void CNeuroFactory::GetInputData(IDataFactory* pDataFactory)
{
	int iDataLength = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			iDataLength += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	

	float* pData = new float[iDataLength];

	int iDataOffset = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_INPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			memcpy(pData + iDataOffset,
				pDataFlow->GetDataFactory()->GetData(),
				pDataFlow->GetDataFactory()->GetDataLength()*sizeof(float));

			iDataOffset += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	

	pDataFactory->SetData(pData, iDataLength);
    delete []pData;
}

void CNeuroFactory::GetOutputData(IDataFactory* pDataFactory)
{
	int iDataLength = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			iDataLength += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	

	float* pData = new float[iDataLength];

	int iDataOffset = 0;

	for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
	{
		IElement* pElement = mNetworkElements.GetNext(pos);
		if (pElement->GetElementType() == ET_OUTPUT)
		{
			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			memcpy(pData + iDataOffset,
				pDataFlow->GetDataFactory()->GetData(),
				pDataFlow->GetDataFactory()->GetDataLength()*sizeof(float));

			iDataOffset += pDataFlow->GetDataFactory()->GetDataLength();
		}
	}	

	pDataFactory->SetData(pData, iDataLength);
    delete []pData;
}

// IStorageController declarations section
bool CNeuroFactory::Serialize(CArchive& ar)
{
	CString csFileInd("#NL_PROJECT_FILE");
	CString csFileVersion("1.0.0.0a");

	if (ar.IsLoading())
	{
		CString csReadFileInd;
		CString csReadFileVersion;

		ar.ReadString(csReadFileInd);
		ar.ReadString(csReadFileVersion);

		if (csReadFileInd != csFileInd || csReadFileVersion != csFileVersion)
			return false;

		ReleaseElementsList();

		sElement* pElement = new sElement(CString(), CString());

		CNeuroLabApp* pAppMain = (CNeuroLabApp*)AfxGetApp();
		IGroupsContainer* pGroupsContainer = NULL;
		IFunctionsFactory* pFunctionsFactory = NULL;
		IComponent* pComponent = pAppMain->mComponents.GetComponentByName(CString("BuilderElements"));		
		if (pComponent)
		{
			pComponent->QueryInterface(IDD_IGroupsContainer, (void**)&pGroupsContainer);	
			pComponent->QueryInterface(IDD_IFunctionsFactory, (void**)&pFunctionsFactory);
		}

		if (!pGroupsContainer || !pFunctionsFactory)
			return false;

		int iElementsCount;
        ar.Read(&iElementsCount, sizeof(int));
		for(int i = 0;i < iElementsCount;i++)
		{
			CString csSysName;
			CString csSysTitle;

			ar.ReadString(csSysName);
			ar.ReadString(csSysTitle);

			pElement->csName = csSysName;
			pElement->csTitle = csSysTitle;

			IElement* tmElement = pGroupsContainer->CreateElement(pElement);
			if (!tmElement)
			{
				ReleaseElementsList();
				return false;
			}

			IStorageController* pStorageController = NULL;
			tmElement->QueryInterface(IDD_IStorageController, (void**)&pStorageController);
			
			pStorageController->Serialize(ar);

			IDataFlow* pDataFlow = NULL;
			tmElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);

			pDataFlow->SetElementFunction(pFunctionsFactory->GetFunctionByName(
				pDataFlow->GetFunctionName()));

			mNetworkElements.AddTail(tmElement);
		}

		for (POSITION pos = mNetworkElements.GetHeadPosition();pos;)
		{			
			IElement* tmElement = mNetworkElements.GetNext(pos);
			IDataConnector* pDataConnector = NULL;
			tmElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

			IConnectionsFactory* pFactory = pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
			pFactory->CreateEnumerator();
			while (CConnection* tmConnection = pFactory->GetNextConnection())
			{	
				CConnection* pOpositeConnection = FindConnectionByPrevPtr(tmConnection->pPrevOpositePtr);

				if (!pOpositeConnection)
				{
					pFactory->RemoveConnection(tmConnection);				
					continue;
				}

				pOpositeConnection->pOpposite = tmConnection;
				pOpositeConnection->pElement = tmElement;

				tmConnection->pOpposite = pOpositeConnection;
			}

			pFactory = pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
			pFactory->CreateEnumerator();
			while (CConnection* tmConnection = pFactory->GetNextConnection())
			{	
				CConnection* pOpositeConnection = FindConnectionByPrevPtr(tmConnection->pPrevOpositePtr);

				if (!pOpositeConnection)
				{
					pFactory->RemoveConnection(tmConnection);				
					continue;
				}

				pOpositeConnection->pOpposite = tmConnection;
				pOpositeConnection->pElement = tmElement;

				tmConnection->pOpposite = pOpositeConnection;
			}
		}
	
	} else
	{
		ar.WriteString(csFileInd); ar.Write("\n",1);
		ar.WriteString(csFileVersion); ar.Write("\n",1);

		int iElementsCount = mNetworkElements.GetCount();
        ar.Write(&iElementsCount, sizeof(int));
		for(POSITION pos = mNetworkElements.GetHeadPosition();pos;)
		{
			IElement* pElement = mNetworkElements.GetNext(pos);
			
			IStorageController* pStorageController = NULL;
			pElement->QueryInterface(IDD_IStorageController, (void**)&pStorageController);

			pStorageController->Serialize(ar);		
		}	
	}

	return true;
}

// IObject declarations section
CString CNeuroFactory::GetClassString()
{
	return _T("CNeuroFactory");
}

void CNeuroFactory::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch(iIDD)
	{
	case IDD_IElementsCollection:
		*ppvObject = (IElementsCollection*)this;
		break;
	case IDD_INetworkProcessor:
		*ppvObject = (INetworkProcessor*)this;
		break;	
	case IDD_INetworkVerifier:
		*ppvObject = (INetworkVerifier*)this;
		break;
	case IDD_IStorageController:
		*ppvObject = (IStorageController*)this;
		break;
	}
}