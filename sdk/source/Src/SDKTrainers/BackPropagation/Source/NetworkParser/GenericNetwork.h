#ifndef GENERICNETWORK_H__BPFANN__INCLUDED_
#define GENERICNETWORK_H__BPFANN__INCLUDED_

namespace Trainer
{

	class GenericNetwork
	{
		
		typedef std::vector< NiKit::IElementPtr > NetworkContainer_;
		
	public:

		typedef unsigned int NetworkDescription_;
		typedef Loki::SmartPtr< 
			NetworkDescription_, 
			Loki::RefCounted,
			Loki::DisallowConversion,
			Loki::AssertCheck,
			Loki::ArrayStorage
		> NetworkDescriptionPtr_;

		GenericNetwork(
			TrMngKit::ITrainerRef trainer,
			NiKit::IElementsCollectionRef elementsCollection,
			DpKit::IDataFileRef data);
			
		// Public interface
		result VerifyNetworkRelevance();
		result VerifyDataCorrespondence();
		result VerifyNetworkIntegrity();
		result CompliteVerification();

		bool IsEmpty();

		void AddElement(NiKit::IElementRef element);
		void Clear();
		size_t Size();
		NiKit::IElementPtr GetAt(unsigned int index);

		NetworkDescriptionPtr_ CreateNetworkDescription();

		// Data acquiring interface
		TrMngKit::ITrainerPtr GetTrainer();
		NiKit::IElementsCollectionPtr GetElementsCollection();
		DpKit::IDataFilePtr GetDataFile();

	private:

		// Private interface
		bool FindElement(NiKit::IElementRef element);

	private:

		TrMngKit::ITrainerPtr trainer_;
		NiKit::IElementsCollectionPtr elementsCollection_;
		DpKit::IDataFilePtr dataFile_;

		NetworkContainer_ network_;

	};

	typedef Loki::SmartPtr<	GenericNetwork > GenericNetworkPtr;
	typedef const GenericNetworkPtr& GenericNetworkRef;

} // namespace Trainer

#endif // !GENERICNETWORK_H__BPFANN__INCLUDED_
