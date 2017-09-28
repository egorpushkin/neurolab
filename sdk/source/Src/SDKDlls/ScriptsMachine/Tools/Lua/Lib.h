#ifndef LIB_H__LUA__SCRIPTSMACHINE__INCLUDED_
#define LIB_H__LUA__SCRIPTSMACHINE__INCLUDED_

namespace ScriptsMachine
{

	typedef std::pair<StringA, float> NumericPair;
	typedef std::pair<StringA, StringA> StringPair;

	typedef std::vector< NumericPair > NumericVector;
	typedef std::vector< StringPair > StringVector;

	typedef const NumericVector& NumericVectorRef;
	typedef const StringVector& StringVectorRef;

	bool IsLibRegistered(lua_State* L, const StringA& name);

	void RegisterLibNumerics(lua_State* L, const StringA& libName, NumericVectorRef muns);
	void RegisterLibStrings(lua_State* L, const StringA& libName, StringVectorRef strings);

} // namespace ScriptsMachine

#endif // !LIB_H__LUA__SCRIPTSMACHINE__INCLUDED_
