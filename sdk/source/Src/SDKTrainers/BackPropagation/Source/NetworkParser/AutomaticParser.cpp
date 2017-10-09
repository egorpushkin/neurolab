#include "TrainerMain.h"

#include "GenericNetwork.h"

#include "AutomaticParser.h"

namespace Trainer
{

	AutomaticParser::AutomaticParser(GenericNetworkRef network)
		: network_(network)
	{		        
	}

	// Public interface
	result AutomaticParser::DoConstructNetwork()
	{
		if ( !network_->GetElementsCollection() || !network_ )
			return false;

		if ( !network_->IsEmpty() )
			network_->Clear();

		NiKit::IElementPtr rootElement = FindRoot();
		if ( !rootElement )
		{
			AddTextMessage(network_->GetTrainer(), "E", "Cannot find network element to start building chain.", "BP Trainer");
			return E_FAIL;
		}

		ContinueChain(rootElement);

		return true;
	}

	// Private interface
	NiKit::IElementPtr AutomaticParser::FindRoot()
	{
		NiKit::IElementsEnumRef elementsEnum = network_->GetElementsCollection()->GetElementsEnumerator();
		for ( bool hasElement = elementsEnum->SelectFirst() ; hasElement ; hasElement = elementsEnum->SelectNext() )
		{
			NiKit::IElement* piCurElement = elementsEnum->GetSelected();

			if ( piCurElement->GetSysName() == "InputFactory" )
				return NiKit::IElementPtr(piCurElement, NiKit::IID_IElement);
		}

		return NULL;
	}

	void AutomaticParser::ContinueChain(NiKit::IElementRef node)
	{	
		char buffer[255];
		sprintf(buffer, "%s %d", node->GetSysTitle().c_str(), node->GetElementID());
		StringA layerName(buffer);
		
		AddTextMessage(network_->GetTrainer(), "N", StringA("'") + layerName + StringA("' has been added to network pattern."), StringA("BP Trainer"));

		network_->AddElement(node);
		
		NiKit::IDataConnectorPtr dataConnector(node, NiKit::IID_IDataConnector);

		NiKit::IConnectionsFactoryPtr connections(dataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY));
		
		NiKit::IConnectionsEnumPtr connEnum(connections->GetConnectionsEnumerator());
		for ( bool hasConn = connEnum->SelectFirst() ; hasConn ; hasConn = connEnum->SelectNext() )
		{
			NiKit::CConnection* pConnection = connEnum->GetSelected();

			if ( pConnection->piElement_->GetSysName() == StringA("NeuronsLayer") )
			{
				ContinueChain(NiKit::IElementPtr(pConnection->piElement_, NiKit::IID_IElement));
				break;
			}
		}
	}

}
