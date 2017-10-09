#ifndef ITEXTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
#define ITEXTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_

/**
* ITextLogProvider interface. Messaging support during training.
*
* @version 1.0.1
*/
interface ITextLogProvider : public ILogProvider
{
	
	/**
	* Adds new chart.
	*
	* @param type Message type.
	* @param message Message body.
	* @param section Initiator's section.
	*/
	virtual result AddMessage(const StringA& type, const StringA& message, const StringA& section) = 0;

};

#endif // !ITEXTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
