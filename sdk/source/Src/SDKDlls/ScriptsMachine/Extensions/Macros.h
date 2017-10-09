#ifndef MACROS_H__EXTENSIONS_SCRIPTSMACHINE__INCLUDED_
#define MACROS_H__EXTENSIONS_SCRIPTSMACHINE__INCLUDED_

#define DECLARE_EXTENSION(name)										\
	class name														\
		: public ScriptingKit::ExtensionImpl						\
	{																\
	public:															\
		virtual result EnhanceState(								\
			ScriptingKit::IScriptRef /* script */,					\
			lua_State* /* L */,										\
			ScriptingKit::IDataBusRef /* dataBus */);				\
	}

#endif // !MACROS_H__EXTENSIONS_SCRIPTSMACHINE__INCLUDED_
