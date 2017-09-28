#include "TrainerMain.h"

#include "GenericNetwork.h"

namespace Trainer
{

	GenericNetwork::GenericNetwork(
		TrMngKit::ITrainerRef trainer,
		NiKit::IElementsCollectionRef elementsCollection,
		DpKit::IDataFileRef data)
		: trainer_(trainer)
		, elementsCollection_(elementsCollection)
		, dataFile_(data)
	{
	}

	// Public interface
	result GenericNetwork::VerifyNetworkRelevance()
	{
		if ( network_.size() == 0 )
			return true;

		NetworkContainer_::const_iterator iter = network_.begin();
		NetworkContainer_::const_iterator end = network_.end();

		for ( ; iter != end ; ++iter )
		{
			if ( !FindElement(*iter) )
			{
				AddTextMessage(trainer_, "E", "Network pattern cannot be used because the source one has been changed since it was constructed.", "BP Trainer");
				return E_FAIL;
			}
		}

		return S_OK;
	}

	result GenericNetwork::VerifyDataCorrespondence()
	{
		if ( !dataFile_ )
		{
			AddTextMessage(trainer_, "E", "Wrong data file object.", "BP Trainer");
			return E_FAIL;
		}
		
		if ( network_.size() == 0 )
		{
			AddTextMessage(trainer_, "W", "Empty network pattern object revealed.", "BP Trainer");
			return S_FALSE;
		}

		NiKit::IElementPtr element = *network_.begin();
		NiKit::ILayerControlPtr layerControl(element, NiKit::IID_ILayerControl);

		uint inputsCount = layerControl->GetDimension();

		element = *(--network_.end());
		layerControl = NiKit::ILayerControlPtr(element, NiKit::IID_ILayerControl);

		uint outputsCount = layerControl->GetDimension();

		if ( inputsCount != dataFile_->GetInputSymbolLength() )
		{
			AddTextMessage(trainer_, "E", "A number of network inputs does not equal to input dimension of training data set.", "BP Trainer");
			return E_FAIL;
		}

		if ( outputsCount != dataFile_->GetOutputSymbolLength() )
		{
			AddTextMessage(trainer_, "E", "A number of network outputs does not equal to output dimension of training data set.", "BP Trainer");
			return E_FAIL;
		}

		return S_OK;
	}

	result GenericNetwork::VerifyNetworkIntegrity()
	{
		if ( network_.size() < 2 )
		{
			AddTextMessage(trainer_, "E", "Network pattern cannot be empty or contain just one element.", "BP Trainer");
			return E_FAIL;
		}

		return S_OK;
	}

	result GenericNetwork::CompliteVerification()
	{
		return ( 
			SUCCEEDED(VerifyNetworkIntegrity()) &&
			SUCCEEDED(VerifyNetworkRelevance()) && 
			SUCCEEDED(VerifyDataCorrespondence()) 
		) ? ( S_OK ) : ( E_FAIL );
	}

	bool GenericNetwork::IsEmpty()
	{
		return ( network_.size() == 0 );
	}

	void GenericNetwork::AddElement(NiKit::IElementRef element)
	{
		network_.push_back(element);
	}

	void GenericNetwork::Clear()
	{
		network_.clear();
	}

	size_t GenericNetwork::Size()
	{
		return network_.size();
	}

	GenericNetwork::NetworkDescriptionPtr_ GenericNetwork::CreateNetworkDescription()
	{
		size_t length = network_.size();
		
		NetworkDescriptionPtr_ layers(new NetworkDescription_[length]); 	

		NetworkContainer_::const_iterator iter = network_.begin();
		NetworkContainer_::const_iterator end = network_.end();

		for ( int index = 0 ; iter != end ; ++iter, ++index )
		{
			NiKit::ILayerControlPtr layerControl(*iter, NiKit::IID_ILayerControl);			

			GetImpl(layers)[index] = layerControl->GetDimension();
		}	

		return layers;
	}

	// Data assigning interface
	TrMngKit::ITrainerPtr GenericNetwork::GetTrainer()
	{
		return trainer_;
	}

	NiKit::IElementsCollectionPtr GenericNetwork::GetElementsCollection()
	{
		return elementsCollection_;
	}

	DpKit::IDataFilePtr GenericNetwork::GetDataFile()
	{
		return dataFile_;
	}

	NiKit::IElementPtr GenericNetwork::GetAt(unsigned int index)
	{
		if ( index >= network_.size() )
			return NULL;

		return network_.at(index);
	}

	// Private interface
	bool GenericNetwork::FindElement(NiKit::IElementRef element)
	{
		if ( !elementsCollection_ )
			return false;

		NiKit::IElementsEnumRef elementsEnum = elementsCollection_->GetElementsEnumerator();
		for ( bool hasElement = elementsEnum->SelectFirst() ; hasElement ; hasElement = elementsEnum->SelectNext() )
		{
			NiKit::IElement* piElement = elementsEnum->GetSelected();

			if ( piElement == GetImpl(element) )
				return true;
		}

		return false;
	}

}
