#include "stdafx.h"

#include "AutomaticParser.h"

AutomaticParser::AutomaticParser(
	IElementsCollection* piElementsCollection,
	ILogProvider* piLogProvider,
	GenericNetwork* pNetwork)
	: piElementsCollection_(piElementsCollection)
	, piLogProvider_(piLogProvider)
	, pNetwork_(pNetwork)
{

}

// Public interface
bool AutomaticParser::DoConstructNetwork()
{
	if ( !piElementsCollection_ || !piLogProvider_ || !pNetwork_ )
		return false;

	if ( !pNetwork_->IsEmpty() )
		pNetwork_->GetNetwork().clear();

	IElement* piRootElement = FindRoot();
	if ( !piRootElement )
	{
		piLogProvider_->AddLogMessage(CString("N"), 
			CString("Cannot find network element to start building chain."), 
			CString("Constructor"));
		return false;
	}

	ContinueChain(piRootElement);

	return true;
}

// Private interface
IElement* AutomaticParser::FindRoot()
{
	piElementsCollection_->CreateElementsEnumerator(USER_ENUMERATOR_RANGE_FROM);
	while ( IElement* piCurElement = piElementsCollection_->GetNextElement(USER_ENUMERATOR_RANGE_FROM) )
	{
		if ( piCurElement->GetSysName() == _T("InputFactory") )
            return piCurElement;
	}

    return NULL;
}

void AutomaticParser::ContinueChain(IElement* piNode)
{	
	CString layerName;
	layerName.Format(_T("%s %d"), piNode->GetElementTitle(), piNode->GetElementID());
	
	piLogProvider_->AddLogMessage(CString("N"), 
		CString("Element '") + layerName + CString("' has been added to network pattern."), 
		CString("Constructor"));

	pNetwork_->GetNetwork().push_back(piNode);
	
	IDataConnector* piDataConnector = NULL;
	piNode->QueryInterface(IDD_IDataConnector, (void**)&piDataConnector);

	IConnectionsFactory* piConnections = piDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
	piConnections->CreateEnumerator(USER_ENUMERATOR_RANGE_FROM);
	while ( CConnection* pConnection = piConnections->GetNextConnection(USER_ENUMERATOR_RANGE_FROM) )
	{
		if ( pConnection->pElement->GetSysName() == _T("NeuronsLayer") )
		{
            ContinueChain(pConnection->pElement);
			break;
		}
	}
}
