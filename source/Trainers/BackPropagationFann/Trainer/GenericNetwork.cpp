#include "stdafx.h"

#include "GenericNetwork.h"

GenericNetwork::GenericNetwork()
	: piElementsCollection_(NULL)
	, piDataFile_(NULL)
	, piLogProvider_(NULL)
{
}

// Initialization interface
void GenericNetwork::SetElementsFactory(IElementsCollection* piCollection)
{
	piElementsCollection_ = piCollection;
}

void GenericNetwork::SetDataFile(IDataFile* piData)
{
	piDataFile_ = piData;
}

void GenericNetwork::SetLogProvider(ILogProvider* piLog)
{
	piLogProvider_ = piLog;
}

// Public interface
GenericNetwork::NetworkContainer& GenericNetwork::GetNetwork()
{
	return network_;
}

bool GenericNetwork::VerifyNetworkRelevance()
{
	if ( network_.size() == 0 )
		return true;

	NetworkContainer::const_iterator iter = network_.begin();
	NetworkContainer::const_iterator end = network_.end();

	for ( ; iter != end ; ++iter )
	{
		if ( !FindElement(*iter) )
		{
			PutLogMessage(CString("Network pattern cannot be used because the source one has been changed since it was constructed.")); 
			return false;
		}
	}

	return true;
}

bool GenericNetwork::VerifyDataCorrespondence()
{
	if ( !piDataFile_ )
	{
		PutLogMessage(CString("System: Wrong data file object.")); 
		return false;
	}
	
	if ( network_.size() == 0 )
		return false;

	IElement* piElement = *network_.begin();
	ILayerControl* piLayerControl = NULL;
	piElement->QueryInterface(IDD_ILayerControl, (void**)&piLayerControl);

	int inputsCount = piLayerControl->GetDimension();

	piElement = *(--network_.end());
	piElement->QueryInterface(IDD_ILayerControl, (void**)&piLayerControl);

	int outputsCount = piLayerControl->GetDimension();

	if ( inputsCount != piDataFile_->GetInputSymbolLength() )
	{
		PutLogMessage(CString("Network inputs' count does not equal to input dimension of training data set.")); 
		return false;
	}

	if ( outputsCount != piDataFile_->GetOutputSymbolLength() )
	{
		PutLogMessage(CString("Network outputs' count does not equal to output dimension of training data set."));
		return false;
	}

	return true;
}

bool GenericNetwork::VerifyNetworkIntegrity()
{
	if ( network_.size() < 2 )
	{
		PutLogMessage(CString("Network pattern cannot be empty or contain just one element.")); 
		return false;
	}

	return true;
}

bool GenericNetwork::CompliteVerification()
{
	return ( 
		VerifyNetworkIntegrity() &&
		VerifyNetworkRelevance() && 
		VerifyDataCorrespondence() 
	);
}

bool GenericNetwork::IsEmpty()
{
	return ( network_.size() == 0 );
}

class PresenceChecker
{
public:
	PresenceChecker(const GenericNetwork::NetworkContainer& container, bool mustPresent)
		: container_(container)
		, mustPresent_(mustPresent) 
	{
	}

	bool operator ()(IElement* piCurElement)
	{
		bool presents = std::find(container_.begin(), container_.end(), piCurElement) != container_.end();

		return ( presents && !mustPresent_ ) || ( !presents && mustPresent_ );
	}

private:

	const GenericNetwork::NetworkContainer container_;
	bool mustPresent_;

};

void GenericNetwork::UpdateNetwork(NetworkContainer& sourceNetwork)
{
	if ( !piElementsCollection_ )
	{
		PutLogMessage(CString("System: Wrong elements collection object.")); 
		return;
	}

	piElementsCollection_->CreateElementsEnumerator(USER_ENUMERATOR_RANGE_FROM);
	while ( IElement* piCurElement = piElementsCollection_->GetNextElement(USER_ENUMERATOR_RANGE_FROM) )
	{
		ILayerControl* piLayerControl = NULL;
		piCurElement->QueryInterface(IDD_ILayerControl, (void**)&piLayerControl);		

		if ( piLayerControl )
			sourceNetwork.push_back(piCurElement);
	}

	// Remove required elements
	GenericNetwork::NetworkContainer::iterator endIter = std::remove_if(
		network_.begin(), 
		network_.end(), 
		PresenceChecker(sourceNetwork, true)
	);
	network_.erase(endIter, network_.end());

	endIter = std::remove_if(
		sourceNetwork.begin(), 
		sourceNetwork.end(), 
		PresenceChecker(network_, false)
	);
	sourceNetwork.erase(endIter, sourceNetwork.end());
}

// Private interface
bool GenericNetwork::FindElement(IElement* piElement)
{
	if ( !piElementsCollection_ )
		return false;

	piElementsCollection_->CreateElementsEnumerator(USER_ENUMERATOR_RANGE_FROM);
	while ( IElement* piCurElement = piElementsCollection_->GetNextElement(USER_ENUMERATOR_RANGE_FROM) )
	{
		if ( piElement == piCurElement )
			return true;
	}

	return false;
}

void GenericNetwork::PutLogMessage(CString& message)
{
	if ( !piLogProvider_ )
		return;

	piLogProvider_->AddLogMessage(CString(_T("TE")), 
		message, 
		CString(_T("Verification")));	
}
