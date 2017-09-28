#ifndef IPROPERTIES_H__TRAINERSMANAGER__INCLUDED_
#define IPROPERTIES_H__TRAINERSMANAGER__INCLUDED_

/**
* IProperties interface. Automatic trainer configuration support.
*
* @version 1.0.1
*/
interface IProperties : public MinCOM::ICommon
{

	/**
	* Adds new argument or updates value for existing one.
	*
	* @param name Argument name to be added or updated.
	* @param value Argument value to be set.
	*/
	virtual result SetArgument(const StringA& name, const MinCOM::CommonVariant& value) = 0;

	/**
	* Returns argument value using specified index.
	*
	* @param index Argument index.
	* @param value Contains returned value.
	*/
	virtual result GetArgument(uint index, MinCOM::CommonVariant& value) const = 0;

	/**
	* Returns argument value using specified name.
	*
	* @param index Argument index.
	* @param value Contains returned value.
	*/
	virtual result GetArgument(const StringA& name, MinCOM::CommonVariant& value) const = 0;

	/**
	* Returns object for enumerating properties.
	*/
	virtual IPropsEnum* GetPropertiesEnum() const = 0;

};

typedef MinCOM::ComPtr<	IProperties > IPropertiesPtr;

#endif // !IPROPERTIES_H__TRAINERSMANAGER__INCLUDED_
