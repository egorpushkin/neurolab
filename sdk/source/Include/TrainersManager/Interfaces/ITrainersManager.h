#ifndef ITRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_
#define ITRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_

/**
* ITrainersManager interface. Trainers management.
*
* @version 1.0.1
*/
interface ITrainersManager : public MinCOM::ICommon
{
	
	/**
	* Setups enumerator object for loading trainers.
	*
	* @param piLoader Enumerator object.
	*/
	virtual result SetLoader(ITrainersLoader* piLoader) = 0;

	/**
	* Performs trainers loading.
	*/
	virtual result LoadTrainers() = 0;

	/**
	* Returns trainer on the specified index.
	*
	* @param trainerIndex Trainer index.
	* @return Pointer to trainer control interface.
	*/
	virtual ITrainer* GetTrainer(uint trainerIndex) = 0;
	
	/**
	* Returns trainer on the specified system name.
	*
	* @param trainerName Trainer system name.
	* @return Pointer to trainer control interface.
	*/	
	virtual ITrainer* GetTrainer(const StringA& trainerName) = 0;
	
	/**
	* Returns trainer on the specified system name and version information.
	*
	* @param trainerName Trainer system name.
	* @param minVersion Minimal trainer version required.
	* @return Pointer to trainer control interface.
	*/		
	virtual ITrainer* GetTrainer(const StringA& trainerName, const PVERSION minVersion) = 0;

	/**
	* Returns trainer on the specified unique identifier.
	*
	* @param trainerId Trainer identifier.
	* @return Pointer to trainer control interface.
	*/	
	virtual ITrainer* GetTrainer(REFCLSID trainerId) = 0;

	/**
	* Returns trainer on the specified unique identifier and version information.
	*
	* @param trainerId Trainer identifier.
	* @param minVersion Minimal trainer version required.
	* @return Pointer to trainer control interface.
	*/	
	virtual ITrainer* GetTrainer(REFCLSID trainerId, const PVERSION minVersion) = 0;

	/**
	* Returns object for enumerating trainers.
	*/
	virtual ITrainersEnum* GetTrainersEnum() = 0;

};

#endif // !ITRAINERSMANAGER_H__TRAINERSMANAGER__INCLUDED_
