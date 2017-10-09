#ifndef ITRAINERSLOADER_H__TRAINERSMANAGER__INCLUDED_
#define ITRAINERSLOADER_H__TRAINERSMANAGER__INCLUDED_

/**
* ITrainersLoader interface. Trainers loading support.
*
* @version 1.0.1
*/
interface ITrainersLoader : public MinCOM::ICommon
{

	/**
	* Simple support for loading process tuning.
	*
	* @param argName Specifies argument name.
	* @param value Specifies argument value.
	*/
	virtual result SetArgumentName(const StringA& argName, const StringA& value) = 0;

	/**
	* Initiates enumeration process.
	*
	* @return Instance of the first found trainer if succeeds, otherwise NULL.
	*/
	virtual ComponentsKit::IComponentLoader* LoadFirstTrainer() = 0;

	/**
	* Goes on enumeration process.
	*
	* @return Instance of the next found trainer if succeeds, otherwise NULL.
	*/
	virtual ComponentsKit::IComponentLoader* LoadNextTrainer() = 0;

};

#endif // !ITRAINERSLOADER_H__TRAINERSMANAGER__INCLUDED_
