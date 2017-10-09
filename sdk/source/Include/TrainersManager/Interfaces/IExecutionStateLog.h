#ifndef IEXECUTIONSTATELOG_H__TRAINERSMANAGER__INCLUDED_
#define IEXECUTIONSTATELOG_H__TRAINERSMANAGER__INCLUDED_

/**
* IExecutionStateLog interface. Performs percentage, timings and 
* other specific information retrieval during training.
*
* @version 1.0.1
*/
interface IExecutionStateLog : public MinCOM::ICommon
{

	/**
	* Returns trainer on the specified index.
	*
	* @param type Information type to be checked.
	* @param paramId Parameter identifier to be checked.
	* @return Returns true if information type is supported by the plugin.
	*/
	virtual bool IsInfoTypeSupported(InfoType type = PercentageInfo, REFCLSID paramId = CLSID_DefaultParam) = 0;

	/**
	* Returns current percentage.
	*
	* @return Percentage value.
	*/
	virtual float GetPercentage() const = 0;

	/**
	* Installs timing.
	*
	* @param timingName Timing system name.
	*/
	virtual result SetupTiming(const StringA& timingName) = 0;
	
	/**
	* Returns time elapsed since timing installation.
	*
	* @param timingName Timing system name.
	* @param milliseconds Time in milliseconds.
	*/
	virtual result GetTimeElapsed(const StringA& timingName, double& milliseconds) = 0;

	/**
	* Returns time elapsed since timing installation.
	*
	* @param timingName Timing system name.
	* @param seconds Time in seconds.
	*/
	virtual result GetTimeElapsed(const StringA& timingName, ulong& seconds) = 0;

	/**
	* Returns time period between two timings.
	*
	* @param timing1Name First timing system name.
	* @param timing2Name Second timing system name.
	* @param milliseconds Time in milliseconds.
	*/
	virtual result GetTimeBetweenYimings(const StringA& timing1Name, const StringA& timing2Name, double& milliseconds) = 0;

	/**
	* Returns time period between two timings.
	*
	* @param timing1Name First timing system name.
	* @param timing2Name Second timing system name.
	* @param seconds Time in seconds.
	*/
	virtual result GetTimeBetweenYimings(const StringA& timing1Name, const StringA& timing2Name, ulong& seconds) = 0;

	/**
	* Returns value of additional trainer-specific parameter.
	*
	* @param paramName Parameter name.
	* @param paramVal Parameter value.
	*/
	virtual result GetParameterValue(const StringA& paramName, MinCOM::CommonVariant& paramVal) const = 0;
};

#endif // !IEXECUTIONSTATELOG_H__TRAINERSMANAGER__INCLUDED_
