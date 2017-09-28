#ifndef IDATABUS_H__SCRIPTINGKIT__INCLUDED_
#define IDATABUS_H__SCRIPTINGKIT__INCLUDED_

/**
 * @file IDataBus.h
 * @short The IDataBus control interface definition. 
 * @author Egor Pushkin <egor.pushkin@scientific-soft.com>
 */

namespace ScriptingKit
{

	/**
	 * @short The IDataBus control interface.  
	 *
	 * This control interface is being used to perform data access and exchange 
	 * abilities for client-script and script-script interactions.
	 *
	 * @version 1.0.1
	 */
	interface IDataBus : public MinCOM::ICommon
	{

		/**
		 * Attaches named data entry to data bus.
		 * 
		 * @param name Specifies name to be associated with data entry.
		 * @param data Data common control interface.
		 * @return Returns S_OK if successful, or an error value otherwise. 
 		 */
		virtual result AcquireData(const StringA& name, const ICommonPtr& data) = 0;

		/**
		 * Detaches named data entry from data bus.
 		 * 
  		 * @param name Specifies name to be detached.
		 * @return Returns S_OK if successful, or an error value otherwise. 
		 */
		virtual result ReleaseData(const StringA& name) = 0;
		
		/**
		 * Verifies whether data data entry with specified name has been already attached.
		 * 
		 * @param name Specifies data entry name.
		 * @return Returns true if found, or false otherwise. 
		 */
		virtual bool IsAcquired(const StringA& name) = 0;

		/**
		 * Refreshes data bus objects. 
		 * 
		 * @return Returns S_OK if successful, or an error value otherwise. 
		 */
		virtual result Refresh() = 0;

		/**
		 * Returns data block associated with specified name.
		 * 
		 * @param name Specifies data entry name.
		 * @return Returns true if , or false otherwise. 
		 */
		virtual ICommonPtr GetData(const StringA& name) = 0;    

	};

	/**
	 * Strong pointer for the IDataBus control interface. 
	 */
	typedef MinCOM::ComPtr< IDataBus > IDataBusPtr;
	typedef const IDataBusPtr& IDataBusRef;

	/**
	 * The IDataBus unique identifier. 
	 */
	// {b11eaf8f-0ca3-4e62-b223-7933a5a62ed1} 
	DEFINE_GUID(IID_IDataBus, 
	0xb11eaf8f, 0x0ca3, 0x4e62, 0xb2, 0x23, 0x79, 0x33, 0xa5, 0xa6, 0x2e, 0xd1);

	/**
	 * Identifier associated with default IDataBus implementation localed directly in scripting engine.
	 */
	// {5090e8b6-a8b2-4f83-a569-8f70c4c9fe71} 
	DEFINE_GUID(CLSID_DataBus, 
	0x5090e8b6, 0xa8b2, 0x4f83, 0xa5, 0x69, 0x8f, 0x70, 0xc4, 0xc9, 0xfe, 0x71);

} // namespace ScriptingKit

#endif // !IDATABUS_H__SCRIPTINGKIT__INCLUDED_
