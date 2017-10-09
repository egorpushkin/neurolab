#ifndef TRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_
#define TRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_

class TrainersManager 
	: public MinCOM::CommonImpl< TrainersManagerKit::ITrainersManager >
{
public:
	TrainersManager();
	virtual ~TrainersManager();

	// ITrainersManager declarations section	
	virtual result						SetLoader(TrMngKit::ITrainersLoader* piLoader);
	virtual result						LoadTrainers();

	virtual TrMngKit::ITrainer*			GetTrainer(uint trainerIndex);
	virtual TrMngKit::ITrainer*			GetTrainer(const StringA& trainerName);
	virtual TrMngKit::ITrainer*			GetTrainer(const StringA& trainerName, const TrMngKit::PVERSION minVersion);
	virtual TrMngKit::ITrainer*			GetTrainer(REFCLSID trainerId);
	virtual TrMngKit::ITrainer*			GetTrainer(REFCLSID trainerId, const TrMngKit::PVERSION minVersion);

	virtual TrMngKit::ITrainersEnum*	GetTrainersEnum();

	// ICommon declarations section	
	virtual result						QueryInterface(REFIID iid, void** ppObject);

private:
	// Private release interface
	void								ReleaseTrainersList();

private:
	TrMngKit::ITrainersLoader*			piLoader_;

	Container::IContainer< TrMngKit::ITrainer* >*					piTrainers_;
	Container::IContainer< ComponentsKit::IComponentLoader* >*		piLibraries_;
};

#endif // !TRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_
