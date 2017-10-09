#include "../TrainersManager.h"

#include "TrainersManager.h"

#include "Enumerators.h"

using namespace ComponentsKit;
using namespace TrainersManagerKit;

TrainersManager::TrainersManager()
	: piLoader_(NULL)
	, piTrainers_(NULL)
	, piLibraries_(NULL)
{
	Container::Container<ITrainer*>* pTrainersContainer = new Container::Container<ITrainer*>;
	pTrainersContainer->QueryInterface(Container::IID_IContainer, (void**)&piTrainers_);
	
	Container::Container<IComponentLoader*>* pTrainerLibs = new Container::Container<IComponentLoader*>;
	pTrainerLibs->QueryInterface(Container::IID_IContainer, (void**)&piLibraries_);	
}

TrainersManager::~TrainersManager()
{
	if (piLoader_)
		piLoader_->Release();

	if (piTrainers_)
		piTrainers_->Release();

	if (piLibraries_)
		piLibraries_->Release();
}

// ITrainersManager implementations section	
result TrainersManager::SetLoader(ITrainersLoader* piLoader)
{
	if (piLoader_)
		piLoader_->Release();

	piLoader_ = piLoader;
	if (piLoader_)
		piLoader_->AddRef();

	return E_NOTIMPL;
}

result TrainersManager::LoadTrainers()
{
	if (!piLoader_)
		return TR_E_LOADERNOTSPECIFIED;

	ReleaseTrainersList();

	for (IComponentLoader* piTrainerLibrary = piLoader_->LoadFirstTrainer(); 
		piTrainerLibrary ; 
		piTrainerLibrary = piLoader_->LoadNextTrainer() )
	{
		ITrainer* piTrainer = NULL;
		piTrainerLibrary->QueryComponentObject(IID_ITrainer, (void**)&piTrainer);
		
		if (piTrainer)
		{
			piTrainers_->Add(piTrainer);
			piLibraries_->Add(piTrainerLibrary);

			piTrainer->Release();
		}

		piTrainerLibrary->Release();
	}

	return S_OK;	
}

ITrainer* TrainersManager::GetTrainer(uint trainerIndex)
{
	return 
		Container::for_each(
			GetImpl( ITrainersEnumPtr( piTrainers_->Clone() ) ), 
			TrainerLocators::LocateIndex(trainerIndex)
		).GetFoundTrainer();
}

ITrainer* TrainersManager::GetTrainer(const StringA& trainerName)
{
	return 
		Container::for_each(
			GetImpl( ITrainersEnumPtr( piTrainers_->Clone() ) ), 
			TrainerLocators::LocateName(trainerName)
		).GetFoundTrainer();
}

ITrainer* TrainersManager::GetTrainer(const StringA& trainerName, const PVERSION minVersion)
{
	return 
		Container::for_each(
			GetImpl( ITrainersEnumPtr( piTrainers_->Clone() ) ), 
			TrainerLocators::LocateName(trainerName, minVersion)
		).GetFoundTrainer();
}

ITrainer* TrainersManager::GetTrainer(REFCLSID trainerId)
{
	return 
		Container::for_each(
			GetImpl( ITrainersEnumPtr( piTrainers_->Clone() ) ), 
			TrainerLocators::LocateClsid(trainerId)
		).GetFoundTrainer();
}

ITrainer* TrainersManager::GetTrainer(REFCLSID trainerId, const PVERSION minVersion)
{
	return 
		Container::for_each(
			GetImpl( ITrainersEnumPtr( piTrainers_->Clone() ) ), 
			TrainerLocators::LocateClsid(trainerId, minVersion)
		).GetFoundTrainer();
}

ITrainersEnum* TrainersManager::GetTrainersEnum()
{
	return piTrainers_->Clone();
}

// ICommon implementations section	
result TrainersManager::QueryInterface(REFIID iid, void** ppObject)
{
	if (iid == MinCOM::IID_ICommon)
		*ppObject = MinCOM::CommonImpl< ITrainersManager >::GetCommon();

	else if (iid == IID_ITrainersManager)
		*ppObject = static_cast< ITrainersManager* >(this);

	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	MinCOM::CommonImpl< ITrainersManager >::GetCommon()->AddRef();
	return S_OK;	
}

// Private release interface
void TrainersManager::ReleaseTrainersList()
{
	piTrainers_->Clear();
	piLibraries_->Clear();	
}
