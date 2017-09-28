#ifndef IEXTENSIONSMNG_H__SCRIPTINGKIT__INCLUDED_
#define IEXTENSIONSMNG_H__SCRIPTINGKIT__INCLUDED_

namespace ScriptingKit
{

	/**
	 * IExtensionsMng interface. 
	 *
	 * @version 1.0.1
	 */
	interface IExtensionsMng : public MinCOM::ICommon
	{
		
		virtual result Register(const IExtensionPtr& extension) = 0;
	    
	};

	typedef MinCOM::ComPtr< IExtensionsMng > IExtensionsMngPtr;

	// {c3768c11-a652-4b00-83b6-3b94f2022f7d} 
	DEFINE_GUID(IID_IExtensionsMng, 
	0xc3768c11, 0xa652, 0x4b00, 0x83, 0xb6, 0x3b, 0x94, 0xf2, 0x02, 0x2f, 0x7d);

} // namespace ScriptingKit

#endif // !IEXTENSIONSMNG_H__SCRIPTINGKIT__INCLUDED_
