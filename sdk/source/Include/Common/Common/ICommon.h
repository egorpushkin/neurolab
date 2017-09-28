#ifndef ICOMMON_H__COMMON__INCLUDED_
#define ICOMMON_H__COMMON__INCLUDED_

/** 
 * \ingroup		CommonKit
 * \class ICommon "CommonKit.h" 
 * \brief Component model core interface.
 *
 * This interface must be used as base for all other interfaces.
*/

interface ICommon
{
	//! This function in used to enrich object model with run time class information receiving mechanizm.
	/**
	 *
	 * \return Returns class identification string. 
	 * Class name is often used as return value.
 	 */
	virtual	String			GetClassString() const = 0;
	
	/**
	 *
	 * \param[in] Iid 
	 * \param[out] ppObject 
	 * \return Returns S_OK or E_NOINTERFACE.
	 */
	virtual result			QueryInterface(REFIID iid, void** ppObject) = 0;

	virtual	ulong			AddRef() = 0;
	virtual	ulong			Release() = 0;

	virtual ~ICommon() {};
};

typedef ComPtr< ICommon > ICommonPtr;
typedef ComPtr< ICommon, false > ICommonWeak;

#endif // !ICOMMON_H__COMMON__INCLUDED_
