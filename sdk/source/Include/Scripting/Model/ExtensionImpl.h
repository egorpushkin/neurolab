#ifndef EXTENSIONIMPL_H__SCRIPTINGKIT__INCLUDED_
#define EXTENSIONIMPL_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	* ExtensionImpl class. Partial IExtension implementation.
	*
	* @version 1.0.1
	*/
	class ExtensionImpl 
		: public MinCOM::CommonImpl< IExtension > 
	{
	public:

		ExtensionImpl()
		{
		}

		virtual ~ExtensionImpl() 
		{
		}

		// IExtension implementations section		

		// Not overridden in this scope
		// virtual result EnhanceState(IScriptRef script, lua_State* L, IDataBusRef dataBus) = 0;

		// ICommon implementations section	
		virtual result QueryInterface(REFIID iid, void** ppObject)
		{
			QUERY_COMMON(iid, ppObject, IExtension);

			CHECK_FOR_IID(iid, ppObject, IExtension, IID_IExtension);

			*ppObject = NULL;
			return E_NOINTERFACE;
		}

	private:

		ExtensionImpl(const ExtensionImpl&); 
		ExtensionImpl& operator =(const ExtensionImpl&);

	};

} // namespace ScriptingKit

#endif // !EXTENSIONIMPL_H__SCRIPTINGKIT__INCLUDED_
