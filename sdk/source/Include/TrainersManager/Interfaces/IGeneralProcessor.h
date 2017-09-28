#ifndef IGENERALPROCESSOR_H__TRAINERSMANAGER__INCLUDED_
#define IGENERALPROCESSOR_H__TRAINERSMANAGER__INCLUDED_

/**
* IGeneralProcessor interface. Manipulates training algorithm execution.
*
* @version 1.0.1
*/
interface IGeneralProcessor : public MinCOM::ICommon
{

	/**
	* Starts training.
	*/
	virtual result Start() = 0;

	/**
	* Suspends training.
	*/
	virtual result Suspend() = 0;

	/**
	* Resumes training.
	*/
	virtual result Resume() = 0;

	/**
	* Stops training.
	*/
	virtual result Stop() = 0;

};

typedef MinCOM::ComPtr< IGeneralProcessor > IGeneralProcessorPtr;

#endif // !IGENERALPROCESSOR_H__TRAINERSMANAGER__INCLUDED_
